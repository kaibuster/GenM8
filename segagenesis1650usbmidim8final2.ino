// GenM8 - sega genesis controller model no. 1650 midiusb to the dirtywave m8 tracker

#include "MIDIUSB.h"
#define NUM_BUTTONS 8

bool buttonB = false;
bool buttonA = false;  
bool buttonC = false;
bool buttonSTART = false;
bool buttonLEFT = false;
bool buttonRIGHT = false;
bool buttonUP = false;
bool buttonDOWN = false;
//                        SEGA no. 1650 (alternate)    M8       M8/SEGA
const uint8_t button1 = 2;  // up high               0(play)      B
const uint8_t button2 = 3;  // down high             1(shift)     A
const uint8_t button3 = 4;  // left high             2(edit)      C
const uint8_t button4 = 5;  // right high            3(option)    START
const uint8_t button5 = 6;  // a trig pin 7 low      4(left)      L
const uint8_t button6 = 6;  // b trig pin 7 high     5(right)     R
const uint8_t button7 = 8;  // c trig pin 7 low      6(up)        U 
const uint8_t button8 = 8;  // start pin 7 high      7(down)      D

const uint8_t channel = 9;
const uint8_t offset = 0;  

const uint8_t selecthighbuttons[NUM_BUTTONS - 2] = { button1, button2, button3, button4, button5, button7 };
const uint8_t selectlowbuttons[2] = { button6, button8 };
// const uint8_t selecthighcommands[NUM_BUTTONS - 2] = { 0 + offset, 1 + offset, 2 + offset, 3 + offset, 4 + offset, 6 + offset };
// const uint8_t selectlowcommands[2] = { 5 + offset, 7 + offset }; (0,1,2,3,4,6) (5,7) maps the 1650 to an alternate orientation

const uint8_t selecthighcommands[NUM_BUTTONS - 2] = { 6 + offset, 7 + offset, 4 + offset, 5 + offset, 3 + offset, 2 + offset };  
const uint8_t selectlowcommands[2] = { 1 + offset, 0 + offset }; // (6,7,4,5,3,2) (1,0) maps the 1650 to the correct orientation

bool *selecthighbool[NUM_BUTTONS - 2] = { &buttonB, &buttonC, &buttonUP, &buttonDOWN, &buttonLEFT, &buttonRIGHT };  //& give a pointer to a variable rather than value of the variable
bool *selectlowbool[2] = { &buttonA, &buttonSTART };

const char buttonbtrig[] = "btrig"; // unit test 
const char buttonatrig[] = "atrig";
const char buttonctrig[] = "ctrig";
const char buttonstart[] = "start";
const char buttonleft[] = "left";
const char buttonright[] = "right";
const char buttonup[] = "up";
const char buttondown[] = "down";

const char *selecthighbuttonnames[NUM_BUTTONS - 2] = { buttonup, buttondown, buttonleft, buttonright, buttonbtrig, buttonctrig };
const char *selectlowbuttonnames[2] = { buttonatrig, buttonstart };

uint8_t notesTime[NUM_BUTTONS];
uint8_t pressedButtons = 0x00;
uint8_t previousButtons = 0x00;
uint8_t intensity;

void setup() {

  Serial.begin(115200);

  for (int i = 0; i < NUM_BUTTONS; i++) {

    pinMode(selecthighbuttons[i], INPUT_PULLUP);
  }

  pinMode(7, OUTPUT);
}

void buttoncheckup() {

  char OutputBuffer[64];

  digitalWrite(7, HIGH);

  for (int i = 0; i < (NUM_BUTTONS - 2); i++) {

    if (!digitalRead(selecthighbuttons[i])) {
      if (!*selecthighbool[i]) {
        sprintf(OutputBuffer, "you pressed: %s", selecthighbuttonnames[i]);
        Serial.println(OutputBuffer);
        *selecthighbool[i] = true;
        // Serial.print(selecthighcommands[i]);  unit test
        // Serial.println(" this key was sent");
        noteOn(channel, selecthighcommands[i], 100);  
      }
    } else if (*selecthighbool[i]) {
      sprintf(OutputBuffer, "you released: %s", selecthighbuttonnames[i]);
      Serial.println(OutputBuffer);
      *selecthighbool[i] = false;
      noteOff(channel, selecthighcommands[i], 100);
    }
  }

  digitalWrite(7, LOW);

  for (int i = 0; i < 2; i++) {

    if (!digitalRead(selectlowbuttons[i])) {
      if (!*selectlowbool[i]) {
        sprintf(OutputBuffer, "you pressed: %s", selectlowbuttonnames[i]);
        Serial.println(OutputBuffer);
        *selectlowbool[i] = true;
        noteOn(channel, selectlowcommands[i], 100);
      }

    } else if (*selectlowbool[i]) {
      sprintf(OutputBuffer, "you released: %s", selectlowbuttonnames[i]);
      Serial.println(OutputBuffer);
      *selectlowbool[i] = false;
      noteOff(channel, selectlowcommands[i], 100);
    }
    MidiUSB.flush();
    delay(40); // any delay around 40-60 provides instant feedback on M8
  }
}

void loop() {

  buttoncheckup();

}

// First parameter is the event type (0x0B = control change).
// Second parameter is the event type, combined with the channel.
// Third parameter is the control number number (0-119).
// Fourth parameter is the control value (0-127).

void controlChange(byte channel, byte control, byte value) {

  midiEventPacket_t event = { 0x0B, 0xB0 | channel, control, value };

  MidiUSB.sendMIDI(event);
}

/*
First parameter is the event type (0x09 = note on, 0x08 = note off).
Second parameter is note-on/note-off, combined with the channel.
Channel can be anything between 0-15. Typically reported to the user as 1-16.
Third parameter is the note number (48 = middle C).
Fourth parameter is the velocity (64 = normal, 127 = fastest).
*/

void noteOn(byte channel, byte pitch, byte velocity) {

  midiEventPacket_t noteOn = { 0x09, 0x90 | channel, pitch, velocity };

  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  //Serial.print

  midiEventPacket_t noteOff = { 0x08, 0x80 | channel, pitch, velocity };

  MidiUSB.sendMIDI(noteOff);
}

//happy tracking (=*o*)/ _kaibuster