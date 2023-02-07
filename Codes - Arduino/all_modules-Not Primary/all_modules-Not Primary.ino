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



int state = 0;
int next_state = 1;
const S1 = 1;
const S2 = 2;
const S3 = 3;
const S4 = 4;


void loop() {
  // ///this function is used to get keys from keypad
  // char input = keypad.getKey();
  // if(input) { 

  // //this function is used to calculate distance  
  // distance = calculateDistance();
  // Serial.println(distance);
  // }
  
  // //this function is used to scan for fingerprints
  // getFingerprintIDez();


  state = next_state;

  switch (expression)
  {
  case S1:
    S1_proc();
    next_state = S2;
    break;

  case S2:
    
    Serial.println("now at step2");
    
    Serial.println("source level is :");
    
    Serial.println(source_level);
    next_state = S3
    break;

  case S3:

    next_state = S4;
    break;

  case S4:

    // if(/*no more input*/){
    //   next_state = S1;
    // }
    // else {
    //   next_state = S2;
    // }
    // break;

  default:
    break;
  } (state) {

  }

}

int passenger_id = -1;
int source_level = 0;
int current_level = 1;
int dest_level = 0;

bool S1_proc{
  result = false
  passenger_id = -1;

  while (passenger_id == -1){
    passenger_id = getFingerprintIDez();
    delay(10);
    Serial.println("waiting for authorization");
  }

    keypad_input = 0;
    while(keypad_input == 0){

    keypad_input = keypad.getKey();
    
    if (48 <= int(keypad_input) && int(keypad_input) <= 51){
      Serial.println(keypad_input);
      source_level = keypad_input;
    }
    else{
      keypad_input = 0;
    }
    delay(10);
    
    Serial.println("waiting for source");
    }

}
