#include <Servo.h>

// Servo variables
const int servoCount = 1;
Servo servos[servoCount];

int pos = 0;

// Range variables
const int analogInPin = A0;

long currentMillis = 0;

int dataCount = 0;

// Button stuff
int lastButtonState = 0;
int buttonState = 0;
int buttonPin = 8;
long buttonTime = 0;

// Data processing
// y = p1*x^4 + p2*x^3 + p3*x^2 + p4*x + p5 

// Coefficients
const int termCount = 5;
float ps[termCount] = {6.1135*pow(10, -9), -1.0478e-05, 0.006638, -1.9374, 259.27};

void establishContact() {
  // Serial.println('A');   // send a capital A
  // delay(300);
}

float processedRange() {
  int raw = analogRead(analogInPin);
  float retRange = 0;
  for (int i = 0; i < termCount; i++) {
    retRange += ps[i]*pow(raw, termCount-1-i);
  }
  return retRange;
}

void outputData(int count) {
  float total = 0;

  for (int i = 0; i < count; i ++) {
    float sensorValue = processedRange();

    total += sensorValue;

    delay(2);
  }
  Serial.println(total/count);
  dataCount++;
}

void setup()
{
  for (int i = 0; i < servoCount; i++) {
    Servo servo;
    servos[i] = servo;
    servo.attach((i*2)+9);
  }

  // Setup range
  Serial.begin(9600);
  establishContact();

  pinMode(buttonPin, INPUT);
}

void loop() {
	loopServo();
}

void loopServo() {
  for(pos = 0; pos < 180; pos += 1) {
    for (int i = 0; i < servoCount; i++) {
      servos[i].write(pos);
      outputData(10);
    }
    delay(15);
  }
  for(pos = 180; pos>=1; pos-=1) {
    for (int i = 0; i < servoCount; i++) {
      servos[i].write(pos);
      outputData(10);
    }
    delay(15);
  }
}