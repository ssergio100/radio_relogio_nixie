void modo_relogio() {


  if( digitalRead(set) == LOW ){

    //   ----------------------HORA-----------------------------
    
    if (B_hora.isPressed()) {
        int hora = hour >= 23 ? 0 : ++hour;
        rtc.setTime(hora, min, sec);
    }
    //    ---------------------MINUTO---------------------------------
    if (B_minuto.isPressed()) {
        int minuto = min >= 59 ? 0 : ++min;
        rtc.setTime(hour, minuto, sec);
    }
 }
 
  h_d = (hour % 100) / 10;
  h_u = hour % 10;
  m_d = (min % 100) / 10;
  m_u = min % 10;

  atualiza();
}
