/*
Pour la personne qui va lire ce code:
    Le rôle de ce paquet de fonction est UNIQUEMENT d'être un four tout à functions pratiques. La plus part des ces functions ne seront
    plus utilisées dans le proto final
*/

void print_variable_float(char* variable_name, float value){
  char sentence[100] = "Voici la valeur de ";
  strcat(sentence, variable_name);
  strcat(sentence, " : ");
  char buffer[64];
  snprintf(buffer, sizeof buffer, "%f", value);
  strcat(sentence, buffer);
  Serial.println(sentence);
}
void print_variable_int(char* variable_name, int value){
  char sentence[100] = "Voici la valeur de ";
  strcat(sentence, variable_name);
  strcat(sentence, " : ");
  char buffer[64];
  snprintf(buffer, sizeof buffer, "%i", value);
  strcat(sentence, buffer);
  Serial.println(sentence);
}
