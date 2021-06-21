#include <TimerOne.h>

const byte buttonPin = 2;
const byte IntPin = 7;
const byte ledPin = 13;
int ledState = LOW;
int ledOn= LOW;
int lastButton;
int currentButton;
int count = 0;

void setup() {
  pinMode(IntPin, INPUT_PULLUP);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  Timer1.initialize(500000);
  Timer1.attachInterrupt(Intrupt);
  currentButton = digitalRead(buttonPin);
}

void loop() {
  
}

void Intrupt() {
  count++;
  if(count == 2) {
    if(digitalRead(IntPin) == HIGH) {
      blink();
    }
    count = 0;
  }
  digitalWrite(ledPin, ledState);
}


void blink() {
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
}
