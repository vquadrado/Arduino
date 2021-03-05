String palavra;

void setup()
{
  Serial.begin(9600);
}

void loop() 
{ 
  while(Serial.available() == 0);
  palavra = Serial.readStringUntil('\n');

  if(palavra == "ping")
  {
    Serial.println("RT00000004 OK");
  }
  else
  {
    Serial.print(palavra);
    Serial.println("-WRONG!");
  }  
}
