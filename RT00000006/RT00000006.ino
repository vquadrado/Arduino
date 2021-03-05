String palavra;
int ledstate = 0;

void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600); 
}

void loop() 
{
  while(Serial.available() == 0);
  palavra = Serial.readStringUntil('\n');
  if (palavra == "led on"){
    ledstate = 1;
  }
  if (palavra == "led off"){
    ledstate = 0;
  }
  if (ledstate == 1){
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("LED ON!");
  }
  else{
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("LED OFF!");
  }
}
