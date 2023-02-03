
const int emergency_light = 10;
void setup() {
  Serial.begin(115200);
  pinMode(emergency_light, OUTPUT);
}

void loop() {
  digitalWrite(emergency_light, HIGH);
  delay(2000);
  digitalWrite(emergency_light, LOW);
  delay(2000);
}
