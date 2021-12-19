/*

Botão Modo : Altera entre os modos : relógio, alarme, dia do mês e dia da semana, tipos de alarme, leitura da bateria interna e silencia alarmes se ele estiver ocorrendo;
Botão Radio: Liga e desliga o rádio;
Botão Up : Muda de estações de radio para baixo;
Botão Dow : Muda de estações de rádio para cima;
Botão Set: Habilita a alteração de horas e minutos da hora , horas e minutos de alarme, dia do mes, dia da semana e tipos de alarme.
Set + Modo Relogio + Up : Ajusta a hora;
Set + Modo Relógio + Dow : Ajusta os minutos;
Set + Modo Alarme + Up : Ajusta hora do alarme;
Set + Modo Alarme + Dow : Ajusta minutos do alarme;
Set + Modo Tipo de Alarme + Up: Ajusta hora de alarme;
Set + Modo Tipo de Alarme + Up: Ajusta hora de alarme;
Set + Modo Dia do Mês e Dia da Semana + Up: Ajusta o dia do mês;
Set + Modo Dia do Mês e Dia da Semana + Dow: Ajusta o dia da semana;
Set + Tipo de Alarme + Up : Habilita e desabilita alarme final de semana;
Set + Tipo de Alarme + Dow : 0 - Alarme desabilitado, 1 - Alarme co buzzer, 2 - Alarme com rádio;

Alarme:
Se o alarmes for  habilitado e setado para o modo 'rádio'(2) e ao despertar o rádio já estiver ligado então será acionado o buzzer;

Em alarme , para silenciar, pressionar o botão MODE.

Ajuste do alarme:
Após ajustar o alarme ele só será gravado quando o relógio sair modo 'ALARME';

Tempo de Alarme:
O tempo máximo de alarme é de uma hora;

Efeito de Transição de Horas:
Ao chegar em 59 minutos e 59 segundos o relógio reproduz um efeito decrescente dos minutos ( de 59 ate 00) mudando a hora ao finalizar o efeito;

Buzzer:
Ao transitar entre os modos é emitido um efeito longo (preeee) ao retornar ao modo RELóGIO;
É emitido um breve som (bip)ao transitar entre os modos e nas mudanças de horas;

*/
#include <Wire.h>
#include <EEPROM.h>
#include <TEA5767.h>
#include <ErriezDS1307.h>
#include <ezButton.h>


ErriezDS1307 rtc;
TEA5767 rfm = TEA5767();
//A0 - 14
//A1 - 15
//A2 - 16
//A3 - 17
//A4 - 18
//A5 - 19
//A6 - 20
//A7 - 21

ezButton B_hora(7);
ezButton B_minuto(8);
ezButton B_set(6); //~ 

#define set_h_d 14 //~  14 A0
#define set_h_u 15 //~  15 A1
#define set_m_d 17 //~  17 A3
#define set_m_u 12
#define buzzer 13
#define set 21
#define radio_power 20
#define vcc_amp A2

int RGB[]={9,10,11};
int sends[]={2, 3, 4, 5};

int address_hora = 0;
int address_minuto = 2;
int address_alarme_weekend = 4;
int address_alarme_active = 5;
int address_last_frequency_fm = 6;
int in_adjust = 0;
int in_alarme = 0;
int inside = 0;

int modo = 0;
int dl = 3;
int radio_standby = 1;
int h_d; //dezena da hora
int h_u; //unidade da hora
int m_d; //dezena dos minutos
int m_u; //unidade dos minutos

int hora_alarme = -1;
int minuto_alarme = -1;
int alarme_active = -1;
int alarme_weekend = -1;

int contador = 0;
int intervalo = 100;

uint8_t hour;
uint8_t min;
uint8_t sec;
uint8_t mday;
uint8_t mon;
uint16_t year;
uint8_t wday;


float freqs[] = {
                  //88.1,   //Gazeta
                  89.1,   //89 FM A Rádio Rock
                  89.7,   //Novabrasil
                  90.5,   //CBN
                  90.9,   //Rádio Bandeirantes
                  91.3,   //Rádio Disney
                  92.1,   //Play
                  92.5,   //Kiss /boa
                  93.7,   //Rádio USP
                  94.7,   //Antena 1
                  95.3,   //Nativa
                  96.1,   //Band
                  96.9,   //BandNews
                  100.9,  //Jovem Pan
                  100.1,  //Transamérica
                  101.7,  //Alfa Fm
                  103.3,  //Cultura
                  105.1,  //Rádio 105
                  107.3   //Eldorado
  };
int f_size = 17;
int f_atual = 15;

void setup()
{

  Serial.begin(9600);
    
  Serial.println("SETUP");

  pinMode(buzzer, OUTPUT);
  pinMode(vcc_amp, OUTPUT);

  pinMode( RGB[0], OUTPUT); //DEFINE O PINO COMO SAÍDA
  pinMode( RGB[1], OUTPUT); //DEFINE O PINO COMO SAÍDA
  pinMode( RGB[2], OUTPUT); //DEFINE O PINO COMO SAÍDA 
      
  pinMode(sends[0], OUTPUT);
  pinMode(sends[1], OUTPUT);
  pinMode(sends[2], OUTPUT);
  pinMode(sends[3], OUTPUT);
  
  pinMode(set_h_d, OUTPUT);
  pinMode(set_h_u, OUTPUT);
  pinMode(set_m_d, OUTPUT);
  pinMode(set_m_u, OUTPUT);



  Wire.begin();
  
  rfm.init();
  rfm.setStereoNC(true);
  rfm.setFrequency(freqs[f_atual]);
  rfm.setStandby(1);
  rfm.setMono(1);


  if (!rtc.begin()) {
     Serial.println("Couldn't find RTC");
    while (1);
  }
  
  rtc.setSquareWave(SquareWave1Hz);

  if (!rtc.isRunning()) {
        rtc.clockEnable(true);
        if (!rtc.setTime(12, 0, 0)) {
              Serial.println(F("Set time failed"));
         }else{
             Serial.println(F("Inicializando RTC"));
          }
    }
   rtc.setSquareWave(SquareWave1Hz);


    if (!rtc.isRunning()) {
        rtc.clockEnable(true);
    }
    rgb(25, 27, 0);
}


void loop()
{


    B_hora.loop();
    B_minuto.loop();
    B_set.loop();



  if(contador >= intervalo){
    if (!  rtc.getDateTime(&hour, &min, &sec, &mday, &mon, &year, &wday)) {
      Serial.println(F("Get time failed"));
    }
    contador = 0;
  } else {
      contador++;
  }
  
  if (min == 59 && sec == 59) {
    transicao();
  }

    
/*

Chaveia entre as funções
*/
 mode();
  switch (modo) {
    case 0:
          //rtc.setSquareWave(SquareWave1Hz);
          rgb(22, 24, 0);
      relogio();
      break;
    case 1:
      if (radio_standby) modo = 2;
         //rtc.setSquareWave(SquareWaveDisable);
            rgb(0, 0, 0);
      radio();
      break;
    case 2:
 
      alarme();
      break;
    case 3:

      calendario();
      break;
    case 4:
 
      ativa_alarme();
      break;
  }
/*
Verifica se está no horario de algum alarme
*/
 despertador();
  

   if ( !analogRead(radio_power)) {
      while(!analogRead(radio_power));
      
        radio_standby = !radio_standby;
         
        if (!radio_standby) {
            Serial.println("Rádio ON");
            modo = 1;
            f_atual= EEPROM_readDouble(address_last_frequency_fm);
            rfm.setFrequency(freqs[f_atual]);
            digitalWrite(vcc_amp, HIGH);
           
            
        } else {
          
           Serial.println("Rádio OFF");
           EEPROM_writeDouble(address_last_frequency_fm, f_atual);
           digitalWrite(vcc_amp, LOW);
           modo = 0;//volta pro relogio
          }

           rfm.setStandby(radio_standby);
        beep();     
   }



  
}//loop



void atualiza() {

  if (h_d > 0) {
    digitalWrite(set_h_d, HIGH);
    escreve_byte(h_d) ;
    digitalWrite(set_h_d, LOW);
  }

  if (h_u > -1 ) {
    digitalWrite(set_h_u, HIGH);
    escreve_byte(h_u);
    digitalWrite(set_h_u, LOW);
  }

  if (m_d > -1 ) {
    digitalWrite(set_m_d, HIGH);
    escreve_byte(m_d) ;
    digitalWrite(set_m_d, LOW);
  }

  if (m_u > -1 ) {
    digitalWrite(set_m_u, HIGH);
    escreve_byte(m_u) ;
    digitalWrite(set_m_u, LOW);
  }
}



void escreve_byte (byte x) {
  
  if ( x & 0b00000001) digitalWrite(sends[0], HIGH); else digitalWrite (sends[0], LOW);
  if ( x & 0b00000010) digitalWrite(sends[1], HIGH); else digitalWrite (sends[1], LOW);
  if ( x & 0b00000100) digitalWrite(sends[2], HIGH); else digitalWrite (sends[2], LOW);
  if ( x & 0b00001000) digitalWrite(sends[3], HIGH); else digitalWrite (sends[3], LOW);

  delay(dl);
}

void rgb(int R, int G, int B){

    analogWrite( RGB[0], R);
    analogWrite( RGB[1], G);
    analogWrite( RGB[2], B);

  }
