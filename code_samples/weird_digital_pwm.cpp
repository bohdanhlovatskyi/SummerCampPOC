const byte ledPin = 5;// the number of the LED pin

byte ledState = LOW;             
unsigned long previousMillis = 0;     

unsigned long intervalOn[5] = {100, 200, 300, 350, 399};    
unsigned long interval = 500; 

void setup() {
  pinMode(ledPin, OUTPUT); 
}

void loop() {

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {      
        digitalWrite(ledPin, 1);
        delay(intervalOn[i]);
        digitalWrite(ledPin, 0);
        delay(500 - intervalOn[i]);
    }
    digitalWrite(ledPin, 0);
    delay(2000);
  }
}

