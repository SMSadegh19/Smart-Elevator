# Smart-Elevator
This is the project of embedded system design.

## Contributors:
* Mohammad Sadegh Salimi

* Parsa Sharifi

* Alireza Foroodnia

* Mohammad Javad Maheronnaghsh

## Help Links
* https://wokwi.com : simulating raspberry pi and arduino online
* https://github.com/raspberrypi/pico-micropython-examples : source code of raspberry pi samples
* https://electropeak.com/learn/interfacing-r308-biometric-fingerprint-sensor-module-with-arduino/ : Fingerprint Sensor


## Structure
### Simple Apps - Raspberri Pi
In this project, I have made a folder named 'Simple Apps - Raspberri Pi' that concludes the neccessary simple python codes to complete this project. I think it is also a good tutorial for new raspberry pi users.
### Simple Apps - Arduino
In this project, I have made a folder named 'Simple Apps - Arduino' that concludes the neccessary simple python codes to complete this project. I think it is also a good tutorial for new arduino users.
### Controller.ino
This file consists of the main codes to run this project.
It is a mixture of main.ino file (that is the state-controller), and all_modules.ino file (that is the abstraction of needed_methods for modules).
After completing this file, our code is finished (except web app).
### Merged - Primary - V1.ino
This file is the last version of file that is a mixture of controlling file and source codes for Arduino.
This file is uploaded on Arduino and then it works.
## Modules
#### Fingerprint Sensor
#### Keypad
#### Light Sensor
#### Buzzer
#### Arduino Board
#### Distance Sensor

## How to use
To get benefits of this project:
* Connect the hardware modules like the attached help (info) and photoes to this project.
* Plugin (connect) Arduino Board to your pc / laptop.
* Download Arduino IDE (according to your system configs) from https://www.arduino.cc/en/donate/
* Copy and paste code in Controller.ino to Arduino IDE
* Verify and Upload code to the connected Arduino Board (Install "Keypad from Stan..." and "Arduino Uno" if needed).
* Open Serial Console and try using it.


## Completing Notes
* We used Fingerprint Sensor instead of mobile app.
* We wanted to use Light Sensor instead of CO Detection Sensor, but unfortunately it damaged.
* We want to use Bluetooth Sensor for additional score, to show a UI/UX for our elevator.
* We have made a Web Application for the previous task.
* We have used Arduino instead of Raspberry Pi. The reasons are:

  * Arduino gives us a better sense of working with a hardware material.
  * Raspberry Pi needs more initial configurations, and needs monitor for the first time use.
  * Compiling codes in Arduino is much more easier.
## TODO
 * Some wires and a battery for remote controller.
 * How to work with bluetooth or wifi module.
 * How to work with rellay and remote modules.
 * Connect mobile to bluetooth module for web application.
 * Complete code for connceting fingerprint module.
 * Report -> Deadline: Bahman 16th
