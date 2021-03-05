String palavra;

void setup()
{
  Serial.begin(9600);
}

void loop() 
{ 
  while(Serial.available() == 0);
  palavra = Serial.readStringUntil('\n');

  if(palavra == "p")
  {
    Serial.println("RT00000003 OK");
  }
  else
  {
    Serial.print(palavra);
    Serial.println("-WRONG!");
  }
}
