Getting started:

This code was written so that the Sega Genesis controller model no. 1650 could act as an external 
microcontroller for the dirtywave m8 tracker. The script will not map the controller to other midi 
gear, nor will it work with other Sega controller types because the arrays throughout point the 
arduino to read midi data per button for the 1650 in the C-1 through G-1 which control the m8s 
button map. 

NOTE-NUMBER  CONTROL          M8 NOTE (ch 10)
-----------  -------          ---------------
0             Play              C-1
1             Shift             C#1
2             Edit              D-1
3             Option            D#1
4             Left              E-1
5             Right             F-1
6             Up                F#1
7             Down              G-1

Shouts out to robhercKV5ROB and MaderDash for the mentorship and knowledge, this code wouldn't be
possible without them and m8 users Okyeron & Avrilcadabra for researching/providing the data sheet 
above. 
  
There are a few resources and scripts available in the arduino library that also cover the basic 
serial reads for the 1650 and other sega controllers, however none that relate directly with 
MIDIUSB or the dirtywave m8. The 1650 contains the 74HC157 chip (high-speed CMOS quad 2-line to 
1-line multiplexer). Pin 7 acts as a select between high and low which allows multiple buttons 
to register data on a single pin. the code was written to address this issue so all 8 buttons
would be usable, but for that reason this script will not work with other sega or retro console
microcontrollers unless modified.  

Important to mention that the dirtywave m8 tracker is a usb device and this sega controller/arduino 
is also a usb device. Both usb devices can't communicate with one another unless routed through a 
midi host. I highly recommend the Retrokits RK006 USB MIDI/GATE which is guaranteed to work with 
this script and would allow for more midi/m8 combinations in the future. 

![Fp6ppcwaMAEdJdm](https://user-images.githubusercontent.com/65822292/221446031-0c436a6b-df09-4bb0-8459-cd0f106dc405.jpg)

This script/project is confirmed to work on the arduino leonardo but might be possible on other
smaller arduino USBMIDI complient boards. 

Setting up:

Once the script is uploaded to your arduino and the 1650 controller wired to the arduino using the 
pin sheet below this paragraph, set your MIDI SETTINGS on your m8 to the default settings as noted 
in the dirtywave m8 manual. You must ensure that "CONTROL MAP CHAN" is set to "10" to match the 
channel assigned in the script otherwise the controller will cease communication. (see bottom for 
more details on this) If you've followed all steps and still aren't getting a response on m8, 
double check your routing options on your RK006. 

SEGA 1650 PIN             Arduino Leonardo
-------------             ----------------
1                                 2          
2                                 3            
3                                 4           
4                                 5            
5                                 5v          
6                                 6        
7                                 7         
8                                GND       
9                                 8         
-------------             ----------------

If you get lost wiring this up, I referred to this url throughout the course of this project and recommend 
you do the same. https://pinoutguide.com/Game/genesiscontroller_pinout.shtml

side note: for anyone looking to modify this code for use with a different retro microcontroller. Once you 
have all your buttons successfully sending on/off messages in serial monitor I suggest running through a 
desktop midi monitor (I use MidiView its free) to see what note data your controllers sending (C-1, D-1, etc).
MidiView will show the buttons on the 1650 triggering the C-2 ascending scale rather than the C-1, in 
reference to the first data sheet. You might also notice on line 24 the channel is set to "9" however the
default "CONTROL MAP CHAN" for m8 is "10" - I do not know why the data does not match, but I'm suspecting it 
might have something to do with how m8 responds to midi data through the MIDIUSB library. Assign the sega 
controller whatever channel you desire, I have it set to the default so each time you load a new song, 
depending on your own midi settings default menu, the controller will immediately work. Despite this the 
code works as intended and I haven't bothered to investigate further. https://hautetechnique.com/midi/midiview/

happy tracking (=^o^)/

_kaibuster 
