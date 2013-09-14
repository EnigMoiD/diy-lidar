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

void setup() {
  Serial.begin(9600);

  pinMode(buttonPin, INPUT);
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
  Serial.print(total/count);
  Serial.println(" cm");
  dataCount++;
}

void loop() { 
  currentMillis = millis();

  lastButtonState = buttonState;
  buttonState = digitalRead(buttonPin);

  if (lastButtonState != buttonState) {
    if (lastButtonState == LOW && buttonState == HIGH) {
      buttonTime = millis();
    }
    else if (lastButtonState == HIGH && buttonState == LOW) {
      unsigned long delta = currentMillis - buttonTime;

      if (delta > 50) {
        outputData(10);
      }
    }
  }
}