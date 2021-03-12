/*
Music Box
  What you Need :
  - VMPK 
  - Playground Express
  - Light Source of some kind
  - 3 Aligator Wires 

This porgram allows you to listen to these songs :
          - "Super Mario theme"  / (The iconic theme from the "Super Mario bros." games)     (Track 0)
          - "Song of fire & ice" / ("Game of Thrones" Opening theme)                         (Track 1)
          - "Mortal Kombat"      / "Mortal Kombat" movie theme                               (Track 2)
in 2 mods :
Mod A: the "Music Box" Allows to read the light and determine tempo, and allow to read Accelerometer to change songs 
-- the stronger the light the tempo is adjusted accordingly , if in darker places will slow, in bright place will speed it up 
- tlit Accelrometer hard to left to prev song 
- tlit Accelrometer softly to left to restart song 
- tlit Accelrometer hard to right to next song 
Mod B: the "Music Box" Allows to read the light to determine octave, and allow to read Capacitance to change songs 
--  Use capacitance to adjust the values. 
- the stronger the light the pitchness will be higher up to the relative max octave 
How to set up : 
- Connect the wires to A3,A4,A5 
- A3 is Prev Song
- A4 is Restart
- A5 is Next 

Name of creator:
 Tal Danai 

Videos :
- Explain       :  https://drive.google.com/file/d/15FzfqeVT6FuxjA5leRAHBeN2c7kSxwZr/view?usp=sharing
- Demonstration :  https://drive.google.com/file/d/1_DGx0bZCnouUVDPYcnwjkUJs_0uL9WSc/view?usp=sharing
 */
#include "MIDIUSB.h"
#include <Adafruit_CircuitPlayground.h>

uint8_t base_octave [] = {5, 5, 3};
uint8_t max_octave[] = {5, 5, 6};
uint8_t min_octave[] = {1, 2, 2};

uint8_t songs [][628] = {
  {76, 76, 0, 76, 72, 76, 79, 0, 67, 0, 72, 0, 67, 0, 64, 0, 69, 71, 70, 69, 67, 76, 79, 81, 77, 79, 76, 72, 74, 71, 0, 72, 0, 67, 0, 64, 0, 69, 71, 70, 69, 67, 76, 79, 81, 77, 79, 76, 72, 74, 71, 0, 79, 78, 77, 75, 0, 76, 0, 68, 69, 72, 0, 69, 72, 74, 0, 79, 78, 77, 75, 0, 76, 0, 84, 0, 84, 84, 0, 79, 78, 77, 75, 0, 76, 0, 68, 69, 72, 0, 69, 72, 74, 0, 75, 0, 74, 0, 72},
  {79, 0, 72, 0, 75, 0, 77, 0, 79, 0, 72, 0, 75, 0, 77, 0, 79, 0, 72, 0, 75, 0, 77, 0, 79, 0, 72, 0, 75, 0, 77, 0, 79, 0, 72, 0, 76, 0, 77, 0, 79, 0, 72, 0, 75, 0, 77, 0, 79, 0, 72, 0, 76, 0, 77, 0, 79, 0, 72, 0, 75, 0, 77, 0, 91, 0, 84, 0, 87, 0, 89, 0, 91, 0, 84, 0, 87, 0, 89, 0, 72, 0, 75, 0, 77, 0, 79, 0, 72, 0, 75, 0, 77, 0, 79, 0, 72, 0, 75, 0, 77, 0, 79, 0, 72, 0, 75, 0, 77, 0, 79, 0, 89, 0, 82, 0, 86, 0, 87, 0, 89, 0, 82, 0, 87, 0, 86, 0, 72, 0, 75, 0, 77, 0, 79, 0, 72, 0, 75, 0, 77, 0, 79, 0, 72, 0, 75, 0, 77, 0, 79, 0, 72, 0, 75, 0, 77, 0, 79, 0, 91, 0, 84, 0, 87, 0, 89, 0, 91, 0, 84, 0, 87, 0, 89, 0, 72, 0, 75, 0, 77, 0, 79, 0, 72, 0, 75, 0, 77, 0, 79, 0, 72, 0, 75, 0, 77, 0, 79, 0, 72, 0, 75, 0, 77, 0, 79, 0, 89, 0, 82, 0, 86, 0, 87, 0, 89, 0, 82, 0, 87, 0, 86, 0, 72, 0, 75, 0, 77, 0, 79, 0, 72, 0, 75, 0, 77, 0, 79, 0, 72, 0, 75, 0, 77, 0, 79, 0, 72, 0, 75, 0, 77, 0, 79, 0, 103, 0, 96, 0, 99, 0, 101, 0, 103, 0, 96, 0, 99, 0, 101, 0, 72, 0, 75, 0, 77, 0, 79, 0, 72, 0, 75, 0, 77, 0, 79, 0, 72, 0, 75, 0, 77, 0, 79, 0, 72, 0, 75, 0, 77, 0, 79, 0, 101, 0, 94, 0, 98, 0, 99, 0, 98, 0},
  {57, 57, 60, 57, 62, 57, 64, 62, 60, 60, 64, 60, 57, 60, 64, 60, 55, 55, 59, 55, 60, 55, 62, 60, 53, 53, 57, 53, 60, 53, 60, 59, 57, 57, 57, 57, 55, 59, 57, 57, 57, 57, 55, 52, 57, 57, 57, 57, 55, 59, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 55, 59, 57, 57, 57, 57, 55, 52, 57, 57, 57, 57, 55, 59, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 55, 59, 57, 57, 57, 57, 55, 52, 57, 57, 57, 57, 55, 59, 57, 57, 57, 57, 57, 57, 57, 57, 64, 57, 60, 57, 58, 57, 60, 57, 58, 55, 57, 64, 57, 60, 57, 58, 57, 60, 57, 58, 55, 57, 64, 57, 60, 57, 58, 57, 60, 57, 58, 55, 55, 55, 57, 57, 57, 0, 57, 64, 57, 60, 57, 58, 57, 60, 57, 58, 55, 57, 64, 57, 60, 57, 58, 57, 60, 57, 58, 55, 57, 0, 57, 0, 57, 0, 57, 0, 57, 57, 60, 57, 62, 57, 64, 62, 60, 60, 64, 60, 57, 60, 64, 60, 55, 55, 59, 55, 60, 55, 62, 60, 53, 53, 57, 53, 60, 53, 60, 59, 57, 57, 57, 57, 55, 59, 57, 57, 57, 57, 55, 52, 57, 57, 57, 57, 55, 59, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 55, 59, 57, 57, 57, 57, 55, 52, 57, 57, 57, 57, 55, 59, 57, 57, 57, 57, 57, 57, 57}
  };
  
uint16_t key_press_len [][628]= {
  {150, 150, 75, 300, 150, 300, 300, 300, 300, 300, 300, 150, 300, 150, 300, 150, 300, 300, 150, 300, 225, 150, 150, 300, 150, 300, 300, 150, 150, 300, 150, 300, 150, 300, 150, 300, 150, 300, 300, 150, 300, 225, 150, 150, 300, 150, 300, 300, 150, 150, 300, 300, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 300, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 600, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 300, 150, 300, 150, 300, 150},
  {374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 1122, 23, 1122, 23, 187, 23, 187, 23, 748, 23, 748, 23, 187, 23, 187, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 1122, 23, 1122, 23, 187, 23, 187, 23, 748, 23, 748, 23, 187, 23, 187, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 1122, 23, 1122, 23, 187, 23, 187, 23, 748, 23, 748, 23, 187, 23, 187, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 1122, 23, 1122, 23, 187, 23, 187, 23, 748, 23, 748, 23, 187, 23, 187, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 1122, 23, 1122, 23, 187, 23, 187, 23, 748, 23, 748, 23, 187, 23, 187, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 1122, 23, 1122, 23, 748, 23, 748, 23, 748, 23, 748, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 748, 374, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 748, 23, 374, 23, 748, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23, 374, 23, 187, 23, 187, 23, 374, 23},
  {214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 428, 428, 428, 428, 214, 214, 428, 428, 428, 428, 214, 214, 428, 428, 428, 428, 214, 214, 428, 428, 214, 107, 214, 107, 428, 428, 428, 428, 428, 214, 214, 428, 428, 428, 428, 214, 214, 428, 428, 428, 428, 214, 214, 428, 428, 214, 107, 214, 107, 428, 428, 428, 428, 428, 214, 214, 428, 428, 428, 428, 214, 214, 428, 428, 428, 428, 214, 214, 428, 428, 214, 107, 214, 107, 428, 107, 214, 107, 214, 107, 214, 107, 214, 107, 107, 214, 107, 214, 107, 214, 107, 214, 107, 214, 107, 107, 214, 107, 214, 107, 214, 107, 214, 107, 214, 107, 107, 214, 107, 214, 107, 214, 321, 107, 107, 214, 107, 214, 107, 214, 107, 214, 107, 107, 214, 107, 214, 107, 214, 107, 214, 107, 214, 107, 107, 214, 321, 107, 321, 107, 321, 107, 321, 107, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 428, 428, 428, 428, 214, 214, 428, 428, 428, 428, 214, 214, 428, 428, 428, 428, 214, 214, 428, 428, 214, 107, 214, 107, 428, 428, 428, 428, 428, 214, 214, 428, 428, 428, 428, 214, 214, 428, 428, 428, 428, 214, 214, 428, 428, 214, 107, 214, 107, 428},
  };
  
uint16_t lengths [] = {99, 314, 258};

int8_t current_change = 0, current_light_pattern = -1; 
String names [] = {"Super Mario bros", "Game of Thrones", "Mortal Kombat"};

int colors [] = {0xFF0000,0x808000,0x800080, 0x00FF00, 0x008080, 0x0000FF, 0x808080}; // 
bool slideSwitch;

uint8_t pin , color;
float tempo; 
uint8_t last_song_played = 0 , current_song_played, last_pin = -1;
uint16_t current_note_played = 0;
void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

void setup() {
  Serial.begin(115200);
  CircuitPlayground.begin();
}

// First parameter is the event type (0x0B = control change).
// Second parameter is the event type, combined with the channel.
// Third parameter is the control number number (0-119).
// Fourth parameter is the control value (0-127).


void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

void loop() {
        int newNote = change_note(songs[current_song_played][current_note_played]), newTempo;
        if (!current_song_checker() && last_song_played != -1) {
          noteOn(1,newNote , 64);
          MidiUSB.flush();
              if (songs[current_song_played][current_note_played] != 0) {
                  color_patteren_on();
              }         
          newTempo = tempo_checker(key_press_len[current_song_played][current_note_played]);
          delay(newTempo);
          noteOff(1,newNote, 64);
          MidiUSB.flush();
          if (songs[current_song_played][current_note_played] != 0) {
              color_patteren_off();
          }
        }
          if (++current_note_played > lengths[current_song_played]){
              switched_songs();
          }
    }

// if switch is on may change tempo determines the tempo 
int tempo_checker(int delays) {
        tempo = map(CircuitPlayground.lightSensor(), 0, 1000, -5, 28);
        slideSwitch = CircuitPlayground.slideSwitch();
        if (!slideSwitch) {
            return delays;
        }
        if(tempo == 0){
          return delays;
        }
        if( tempo < 0){
          // slowing tempo
            return delays * (10 + tempo);
        }else{
            return delays /  (tempo/4 + 1);
        }
    }
// if switch is off may change octave and determine which octave is needed
int change_note(int note) {
        if (slideSwitch||note == 0) {
            return note;
        }
        int newNote = 0;
        current_change = map(CircuitPlayground.lightSensor(), 0, 1000, -2, 2);
        Serial.print("light , current change : ");
        Serial.print(current_change);
        if (current_change + base_octave[current_song_played] > max_octave[current_song_played]) {
            newNote = note + ((max_octave[current_song_played] - base_octave[current_song_played]) * 12);
        } else if (current_change + base_octave[current_song_played] < min_octave[current_song_played]) {
            newNote = note + ((min_octave[current_song_played] - base_octave[current_song_played]) * 12);
        } else {
            newNote = note + (current_change) * 12;
        }
        Serial.print(" Note: ");
        Serial.println(newNote);
        return newNote;
    }
// returns true if song was changed  
bool current_song_checker() {
        slideSwitch = CircuitPlayground.slideSwitch();
        if (slideSwitch) {
            int8_t x = map(CircuitPlayground.motionX(), -20, 20, -6, 6);
            if (x <= -2 || x >= 2) {
                if (x <= -3) {
                    move_to_prev_song();
                } else if (x == 2) {
                    move_to_next_song();
                } else {
                    current_note_played = 0;
                }
                return true;
            } else {
                return false;
            }
        } else {
            int8_t tem = map(CircuitPlayground.readCap(A3), 400, 1016, 0, 5);
            int8_t temp1 = map(CircuitPlayground.readCap(A4), 400, 1016, 0, 5);
            int8_t temp2 = map(CircuitPlayground.readCap(A5), 400, 1016, 0, 5);
            Serial.println(temp2);
            if (tem >= 4 || temp1 >= 4 || temp2 >= 4) {
                if (tem >= 4) {
                    move_to_prev_song();
                } else if (temp2 >= 4) {
                    move_to_next_song();
                } else {
                    current_note_played = 0;
                }
                return true;
            } else {
                return false;
            }
        }
    }

// turns the light on for the song 
void color_patteren_on(){
 if(current_light_pattern == 0){
      pin = random(0, 9), color = random(0, sizeof(colors)/4);
      CircuitPlayground.setPixelColor(pin, colors[color]);
 }else if(current_light_pattern == 1){
      pin = random(0, 9), color = random(0, sizeof(colors)/4);
      CircuitPlayground.setPixelColor(pin, colors[color]);
      CircuitPlayground.setPixelColor(9 - pin, colors[color]);
 }else if(current_light_pattern == 2){
      pin = (++last_pin)%10, color = random(0, sizeof(colors)/4);
      CircuitPlayground.setPixelColor(pin, colors[color]);
 }else if(current_light_pattern == 3){
      pin = (++last_pin)%10, color = random(0, sizeof(colors)/4);
      CircuitPlayground.setPixelColor(pin, colors[color]);
      CircuitPlayground.setPixelColor((pin + 5)%10, colors[color]);
 }else{
      // current_light_pattern == 4
      color = random(0, sizeof(colors)/4);
      for(int i = 0; i< 10; i++){
         CircuitPlayground.setPixelColor(i, colors[color]);
      }
 }
}
// turns the light off for the song 
void color_patteren_off(){
   if(current_light_pattern == 0){
      CircuitPlayground.setPixelColor(pin, 0x000000);
   }else if(current_light_pattern == 1){
      CircuitPlayground.setPixelColor(pin, 0x000000);
      CircuitPlayground.setPixelColor(9 - pin, 0x000000);
   }else if(current_light_pattern == 2){
      CircuitPlayground.setPixelColor(pin, 0x000000);
   }else if(current_light_pattern == 3){
      CircuitPlayground.setPixelColor(pin, 0x000000);
      CircuitPlayground.setPixelColor((pin + 5)%10, 0x000000);
   }else{
    //current_light_pattern == 4 
    for(int i = 0; i< 10; i++){
         CircuitPlayground.setPixelColor(i, 0x000000);
        }
    }
}
// auto play
void switched_songs(){
  CircuitPlayground.clearPixels();
  last_song_played = current_song_played;
  current_song_played = (current_song_played + 1)% 3;
  current_note_played = 0;
  Serial.println("Playing: " + names[current_song_played]);
  current_light_pattern = random(0,4);
  delay(1000);
}
// songs switched manually to next
void move_to_next_song(){ 
  CircuitPlayground.clearPixels();
  last_song_played = current_song_played;
  current_song_played = (current_song_played + 1)% 3;
  current_note_played = 0;
  Serial.println("Playing: " + names[current_song_played]);
  current_light_pattern = random(0,4);
  delay(500);
}
// songs switched manually to next
void move_to_prev_song(){
  CircuitPlayground.clearPixels();
  last_song_played = current_song_played;
  if(current_song_played != 0){
    current_song_played = (current_song_played - 1)% 3;
  }else{
    current_song_played = 2;
  }
  current_note_played = 0;
  Serial.println("Playing: " + names[current_song_played]);
  current_light_pattern = random(0,4);
  delay(500);
}
