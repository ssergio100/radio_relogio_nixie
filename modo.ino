void mode() {

  if (B_set.isPressed()) {

    if (in_alarme == 1) {
  
        digitalWrite(buzzer, LOW);//PARO BUZZER
        rfm.setStandby(1);//PARO RÁDIO
        digitalWrite(vcc_amp, LOW);//Desligo amplificador de audio
        in_alarme = 0; //pronto para o proxima alarme...

    } else {

      modo = (modo < 4) ? ++modo : 0;
      Serial.println(modo);
      if (modo == 0) {
        rtc.setSquareWave(SquareWave1Hz);
        preee(3, 20);
      } else { 
        beep();
      }

      if(modo==1){ 
        Serial.println("Radio");
            rtc.setSquareWave(SquareWaveDisable);
            
        }
    }
  }

   return modo;
}
