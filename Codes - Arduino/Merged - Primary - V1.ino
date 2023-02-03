// Merged Code - Version 1

#include <Keypad.h>
const int emergency_buzzer = 10;
byte rowPins[4] = {5, 4, 3, 2};
byte colPins[4] = {A3, A2, A1, A0};
char keys[4][4] = {
  {'1', '2', '3', '3'},
  {'4', '5', '6', '2'},
  {'7', '8', '9', '1'},
  {'*', '0', '#', '0'}
};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, 4, 4);


char level = 0;
bool emergency;
bool go_up;
bool go_down;
bool opened_door;
long duration;
int distance;
const int trig = 6;
const int echo = 7;

void setup() {
  Serial.begin(9600);
  pinMode(emergency_buzzer, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  level = '0';
  go_down = false;
  go_up  = false;
  opened_door = false;
  emergency = false;
}

int calculateDistance(){ 
  digitalWrite(trig, LOW); 
  delayMicroseconds(2);
  digitalWrite(trig, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH, 50000); 
  distance= duration*0.034/2;
  return distance;
}

char keypad_input;
void loop() {
  if (go_down == false && go_up == false && emergency == false){
    keypad_input = keypad.getKey();
    if (keypad_input){
      // int new_floor = int(keypad_input);
      // bool ans = new_floor = level;
      // Serial.println(ans);
      if (level == keypad_input){
        Serial.println("Stay in this floor!");
        opened_door = true;
        delay(3000);
        opened_door = false;
          
          delay(100);
          int e_number = 0;
          for(int i = 1; i < 40; i += 1){
            distance = calculateDistance(); 
            if (distance > 0 & distance < 19){
              e_number += 1;
              Serial.println("EMErg");
            }
            delay(10);
          }
          if (e_number >= 2){
            emergency = true;
          }
          
      }
      else if (level < int(keypad_input)){
        // Serial.println(level);
        // Serial.println(keypad_input);
        go_up = true;
        Serial.println("Going up!");
        delay(1000);
        Serial.println(keypad_input);
        Serial.println(level);
        for (int j = 0; j < int(keypad_input - level); j += 1){
          // level += 1;
          Serial.println("One level Up!");
          digitalWrite(emergency_buzzer, HIGH);
          delay(300);
          digitalWrite(emergency_buzzer, LOW);
          delay(300);
          
        }
        // level -= 1;
        level = keypad_input;
        go_up = false;
        Serial.println("Current Level is: ");
        Serial.println(level);
      }
    

        
      
      else if (level > int(keypad_input)){
        go_down = true;
        Serial.println("Going down!");
        delay(1000);
        Serial.println(keypad_input);
        Serial.println(level);
        for (int j = 0; j < int(- keypad_input + level); j += 1){
          // level -= 1;
          Serial.println("One level Down!");
          digitalWrite(emergency_buzzer, HIGH);
          delay(300);
          digitalWrite(emergency_buzzer, LOW);
          delay(300);
         
        }
        level = keypad_input;
        // level += 1;
         go_down = false;
          Serial.println("Current Level is: ");
          Serial.println(level);
      }
      
      // Serial.println(keypad_input);
  
    }
  }
  
  else if (emergency == true){
    Serial.println("Emergency!");
    for(int i = 0; i < 30; i += 1){
      
      digitalWrite(emergency_buzzer, HIGH);
      delay(100);
      digitalWrite(emergency_buzzer, LOW);
      delay(100);
    }
    emergency = false;
    delay(3000);
    level = '0';
    
  }
  
}

