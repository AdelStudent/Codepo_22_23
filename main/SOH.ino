double nomCapacity = 200000;  // Capacité nominale de la batterie en mAh
double PeukertCst = 1.25;    // Constante de Peukert -> calcul de la capacité

double determineSOH(double SOC, float calculateThermistance_value) {
  double capacity;
  double SOH;

  double adjustedCapacity = pow(nomCapacity * pow(SOC, PeukertCst), (1 / PeukertCst));
  capacity = adjustedCapacity * (1 - 0.005 * (calculateThermistance_value - 25));
  SOH = (capacity / nomCapacity); // * 100.0;

  return SOH;
}

double SOHdetermination(float calculateThermistance_value) {
  double capacity[nbBatteries];

  double adjustedCapacity_12 = pow(nomCapacity * pow(SOC_12, PeukertCst), (1 / PeukertCst));
  double adjustedCapacity_24 = pow(nomCapacity * pow(SOC_24, PeukertCst), (1 / PeukertCst));
  double adjustedCapacity_36 = pow(nomCapacity * pow(SOC_36, PeukertCst), (1 / PeukertCst));
  double adjustedCapacity_48 = pow(nomCapacity * pow(SOC_48, PeukertCst), (1 / PeukertCst));

  capacity[0] = adjustedCapacity_12 * (1 - 0.005 * (calculateThermistance_value - 25));
  capacity[1] = adjustedCapacity_24 * (1 - 0.005 * (calculateThermistance_value - 25));
  capacity[2] = adjustedCapacity_36 * (1 - 0.005 * (calculateThermistance_value - 25));
  capacity[3] = adjustedCapacity_48 * (1 - 0.005 * (calculateThermistance_value - 25));

  double SOH[nbBatteries];
  SOH[0] = (capacity[0] / nomCapacity); // * 100.0;
  SOH[1] = (capacity[1] / nomCapacity); // * 100.0;
  SOH[2] = (capacity[2] / nomCapacity); // * 100.0;
  SOH[3] = (capacity[3] / nomCapacity); // * 100.0;

  double SOH_pack;
  double totalCapacity = 0.0;
  totalCapacity = capacity[0] + capacity[1] + capacity[2] + capacity[3];
  SOH_pack = (totalCapacity / (nbBatteries * nomCapacity)); //* 100.0;

/*
  // Affichage du SOH de chaque batterie
  for (int i = 0; i < nbBatteries; i++) {
    Serial.print("Battery ");
    Serial.print(i + 1);
    Serial.print(" State of Health (SOH): ");
    Serial.print(SOH[i]);
    Serial.println("%");
  }

  // Affichage du SOH du pack
  Serial.print("State of Health (SOH) of the pack: ");
  Serial.print(SOH_pack);
  Serial.println("%");

  // Ajoutez ici le reste du code pour d'autres actions ou boucles
*/
  return SOH_pack; 
}
