void radio() {

   if( analogRead(set)){
   
      if (B_minuto.isPressed()) {
         in_adjust = 1;
         f_atual = (f_atual < f_size) ? f_atual+1 : 0;
      }
  
      if (B_hora.isPressed()) {
         in_adjust = 1;
        f_atual = (f_atual > 0) ? f_atual-1 : f_size;   
       }
       
      
  } else {
    
        if (B_minuto.isPressed() && modo == 1) {
           in_adjust = 1;
            freqs[f_atual] = freqs[f_atual] + 0.2;
            if(freqs[f_atual] > 107.90){freqs[f_atual] = 76.10;}   
        }
  
        if (B_hora.isPressed() && modo == 1) {
           in_adjust = 1;
            freqs[f_atual] = freqs[f_atual]- 0.2;
            if(freqs[f_atual] < 76.10){freqs[f_atual] = 107.90;}    
        }

        //rfm.setFrequency(freqs[f_atual]);
  }

 if(in_adjust){
    Serial.println(rfm.isStereo());
    rfm.setFrequency(freqs[f_atual]);
  
    float f = rfm.getFrequency();
    in_adjust = 0;
  }

    //Serial.println(rfm.getSignalLevel());
  
    char buf[10];
    
    dtostrf(freqs[f_atual], 6, 1, buf);

     h_d = (buf[1] != '1') ? -1 : buf[1];
     h_u = buf[2];
     m_d = buf[3];
     m_u = buf[5]; 
      
     atualiza();
     
}
