
// long duration;
// int distance;
    
const int trig = 12;
const int echo = 11;

 #include <NewPing.h>  
    
// void setup() {
//   pinMode(trig, OUTPUT);
//   pinMode(echo, INPUT); 
//   Serial.begin(9600); 
// }
// void loop() {
//   distance = calculateDistance();
      
//   delay(100);
  
//     Serial.println(distance); 

// }
// int calculateDistance(){ 
//   digitalWrite(trig, LOW); 
//   delayMicroseconds(2);
//   digitalWrite(trig, HIGH); 
//   delayMicroseconds(10);
//   digitalWrite(trig, LOW);
//   duration = pulseIn(echo, HIGH); 
//   distance= duration*0.034/2;
//   return distance;
// }

NewPing sonar (trig, echo, 100);// create ultrasonic object with the following parameters (Trig=3, Echo=2, Max distance=400cm)
float distance;// initialize a variable of type float
void setup() {
Serial.begin (9600);// initialize serial communication at 9600 bits per second
}
void loop() {
distance = sonar.ping_cm();// putting the measured value in distance
Serial.print("Distance= ");// print "Distance"
Serial.print(distance);// print the value of the distance
Serial.println(" cm");// print "cm"
delay(100);// wait half a second
}