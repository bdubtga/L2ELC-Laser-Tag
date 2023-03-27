#include <SPI.h> //`SPI.h` is a library that allows you to communicate with SPI devices.
#include <Wire.h> //`Wire.h` is a library that allows you to communicate with I2C devices.
#include "RF24.h" //`RF24.h` is a library that allows you to communicate with nRF24L01+ modules.
RF24 ReceiveRadio (9, 10); //Pin definitions for the nRF24L01+ module.
const int datanum = 6; //Number of data points in array.
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
  ReceiveRadio.printDetails(); //Prints details of RF module for debugging
  delay(500); //Delay to let nRF24L01+ module initialize.
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
    Serial.println(data[5]);
  }
}
