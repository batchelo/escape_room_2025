# escape_room_2025
This is the code to run the console
The current (latest version) is the ER_2025_console_less_lights.  There are fewer lights because I switched to a different string of lights.
I have added a bunch of delays, thinking that the problem was a timing issue.  But that did not seem to help.
Comments welcome.  Do you see any obvious problems?
the "singe_string_led_test" works just fine for each of the strings.  I simple change the pin number, run it and it works fine.
So, I don't think that it is a problem with the wiring.
But the "pixel_test" code does not work.  
I was starting to think that I need to fully power off the ESP32, between each upload.  Perhasp there is resitual code in some memory space
that is not wiped by the upload process and the "pressing the boot button" when uploading code.

