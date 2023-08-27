//   ________  _______   ________         ___  ___          ___       __   ________  ___       ___       ___  ________      
//  |\   __  \|\  ___ \ |\   ___  \      |\  \|\  \        |\  \     |\  \|\   __  \|\  \     |\  \     |\  \|\   ____\     
//  \ \  \|\ /\ \   __/|\ \  \\ \  \     \ \  \ \  \       \ \  \    \ \  \ \  \|\  \ \  \    \ \  \    \ \  \ \  \___|_    
//   \ \   __  \ \  \_|/_\ \  \\ \  \  __ \ \  \ \  \       \ \  \  __\ \  \ \   __  \ \  \    \ \  \    \ \  \ \_____  \   
//    \ \  \|\  \ \  \_|\ \ \  \\ \  \|\  \\_\  \ \  \       \ \  \|\__\_\  \ \  \ \  \ \  \____\ \  \____\ \  \|____|\  \  
//     \ \_______\ \_______\ \__\\ \__\ \________\ \__\       \ \____________\ \__\ \__\ \_______\ \_______\ \__\____\_\  \ 
//      \|_______|\|_______|\|__| \|__|\|________|\|__|        \|____________|\|__|\|__|\|_______|\|_______|\|__|\_________\
//                                                                                                              \|_________|
#include <RF24.h> //librarys for rf nano
#include <RF24_config.h>
#include <nRF24L01.h>
#include <printf.h>
#include <Wire.h> //`Wire.h` is a library that allows you to communicate with I2C devices.
#include <LiquidCrystal_I2C.h> // for the lcd
int input;
const int datanum = 12;
int data[datanum];
RF24 SendRadio(9, 10);
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int b1 = 8;
int b2 = 7;
int b3 = 6;
int s1 = 5;
int s2 = 4;
int s3 = 3;
int j1x = A0;
int j1y = A1;
int j1sw = A2;
int j2x = A6;
int j2y = A7;
int j2sw = A3;


void setup()
{
  Serial.begin(115200); // Start serial communication. (115200 baud for RF-NANO)
  pinMode(b1, INPUT_PULLUP);
  pinMode(b2, INPUT_PULLUP);
  pinMode(b3, INPUT_PULLUP);
  pinMode(s1, INPUT_PULLUP);
  pinMode(s2, INPUT_PULLUP);
  pinMode(s3, INPUT_PULLUP);
  pinMode(j1x, INPUT);
  pinMode(j1y, INPUT);
  pinMode(j1sw, INPUT_PULLUP);
  pinMode(j2x, INPUT);
  pinMode(j2y, INPUT);
  pinMode(j2sw, INPUT_PULLUP);

  SendRadio.begin(); //Start the nRF24L01+ module.
  SendRadio.setAddressWidth(5); //Set the address width to 5 bytes.
  SendRadio.openWritingPipe(0xF0F0F0F066LL); //Sends data on this 40-bit address
  SendRadio.setChannel(115);           //115 band above WIFI signals
  SendRadio.setPALevel(RF24_PA_MAX);   //Max to provide maximum range
  SendRadio.setDataRate(RF24_1MBPS) ;  //experiment with this to try get more range (lower = more range but less speed)
  SendRadio.stopListening(); //Stop Receiving and start transminitng

}

void loop()
{
  data[0] = digitalRead(b1);
  data[1] = digitalRead(b2);
  data[2] = digitalRead(b3);
  data[3] = digitalRead(s1);
  data[4] = digitalRead(s2);
  data[5] = digitalRead(s3);
  data[6] = analogRead(j1x);
  data[7] = analogRead(j1y);
  data[8] = digitalRead(j1sw);
  data[9] = analogRead(j2x);
  data[10] = analogRead(j2y);
  data[11] = digitalRead(j2sw);
  SendRadio.openWritingPipe(0xF0F0F0F066); //Sends data on this 40-bit address
  SendRadio.write(data, datanum * sizeof(int));; //Send the data array.
  Serial.print(data[0]);
  Serial.print("  ");
  Serial.print(data[1]);
  Serial.print("  ");
  Serial.print(data[2]);
  Serial.print("  ");
  Serial.print(data[3]);
  Serial.print("  ");
  Serial.print(data[4]);
  Serial.print("  ");
  Serial.print(data[5]);
  Serial.print("  ");
  Serial.print(data[6]);
  Serial.print("  ");
  Serial.print(data[7]);
  Serial.print("  ");
  Serial.print(data[8]);
  Serial.print("  ");
  Serial.print(data[9]);
  Serial.print("  ");
  Serial.print(data[10]);
  Serial.print("  ");
  Serial.print(data[11]);
  Serial.println("  ");
}
