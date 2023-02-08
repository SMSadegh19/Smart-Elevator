/**
   Copyright (C) 2020, Uri Shaked.
   Released under the MIT License.
*/

/*    
   * Ultrasonic Sensor HC-SR05/4 and Arduino
    * by Hanie Kiani
*  https://electropeak.com/learn
    */

/*
  SRF005 Ultrasonic Sensor
  modified on 22 Sep 2020
  by Mohammad Reza Akbari @ Electropeak
  Home

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






// #include<NewPing.H>// include newping library

// NewPing sonar (6, 7, 450);// create ultrasonic object with the following parameters (Trig=3, Echo=2, Max distance=400cm)
// float distance;// initialize a variable of type float




char return_bluetooth(){
  int arrivingdatabyte; 
  if(Serial.available( ) > 0) {  
    arrivingdatabyte = Serial.read( ); 
    if (arrivingdatabyte > 0 && arrivingdatabyte != 10 && arrivingdatabyte != 13){
      return char(arrivingdatabyte);
    }
  } 
  return -1;
}



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
long distance;
    
const int trig = 12;
const int echo = 11;
const int rx = 0;
const int ts = 1;

//kar nemikone
int calculateDistance(){ 
  
  digitalWrite(trig, LOW); 
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trig, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance= duration*100/2;
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

const int emergency_buzzer = 10;

void setup() {
  Serial.begin(9600);
  //pin decleration for distance module 
  pinMode(trig, OUTPUT); // Sets the trigPin as an Output
  pinMode(echo, INPUT); // Sets the echoPin as an Input
  pinMode(11, INPUT);

  pinMode(emergency_buzzer, OUTPUT);
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
const int S1 = 1;
const int S2 = 2;
const int S3 = 3;
const int S4 = 4;
const int S5 = 5;


int passenger_id = -1;
int source_level = 0;
int current_level = 48;
int dest_level = 0;
bool intruder = false;
char keypad_input = 0;

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

  switch (state)
  {
  case S1:
    S1_proc();
    if(intruder){
      next_state = S5;}
    else {
      next_state = S2;}
    break;

  case S2:
    
    
    S2_proc();
    next_state = S3;
    break;

  case S3:
    S3_proc();
    next_state = S1;
    //next_state = S4;
    break;

  case S4:

    // if(/*no more input*/){
    //   next_state = S1;
    // }
    // else {
    //   next_state = S2;
    // }
    // break;
  case S5:
    emergency_proc();
    next_state = S1;  
    break;
  default:
    break;
  }
}



void S1_proc() {
  
  passenger_id = -1;
  Serial.println("waiting for authorization");
  while (passenger_id == -1){
    
    keypad_input = keypad.getKey();
    if(keypad_input == 53){
      intruder = true;
      return;
    }
    passenger_id = getFingerprintIDez();
    delay(1);
    //Serial.println("waiting for authorization");

  }

    Serial.println("waiting for source");
    // keypad_input = 0;
    int answer = -1;
    while(answer == -1){

    // keypad_input = keypad.getKey();
  
    answer = return_bluetooth();
    }


    if (48 <= int(answer) && int(answer) <= 51){
      source_level = answer;
    }
    else{
      answer = -1;
    }
    delay(10);
    
    
    }




void S2_proc(){
  
      
      

      while (current_level < int(source_level)) {
        go_up();
      }

      while (current_level > int(source_level)) {
        go_down();
      }
      
      if (current_level == int(source_level)){
        open_door();
        delay(5000);
        close_door();
      }

    Serial.println("waiting for destination");
    keypad_input = 0;
    while(keypad_input == 0){

    keypad_input = keypad.getKey();
    
    if (48 <= int(keypad_input) && int(keypad_input) <= 51){
      dest_level = keypad_input;
    }
    else{
      keypad_input = 0;
    }
    delay(10);
    
 
    }

  
}



void S3_proc(){

    if (current_level == int(dest_level)){
        Serial.println("maskhare kardi maro ?!");
        return;
      }

    while (current_level < int(dest_level)) {
        go_up();
      }

      while (current_level > int(dest_level)) {
        go_down();
      }
      
      if (current_level == int(dest_level)){
        open_door();
        delay(5000);
        close_door();
      }
}


void emergency_proc(){
  
    while(digitalRead(11) != HIGH){

    digitalWrite(emergency_buzzer, HIGH);
      delay(50);
      digitalWrite(emergency_buzzer, LOW);
      delay(50);
  }
  intruder = false;
}


// void serial(){
//   int ByteReceived = 0;
//   if (Serial.available() > 0) {
//     // read byte of received data:
//     ByteReceived = Serial.read();
//     // prints the received data on serial monitor
//     Serial.print(" Received Serial Data is: ");
//     Serial.println((char)ByteReceived);
//   }
// }


void go_up(){
  digitalWrite(emergency_buzzer, HIGH);
      delay(500);
      digitalWrite(emergency_buzzer, LOW);
      delay(500);
      digitalWrite(emergency_buzzer, HIGH);
      delay(500);
      digitalWrite(emergency_buzzer, LOW);
      delay(1000);  
      current_level++;
      Serial.print("currently at level");
      
      Serial.println(char(current_level));

}

void go_down(){
  digitalWrite(emergency_buzzer, HIGH);
      delay(300);
      digitalWrite(emergency_buzzer, LOW);
      delay(300);
      digitalWrite(emergency_buzzer, HIGH);
      delay(300);
      digitalWrite(emergency_buzzer, LOW);
      delay(300);
      digitalWrite(emergency_buzzer, HIGH);
      delay(300);
      digitalWrite(emergency_buzzer, LOW);
      delay(1000);  
      current_level--;
      
      Serial.print("currently at level");
      
      Serial.println(char(current_level));
}

void open_door(){
    digitalWrite(emergency_buzzer, HIGH);
      delay(100);
      digitalWrite(emergency_buzzer, LOW);
      delay(100);
      digitalWrite(emergency_buzzer, HIGH);
      delay(100);
      digitalWrite(emergency_buzzer, LOW);
      delay(100);
      Serial.println("door is now Open!");
}

void close_door(){
    digitalWrite(emergency_buzzer, HIGH);
      delay(100);
      digitalWrite(emergency_buzzer, LOW);
      delay(100);
      digitalWrite(emergency_buzzer, HIGH);
      delay(100);
      digitalWrite(emergency_buzzer, LOW);
      delay(100);
      Serial.println("door is now Closed!");
}
