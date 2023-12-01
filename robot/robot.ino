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
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#define PIN A2      // On Trinket or Gemma, suggest changing this to 1
#define NUMPIXELS 6 // Popular NeoPixel ring size
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 500    // Time (in milliseconds) to pause between pixels
const int datanum = 12; // Number of data points in array.
int data[datanum];      // Array to store data/
RF24 ReceiveRadio(9, 10);
int pin_pwma = 5;
int pin_pwmb = 6;
int pin_ain1 = 4;
int pin_ain2 = 2;
int pin_bin1 = 7;
int pin_bin2 = 8;
int pin_laser = A3;
int pin_servotilt = A5;
int pin_servopan = A4;
int deadzone = 50;
int ltrim = 0;
int rtrim = 0;
int val_servotilt = 1500;
int sensor_pin = A7;
int lives = 5;
int drive = true;

Servo servotilt;

void setup()
{
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  pixels.begin();       // INITIALIZE NeoPixel strip object (REQUIRED)
  Serial.begin(115200); // Start serial monitor (115200 for RF Nano)
  // Configure and start RF radio
  ReceiveRadio.begin();
  ReceiveRadio.setAddressWidth(5);
  ReceiveRadio.openReadingPipe(1, 0xF0F0F0F066LL);
  ReceiveRadio.setChannel(115);         // 115 band above WIFI signals
  ReceiveRadio.setPALevel(RF24_PA_MAX); // Max to provide maximum range
  ReceiveRadio.setDataRate(RF24_1MBPS); // experiment with this to try get more range
  ReceiveRadio.startListening();        // Changes RF module to recieve mode
  pinMode(pin_pwma, OUTPUT);
  pinMode(pin_pwmb, OUTPUT);
  pinMode(pin_ain1, OUTPUT);
  pinMode(pin_ain2, OUTPUT);
  pinMode(pin_bin1, OUTPUT);
  pinMode(pin_bin2, OUTPUT);
  pinMode(sensor_pin, INPUT);
  digitalWrite(pin_ain1, LOW);
  digitalWrite(pin_ain2, LOW);
  digitalWrite(pin_bin1, LOW);
  digitalWrite(pin_bin2, LOW);
  analogWrite(pin_pwma, 0);
  analogWrite(pin_pwmb, 0);
  pinMode(pin_laser, OUTPUT);
  servotilt.attach(A4);
  servotilt.write(1000);
  servotilt.detach();
  pixels.clear();
  pixels.setPixelColor(0, pixels.Color(255, 0, 0));
  pixels.setPixelColor(1, pixels.Color(255, 0, 0));
  pixels.setPixelColor(2, pixels.Color(0, 255, 0));
  pixels.setPixelColor(3, pixels.Color(0, 255, 0));
  pixels.setPixelColor(4, pixels.Color(0, 0, 255));
  pixels.setPixelColor(5, pixels.Color(0, 0, 255));
  pixels.show();
  delay(1000);
  pixels.clear();
  pixels.show();
}

void loop()
{
  if (data[1] == 0)
  {
    servotilt.attach(A4);
  }
  else
  {
    servotilt.detach();
  }
  if (ReceiveRadio.available())
  {
    ReceiveRadio.read(data, datanum * sizeof(int));
    if (data[5] == 1)

    {
      if (data[1] == 1)
      {
        if (drive == true) {
          if (data[6] < (535 - deadzone))
          {
            digitalWrite(pin_ain1, LOW);  // Changed to LOW
            digitalWrite(pin_ain2, HIGH); // Changed to HIGH
            // fucntion to set speed 0-255
            analogWrite(pin_pwma, map(data[6], 0, 512, 255, 0));
            Serial.print(map(data[6], 0, 512, 255, 0));
          }
          else if (data[6] > (535 + deadzone))
          {
            digitalWrite(pin_ain1, HIGH); // Changed to HIGH
            digitalWrite(pin_ain2, LOW);  // Changed to LOW
            // fucntion to set speed 0-255
            analogWrite(pin_pwma, map(data[6], 512, 1023, 0, 255));
            Serial.print(map(data[6], 512, 1023, 0, 255));
          }
          else
          {
            digitalWrite(pin_ain1, LOW); // Changed to LOW
            digitalWrite(pin_ain2, LOW); // Changed to LOW
          }
        // j2
          if (data[9] < (521 - deadzone))
          {
            digitalWrite(pin_bin1, LOW);  // Changed to LOW
            digitalWrite(pin_bin2, HIGH); // Changed to HIGH
            // fucntion to set speed 0-255
            analogWrite(pin_pwmb, map(data[9], 0, 512, 255, 0));
            Serial.print(map(data[9], 0, 512, 255, 0));
          }
          else if (data[9] > (521 + deadzone))
          {
            digitalWrite(pin_bin1, HIGH); // Changed to HIGH
            digitalWrite(pin_bin2, LOW);  // Changed to LOW
            // fucntion to set speed 0-255
            analogWrite(pin_pwmb, map(data[9], 512, 1023, 0, 255));
            Serial.print(map(data[9], 512, 1023, 0, 255));
          }
          else
          {
            digitalWrite(pin_bin1, LOW); // Changed to LOW
            digitalWrite(pin_bin2, LOW); // Changed to LOW
          }
        }
      }
      else
      {
        // code to move laser
        if (data[6] < (535 - deadzone))
        {
          val_servotilt = val_servotilt + 1;
          servotilt.write(val_servotilt);
          if (data[3] == 1)
          {
            delay(100);
          }
        }
        else if (data[6] > (535 + deadzone))
        {
          val_servotilt = val_servotilt - 1;
          servotilt.write(val_servotilt);

          if (data[3] == 1)
          {
            delay(100);
          }
        }
        else
        {
        }
        if (data[7] < (521 - deadzone))
        {
          // use motors to turn left slowly
          analogWrite(pin_pwmb, 50);
          digitalWrite(pin_bin1, HIGH);
          digitalWrite(pin_bin2, LOW);
          analogWrite(pin_pwma, 50);
          digitalWrite(pin_ain1, LOW);
          digitalWrite(pin_ain2, HIGH);
        }
        else if (data[7] > (521 + deadzone))
        {
          // use motors to turn right slowly
          analogWrite(pin_pwma, 50);
          digitalWrite(pin_ain1, HIGH);
          digitalWrite(pin_ain2, LOW);
          analogWrite(pin_pwmb, 50);
          digitalWrite(pin_bin1, LOW);
          digitalWrite(pin_bin2, HIGH);
        }
        else
        {
          // stop motors
          analogWrite(pin_pwma, 0);
          digitalWrite(pin_ain1, LOW);
          digitalWrite(pin_ain2, LOW);
          analogWrite(pin_pwmb, 0);
          digitalWrite(pin_bin1, LOW);
          digitalWrite(pin_bin2, LOW);
        }
      }
    }
    if (data[4] == 1)
    {
      digitalWrite(pin_laser, HIGH);
    }
    else
    {
      digitalWrite(pin_laser, LOW);
    }
  }
  // code to track lives
  int sensor_value = analogRead(sensor_pin);
  if (sensor_value > 400)
  {
    lives = lives - 1;
    Serial.println(lives);
    delay(500);
  }
  if (data[1] == 1) {
    if (lives > 0)
  {
    for (int i = lives; i > 0; i--)
    {
      pixels.setPixelColor(lives + 1, pixels.Color(0, 0, 0));
      pixels.setPixelColor(i, pixels.Color(255, 255, 255));
      pixels.show();
    }
  }
  else
  {
    pixels.clear();
    for (int i = 0; i < 6; i++)
    {
      pixels.setPixelColor(i, pixels.Color(255, 0, 0));
    }

    pixels.show();
    drive = false;
    analogWrite(pin_pwma, 0);
    digitalWrite(pin_ain1, LOW);
    digitalWrite(pin_ain2, LOW);
    analogWrite(pin_pwmb, 0);
    digitalWrite(pin_bin1, LOW);
    digitalWrite(pin_bin2, LOW);
  }
  }
}
