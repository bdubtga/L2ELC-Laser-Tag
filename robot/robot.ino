//   ________  _______   ________         ___  ___          ___       __   ________  ___       ___       ___  ________      
//  |\   __  \|\  ___ \ |\   ___  \      |\  \|\  \        |\  \     |\  \|\   __  \|\  \     |\  \     |\  \|\   ____\     
//  \ \  \|\ /\ \   __/|\ \  \\ \  \     \ \  \ \  \       \ \  \    \ \  \ \  \|\  \ \  \    \ \  \    \ \  \ \  \___|_    
//   \ \   __  \ \  \_|/_\ \  \\ \  \  __ \ \  \ \  \       \ \  \  __\ \  \ \   __  \ \  \    \ \  \    \ \  \ \_____  \   
//    \ \  \|\  \ \  \_|\ \ \  \\ \  \|\  \\_\  \ \  \       \ \  \|\__\_\  \ \  \ \  \ \  \____\ \  \____\ \  \|____|\  \  
//     \ \_______\ \_______\ \__\\ \__\ \________\ \__\       \ \____________\ \__\ \__\ \_______\ \_______\ \__\____\_\  \ 
//      \|_______|\|_______|\|__| \|__|\|________|\|__|        \|____________|\|__|\|__|\|_______|\|_______|\|__|\_________\
//                                                                                                              \|_________|
#include <SPI.h>
#include <Wire.h>
#include "RF24.h"
#include "printf.h"
#include <Servo.h>
const int datanum = 12; //Number of data points in array.
int data[datanum]; //Array to store data/
RF24 ReceiveRadio (9, 10);
int pin_pwma = 5;
int pin_pwmb = 6;
int pin_ain1 = 4;
int pin_ain2 = 2;
int pin_bin1 = 7;
int pin_bin2 = 8;
int pin_laser = A3;
int pin_servotilt = A5;
int pin_servopan = A4;

Servo servotilt;
Servo servopan;

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
  pinMode(pin_pwma, OUTPUT);
  pinMode(pin_pwmb, OUTPUT);
  pinMode(pin_ain1, OUTPUT);
  pinMode(pin_ain2, OUTPUT);
  pinMode(pin_bin1, OUTPUT);
  pinMode(pin_bin2, OUTPUT);
  digitalWrite(pin_ain1, LOW);
  digitalWrite(pin_ain2, LOW);
  digitalWrite(pin_bin1, LOW);
  digitalWrite(pin_bin2, LOW);
  analogWrite(pin_pwma, 0);
  analogWrite(pin_pwmb, 0);
  pinMode(pin_laser, OUTPUT);
  servopan.attach(A4);
  servotilt.attach(A5);
  servopan.write(1500);
  servotilt.write(1500);
}

void loop() {
    if (ReceiveRadio.available()) {
    ReceiveRadio.read(data, datanum * sizeof(int));
    analogWrite(pin_pwma, data[0]);
    digitalWrite(pin_ain1, data[1]);
    digitalWrite(pin_ain2, data[2]);
    analogWrite(pin_pwmb, data[3]);
    digitalWrite(pin_bin1, data[4]);
    digitalWrite(pin_bin2, data[5]);
    digitalWrite(pin_laser, data[6]);
    servotilt.write(data[7]);
    servopan.write(data[8]);
  }
}
