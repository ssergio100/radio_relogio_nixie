void alarme() {
  
  if (EEPROM.read(address_alarme_active) > 0) { //0,1 ou 2
     //Serial.println("ATIVADO");
     rtc.getDateTime(&hour, &min, &sec, &mday, &mon, &year, &wday);

    if ( wday > 4 && EEPROM.read(address_alarme_weekend) == 0 ) {
      //ZZzzzZzzzzZZzZzZzzZ
    } else {

      
      if (
          !in_alarme 
          && hour == EEPROM.read(address_hora) 
          && min == EEPROM.read(address_minuto)
          && sec == 0
        ) {
          if ( EEPROM.read(address_alarme_active) == 1 ) {
              Serial.println(F("Alarme buzzer"));
              digitalWrite(buzzer, HIGH);
          } else {
              //se radio ja estiver ativado ultiliza o buzzer
              if( !radio_standby ){
                   digitalWrite(buzzer, HIGH);
                } else {
                     Serial.println(F("Alarme radio"));
                     radio.setStandby(0);
                     delay(5);
                     digitalWrite(vcc_amp, HIGH);
                }
              
          }
          
         in_alarme = 1;
      }
    }
  }

}
