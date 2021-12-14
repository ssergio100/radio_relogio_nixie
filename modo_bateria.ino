 void modo_bateria() {

    int sensorValue = analogRead(A3);
    float voltage = sensorValue * (5.0 / 1023.0);
    
    //Serial.println(voltage);
    int int_voltage = voltage * 100;

    h_d = -1;
    h_u = ((int_voltage % 1000) / 10) / 10;
    m_d = (int_voltage % 100) / 10;
    m_u = int_voltage % 10;
    
    atualiza();
  }
