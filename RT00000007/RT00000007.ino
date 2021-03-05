String palavra;
String a;
String b;
String tempo;
int x;
int err;
const int ledPin =  LED_BUILTIN;// the number of the LED pin

// Variables will change:
int ledstate = LOW;             // ledstate used to set the LED

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated


long interval = 1000;

void setup() {
  // set the digital pin as output:
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  while (Serial.available() == 0);
  palavra = Serial.readStringUntil('\n');
  if (palavra == "led on")
  {
    ledstate = HIGH;
    Serial.println("Led ON");
  }
  if (palavra == "led off")
  {
    ledstate = LOW;
    Serial.println("Led OFF");
  }
  digitalWrite(ledPin, ledstate);
  // ################# blink ######################
  if (palavra.startsWith("led blink")) {
    tempo = palavra.substring(10);
    x = tempo.toInt();
    interval = long(x);
    if (interval < 100 || 2000 < interval) {
      Serial.println("erro");
    }
    else {
      Serial.print("Led blinking at ");
      Serial.print(interval);
      Serial.println(" ms.");
      while (1) {
        unsigned long currentMillis = millis();
        if (currentMillis - previousMillis >= interval) {
          // save the last time you blinked the LED
          previousMillis = currentMillis;

          // if the LED is off turn it on and vice-versa:
          if (ledstate == LOW) {
            ledstate = HIGH;
          } else {
            ledstate = LOW;
          }

          // set the LED with the ledstate of the variable:
          digitalWrite(ledPin, ledstate);
        }
        if (Serial.available() > 0) {
          a = Serial.readStringUntil('\n');
          //Serial.println(a);
          if (a == "led on") {
            ledstate = HIGH;
            Serial.println("Led ON");
            break;
          }
          if (a == "led off") {
            ledstate = LOW;
            Serial.println("Led OFF");
            break;

          }
        }
      }
    }
  }
  digitalWrite(ledPin, ledstate);
}




//led blink 500
//if ((a == "led on") || (a == "led off"))
