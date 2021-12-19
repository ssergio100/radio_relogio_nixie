void alarme() {

  
  hora_alarme    = hora_alarme == -1    ? EEPROM.read(address_hora)    : hora_alarme;
  minuto_alarme  = minuto_alarme == -1  ? EEPROM.read(address_minuto)  : minuto_alarme;
  

 if(!analogRead(set)){
  
      //      ----------------------HORA-----------------------------
    
      if (B_hora.isPressed()) {
         in_adjust = 1;
          hora_alarme++;
          if(hora_alarme > 23 ){hora_alarme = 0;}
      }
      //    ---------------------MINUTO---------------------------------
    
      if (B_minuto.isPressed()) {
         in_adjust = 1;
          minuto_alarme++;
          if(minuto_alarme > 59 ){minuto_alarme = 0;};
      }

 }


 if(in_adjust && analogRead(set)){
          EEPROM.put(address_hora, hora_alarme);
          EEPROM.put(address_minuto, minuto_alarme);
          Serial.println("Gravando");
          Serial.print("hora_alarme:");
          Serial.println(hora_alarme);
          Serial.print("minuto_alarme:");
          Serial.println(minuto_alarme);
          Serial.print("alarme_active:");
          Serial.println(alarme_active);
          Serial.print("alarme_weekend:");
          Serial.println(alarme_weekend);

  
          beep();
          in_adjust = 0;
      }
 
  h_d = (hora_alarme % 100) / 10;
  h_u = hora_alarme % 10;
  m_d = (minuto_alarme % 100) / 10;
  m_u = minuto_alarme % 10;


  atualiza();
}
