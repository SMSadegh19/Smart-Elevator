
long duration;
int distance;
    
const int trig = 6;
const int echo = 7;
   
    
void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT); 
  Serial.begin(9600); 
}
void loop() {
  distance = calculateDistance();
      
  delay(100);
  if (distance > 0 & distance < 10){
    Serial.println("Emergency!");
    Serial.println(distance); 
  }

}
int calculateDistance(){ 
  digitalWrite(trig, LOW); 
  delayMicroseconds(2);
  digitalWrite(trig, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH); 
  distance= duration*0.034/2;
  return distance;
}