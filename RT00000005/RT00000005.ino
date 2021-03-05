int x = 1;
String palavra;

void setup() 
{
  Serial.begin(9600);
}

void loop()
{
  while(Serial.available() == 0);
  palavra = Serial.readStringUntil('\n');
  Serial.print("[START]");
  Serial.print("[");
  Serial.print(x);
  Serial.print("]");
  Serial.print("[");
  Serial.print(palavra);
  Serial.print("]");
  Serial.println("[END]");
  x++;
}
