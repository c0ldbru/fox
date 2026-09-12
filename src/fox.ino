/*   
 *   Much of this code was copied from / inspired by Yet Another Foxbox
 *   (YAFB) by Gregory Stoike (KN4CK) which can be found here:
 *   https://github.com/N8HR/YAFB. It has been stripped down and adapted
 *   for use on a Seeed Studio XIAO ESP32C3 and a NiceRF SA868. All credit
 *   for this project goes to Gregory Stoike; I just made his work simple
 *   enough for my own simple foxes.
 *      
 *   This project is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This project is distributed in the hope that it will be useful, but
 *   WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 *   General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this. If not, see <https://www.gnu.org/licenses/>.
 */

#include <SoftwareSerial.h> // ESP software serial for SA868 connection

String callmessage = "Fox Hunt"; // your callsign goes here
String morse = ""; // leave this blank for now; it will be filled in during setup
float frequency = 146.565; // 146.565 is the normal TX frequency for foxes
int delayms = 30000; // delay between transmissions in milliseconds
int initial_delay = 1000; // delay before transmissions start in milliseconds
byte bandwidth = 1; // Bandwidth, 0=12.5k, 1=25K
byte squelch = 1; // Squelch 0-8, 0 is listen/open
byte volume = 5; // Volume 1-8

#define PTT_Pin 5 // GPIO05 | D3 on XIAO
#define PD_Pin 6 // GPIO06 | D4 on XIAO
#define HL_Pin 7 // GPIO07 | D5 on XIAO
#define rx 20 // GPIO20 | D7 on XIAO
#define tx 21 // GPIO21 | D6 on XIAO

SoftwareSerial ESerial(rx, tx);

void setup(){
  ESerial.begin(9600);
  delay(initial_delay);

  morse = createMorse(callmessage);
  
  pinMode(PTT_Pin, OUTPUT);
  pinMode(PD_Pin, OUTPUT);
  pinMode(HL_Pin, OUTPUT);
  digitalWrite(PTT_Pin, HIGH); // LOW is TX, High is RX
  digitalWrite(PD_Pin, HIGH); // LOW is power down mode, HIGH to power up
  digitalWrite(HL_Pin, LOW); // LOW for low power, HIGH is for high power -- HIGH seems to cause issues.
  delay(3000);
  moduleInit();
  moduleSetFreq(frequency);
  moduleSetVol(volume);
}

void loop(){
    digitalWrite(PTT_Pin, LOW); // Put the SA868 in TX mode

    delay(750);
    playMelody();
    delay(750);
    playMorse();
    
    digitalWrite(PTT_Pin, HIGH); // Put the SA868 in RX mode
    delay(delayms); // wait 30 seconds to allow cooldown of SA868
}

void moduleInit(){
  ESerial.print("AT+DMOCONNECT\r\n");
  delay(500);
};

void moduleSetFreq(float freq){
  String toSend="";
  toSend+="AT+DMOSETGROUP=1,";
  toSend+=String(freq,4);
  toSend+=",";
  toSend+=String(freq,4);
  toSend+=",";
  toSend+="0000,";
  toSend+="3,";
  toSend+="0000";
  toSend+="\r\n";
  ESerial.print(toSend);
  delay(100);
};

void moduleSetVol(uint8_t vol){
  String toSend="";
  if(vol>8) vol=8;
  toSend+="AT+DMOSETVOLUME=";
  toSend+=(String)vol;
  toSend+="\r\n";
  ESerial.print(toSend);
  delay(100);
};
