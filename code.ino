/*
  WiFi Web Server LED Blink

  A simple web server that lets you blink an LED via the web.
  This sketch will print the IP address of your WiFi module (once connected)
  to the Serial Monitor. From there, you can open that address in a web browser
  to turn on and off the LED on pin 9.

  If the IP address of your board is yourAddress:
  http://yourAddress/H turns the LED on
  http://yourAddress/L turns it off

  This example is written for a network using WPA encryption. For
  WEP or WPA, change the WiFi.begin() call accordingly.

  Circuit:
   Board with NINA module (Arduino MKR WiFi 1010, MKR VIDOR 4000 and UNO WiFi Rev.2)
   LED attached to pin 9

  created 25 Nov 2012
  by Tom Igoe
*/
#include <SPI.h>
#include <WiFiNINA.h>

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;                 // your network key index number (needed only for WEP)

int status = WL_IDLE_STATUS;
WiFiServer server(80);

// pin output state of LED
String REDSTATUS = "off";
String YELLOWSTATUS = "off";
String GREENSTATUS = "off";

// Variables to pins
const int led1 = 4;
const int led2 = 7;
const int led3 = 8;

String host;

void setup() {
  Serial.begin(9600);      // initialize serial communication
  pinMode(9, OUTPUT);      // set the LED pin mode

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);


  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                   // print the network name (SSID);

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    delay(10000);
  }
  server.begin();                           // start the web server on port 80
  printWifiStatus();                        // you're connected now, so print out the status
}


void loop() {
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        host += c;
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            if (host.indexOf("GET /4/on") >= 0) {
              Serial.println("RED LED is on");
              REDSTATUS = "on";
              digitalWrite(led1, HIGH);
            }
            if (host.indexOf("GET /4/off") >= 0)
            {
              digitalWrite(led1, LOW);
              REDSTATUS = "off";
              Serial.println("RED LED is off");
            }
            if (host.indexOf("GET /7/on") >= 0) {
              Serial.println("white LED is on");
              GREENSTATUS = "on";
              digitalWrite(led3, HIGH);
            }
            if (host.indexOf("GET /7/off") >= 0)
            {
              digitalWrite(led3, LOW);
              GREENSTATUS = "off";
              Serial.println("white LED is off");
            }
            if (host.indexOf("GET /8/on") >= 0) {
              Serial.println("Yellow LED is on");
              YELLOWSTATUS = "on";
              digitalWrite(led2, HIGH);
            }
            if (host.indexOf("GET /8/off") >= 0)
            {
              digitalWrite(led2, LOW);
              YELLOWSTATUS = "off";
              Serial.println("Yellow LED is off");
            }
            if (host.indexOf("GET /4/7/8/on") >= 0) {
              Serial.println("Red-Yellow-GREEN LED is on");
              REDSTATUS = "on";
              YELLOWSTATUS = "on";
              GREENSTATUS = "on";
              digitalWrite(led1, HIGH);
              delay(100);
              digitalWrite(led1, LOW);
              digitalWrite(led3, HIGH);
              delay(100);
              digitalWrite(led3, LOW);
              delay(100);
              digitalWrite(led2, HIGH);
              delay(100);
              digitalWrite(led2, LOW);
              digitalWrite(led1, HIGH);
              delay(100);
              digitalWrite(led1, HIGH);
              digitalWrite(led3, HIGH);
              digitalWrite(led2, HIGH);
              delay(500);
              digitalWrite(led1, LOW);
              digitalWrite(led3, LOW);
              digitalWrite(led2, LOW);
              delay(200);
              digitalWrite(led2, HIGH);
              delay(100);
              digitalWrite(led2, LOW);
              digitalWrite(led1, HIGH);
              delay(100);
              digitalWrite(led1, HIGH);
              digitalWrite(led3, HIGH);
              digitalWrite(led2, HIGH);
              delay(500);
              digitalWrite(led1, LOW);
              digitalWrite(led3, LOW);
              digitalWrite(led2, LOW);
            }
            if (host.indexOf("GET /2/3/4/off") >= 0) {
              Serial.println("Red-Yellow-White LED is off");
              REDSTATUS = "off"; YELLOWSTATUS = "off"; GREENSTATUS = "off";
              digitalWrite(led1, LOW);
              digitalWrite(led2, LOW);
              digitalWrite(led3, LOW);
            }

            client.print("<!DOCTYPE html>");
            client.print("<html lang=\"en\">");
            client.print("<head>");
            client.print("    <title>The Button</title>");
            client.print("    <style>");
            client.print("        body {");
            client.print("            background-color: #3d0049;");
            client.print("        }");
            client.print("        .heading {");
            client.print("            background-color: #0026ff;");
            client.print("            padding: 10px 10px 10px 20px;");
            client.print("            color: rgb(255, 255, 255);");
            client.print("            border-radius: 50px;");
            client.print("            text-align: center;");
            client.print("            cursor: pointer;");
            client.print("        }");
            client.print("        .flex-container {");
            client.print("            display: flex;");
            client.print("            justify-content: center;");
            client.print("        }");
            client.print("        .button {");
            client.print("            border: none;");
            client.print("            color: white;");
            client.print("            width: auto;");
            client.print("            padding: 16px 32px;");
            client.print("            text-align: center;");
            client.print("            display: inline-block;");
            client.print("            font-size: 16px;");
            client.print("            margin: 16px 20px;");
            client.print("            cursor: grab;");
            client.print("            border-radius: 50%;");
            client.print("        }");
            client.print("        .button1 {");
            client.print("            background-color: #ffffff;");
            client.print("            color: #000000;");
            client.print("            border: 2px solid #00FF00;");
            client.print("        }");
            client.print("        .button1:hover {");
            client.print("            background-color: #00FF00;");
            client.print("            color: #ffffff;");
            client.print("        }");
            client.print("        .button2:active {");
            client.print("            cursor: grabbing;");
            client.print("        }");
            client.print("        .button3:active {");
            client.print("            cursor: grabbing;");
            client.print("        }");
            client.print("        .button4:active {");
            client.print("            cursor: grabbing;");
            client.print("        }");
            client.print("        .button1:active {");
            client.print("            cursor: grabbing;");
            client.print("        }");
            client.print("        .button2 {");
            client.print("            background-color: #ffffff;");
            client.print("            color: #000000;");
            client.print("            border: 2px solid #dcff18;");
            client.print("        }");
            client.print("        .button2:hover {");
            client.print("            background-color: #dcff18;");
            client.print("            color: #ffffff;");
            client.print("        }");
            client.print("        .button3 {");
            client.print("            background-color: rgb(255, 255, 255);");
            client.print("            color: #000000;");
            client.print("            border: 2px solid hsl(0, 100%, 59%);");
            client.print("        }");
            client.print("        .button3:hover {");
            client.print("            background-color: hsl(0, 100%, 59%);");
            client.print("            color: white;");
            client.print("        }");
            client.print("        .button4 {");
            client.print("            background-color: rgb(255, 255, 255);");
            client.print("            color: #000000;");
            client.print("            border: 2px solid hsl(0, 100%, 59%);");
            client.print("        }");
            client.print("        .button4:hover {");
            client.print("            background: rgb(255, 43, 43);");
            client.print("            background: linear-gradient(90deg, rgba(255, 43, 43, 1) 0%, rgba(241, 253, 29, 1) 50%, rgba(88, 255, 93, 1) 100%);");
            client.print("            color: #000000;");
            client.print("            border: 2px solid hsl(0, 0%, 0%);");
            client.print("        }");
            client.print("        footer {");
            client.print("            text-align: center;");
            client.print("            color: #dddddd;");
            client.print("            padding-top: 50px;");
            client.print("        }");
            client.print("    </style>");
            client.print("</head>");
            client.print("<body>");
            client.print("    </div>");
            client.print("    <br />");
            client.print("    <br />");
            client.print("    <h1 class=\"heading\" style = \" color: #000000f8\">");
            client.print("        Choose your button");
            client.print("    </h1>");
            client.print("    <div class=\"flex-container\">");
            client.print("        <button class=\"button button4\">Traffic</button>");
            client.print("    </div>");
            client.print("    <div class=\"flex-container\">");
            
            // Display current state, and on/off buttons for PIN 2 Red LED
            client.println("<p style=\"color:RED\">Red LED is " + REDSTATUS + "</p>");
            // If the REDSTATUS is off, it displays the off button
            if (REDSTATUS == "off")
            {
              client.println("<p><a href=\"/4/on\"><button class=\"button button3\">Red</button></a></p>");
            }
            else
            {
              client.println("<p><a href=\"/4/off\"><button class=\"button button3\">Red</button></a></p>");
            }

            // Display current state, and on/off buttons for PIN 3 Yellow LED
            client.println("<p style=\"color:Yellow\">Yellow LED is " + YELLOWSTATUS + "</p>");
            // If the YELLOWSTATUS is off, it displays the off button
            if (YELLOWSTATUS == "off")
            {
              client.println("<p><a href=\"/8/on\"><button class=\"button button4\">GREE</button></a></p>");
            }
            else
            {
              client.println("<p><a href=\"/8/off\"><button class=\"button button4\">GREEN</button></a></p>");
            }
            
            // Display current state, and on/off buttons for PIN 4 Green LED
            client.println("<p style=\"color:White\">white LED is " + GREENSTATUS + "</p>");
            // If the GREENSTATUS is off, it displays the off button
            if (GREENSTATUS == "off")
            {
              client.println("<p><a href=\"/7/on\"><button class=\"button button2\">Yellow</button></a></p>");
            }
            else
            {
              client.println("<p><a href=\"/7/off\"><button class=\"button button2\">Yellow</button></a></p>");
            }
            
            client.println("<p style=\"color:RED\">Red-Yellow-White LED is " + REDSTATUS + "</p>");
            if (YELLOWSTATUS == "off" && REDSTATUS == "off" && GREENSTATUS == "off")
            {
              client.println("<p><a href=\"/4/7/8/on\"><button class=\"button button1\">Red-Yellow-Green/off</button></a></p>");
            }
            else
            {
              client.println("<p><a href=\"/4/7/8/off\"><button class=\"button button1\">Red-Yellow-Green/off</button></a></p>");
            }

            client.print("    </div>");
            client.print("    <footer>");
            client.print("        Designed/Enhanced/sponsord/produced by Tanish Dhapola (2010993021)");
            client.print("    </footer>");
            client.print("</body>");
            client.print("</html>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(9, HIGH);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(9, LOW);                // GET /L turns the LED off
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}
