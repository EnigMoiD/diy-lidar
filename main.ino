#include <Servo.h>

// Servo variables
const int servoCount = 2;
Servo servos[servoCount];

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

float processedRange() {
	int raw = analogRead(analogInPin);
	float retRange = 0;
	for (int i = 0; i < termCount; i++) {
		retRange += ps[i]*pow(raw, termCount-1-i);
	}
	return retRange;
}

float averagedRange(int count) {
	float total = 0;

	for (int i = 0; i < count; i ++) {
		float sensorValue = processedRange();

		total += sensorValue;

		delay(2);
	}

	return total/count;
}

void printPoint(float R, float phi, float theta) {
	// Radius
	Serial.println(R);
	// Servo 0 phi
	Serial.println(phi);
	// Servo 1 theta
	Serial.println(theta);
}

void setup() {
	for (int i = 0; i < servoCount; i++) {
		Servo servo;
		servos[i] = servo;
		servo.attach((i*2)+9);
	}

	setupServo();

	// Setup range
	Serial.begin(9600);

	pinMode(buttonPin, INPUT);
}

void loop() {
	loopServo();
}

void setupServo() {
	servos[0].write(10);
	servos[1].write(55);
	delay(1000);
}

void loopServo() {
	for(int phi = 10; phi < 70; phi += 2) {
		servos[0].write(phi);
		servos[1].write(55);
		delay(300);
		for(int theta = 55; theta < 110; theta += 1) {
			servos[1].write(theta);
			delay(100);
			printPoint(averagedRange(10), phi, theta);
			delay(50);
		}
	}
}