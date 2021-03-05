const int ledPin =  9;
int ledstate = LOW;

int fadevalue;
int pwm;
int x;

unsigned long previousMillis = 0;
long interval = 1000;

String palavra;
String a;


void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  while (Serial.available() == 0);
  palavra = Serial.readStringUntil('\n');

  //#############parse da string##############

  if (palavra.startsWith("led")) {
    a = palavra.substring(4);
    if (a == "on") {
      ledstate = 255;
      Serial.println("Led ON");
    }
    if (a == "off") {
      ledstate = 0;
      Serial.println("Led OFF");
    }
    if (a == "") {
      Serial.println("input error");
    }
    if ((a != "on") && (a != "off") && (a != "")) {
      x = a.toInt();
      x = long(x);
      if (x < 0 || 100 < x) {
        Serial.println("pwm value error");
      }
      else {
        pwm = x;
        fadevalue = map(pwm, 0, 100, 0, 255);
        Serial.println("Led fading at:");
        Serial.print("pwm value (%): ");
        Serial.print(pwm);
        Serial.print(", fade value(0-255): ");
        Serial.println(fadevalue);
        ledstate = fadevalue;
      }
    }
  }
  else {
    Serial.println("input error");
  }
  analogWrite(ledPin, ledstate);
}
