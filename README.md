# DuinoClock
A simple alarm clock made using Arduino nano, LCD and a DS3231 RTC chip

**Document Status**: Draft

## Schematic
*To be added*

## Instructions

* Download the repository as a zip and extract it.
* The files under the *DuinoClock/support/library* folder need to be added to the Arduino libraries.
  * Go to *Sketch* -> *Include Library* -> *Add .ZIP Library* and follow the instructions on-screen.
* Connect all the components as per the schematic. Connect the Arduino to your PC.
* Once the libraries are added successfully, set the correct date, time and day of week.
  * To do this, open *DuinoClock/support/set_time/set_time.ino*
  * Set the correct parameters and upload the sketch
* Open the DigitalAlarmClock.ino sketch and upload it.

That's it - the time should be displayed.
