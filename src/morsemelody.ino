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

#define Sound_Pin 3 // GPIO03 | D1 on XIAO

// ledc is used to create different tones
int ledc_freq = 2000;
int ledc_channel = 0;
int ledc_resolution = 8;

// Notes and Frequencies
#define REST 0
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978


/****************************************************************************** 
 * Morse and Audio Playing Functions
 * 
 * playMelody
 *    Plays a small melody
 *    
 * playMorse
 *    Plays 'callsign' in morse code
 *    
 * createMorse
 *    Converts 'callmessage' into a morse code language
 ******************************************************************************/
 
 /****************************************************************************** 
 * The playMelody fuction was adpated from:
 * https://github.com/robsoncouto/arduino-songs
 *                                                 
 * From https://github.com/robsoncouto/arduino-songs/blob/master/README.md
 *  Commit 8fb1283 on Feb 13, 2019 
 *  
 *    Copyright
 * 
 *    Every sketch here has been written by myself, although based on 
 *    scores I found online or books I own. These scores are linked in 
 *    each file when possible. You can use the sketches for anything, 
 *    I only kindly ask that you give credit if you use these codes on 
 *    a tutorial, video, example, etc.
 ******************************************************************************/

void playMelody() 
{
  // Change this to make the song slower or faster
  int tempo = 140;
  
  // Notes of the moledy followed by the duration
  // A 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
  // Negative numbers are used to represent dotted notes,
  //  so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
  int melody[] = 
  {
  NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16, NOTE_FS5,-8, NOTE_FS5,-8, NOTE_E5,-4,
  NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16, NOTE_E5,-8, NOTE_E5,-8, NOTE_D5,-8, 
  NOTE_CS5,16, NOTE_B4,-8, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_D5,4, NOTE_E5,8, NOTE_CS5,-8, NOTE_B4,16, NOTE_A4,8, NOTE_A4,8, NOTE_A4,8, 
  NOTE_E5,4, NOTE_D5,2, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_FS5,-8, NOTE_FS5,-8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_A5,4, NOTE_CS5,8, NOTE_D5,-8, NOTE_CS5,16, NOTE_B4,8, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_D5,4, NOTE_E5,8, NOTE_CS5,-8, NOTE_B4,16, NOTE_A4,4, NOTE_A4,8, NOTE_E5,4, NOTE_D5,2, REST,4,
  };
  
  // sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
  // There are two values per note (pitch and duration), so for each note there are four bytes
  int notes = sizeof(melody) / sizeof(melody[0]) / 2;
  
  // This calculates the duration of a whole note in ms (60s/tempo)*4 beats
  int wholenote = (60000 * 4) / tempo;
  
  int divider = 0, noteDuration = 0;

  // Iterate over the notes of the melody.
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) 
  {
    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // Regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // Dotted notes are represented with negative durations
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(Sound_Pin, melody[thisNote], noteDuration * 0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    noTone(Sound_Pin);
  }
}

/****************************************************************************** 
 * Morse Generating Function
 * 
 *  Input: Yet Another Foxbox
 *  Output: -.-- . - / .- -. --- - .... . .-. / ..-. --- -..- -... --- -..-
 ******************************************************************************/

String createMorse(String toconvert)
{
  struct dict
  {
      char character;
      char morse[8];
  };

  dict morseLookup[54] = 
  {
    { 'a', ".-" },
    { 'b', "-..." },
    { 'c', "-.-." },
    { 'd', "-.." },
    { 'e', "." },
    { 'f', "..-." },
    { 'g', "--." },
    { 'h', "...." },
    { 'i', ".." },
    { 'j', ".---" },
    { 'k', "-.-" },
    { 'l', ".-.." },
    { 'm', "--" },
    { 'n', "-." },
    { 'o', "---" },
    { 'p', ".--." },
    { 'q', "--.-" },
    { 'r', ".-." },
    { 's', "..." },
    { 't', "-" },
    { 'u', "..-" },
    { 'v', "...-" },
    { 'w', ".--" },
    { 'x', "-..-" },
    { 'y', "-.--" },
    { 'z', "--.." },
    { '0', "-----" },
    { '1', ".----" },
    { '2', "..---" },
    { '3', "...--" },
    { '4', "....-" },
    { '5', "....." },
    { '6', "-...." },
    { '7', "--..." },
    { '8', "---.." },
    { '9', "----." },
    { '.', ".-.-.-" },
    { ',', "--..--" },
    { '\?', "..--.." },
    { '\'', ".----." },
    { '!', "-.-.--" },
    { '/', "-..-." },
    { '(', "-.--." },
    { ')', "-.--.-" },
    { '&', ".-..." },
    { ':', "---..." },
    { ';', "-.-.-." },
    { '=', "-...-" },
    { '+', ".-.-." },
    { '-', "-....-" },
    { '_', "..--.-" },
    { '\"', ".-..-." },
    { '$', "...-..-" },
    { '@', ".--.-." },
  };
  
  morse = "";
  toconvert.toLowerCase();

  for (int messagei = 0; messagei < toconvert.length(); messagei++)
  {
    for (int structi = 0; structi < sizeof(morseLookup)/sizeof(dict); structi++)
    {
      if (isSpace(toconvert.charAt(messagei)))
      {
        morse.concat("/ ");
        break;
      }
      else if (toconvert.charAt(messagei) == morseLookup[structi].character)
      {
        morse.concat(morseLookup[structi].morse);
        morse.concat(" ");
      }
    }
  }

  return morse;
}


/****************************************************************************** 
 * Morse Playing Function
 ******************************************************************************/
 
void playMorse() 
{
  /*
   * short mark, dot or "dit" (.): "dot duration" is one time unit long      
   * longer mark, dash or "dah" (-): three time units long
   * inter-element gap between the dots and dashes within a character: one dot duration or one unit long
   * short gap (between letters): three time units long      
   * medium gap (between words): seven time units long
   */
  
  int wpm = 13;
  int morsetone = 800;
  
  int wpmduration = (60000) / (wpm*50);

  ledcSetup(ledc_channel, ledc_freq, ledc_resolution);
  ledcAttachPin(Sound_Pin, ledc_channel);

  // convertedmessage
  Serial.println("Playing morse start");
  for (int i = 0; i < morse.length(); i++)
  {
    // only have . - / SPACE
    switch (morse.charAt(i))
    {
      case '.':
        ledcWriteTone(ledc_channel, morsetone * 10);
        delay(1 * wpmduration);
        ledcWriteTone(ledc_channel, 0);
        delay(1 * wpmduration);
        break;
      case '-':
        ledcWriteTone(ledc_channel, morsetone * 10);
        delay(3 * wpmduration);
        ledcWriteTone(ledc_channel, 0);
        delay(1 * wpmduration);
        break;
      case ' ':
        delay(2 * wpmduration);
        break;
      case '/':
        delay(6 * wpmduration);
        break;
    }
  }

  Serial.println("Playing morse end");
  ledcDetachPin(Sound_Pin);
}
