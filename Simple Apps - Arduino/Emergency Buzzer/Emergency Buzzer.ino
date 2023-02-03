
const int emergency_buzzer = 10;
void setup() {
  Serial.begin(115200);
  pinMode(emergency_buzzer, OUTPUT);
}

void loop() {
  digitalWrite(emergency_buzzer, HIGH);
  delay(100);
  digitalWrite(emergency_buzzer, LOW);
  delay(100);
}
