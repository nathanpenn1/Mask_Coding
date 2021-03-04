const byte ledPin = 13;
const byte interruptPinX = 2;
volatile byte state = HIGH;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(interruptPinX, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPinX), blink, CHANGE);
}

void loop() {
  digitalWrite(ledPin, state);
}

void blink() {
  state = !state;
}
