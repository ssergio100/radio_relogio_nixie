void modo_ativa_alarme() {

  if ( digitalRead(set) == LOW  ) {

    if (B_hora.isPressed()) {
      EEPROM.write(address_alarme_weekend, !EEPROM.read(address_alarme_weekend));
    }

    if (B_minuto.isPressed()) {
      int atv = EEPROM.read(address_alarme_active);
      int atv2 = (atv == 2) ? 0 : atv + 1;
      Serial.println(atv);
      EEPROM.write(address_alarme_active, atv2);
    }

  }

  h_d = 0;
  h_u = EEPROM.read(address_alarme_weekend);
  m_d = -1;
  m_u = EEPROM.read(address_alarme_active);

  atualiza();

}
