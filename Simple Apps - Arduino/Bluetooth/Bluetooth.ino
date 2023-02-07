

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


 
void setup() {  
Serial.begin(9600);  
}  

void loop() {  
  int answer = return_bluetooth();
  if (answer != -1){
    Serial.println(char(answer));
  }
}  