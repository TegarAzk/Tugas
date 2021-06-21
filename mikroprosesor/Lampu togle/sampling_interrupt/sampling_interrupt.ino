#include <TimerOne.h>

const byte buttonPin = 2;
const byte ledPin = 13;
int ledState = LOW;
int ledOn = LOW;
int lastButton;
int currentButton;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(blink); // blinkLED to run every 1 seconds
}

void loop() {
  
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
  digitalWrite(ledPin, ledState);
}
