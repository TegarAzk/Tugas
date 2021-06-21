const byte buttonPin = 2;
const byte ledPin = 13;
int ledState = LOW;
int ledOn = LOW;
int lastButton;
int currentButton;

void setup() {
  Serial.begin(9600);
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
  if(ledOn == HIGH) {
    ledState = !ledState;
  }
  else{
    ledState = LOW;  
  }
  digitalWrite(ledPin, ledState);
}
