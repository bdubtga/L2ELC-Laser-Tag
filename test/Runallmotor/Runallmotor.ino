/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 https://www.arduino.cc/en/Tutorial/LibraryExamples/Sweep
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
Servo myservo2;
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(A4);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(A5);

  pinMode(5, OUTPUT); // writes to max speed for both wheels
  analogWrite(5, 255);
  pinMode(6, OUTPUT);
  analogWrite(6, 255);

  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);

  pinMode(7, OUTPUT); 
  pinMode(8, OUTPUT);


}

void loop() {

  digitalWrite(2, HIGH);
  digitalWrite(4, LOW);

  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);

  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }

  digitalWrite(2, LOW);
  digitalWrite(4, HIGH);
  
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);

  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
}
