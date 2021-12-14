# radio_relogio_nixie
Radio relógio com Arduino, TEA 5767 e RTC 1307

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
