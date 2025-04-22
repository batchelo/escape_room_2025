# escape_room_2025
This is the code to run the console for Elon's 2025 Escape Room.
The final version of this code is in the file "ER_2025_console_final".  

It initiates by:
1) setting four flags to 0
2) powering the electromagnet (which locks the tubes inside)
3) lights four leds, which indicate that the four samples are in "inert stasis"

When players use the keypad to put in a code, and then press "#", the script will evalauate whether that is a correct code.
If so, then it will:
(1) set a flag to 1
(2) switch to a light that says "sample activated" and 
(3) lights will illuminate under that specific tube.

When all four codes are correctly entered, 
(1) the electromagnet will be disabled, 
(2) congratulations offered, and 
(3) players will be instructed to take the tubes and leave the ship.
