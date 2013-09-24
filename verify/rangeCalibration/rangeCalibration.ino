const int analogInPin = A0;

long currentMillis = 0;

int dataCount = 0;

// Button stuff
int lastButtonState = 0;
int buttonState = 0;
int buttonPin = 8;
long buttonTime = 0;

void setup() {
  Serial.begin(9600);

  pinMode(buttonPin, INPUT); 
}

void outputData(int count) {
  int total = 0;

  for (int i = 0; i < count; i ++) {
    int sensorValue = analogRead(analogInPin);

    total += sensorValue;

    Serial.println(sensorValue);

    delay(2);
  }
  Serial.println(dataCount);
  Serial.println(total/count);
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