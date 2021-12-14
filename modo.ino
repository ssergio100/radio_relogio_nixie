void mode() {

  if (B_set.isPressed()) {
    Serial.print("Hora de alarme:");
    Serial.println(hora_alarme);
    Serial.print("Minutos de alarme:");
    Serial.println(minuto_alarme);

    Serial.print("in_alarme:");
    Serial.println(in_alarme);

    Serial.print("Hora memoria:");
    Serial.println(EEPROM.read(address_hora));
    Serial.print("Minutos memoria:");
    Serial.println(EEPROM.read(address_minuto));


    if (in_alarme == 1) {
  
        digitalWrite(buzzer, LOW);//PARO BUZZER
        radio.setStandby(1);//PARO RÁDIO
        digitalWrite(vcc_amp, LOW);//Desligo amplificador de audio
        in_alarme = 0; //pronto para o proxima alarme...

    } else {

      modo = (modo < 4) ? ++modo : 0;

      Serial.println(modo);
      if (modo == 0) 
        preee(3, 20);
      else 
        beep();
      
    }
  }
}
