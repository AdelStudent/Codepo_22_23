
void SD_init(int *init_flag_SD){ //Le pointeur initial est à 0 si il y a une carte -> update to 1
  // Le pointeur est appelé flag car il indique si l'initialisation s'est fait correctement
  //print_variable("CS_PIN",CS_PIN);
  if(SD.begin(CS_PIN)==true){
    //Serial.println("La carte SD a bien démarrée");
    *init_flag_SD = 1;
  }
  else{
    Serial.println("La carte SD n'a PAS ete trouve!");
  }
}


void delete_file(String filename){
  //Si le file existe, on le supprime (utile pour les tests)
  if(verify_file_existing(filename)){ //vérifie d'abord que le fichier existe sur la carte 
  // correpond à une boucle if True
    SD.remove(filename);
    Serial.println("Report a été nettoyé");
  }
}
bool verify_file_existing(String filename){ //filename to be checked 
  //Si le file existe, on le supprime (utile pour les tests)
  if(SD.exists(filename)){
    Serial.println("Le file existe!");
    return true; //retourne une réponde boolean 
  }else{
    Serial.println("Le file n'existe pas.");
    return false; //retourne une autre réponse de boolean 
  }
}