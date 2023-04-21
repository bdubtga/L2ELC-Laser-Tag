#include <SPI.h> //`SPI.h` is a library that allows you to communicate with SPI devices.
#include <Wire.h> //`Wire.h` is a library that allows you to communicate with I2C devices.
#include <LiquidCrystal_I2C.h> // for the lcd
const int J1X = A0; //Pin definitions for the joysticks.
const int J1Y = A1;
const int J1SW = A2;
const int J2X = A6;
const int J2Y = A7;
const int J2SW = A3;
const int datanum = 6; //Number of data points in array.
int data[datanum]; //Array to store data.
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  Serial.begin(9600); //Start serial communication. (115200 baud for RF-NAN)
  pinMode(J1X, INPUT); //Set the pin modes for the joysticks.
  pinMode(J1Y, INPUT);
  pinMode(J1SW, INPUT);
  pinMode(J2X, INPUT);
  pinMode(J2Y, INPUT);
  pinMode(J2SW, INPUT);
  delay(500); //Delay to let nRF24L01+ module initialize.
  lcd.init();                      // initialize the lcd
  lcd.backlight();
}

void loop() {
  data[0] = analogRead(J1X); // Read values form joysticks and put into array
  data[1] = analogRead(J1Y);
  data[2] = analogRead(J1SW);
  data[3] = analogRead(J2X);
  data[4] = analogRead(J2Y);
  data[5] = analogRead(J2SW);
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
  lcd.setCursor(0,0);
  lcd.print("J1X: ");
  lcd.print(data[0]);
  lcd.setCursor(0,1);
  lcd.print("J1Y: ");
  lcd.print(data[1]);
  lcd.setCursor(0,2);
  lcd.print("J1SW: ");
  lcd.print(data[2]);
  lcd.setCursor(10,0);
  lcd.print("J2X: ");
  lcd.print(data[3]);
  lcd.setCursor(10,1);
  lcd.print("J2Y: ");
  lcd.print(data[4]);
  lcd.setCursor(10,2);
  lcd.print("J2SW: ");
  lcd.print(data[5]); 
  delay(100); //Delay to allow the lcd to update.
  lcd.clear();
}
