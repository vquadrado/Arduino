#include <WiFi.h>
#include <WiFiMulti.h>

int LED1 = 2;
int ledstate = LOW;

String palavra;
String a;

boolean exitFlag = false;

WiFiMulti wifiMulti;

//Este código está escrito para funcionar para n clientes telnet
#define MAX_SRV_CLIENTS 2

const char* ssid = "NetGalileu-8352";
const char* password = "8352140d";

WiFiServer server(23);
WiFiClient serverClients[MAX_SRV_CLIENTS];

void setup() {
  pinMode(LED1, OUTPUT);

  Serial.begin(115200);
  Serial.println("\nConnecting");

  wifiMulti.addAP(ssid, password);
  
  //Inicia conexão
  Serial.println("Connecting Wifi ");
  for (int loops = 10; loops > 0; loops--) {
    if (wifiMulti.run() == WL_CONNECTED) {
      Serial.println("");
      Serial.print("WiFi connected ");
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
      break;
    }
    else {
      Serial.println(loops);
      delay(1000);
    }
  }
  //se não consegue após 10 tentativas, reinicia o programa
  if (wifiMulti.run() != WL_CONNECTED) {
    Serial.println("WiFi connect failed");
    delay(1000);
    ESP.restart();
  }

  //inicia o servidor
  server.begin();
  server.setNoDelay(true);
  Serial.print("Ready! Use 'telnet ");
  Serial.print(WiFi.localIP());
  Serial.println(" 23' to connect");
}

void loop() {
  uint8_t i;
  if (wifiMulti.run() == WL_CONNECTED) {

    //verifica se há novos clients telnet
    if (server.hasClient()) {
      for (i = 0; i < MAX_SRV_CLIENTS; i++) {
        //find free/disconnected spot
        if (!serverClients[i] || !serverClients[i].connected()) {
          if (serverClients[i]) serverClients[i].stop();
          serverClients[i] = server.available();
          if (!serverClients[i]) Serial.println("available broken");
          Serial.print("New client: ");
          Serial.print(i); Serial.print(' ');
          Serial.println(serverClients[i].remoteIP());
          break;
        }
      }
      if (i >= MAX_SRV_CLIENTS) {
        server.available().stop();
      }
    }

    //procura por dados nos clients
    for (i = 0; i < MAX_SRV_CLIENTS; i++) {
      if (serverClients[i] && serverClients[i].connected()) {
        if (serverClients[i].available()) {
          //Pega dados do client telnet e coloca na variavel palavra
          while (serverClients[i].available()) palavra = serverClients[i].readStringUntil('\n');

          //se a string começar com led, faz parse
          if (palavra.startsWith("led on")) {
            serverClients[i].write("led on ok\r\n");
            Serial.println("Led ON");
            ledstate = HIGH;
          }
          else if (palavra.startsWith("led off")) {
            serverClients[i].write("led off ok\r\n");
            Serial.println("Led OFF");
            ledstate = LOW;
          }
          else if (exitFlag) {
            if (!palavra.startsWith("led off") || !palavra.startsWith("led on")) {
              serverClients[i].write("erro\r\n");
              Serial.println("erro");
            }
          }
          exitFlag = true;
        }
      }
      else {
        if (serverClients[i]) {
          serverClients[i].stop();
        }
      }
    }
  }
  else {
    Serial.println("WiFi not connected!");
    for (i = 0; i < MAX_SRV_CLIENTS; i++) {
      if (serverClients[i]) serverClients[i].stop();
    }
    delay(1000);
  }
  digitalWrite(LED1, ledstate);
}
