void modo_radio() {
      
    float f = radio.getFrequency();
    
      
    char buf[10];
    dtostrf(f, 6, 1, buf);

     h_d = (buf[1] != '1') ? -1 : buf[1];
     h_u = buf[2];
     m_d = buf[3];
     m_u = buf[5]; 
      
     atualiza();
     

    if( digitalRead(set) == HIGH ){
  
      if (B_minuto.isPressed()) {
         if(f_atual < f_size){
              f_atual = f_atual+1;
          }else{
             f_atual = 0;
            }
      }
  
      if (B_hora.isPressed()) {
           if(f_atual > 0){
              f_atual = f_atual-1;
            }else{
             f_atual = f_size;
            }
           
       }
      radio.setFrequency(freqs[f_atual]);
      
  } else {
    
        if (B_minuto.isPressed() && modo == 1) {
            freqs[f_atual] = freqs[f_atual] + 0.2;
            if(freqs[f_atual] >107.90){freqs[f_atual] = 76.10;}   
        }
  
        if (B_hora.isPressed() && modo == 1) {
            freqs[f_atual] = freqs[f_atual]- 0.2;
            if(freqs[f_atual] < 76.10){freqs[f_atual] = 107.90;}    
        }

        radio.setFrequency(freqs[f_atual]);
      }

   if (B_minuto.isPressed() || B_hora.isPressed()) {
        Serial.print(f);
        Serial.print("--sinal:");
        Serial.print(radio.getSignalLevel());
        Serial.print("--Stereo:");
        Serial.println(radio.isStereo());
    }
}
