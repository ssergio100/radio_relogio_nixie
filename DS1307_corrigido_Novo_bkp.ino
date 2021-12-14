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
TEA5767 radio = TEA5767();
//A0 - 14
//A1 - 15
//A2 - 16
ezButton radio_power(14);
ezButton B_hora(7);
ezButton B_minuto(8);
ezButton B_set(6);


#define send_h_d 2
#define send_h_u 3
#define send_m_d 4
#define send_m_u 5

#define set_h_d 9
#define set_h_u 10
#define set_m_d 11
#define set_m_u 12
#define buzzer 13


const int set = A1;
const int vcc_amp = A2;

int address_hora = 0;
int address_minuto = 2;
int address_alarme_weekend = 4;
int address_alarme_active = 5;
int address_last_frequency_fm = 6;
int in_adjust = 0;
int in_alarme = 0;
//int silence_alarme = 0;
int modo = 0;
int dl = 3;
int radio_standby = 1;
int radio_minlvl = 0;
int h_d; //dezena da hora
int h_u; //unidade da hora
int m_d; //dezena dos minutos
int m_u; //unidade dos minutos

int hora_alarme;
int minuto_alarme;

float f;

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
  Serial.println("Rodando");

  pinMode(set, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  pinMode(vcc_amp, OUTPUT);
  
  pinMode(send_h_d, OUTPUT);
  pinMode(send_h_u, OUTPUT);
  pinMode(send_m_d, OUTPUT);
  pinMode(send_m_u, OUTPUT);
  
  pinMode(set_h_d, OUTPUT);
  pinMode(set_h_u, OUTPUT);
  pinMode(set_m_d, OUTPUT);
  pinMode(set_m_u, OUTPUT);


  Serial.begin(9600);
  Wire.begin();
  
  radio.init(radio_minlvl);
  radio.setStereoNC(true);
  radio.setFrequency(freqs[f_atual]);


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
  // rtc.isRunning() == true;
   rtc.setSquareWave(SquareWave1Hz);


    if (!rtc.isRunning()) {
        rtc.clockEnable(true);
    }

 
}


void loop()
{
    radio_power.loop();
    B_hora.loop();
    B_minuto.loop();
    B_set.loop();





  if (!rtc.getTime(&hour, &min, &sec)) {
    Serial.println(F("Get time failed"));
  }

  if (min == 59 && sec == 59) {
    transicao();
  }
/*

 Atualiza a hora de alarme caso ela tenha sido alterada
*/
atualizaHoraAlarme();
/*
Chaveia entre as funções
*/
 mode();
/*
Verifica se está no horario de algum alarme
*/
 alarme();
  
  switch (modo) {
    case 0:
      modo_relogio();
      break;
    case 1:
      if (radio_standby) modo = 2;
      modo_radio();
      break;
    case 2:
      modo_alarme();
      break;
    case 3:
      modo_calendario();
      break;
    case 4:
      modo_ativa_alarme();
      break;
  }

   if (radio_power.isReleased()) {
    
        radio_standby = !radio_standby;
         
        if (!radio_standby) {
          
            Serial.println("Rádio ON");
             modo = 1;
            float last_frequency = EEPROM_readDouble(6);
            radio.setFrequency(last_frequency);
            digitalWrite(vcc_amp, HIGH);
            
        } else {
          
           Serial.println("Rádio OFF");
           modo = 0;//volta pro relogio
           EEPROM_writeDouble(6, radio.getFrequency());

           digitalWrite(vcc_amp, LOW);
          }

           radio.setStandby(radio_standby);
        beep();     
   }
}//loop



int atualiza() {

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

  if ( x & 0b00000001) digitalWrite(send_h_d, HIGH); else digitalWrite (send_h_d, LOW);
  if ( x & 0b00000010) digitalWrite(send_h_u, HIGH); else digitalWrite (send_h_u, LOW);
  if ( x & 0b00000100) digitalWrite(send_m_d, HIGH); else digitalWrite (send_m_d, LOW);
  if ( x & 0b00001000) digitalWrite(send_m_u, HIGH); else digitalWrite (send_m_u, LOW);

  delay(dl);
}
