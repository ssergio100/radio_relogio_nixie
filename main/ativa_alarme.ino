void ativa_alarme() {

alarme_active   = alarme_active == -1   ? EEPROM.read(address_alarme_active)  : alarme_active;
alarme_weekend  = alarme_weekend == -1  ? EEPROM.read(address_alarme_weekend) : alarme_weekend;
  
  if ( analogRead(set) == LOW  ) {

    if (B_hora.isPressed()) {
      in_adjust = 1;
      alarme_weekend = !alarme_weekend;
     
    }

    if (B_minuto.isPressed()) {
      in_adjust = 1;
      alarme_active = (alarme_active == 2) ? 0 : alarme_active + 1;
    }

  }

  if(in_adjust && analogRead(set)){
      EEPROM.put(address_alarme_weekend, alarme_weekend);
      EEPROM.put(address_alarme_active, alarme_active);
      Serial.print("Desperta final de semana:");
      Serial.println(alarme_weekend);
      Serial.print("Tipo de alarme:");
      Serial.println(alarme_active);
      in_adjust = 0;
    }

  h_d = 0;
  h_u = alarme_weekend;
  m_d = -1;
  m_u = alarme_active;

  atualiza();

}
