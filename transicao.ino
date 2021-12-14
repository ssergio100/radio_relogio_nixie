void transicao() {

  modo = 0; //Volta , no maximo, em uma hora para para o 'modo relogio' se ficou esquecido em algum modo diferente.


  for (int x = 58; x >= 0; x--) {

    m_d = (x % 100) / 10;
    m_u = x % 10;

    digitalWrite(set_m_d, HIGH);
    escreve_byte(m_d);
    delay(4);
    digitalWrite(set_m_d, LOW);

    digitalWrite(set_m_u, HIGH);
    escreve_byte(m_u) ;
    delay(4);
    digitalWrite(set_m_u, LOW);

    digitalWrite(set_h_d, HIGH);
    escreve_byte(h_d) ;
    digitalWrite(set_h_d, LOW);

    digitalWrite(set_h_u, HIGH);
    escreve_byte(h_u) ;
    digitalWrite(set_h_u, LOW);

  }
   beep();
}
