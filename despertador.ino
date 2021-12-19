void despertador() {
  
  hora_alarme    = address_hora == -1    ? EEPROM.read(address_hora)           : hora_alarme;
  minuto_alarme  = minuto_alarme == -1  ? EEPROM.read(address_minuto)         : minuto_alarme;
  alarme_active   = alarme_active == -1   ? EEPROM.read(address_alarme_active)  : alarme_active;
  alarme_weekend  = alarme_weekend == -1  ? EEPROM.read(address_alarme_weekend) : alarme_weekend;


//  Serial.print("hora_alarme:");
//  Serial.println(hora_alarme);
//  Serial.print("minuto_alarme:");
//  Serial.println(minuto_alarme);
//  Serial.print("alarme_active:");
//  Serial.println(alarme_active);
//  Serial.print("alarme_weekend:");
//  Serial.println(alarme_weekend);
   
  if (alarme_active > 0) { //0,1 ou 2
     //Serial.println("ATIVADO");
    

    if ( wday > 4 && alarme_weekend == 0 ) {
      //ZZzzzZzzzzZZzZzZzzZ
    } else {

      if (
          !in_alarme 
          && hour == hora_alarme 
          && min == minuto_alarme
          && sec == 0
        ) {
          if ( alarme_active == 1 ) {
              Serial.println(F("Alarme buzzer"));
              digitalWrite(buzzer, HIGH);
          } else {
              //se radio ja estiver ativado ultiliza o buzzer
              if( !radio_standby ){
                   digitalWrite(buzzer, HIGH);
                } else {
                     Serial.println(F("Alarme radio"));
                     rfm.setStandby(0);
                     delay(5);
                     digitalWrite(vcc_amp, HIGH);
                }
          }
          
         in_alarme = 1;
      }
    }
  }
}
