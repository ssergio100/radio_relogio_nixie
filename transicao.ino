void transicao() {

  modo = 0; //Volta , no maximo, em uma hora para para o 'modo relogio' se ficou esquecido em algum modo diferente.


  while (min > 0) {

    min--;
    m_d = (min % 100) / 10;
    m_u = min % 10;
    if(min == 1 ){hour++;}
    h_d = (hour % 100) / 10;
    h_u = hour % 10;
    
    digitalWrite(set_m_d, HIGH);
    escreve_byte(m_d);
    delay(5);
    digitalWrite(set_m_d, LOW);

    digitalWrite(set_m_u, HIGH);
    escreve_byte(m_u) ;
    delay(5);
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
