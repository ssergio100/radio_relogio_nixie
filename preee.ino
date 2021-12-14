

void preee(int m, int t) {
  
  for(int v = 0; v <= m; v++){
    
    digitalWrite(buzzer, HIGH);
    delay(t);
    digitalWrite(buzzer, LOW);
    delay(t);
  }

}

void beep() {
  digitalWrite(buzzer, HIGH);
  delay(25);
  digitalWrite(buzzer, LOW);
}
