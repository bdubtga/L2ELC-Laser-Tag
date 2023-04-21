#include <SPI.h>
#include <Wire.h>
#include "RF24.h"
#include "printf.h"
#include <LiquidCrystal_I2C.h> // for the lcd
RF24 ReceiveRadio (9, 10);
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display


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
  lcd.init(); // initialize the lcd
  lcd.backlight();
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
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Mode: ");
    lcd.print(data[9]);
  }
}
