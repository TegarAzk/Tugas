const byte buttonPin = 2;
const byte ledPin = 13;
int ledState = LOW;
int ledOn = LOW;
int lastButton;
int currentButton;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  currentButton = digitalRead(buttonPin);
}

void loop() {
  lastButton    = currentButton;
  currentButton = digitalRead(buttonPin);
  if(lastButton == HIGH && currentButton == LOW) {
    ledOn = !ledOn;
  }
  while(ledOn == HIGH) {
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
    delay(1000);
    
    lastButton    = currentButton;
    currentButton = digitalRead(buttonPin);
    if(lastButton == HIGH && currentButton == LOW) {
      ledOn = !ledOn;
    }    
  }
}
