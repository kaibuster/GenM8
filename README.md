# Gen1650-M8
Map your Sega Genesis controller model no. 1650 to M8 controls. 

This code was written so that the Sega Genesis controller model no. 1650 could act as an external 
microcontroller for the dirtywave m8 tracker. The script will not map the controller to other midi 
gear because the array you'll find in lines 45 & 46 point the arduino to read midi data per button 
in the C-1 through G-1 which control the m8s button map. 

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

This script/project are confirmed to work on the arduino leonardo but might be possible on other
smaller arduino USBMIDI complient boards. 

Once the script is uploaded to your arduino and the 1650 controller wired to the arduino, set your MIDI 
SETTINGS on your m8 to the default settings as noted in the dirtywave m8 manual. You must ensure that 
"CONTROL MAP CHAIN" is set to "10" to match the channel assigned in the script otherwise the controller 
will cease communication.

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

happy tracking

_kaibuster 
