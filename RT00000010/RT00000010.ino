const int ledPin =  9;
const int buttonPin = 8;
const int buzzerPin = 3;

int ledstate = LOW;
int buttonState = 0;

int fadevalue;
int pwm;
int x;
int y;
int t_buzz;
int x_buzz;
int custombuzz = 0;

String palavra;
String a;
String b;

unsigned long time_now = 0;


void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // verifica botão
  buttonState = digitalRead(buttonPin);
  if (buttonState == 1) {
    //buzz default
    if (custombuzz == 0) {
      for (int i = 1; i <= 2; i++) {
        analogWrite(buzzerPin, 10);
        delay(500);
        analogWrite(buzzerPin, 0);
        delay(500);
      }
    }
    //buzz custom
    else {
      for (int i = 1; i <= x_buzz; i++) {
        analogWrite(buzzerPin, 127);
        digitalWrite(ledPin, HIGH);
        delay(t_buzz);
        analogWrite(buzzerPin, 0);
        digitalWrite(ledPin, LOW);
        delay(t_buzz);
      }
    }
  }
  else {
    while (Serial.available() > 0);
    palavra = Serial.readStringUntil('\n');
    //#############parse da string##############
    //Consegui fazer o parse apenas com substring e não com a barra de espaços,
    //portanto meu imput do led fade precisa conter 3 caracteres, por exemplo:
    //led fade 010 50
    if (palavra.startsWith("buzzer")) {
      a = palavra.substring(7, 10);
      b = palavra.substring(11);
      t_buzz = long(a.toInt()); //período
      x_buzz = long(b.toInt()); //repetições
      custombuzz = 1;

      Serial.print("buzzer configurado, período: ");
      Serial.print(t_buzz);
      Serial.print("ms e ");
      Serial.print(x_buzz);
      Serial.println(" repetições.");

    }
    if (palavra.startsWith("led fade")) {
      a = palavra.substring(9, 12);
      b = palavra.substring(13);
      x = long(a.toInt()); //% de fade
      y = long(b.toInt()); //periodo

      // condições de erro
      if  (x < 0 || 100 < x) {
        Serial.println("fade value error");
      }
      else if  (y < 0 || 5000 < y) {
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
      // else {
      //   Serial.println("input error");
      // }
      analogWrite(ledPin, ledstate);
    }
  }
}
