void calendario() {


  rtc.getDateTime(&hour, &min, &sec, &mday, &mon, &year, &wday);

  //      ----------------------HORA-----------------------------


 if(!analogRead(set)){
     in_adjust = 1;
     
      if (B_hora.isPressed()) {
      
          int dia_mes = mday >= 31 ? 1 : ++mday;
          rtc.setDateTime  (hour, min, sec, dia_mes, 11, 2021, wday) ;
      }
        //    ---------------------MINUTO---------------------------------
        if (B_minuto.isPressed()) {
 
            int semana =  ++wday  ;
            rtc.setDateTime  (hour, min, sec, mday, 11, 2021, semana) ;
        }
 }


  //Mudo para o formato que faz mais sentido no Brasil
  switch(wday){
  case 0:
   wday = 1;//domingo
   break;
  case 1:
   wday = 2;//segunda
   break;
    case 2:
   wday = 3;//terça
   break;
    case 3:
   wday = 4;//quarta
   break;
    case 4:
   wday = 5;//quinta
   break;
    case 5:
   wday = 6;//sexta
   break;
    case 6:
   wday = 7;//sabado
   break;
  }
  
  h_d = (mday % 100) / 10;
  h_u = mday % 10;
  m_d = -1;
  m_u = wday % 10;

  atualiza();
}
