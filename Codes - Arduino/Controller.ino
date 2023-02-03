/**
   Copyright (C) 2020, Uri Shaked.
   Released under the MIT License.
*/

/*    
   * Ultrasonic Sensor HC-SR05/4 and Arduino
    * by Hanie Kiani
*  https://electropeak.com/learn
    */


/*************************************************** 
  This is an example sketch for our optical Fingerprint sensor
  Designed specifically to work with the Adafruit BMP085 Breakout 
  ----> http://www.adafruit.com/products/751
  These displays use TTL Serial to communicate, 2 pins are required to 
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!
  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Adafruit_Fingerprint.h>
SoftwareSerial mySerial(8, 9);

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);



#include <Keypad.h>

/* Keypad setup */
const byte KEYPAD_ROWS = 4;
const byte KEYPAD_COLS = 4;
byte rowPins[KEYPAD_ROWS] = {5, 4, 3, 2};
byte colPins[KEYPAD_COLS] = {A3, A2, A1, A0};
char keys[KEYPAD_ROWS][KEYPAD_COLS] = {
  {'1', '2', '3', '+'},
  {'4', '5', '6', '-'},
  {'7', '8', '9', '*'},
  {'.', '0', '=', '/'}
};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS);
// invoked using keypad.getkey();

  

// distance module setup
long duration;
int distance;
    
const int trig = 6;
const int echo = 7;

int calculateDistance(){ 
  
  digitalWrite(trig, LOW); 
  delay(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trig, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance= duration*0.034/2;
  return distance;
}

//fingerprint functions
uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence); 

  return finger.fingerID;
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID; 
}


void setup() {
  Serial.begin(115200);
  //pin decleration for distance module 
  pinMode(trig, OUTPUT); // Sets the trigPin as an Output
  pinMode(echo, INPUT); // Sets the echoPin as an Input
  //fingerprint initiate
  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  delay(100);
  Serial.println("\n\nAdafruit finger detect test");

  // set the data rate for the sensor serial port
  finger.begin(57600);
  
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }

  finger.getTemplateCount();
  Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  Serial.println("Waiting for valid finger...");
}




void loop() {
  ///this function is used to get keys from keypad
  char input = keypad.getKey();
  if(input) { 

  //this function is used to calculate distance  
  distance = calculateDistance();
  Serial.println(distance);
  }
  
  //this function is used to scan for fingerprints
  getFingerprintIDez();
}






// #include <iostream>
// #include<dos.h>
// using namespace std;

int main() {


    //states = ["waiting", "get_floor_to_go", "move_to_start", "load_passengers", "close_door", "compute_floor",
    //        "leave_to_destination", "open_door", "close_door"]

    int go_up = 0;
    int go_down = 0;
    int curent_floor = 0;
    String current_state = "waiting";
    String next_state = "";
    int door_open = 0;

    int emergency_alert = 0;


    int start_floor = 0;
    int destination_floor = 0;

    //Event e


    while (true) {

        while (true) {

            if (current_state == "waiting") {
                if(emergency_alert == 1){
                    break;
                }
                door_open = 0;
                //if gets floor number to go:
                next_state = "get_floor_to_go";
            } else if (current_state == "get_floor_to_go") {
                if(emergency_alert == 1){
                    break;
                }
                //get start floor
                start_floor = 123;
                next_state = "move_to_start";

            } else if (current_state == "move_to_start") {
                if(emergency_alert == 1){
                    break;
                }
                if (curent_floor > start_floor) {
                    go_up = 0;
                    go_down = 1;
                    curent_floor -= 1;
                    next_state = "move_to_start";
                } else if (curent_floor < start_floor) {
                    if(emergency_alert == 1){
                        break;
                    }
                    go_down = 0;
                    go_up = 1;
                    curent_floor += 1;
                    next_state = "move_to_start";
                } else if (curent_floor == start_floor) {
                    if(emergency_alert == 1){
                        break;
                    }
                    go_down = 0;
                    go_up = 0;
                    go_down = 0;
                    next_state = "load_passengers";
                }
            } else if (current_state == "load_passengers") {
                if(emergency_alert == 1){
                    break;
                }
                door_open = 1;
                //wait seconds
                delay(5000);
                next_state = "close_door";
            } else if (current_state == "close_door") {
                if(emergency_alert == 1){
                    break;
                }
                door_open = 0;
                next_state = "compute_floor";
            } else if (current_state == "compute_floor") {
                if(emergency_alert == 1){
                    break;
                }
                //todo update destination floor
                destination_floor = 123;
                next_state = "leave_to_destination";
            } else if (current_state == "leave_to_destination") {
                if(emergency_alert == 1){
                    break;
                }

                if (curent_floor > destination_floor) {
                    go_up = 0;
                    go_down = 1;
                    curent_floor -= 1;
                    delay(1000);
                    next_state = "leave_to_destination";
                } else if (curent_floor < destination_floor) {
                    go_down = 0;
                    go_up = 1;
                    curent_floor += 1;
                    delay(1000);
                    next_state = "leave_to_destination";
                } else if (curent_floor == destination_floor) {
                    go_up = 0;
                    go_down = 0;
                    next_state = "open_door";
                }
            } else if (current_state == "open_door") {
                if(emergency_alert == 1){
                    break;
                }
                door_open = 1;
                //wait seconds!!!
                delay(5000);
                next_state = "close_door";
            } else if (current_state == "close_door") {
                if(emergency_alert == 1){
                    break;
                }
                door_open = 0;
                next_state = "waiting";
            }
            current_state = next_state;
        }

        if (go_up == 1) {
            curent_floor += 1;
            delay(1000);
            go_up = 0;
        }
        if (go_down == 1) {
            curent_floor -= 1;
            delay(1000);
            go_down = 0;
        }

        door_open = 1;
        //wait few seconds
        delay(5000);
        door_open = 0;

        next_state = "waiting";
    }

}