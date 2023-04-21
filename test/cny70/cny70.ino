int pin = A5;
void setup() {
  Serial.begin(115200);
  pinMode(pin, INPUT);
}