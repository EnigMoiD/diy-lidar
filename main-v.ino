#include <Servo.h>

// Servo variables
const int servoCount = 1;
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

void printPoint(float R, float theta) {
	// Radius
	Serial.println(R);
	// Servo 0 theta
	Serial.println(theta);
}

void setup() {
	for (int i = 0; i < servoCount; i++) {
		Servo servo;
		servos[i] = servo;
		servo.attach((i*2)+11);
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
	servos[0].write(0);
	delay(1000);
}

void loopServo() {
	for(int theta = 45; theta < 90; theta += 1) {
		servos[0].write(theta);
		delay(400);
		printPoint(averagedRange(10), theta);
		delay(200);
	}
}