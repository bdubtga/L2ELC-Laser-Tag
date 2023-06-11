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


void setup()
{
  Serial.begin(115200); // Start serial communication. (115200 baud for RF-NANO)

  pinMode(3, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(A3, INPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);

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
  data[0] = (analogRead(A3)/4);
  data[1] = digitalRead(5);
  data[3] = analogRead(A3)/4;
  data[5] = digitalRead(3);
  SendRadio.openWritingPipe(0xF0F0F0F066); //Sends data on this 40-bit address
  SendRadio.write(data, datanum * sizeof(int));; //Send the data array.
  Serial.print(data[0]);
  Serial.print("  ");
  Serial.print(data[1]);
  Serial.print("  ");
  Serial.print(data[3]);
  Serial.print("  ");
  Serial.println(data[5]);
}
