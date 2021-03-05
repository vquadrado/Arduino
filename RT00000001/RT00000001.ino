void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int x = 1;
  while (x <= 100) {
    Serial.print("RT00000001");
    Serial.print(" ");
    Serial.print(x);
    Serial.println();
    x++;
  }
  while(1){   
  }
}
