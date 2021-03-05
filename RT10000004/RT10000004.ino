// Load Wi-Fi library
#include <WiFi.h>

//Set setwork ssid
const char* ssid     = "esp32_";

// Set IP Address details
IPAddress local_IP(192, 168, 4, 1);
IPAddress gateway(192, 168, 4, 1);
IPAddress subnet(255, 255, 255, 0);

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output2State = "off";

// Assign output variables to GPIO pins
const int output2 = 2;

void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(output2, OUTPUT);
  // Set output to LOW
  digitalWrite(output2, LOW);

  //wait serial initialization
  delay(500);

  //Get WiFi soft AP interface MAC address
  //remove the ":" in the mac address and concatenate it to ssid name.
  WiFi.mode(WIFI_MODE_AP);
  String macOne = WiFi.softAPmacAddress();
  String macTwo = macOne;
  macTwo.replace(":", "");
  String newSsid = String(ssid);
  newSsid.concat(macTwo);
  ssid = newSsid.c_str();
  Serial.print("SSID Updated to: ");
  Serial.println(ssid);

  // Connect to Wi-Fi network with SSID
  Serial.println("Setting AP (Access Point)…");
  WiFi.softAP(ssid);
  delay(100);

  //configure access point
  Serial.print("Setting soft-AP configuration ... ");
  Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Ready" : "Failed!");
  delay(100);

  //Print MAC and IP address
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP().toString());
  Serial.print("MAC address: ");
  Serial.println(WiFi.softAPmacAddress());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // turns the GPIOs on and off
            if (header.indexOf("GET /2/on") >= 0) {
              Serial.println("GPIO 2 on");
              output2State = "on";
              digitalWrite(output2, HIGH);
            } else if (header.indexOf("GET /2/off") >= 0) {
              Serial.println("GPIO 2 off");
              output2State = "off";
              digitalWrite(output2, LOW);
            }

            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #66a3ff; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");

            // Web Page Heading
            client.println("<body><h1>Welcome, Stranger!</h1>");
            client.println("<body><h1>ESP32 web server</h1>");

            //Display MAC and IP address
            client.println("<p>IP:" + (WiFi.softAPIP().toString()) + "</p>");
            client.println("<p>MAC: " + WiFi.softAPmacAddress() + "</p>");

            // Display current state, and ON/OFF buttons for GPIO 2
            client.println("<p>Led 1 state: " + output2State + "</p>");
            // If the output2State is off, it displays the ON button

            //print the buttons
            client.println("<p><a href=\"/2/on\"><button class=\"button\">LED ON</button></a></p>");
            client.println("<p><a href=\"/2/off\"><button class=\"button button2\">LED OFF</button></a></p>");

            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
