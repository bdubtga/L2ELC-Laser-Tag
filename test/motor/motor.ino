int am1 = 4;       // a motor pin 1
int am2 = 3;       // a motor pin 2
int bm1 = 7;       // b motor pin 1
int bm2 = 8;       // b motor pin 2
int aspeed = 0;    // a motor speed
int aspeedpin = 5; // a motor speed pin
int bspeed = 0;    // b motor speed
int bspeedpin = 6; // b motor speed pin
char input;        // input from serial

void setup()
{
    pinMode(am1, OUTPUT);
    pinMode(am2, OUTPUT);
    pinMode(bm1, OUTPUT);
    pinMode(bm2, OUTPUT);
    pinMode(aspeedpin, OUTPUT);
    pinMode(bspeedpin, OUTPUT);
    Serial.begin(38400);
}

void loop() {
    aspeed = 255;
    bspeed = 255;
    analogWrite(aspeedpin, aspeed);
    analogWrite(bspeedpin, bspeed);
    digitalWrite(am1, HIGH);
    digitalWrite(am2, LOW);
    digitalWrite(bm1, HIGH);
    digitalWrite(bm2, LOW);
    Serial.println("Forward");
    Serial.println("Press any key to stop");
}