#include <extendedKalmanFilter.h>
//EN LIEN MAIS A METTRE DANS LE BON FICHIER 
//File file;
float input_pack_bat_current;
float output_pack_bat_current;
double I[3];
double V[4];

// A mettre dans le boucle setup
//creationParametreKalman()

// PARAMETRES POUR LE FILTRE DE KALMAN 
// *********************************************
const int nbBatteries = 4; //4 Batteries par ligne dont on prend les mesures 
double DeltaT; //Temps -> que l'on retrouve notament dans la matrice de transition (exp)
double Qn_rated; // Capacité nominale des batteries 
double voltage_rated; //Tension nominale 
double current_rated; //Courant nominale 

double X[2*nbBatteries]; //X = [SOC, V1] -> Pour chaque batteries 
double Z[3*nbBatteries]; //Z = [R0, R1, tau_1] où tau_1 = C1*R1
double Px[4*nbBatteries]; //matrice de covariance de l'erreur x-> SOC
double Pz[9*nbBatteries]; //matrice de covariance de l'erreur z-> Model de la batterie
double Qx[4*nbBatteries]; // matrice de covariance du process noise 
double Qz[9*nbBatteries]; // matrice de covariance du process noise 
  // La taille des P et Q est observable dans le code de l'année passée 

// double SOCOCV_12 [5] -> Même si prend pas toutes les batteries 
//il faut les mêmes dimensions de vecteur pour faire les opérations  
double SOCOCV_12[5]; //polynome de la courbe pour la batterie à 12V 
double dSOCOCV_12[4]; // dérivées de la courbe pour la batterie à 12V 
double SOCOCV_24[5];
double dSOCOCV_24[4];
double SOCOCV_36[5]; 
double dSOCOCV_36[4];
double SOCOCV_48[5]; // Dans le code de l'année passée -> Tension du pack 
double dSOCOCV_48[4]; 

// Facteur pour prendre la distribution Gaussienne je pense 
double alpha_x[nbBatteries]; // facteur 
double betha_x[nbBatteries]; //facteur 
double alpha_z[nbBatteries];
double betha_z[nbBatteries]; 
double rho_x = 1; //à vérifier mais je pense que c'est un bon choix 
double rho_z = 1; 

// Pour faire un state observer
double error = 0.0; //Valeur initiale de l'erreur entre la tension du model et la réelle 
double kalmanTime = 0.0; // -> à voir 

// Autre
  // A mettre sous forme de vecteur dans nos données
double SOC_coulomb[nbBatteries] = {1.0, 1.0, 1.0, 1.0}; 
double Capacities[nbBatteries] = {200*3600, 200*3600, 200*3600, 200*3600}; //Asec
  // pour l'itération 
//unsigned long iteration_period = 0;
//unsigned long previous_iteration = 0; 
char input[3000];

// Final SOC
double SOC_12;
double SOC_24;
double SOC_36; 
double SOC_48;

// INITIALISATION DES PARAMETRES POUR LES FILTRES DE KALMAN 
  //Sauvegarde dans la carte SD 

// Besoin d'une condition pour initialiser 
void initialisationKalman(String filename, double *X, double *Z, double SOCOCV[5],
                          double dSOCOCV[4], double *Px, double *Pz, double *Qx,
                          double *Qz, double *alpha_x, double *betha_x, double *alpha_z,
                          double *betha_z, double *Qn_rated, double *voltage_rated, double *current_rated){
  if(SD.begin(CS_PIN)==true){ //-> carte SD au lieu de JSON
    // Création d'un fichier pour enregistrer les paramètres de Kalman  
    File fichierKalman = SD.open(filename, FILE_READ);
    // Vecteur avec les données des paramètres 
    int maxLines = 31;
    double para[maxLines]; 
    int ligneCourante = 0;
    // Lire les données de la carte SD -> première ligne = V1, deuxième ligne = SOCOCV[0], ...
    while (fichierKalman.available() && ligneCourante < maxLines) {
      String valeurlue = file.readStringUntil('\n'); //Lit toute la ligne 
      para[ligneCourante] = valeurlue.toDouble(); //Enregistre dans le fichier les paramètres 
      ligneCourante++;
    }
    fichierKalman.close();

    //int nbPara = 30;
    //double Para_list[] = {X[0],"bat100.txt","bat020.txt","bat401.txt","bat500.txt"};
    //for (int i = 0; i < nbPara; i++){
    //  para[i] = Para_list[i]; 
    //}
      para[0] = X[0]; //=SOC_init
      //SOC_init = X[0];
      SOC_init = determine_SOC(input_pack_bat_current, output_pack_bat_current); 
      para[1] = X[1]; //V1
      para[2]= Z[0]; //R0
      para[3] = Z[1]; //R1
      para[4] = Z[2]; //tau_1
      para[5] = alpha_x[0]; 
      para[6] = betha_x[0];
      para[7] = alpha_z[0]; 
      para[8] = betha_z[0]; 
      para[9] = *Qn_rated;
      para[10] = *voltage_rated;
      para[11] = *current_rated; 
      para[12] = SOCOCV[0]; 
      para[13] = SOCOCV[1]; 
      para[14] = SOCOCV[2]; 
      para[15] = SOCOCV[3]; 
      para[16] = SOCOCV[4]; 
      para[17] = dSOCOCV[0]; 
      para[18] = dSOCOCV[1]; 
      para[19] = dSOCOCV[2]; 
      para[20] = dSOCOCV[3]; 
      para[21] = Px[0]; //Sera une matrice avec des 0 
      para[22] = Px[3]; Px[1] = 0; Px[2] =0;
      para[23] = Qx[0]; //Sera une matrice avec des 0 
      para[24] = Qx[3]; Qx[1] = 0; Qx[2] =0;
      para[25] = Pz[0]; Pz[1] = 0; Pz[2] = 0; Pz[3] = 0; 
      para[26] = Pz[4]; Pz[5] = 0; Pz[6] = 0; Pz[7] = 0; 
      para[27] = Pz[8];
      para[28] = Qz[0]; Qz[1] = 0; Qz[2] = 0; Qz[3] = 0; 
      para[29] = Qz[4]; Qz[5] = 0; Qz[6] = 0; Qz[7] = 0; 
      para[30] = Qz[8];
  }
  else{
    Serial.print("Pas de carte SD, paramètres par défaut utilisé (de l'année passée)");
    // Lecture du fichier mémoire avec les paramètres de Kalman 
    //for (int i = 0; i < nbBatteries; i++){
    //  if (i % 2 ==0){ // Pour les valeurs paires du vecteur d'état -> Met les SOCs des différentes batteries 
    //    double SOCd[i] = X[i]; 
    //  }
    //  else{ // Pour les valeurs impaires du vecteur d'état -> Met les V1
    //    double V1d[i] = X[i];
    //  }
    //}

    // VALEUR RECOLTES SUR LA CARTE SD DE L'ANNEE PASSEE 
      // Pour donner un point de départ au filtre si il y a un problème  
    X[0] = 9.95e-01; X[1] = 0.0;
    Z[0] = 8.92e-03; Z[1] = 2.72e-03; Z[2] = Z[1]*1.43e03;
    alpha_x[0] = 1.11e04; betha_x[0] = 5.60e03; alpha_z[0] = 1.11e04; betha_z[0] = 5.60e03;  
    *Qn_rated = 1.44e06; *voltage_rated = 1.20e01; *current_rated = 1.30e00;
    SOCOCV[0] = -8.05e00; SOCOCV[1] = 1.64e01; SOCOCV[2] = -1.03e01; SOCOCV[3] = 3.38e00; SOCOCV[4] = 1.15e01;
    dSOCOCV[0] = -3.22e01; dSOCOCV[1] = 4.93e01; dSOCOCV[2] = -2.06e01; dSOCOCV[3] = 3.38e00;
    Px[0] = 2.19e-02; Px[3] = 8.01e-06; Px[1] = 0; Px[2] = 0;
    Qx[0] = 1.00e-06; Qx[3] = 1.00e-06; Qx[1] = 0; Qx[2] = 0; 
    Pz[0] = 2.21e-06; Pz[4] = 2.21e-06; Pz[8] = 2.21e-06; Pz[1] = 0; Pz[2] = 0; Pz[3] = 0; Pz[5] = 0; Pz[6] = 0; Pz[7] = 0;  
    Qz[0] = 1.00e-10; Qz[4] = 1.00e-10; Qz[8] = 1.00e-10; Qz[1] = 0; Qz[2] = 0; Qz[3] = 0; Qz[5] = 0; Qz[6] = 0; Qz[7] = 0;
  }
}

// VALEUR INITIALE DU SOC (COULOMB COUNTING) ET LINEARISATION DU MODELE DE LA BATTERIE 
void CoulombCounting(){
  // De l'année passée 
  for (int i = 0; i < nbBatteries; i++){
    SOC_coulomb[i] -= (I[0] * DeltaT) /Capacities[i]; //- avant le =  
  } 
  //Notre code donne le SOC_init 
  //determine_SOC(input_pack_bat_current, output_pack_bat_current);
  
}

// ALGORITHME DU FILTRE DE KALMAN (PREDICTION ET UPDATE)************************
void FiltreKALMAN(){ 
  DeltaT = (double)(millis()*0.001 - kalmanTime); //différence entre le temps actuel et le précédent 
  kalmanTime = (double)(millis()*0.001); //Stock le temps d'itération précédente

  CoulombCounting();
  
  for(int i = 0; i < nbBatteries; i++) { // Kalmann filter applied on each 
    if(i == 0) {
      extendedKalmanFilter(I[0]/5, I[0]/5, X + 2*i, Z + 3*i, SOCOCV_12, dSOCOCV_12, V[i], Px + 4*i, Pz + 9*i, Qx + 4*i, Qz + 9*i, &betha_x[i], &betha_z[i], &alpha_x[i], &alpha_z[i], rho_x, rho_z, DeltaT, Capacities[i]);
    } 
    else if(i == 1) {
      extendedKalmanFilter(I[0]/5, I[0]/5, X + 2*i, Z + 3*i, SOCOCV_24, dSOCOCV_24, V[i], Px + 4*i, Pz + 9*i, Qx + 4*i, Qz + 9*i, &betha_x[i], &betha_z[i], &alpha_x[i], &alpha_z[i], rho_x, rho_z, DeltaT, Capacities[i]);
    } 
    else if(i == 2) {
      extendedKalmanFilter(I[0]/5, I[0]/5, X + 2*i, Z + 3*i, SOCOCV_36, dSOCOCV_36, V[i], Px + 4*i, Pz + 9*i, Qx + 4*i, Qz + 9*i, &betha_x[i], &betha_z[i], &alpha_x[i], &alpha_z[i], rho_x, rho_z, DeltaT, Capacities[i]);
    } 
    else if(i == 3) {
      extendedKalmanFilter(I[0]/5, I[0]/5, X + 2*i, Z + 3*i, SOCOCV_48, dSOCOCV_48, V[i], Px + 4*i, Pz + 9*i, Qx + 4*i, Qz + 9*i, &betha_x[i], &betha_z[i], &alpha_x[i], &alpha_z[i], rho_x, rho_z, DeltaT, Capacities[i]);
      double pack = extendedKalmanFilter(I[0]/5, I[0]/5, X + 2*i, Z + 3*i, SOCOCV_48, dSOCOCV_48, V[i], Px + 4*i, Pz + 9*i, Qx + 4*i, Qz + 9*i, &betha_x[i], &betha_z[i], &alpha_x[i], &alpha_z[i], rho_x, rho_z, DeltaT, Capacities[i]); 
    }
  }
  
  // Doit mettre le SOC filtré quelque part -> l'année passée c'était direct sur l'écran LCD 
  SOC_12 = X[0];
  SOC_24 = X[2];
  SOC_36 = X[4];
  SOC_48 = X[8];

  // enregistrement dans des dossiers de la carte SD avec les heures de l'ESP32
  //measure_and_save("SOC12", date, SOC_12);
  //measure_and_save("SOC24", date, SOC_24);
  //measure_and_save("SOC36", date, SOC_36);
  //measure_and_save("SOC48", date, SOC_48);


  // Doit sauver les paramètres recalculées dans le carte SD 
  if (millis() - lastUpdateFilter >= 60 * 60 * 1000){
    sauvegardeParametresKalman("KALMAN.txt", X, Z, SOCOCV_12, dSOCOCV_12, Px, Pz, Qx, Qz, alpha_x, betha_x, alpha_z, betha_z, &Qn_rated, &voltage_rated, &current_rated);
    lastUpdateFilter = millis();
  }
}
//******************************************************************************

void creationParametreKalman(){
  // Opération initiale pour la batterie à 12V
  initialisationKalman("KALMAN.txt", X, Z, SOCOCV_12, dSOCOCV_12, Px, Pz, Qx, Qz, alpha_x, betha_x, alpha_z, betha_z, &Qn_rated, &voltage_rated, &current_rated);
  duplicate(X, Z, Px, Pz, Qx, Qz, alpha_x, betha_x, alpha_z, betha_z, nbBatteries);
    
  // Pour avoir la courbe SOCOCV pour toutes les tensions
  dubble(SOCOCV_24, SOCOCV_12, 5, 2);  
  dubble(dSOCOCV_24, dSOCOCV_12, 4, 2);
  dubble(SOCOCV_36, SOCOCV_12, 5, 3);  
  dubble(dSOCOCV_36, dSOCOCV_12, 4, 3);
  dubble(SOCOCV_48, SOCOCV_12, 5, 4);
  dubble(dSOCOCV_48, dSOCOCV_12, 4, 4);
}

// duplique les valeurs des tableaux d'entrée pour les autres batteries 
//Fait en sorte que les matrices ont la taille suffisante pour prendre en compte toute les batteries 
void duplicate(double *X, double *Z, double *Px, double *Pz, double *Qx, 
              double *Qz, double *alpha_x, double *betha_x, double *alpha_z, double *betha_z, int nbBatteries) {
                
            for(int i = 1; i < nbBatteries; i++) { //Pour la seconde batterie 
              for (int j = 0; j < 4; j++) {
                Qx[i*4 + j] = Qx[j];
                Px[i*4 + j] = Px[j];
              }
              for (int j = 0; j < 3; j++) {
                Z[i*3 + j] = Z[j]; 
              }
              for (int j = 0; j < 2; j++) {
                X[i*2 + j] = X[j];
              }
              for (int j = 0; j < 9; j++) { 
                Pz[i*9 + j] = Pz[j];
                Qz[i*9 + j] = Qz[j];
              }
              alpha_x[i] = alpha_x[0]; //Qu'importe la batterie, ces facteurs restent les mêmes 
              betha_x[i] = betha_x[0];
              alpha_z[i] = alpha_z[0];
              betha_z[i] = betha_z[0];
            }
}


// double la valeur de 12V pour obtenir les autres valeurs de tensions (36v = 3x12V)
void dubble(double *list1, double *list2, int l, double factor) {
  for(int i = 0; i < l; i++) {
    list1[i] = list2[i]*factor;
  }
}

void sauvegardeParametresKalman(String filename, double *X, double *Z, double SOCOCV[5],
                                double dSOCOCV[4], double *Px, double *Pz, double *Qx,
                                double *Qz, double *alpha_x, double *betha_x, double *alpha_z,
                                double *betha_z, double *Qn_rated, double *voltage_rated, double *current_rated) {
  if (SD.begin(CS_PIN) == true) {
    // Ouvrir le fichier pour écrire les paramètres de Kalman
    File fichierKalman = SD.open(filename, FILE_WRITE);
    if (fichierKalman) {
      // Écrire les paramètres dans le fichier
      fichierKalman.println(String(X[0])); // SOC_init
      fichierKalman.println(String(X[1])); // V1
      fichierKalman.println(String(Z[0])); // R0
      fichierKalman.println(String(Z[1])); // R1
      fichierKalman.println(String(Z[2])); // tau_1
      fichierKalman.println(String(alpha_x[0]));
      fichierKalman.println(String(betha_x[0]));
      fichierKalman.println(String(alpha_z[0]));
      fichierKalman.println(String(betha_z[0]));
      fichierKalman.println(String(*Qn_rated));
      fichierKalman.println(String(*voltage_rated));
      fichierKalman.println(String(*current_rated));
      fichierKalman.println(String(SOCOCV[0]));
      fichierKalman.println(String(SOCOCV[1]));
      fichierKalman.println(String(SOCOCV[2]));
      fichierKalman.println(String(SOCOCV[3]));
      fichierKalman.println(String(SOCOCV[4]));
      fichierKalman.println(String(dSOCOCV[0]));
      fichierKalman.println(String(dSOCOCV[1]));
      fichierKalman.println(String(dSOCOCV[2]));
      fichierKalman.println(String(dSOCOCV[3]));
      fichierKalman.println(String(Px[0]));
      fichierKalman.println(String(Px[3]));
      fichierKalman.println(String(Qx[0]));
      fichierKalman.println(String(Qx[3]));
      fichierKalman.println(String(Pz[0]));
      fichierKalman.println(String(Pz[4]));
      fichierKalman.println(String(Pz[8]));
      fichierKalman.println(String(Qz[0]));
      fichierKalman.println(String(Qz[4]));
      fichierKalman.println(String(Qz[8]));

      // Fermer le fichier
      fichierKalman.close();
    } else {
      Serial.println("Erreur lors de l'ouverture du fichier.");
    }
  } else {
    Serial.println("Pas de carte SD, les paramètres ne peuvent pas être sauvegardés.");
  }
}

void update_kalman_vector(float bat_volt_1,float bat_volt_2,float bat_volt_3,float bat_volt_4,double output_pack_bat_current,double pv_generated_current,double grid_current){
    // Création des vecteurs pour avoir le Filtre de Kalman 
    V[0] = bat_volt_1;
    V[1] = bat_volt_2; 
    V[2] = bat_volt_3;
    V[3] = bat_volt_4;

    I[0] = output_pack_bat_current; //I[0] = celui en "sortie" du pack sur celui de l'année passée
    I[1] = pv_generated_current; 
    I[2] = grid_current;     
}
