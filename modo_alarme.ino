void modo_alarme() {


if(!in_adjust){
  hora_alarme = EEPROM.read(address_hora);
  minuto_alarme = EEPROM.read(address_minuto);
}

in_adjust = 1;

 if(digitalRead(set) == LOW){
  
      //      ----------------------HORA-----------------------------
    
      if (B_hora.isPressed()) {
            hora_alarme++;
            if(hora_alarme > 23 ){hora_alarme =0;}
              h_d = (hora_alarme % 100) / 10;
              h_u = hora_alarme % 10;
              m_d = (minuto_alarme % 100) / 10;
              m_u = minuto_alarme % 10;
            atualiza();

      }
      //    ---------------------MINUTO---------------------------------
    
      if (B_minuto.isPressed()) {
           minuto_alarme++;
           if(minuto_alarme > 59 ){minuto_alarme =0;}
            h_d = (hora_alarme % 100) / 10;
            h_u = hora_alarme % 10;
            m_d = (minuto_alarme % 100) / 10;
            m_u = minuto_alarme % 10;
           atualiza();
      }

 }
 
  h_d = (hora_alarme % 100) / 10;
  h_u = hora_alarme % 10;
  m_d = (minuto_alarme % 100) / 10;
  m_u = minuto_alarme % 10;


  atualiza();
}
