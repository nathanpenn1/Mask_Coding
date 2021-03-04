const byte ledPin = 13;
const byte interruptPinX = 2;
byte prevState = 0;
const byte WELCOME_SCREEN = 0;
const byte GRAPH_SCREEN = 1;
volatile byte state = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(interruptPinX, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPinX), blink, CHANGE);
}

void loop() {
  digitalWrite(ledPin, state);
  Serial.println(state);
  delay(1000);
////  if(state == prevState){ // simulating no button press
////    // do nothing
////  }
////  else{ // if button was pressed
//    if (state >= 1)
//    {
//      state = 0;
//    }
//    else
//    {
//      state = 1;
//    }
////  }
//  Serial.println(state);
//  delay(100);
//  prevState = state;
}

void blink() {
//  state = !state;
  changeState();
}

void changeState(){

  if(state == 0){
    state = 1;
  }
  else
  {
    state = 0;
  }
}
