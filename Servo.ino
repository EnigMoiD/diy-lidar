// Sweep
// by BARRAGAN <http://barraganstudio.com>
// This example code is in the public domain.


#include <Servo.h>

const int servoCount = 2;
Servo servos[servoCount];  // create servo object to control a servo
                // a maximum of eight servo objects can be created

int pos = 0;    // variable to store the servo position

void setup()
{
  for (int i = 0; i < servoCount; i++) {
    Servo servo;
    servos[i] = servo;
    servo.attach((i*2)+9);
  }
}

void loop()
{
  for(pos = 0; pos < 180; pos += 1) {
    for (int i = 0; i < servoCount; i++) {
      servos[i].write(pos);
    }
    delay(15);
  }
  for(pos = 180; pos>=1; pos-=1) {
    for (int i = 0; i < servoCount; i++) {
      servos[i].write(pos);
    }
    delay(15);
  }
}