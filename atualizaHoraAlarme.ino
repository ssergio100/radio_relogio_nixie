 void atualizaHoraAlarme(){
 
   if ( hora_alarme != EEPROM.read(address_hora) && modo == 0) {
      EEPROM.write(address_hora, hora_alarme);
      Serial.print(F("Ajustando hora de alarme:"));
      Serial.println(hora_alarme);
    }
  
    if ( minuto_alarme !=  EEPROM.read(address_minuto) && modo == 0 ) {
      EEPROM.write(address_minuto, minuto_alarme);
      Serial.print(F("Ajustando minuto de alarme:"));
      Serial.println(minuto_alarme);
      
   }

 }
