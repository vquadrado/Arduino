const int ledPin =  9;
int ledstate = LOW;

int fadevalue;
int pwm;
int x;
int y;

String palavra;
String a;
String b;

unsigned long time_now = 0;


void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  while (Serial.available() == 0);
  palavra = Serial.readStringUntil('\n');


  //#############parse da string##############
  if (palavra.startsWith("led fade")) {
    a = palavra.substring(9, 12);
    b = palavra.substring(13);
    x = long(a.toInt()); //% de fade
    y = long(b.toInt()); //periodo
    
    // condições de erro
    if  (x < 0 || 100 < x) {
      Serial.println("fade value error");
    }
    else if  (y < 0 || 50 < y) {
      Serial.println("time value error");
    }
    else {
      Serial.print("Led fading up and down, power: ");
      Serial.print(x);
      Serial.print("%");
      Serial.print(", and period: ");
      Serial.print(y);
      Serial.println("ms.");
      

      while (1) {
        time_now = millis(); //fade com função cosseno se mostrou muito mais simples de implementar que uma função linear
        fadevalue = 128 + 127 * cos(2 * PI / y * time_now);
        analogWrite(ledPin, fadevalue);
        //break loop
        if (Serial.available() > 0) {
          a = Serial.readStringUntil('\n');
          if (a == "led on") {
            analogWrite(ledPin, 255);
            Serial.println("Led ON");
            break;
          }
          if (a == "led off") {
            analogWrite(ledPin, 0);
            Serial.println("Led OFF");
            break;
          }
        }
      }
    }
  }

  //##############################RT07######################
  else {
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
      if ((a != "on") && (a != "off") && (a != "") && (a != "fade")) {
        x = long(a.toInt());
        if (x < 0 || 100 < x) {
          Serial.println("pwm value error");
        }
        else {
          pwm = x;
          fadevalue = map(pwm, 0, 100, 0, 255);
          Serial.print("Led fade at: ");
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
}
