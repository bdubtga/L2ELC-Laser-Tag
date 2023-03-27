#include <SPI.h> //`SPI.h` is a library that allows you to communicate with SPI devices.
#include <Wire.h> //`Wire.h` is a library that allows you to communicate with I2C devices.
#include "RF24.h" //`RF24.h` is a library that allows you to communicate with nRF24L01+ modules.
RF24 SendRadio(9, 10); //Pin definitions for the nRF24L01+ module.
const int J1X = A2; //Pin definitions for the joysticks.
const int J1Y = A1;
const int J1SW = A0;
const int J2X = A5;
const int J2Y = A4;
const int J2SW = A3;
const int datanum = 6; //Number of data points in array.
int data[datanum]; //Array to store data.

void setup() {
  Serial.begin(115200); //Start serial communication. (115200 baud for RF-NAN)
  SendRadio.begin(); //Start the nRF24L01+ module.
  SendRadio.setAddressWidth(5); //Set the address width to 5 bytes.
  SendRadio.openWritingPipe(0xF0F0F0F066LL); //Sends data on this 40-bit address
  SendRadio.setChannel(115);           //115 band above WIFI signals
  SendRadio.setPALevel(RF24_PA_MAX);   //Max to provide maximum range
  SendRadio.setDataRate(RF24_1MBPS) ;  //experiment with this to try get more range (lower = more range but less speed)
  SendRadio.stopListening(); //Stop Receiving and start transminitng
  SendRadio.printDetails(); //Prints randio details for debugging
  pinMode(J1X, INPUT); //Set the pin modes for the joysticks.
  pinMode(J1Y, INPUT);
  pinMode(J1SW, INPUT);
  pinMode(J2X, INPUT);
  pinMode(J2Y, INPUT);
  pinMode(J2SW, INPUT);
  delay(500); //Delay to let nRF24L01+ module initialize.
}

void loop() {
  data[0] = analogRead(J1X); // Read values form joysticks and put into array
  data[1] = analogRead(J1Y);
  data[2] = analogRead(J1SW);
  data[3] = analogRead(J2X);
  data[4] = analogRead(J2Y);
  data[5] = analogRead(J2SW);




  // can this be removed? because its in setup (try with arduino)
  SendRadio.openWritingPipe(0xF0F0F0F066); //Sends data on this 40-bit address
  SendRadio.write(data, datanum * sizeof(int));; //Send the data array.
  Serial.print(data[0]); //Print the data to the serial monitor for debugging.
  Serial.print(" ");
  Serial.print(data[1]);
  Serial.print(" ");
  Serial.print(data[2]);
  Serial.print(" ");
  Serial.print(data[3]);
  Serial.print(" ");
  Serial.print(data[4]); 
  Serial.print(" ");
  Serial.println(data[5]);
  delay(100); //Delay to prevent flooding the serial monitor. (remove this for final version)
}
