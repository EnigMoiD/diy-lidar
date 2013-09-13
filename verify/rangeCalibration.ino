const int analogInPin = A0;
const int analogOutPin = 9;

long currentMillis = 0;

int sensorValue = 0;
int outputValue = 0;

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

  Serial.println("Data points");
  Serial.println("--------------------");
  for (int i = 0; i < count; i ++) {
    sensorValue = analogRead(analogInPin);

    total += sensorValue;

    Serial.println(sensorValue);

    delay(2);
  }
  Serial.println("Average");
  Serial.println("--------------------");
  Serial.println(total/count);
  Serial.println("====================");
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