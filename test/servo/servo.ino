#include <SPI.h>
#include <Wire.h>
#include "RF24.h"
#include "printf.h"
#include <Servo.h>
RF24 ReceiveRadio (9, 10);
Servo servo1;
Servo servo2;


const int datanum = 12; //Number of data points in array.
int data[datanum]; //Array to store data/

void setup() {
  Serial.begin(115200); //Start serial monitor (115200 for RF Nano)
  // Configure and start RF radio
  ReceiveRadio.begin();
  ReceiveRadio.setAddressWidth(5);
  ReceiveRadio.openReadingPipe(1, 0xF0F0F0F066LL);
  ReceiveRadio.setChannel(115);  //115 band above WIFI signals
  ReceiveRadio.setPALevel(RF24_PA_MAX); //Max to provide maximum range
  ReceiveRadio.setDataRate(RF24_1MBPS) ;  //experiment with this to try get more range
  ReceiveRadio.startListening(); //Changes RF module to recieve mode
    pinMode(5, OUTPUT);
    Serial.begin(115200);
    servo1.attach(9);
    servo2.attach(10);
    servo1.write(0);
    servo2.write(0);
}
int servo1pos = 0;
int servo2pos = 0;
int servoupdate() {
    servo1pos = data[0];
    servo2pos = data[1];
    servo1.write(servo1pos);
    servo2.write(servo2pos);
}

void loop() {
    if (ReceiveRadio.available()) {
    ReceiveRadio.read(data, datanum * sizeof(int));
    Serial.print(data[0]);
    Serial.print(" ");
    Serial.print(data[1]);
    Serial.print(" ");
    Serial.print(data[2]);
    Serial.print(" ");
    Serial.print(data[3]);
    Serial.print(" ");
    Serial.print(data[4]);
    Serial.print(" ");
    Serial.print(data[5]);
    Serial.print(" ");
    Serial.print(data[6]);
    Serial.print(" ");
    Serial.print(data[7]);
    Serial.print(" ");
    Serial.print(data[8]);
    Serial.print(" ");
    Serial.print(data[9]);
    Serial.print(" ");
    Serial.print(data[10]);
    Serial.print(" ");
    Serial.print(data[11]);
    Serial.println(" ");
  }
}
