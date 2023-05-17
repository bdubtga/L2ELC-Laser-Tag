#include <RF24.h> //librarys for rf nano
#include <RF24_config.h>
#include <nRF24L01.h>
#include <printf.h>

#include <Wire.h> //`Wire.h` is a library that allows you to communicate with I2C devices.
#include <LiquidCrystal_I2C.h> // for the lcd
const int J1X = A0;
const int J1Y = A1;
const int J1SW = A2;
const int J2X = A6;
const int J2Y = A7;
const int J2SW = A3;
const int BT1 = 8;
const int BT2 = 7;
const int BT3 = 6;
const int SW1 = 5;
const int SW2 = 4;
const int SW3 = 3;
const int LSR = 2;
const int datanum = 12;
int data[datanum];
RF24 SendRadio(9, 10);
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display


void setup()
{
  Serial.begin(115200); // Start serial communication. (115200 baud for RF-NANO)
  pinMode(J1X, INPUT);  // Set the pin modes for inputs.
  pinMode(J1Y, INPUT);
  pinMode(J1SW, INPUT_PULLUP); // Pullup resistor for switch
  pinMode(J2X, INPUT);
  pinMode(J2Y, INPUT);
  pinMode(J2SW, INPUT_PULLUP); // Pullup resistor for switch
  pinMode(BT1, INPUT_PULLUP);
  pinMode(BT2, INPUT_PULLUP);
  pinMode(BT3, INPUT_PULLUP);
  pinMode(SW1, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);
  pinMode(SW3, INPUT_PULLUP);
  pinMode(LSR, OUTPUT);
  SendRadio.begin(); //Start the nRF24L01+ module.
  SendRadio.setAddressWidth(5); //Set the address width to 5 bytes.
  SendRadio.openWritingPipe(0xF0F0F0F066LL); //Sends data on this 40-bit address
  SendRadio.setChannel(115);           //115 band above WIFI signals
  SendRadio.setPALevel(RF24_PA_MAX);   //Max to provide maximum range
  SendRadio.setDataRate(RF24_1MBPS) ;  //experiment with this to try get more range (lower = more range but less speed)
  SendRadio.stopListening(); //Stop Receiving and start transminitng
  lcd.init(); // initialize the lcd
  lcd.backlight();
}

void loop()
{
  data[0] = analogRead(J1X); // Read values form joysticks and put into array
  data[1] = analogRead(J1Y);
  data[2] = digitalRead(J1SW);
  data[3] = analogRead(J2X);
  data[4] = analogRead(J2Y);
  data[5] = digitalRead(J2SW);
  data[6] = digitalRead(BT1);
  data[7] = digitalRead(BT2);
  data[8] = digitalRead(BT3);
  data[9] = digitalRead(SW1);
  data[10] = digitalRead(SW2);
  data[11] = digitalRead(SW3);
  SendRadio.openWritingPipe(0xF0F0F0F066); //Sends data on this 40-bit address
  SendRadio.write(data, datanum * sizeof(int));; //Send the data array.
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
  if (data[9] == 0) {
    digitalWrite(LSR, HIGH);
  } else {
    digitalWrite(LSR, LOW);
  }
}
