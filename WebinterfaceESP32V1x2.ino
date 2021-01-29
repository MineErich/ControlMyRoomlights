//basic functions by Arduino IDE examples..

// Load Wi-Fi library
#include <WiFi.h>

// Replace with your network credentials
const char* ssid     = "ssid";
const char* password = "password";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// settings
String ooState = "off";
String mState = "choose color";

// Variables for Brightness
uint8_t bri = 10;
int internIr;
int internIg;
int internIb;

void realOutput(int ir, int ig, int ib)
{
  int ROr;
  int ROg;
  int ROb;
  if (ooState == "on") {
    //r
    ROr = ir*bri/10;
    //g
    ROg = ig*bri/10;
    //b
    ROb = ib*bri/10;
  
    sigmaDeltaWrite(0, ROr);
    sigmaDeltaWrite(1, ROg);
    sigmaDeltaWrite(2, ROb);
  } else if (ooState == "off") {
    Serial.println("Error: string ooState is invalid: LED is off");
  }
}


void setup() {
  Serial.begin(115200);
  //setup channels with frequency 312500 Hz
  sigmaDeltaSetup(0, 12000);
  sigmaDeltaSetup(1, 12000);
  sigmaDeltaSetup(2, 12000);
  
  //attach pins to channels
  sigmaDeltaAttachPin(13,0); //red
  sigmaDeltaAttachPin(12,1); //green
  sigmaDeltaAttachPin(14,2); //blue
  
  //initialize channels to off
  sigmaDeltaWrite(0, 0);
  sigmaDeltaWrite(1, 0);
  sigmaDeltaWrite(2, 0);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
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
            
            // action
            if (header.indexOf("GET /off") >= 0) { //off
              Serial.println("LED off");
              ooState = "off";
              sigmaDeltaWrite(0, 0);
              sigmaDeltaWrite(1, 0);
              sigmaDeltaWrite(2, 0);
            } else if (header.indexOf("GET /on") >= 0) { //on
              Serial.println("LED on");
              ooState = "on";
/*--NEXTNEXTNEXTNEXTNEXTNEXTNEXTNEXTNEXTNEXTNEXTNEXTNEXTNEXTNEXTNEXTNEXTNEXTNEXTNEXT--*/ 
            } else if (header.indexOf("GET /up") >= 0) {
              Serial.println("set bri up");
              if (bri >= 1 and bri < 10) {
                bri = bri+1;
                Serial.println("updated bri");
                realOutput(internIr, internIg, internIb);
              } else {
                Serial.println("Error: integer bri: invalid");
              }
            } else if (header.indexOf("GET /do") >= 0) {
              Serial.println("set bri down");
              if (bri > 1 and bri <= 10) {
                bri = bri-1;
                Serial.println("updated bri");
                realOutput(internIr, internIg, internIb);
              } else {
                Serial.println("Error: integer bri: invalid");
              }
/*--NEXTNEXTNEXTNEXTNEXTNEXTNEXTNEXTNEXTNEXTNEXTNEXTNEXTNEXTNEXTNEXTNEXTNEXTNEXTNEXT--*/
            } else if (header.indexOf("GET /re") >= 0) { //red
              Serial.println("mState = red");
              mState = "red";
              realOutput(255, 0, 0);
              /********************************************************************/
            } else if (header.indexOf("GET /gr") >= 0) { //green
              Serial.println("mState = green");
              mState = "green";
              realOutput(0, 255, 0);
              /********************************************************************/
            } else if (header.indexOf("GET /bl") >= 0) { //blue
              Serial.println("mState = blue");
              mState = "blue";
              realOutput(0, 0, 255);
              /********************************************************************/
            } else if (header.indexOf("GET /ye") >= 0) { //yellow
              Serial.println("mState = yellow");
              mState = "yellow";
              realOutput(255, 255, 0);
              /********************************************************************/
            } else if (header.indexOf("GET /cy") >= 0) { //cyan
              Serial.println("mState = cyan");
              mState = "cyan";
              realOutput(0, 255, 255);
              /********************************************************************/
            } else if (header.indexOf("GET /pi") >= 0) { //pink
              Serial.println("mState = pink");
              mState = "pink";
              realOutput(255, 0, 255);
              /********************************************************************/
            }

            
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            //client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<title>Webinterface Liley 1x0</title>");
            // CSS to style the buttons 
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center; background-color: #708090;}");
            client.println(".button { background-color: #FFA500; border: none; color: white; float: left; width: 100%;");
            client.println("text-decoration: none; font-size: 12px; cursor: pointer; border-radius: 8px; min-width: 50px; min-height: 50px; max-width: 50px; max-height: 50px;}");
            client.println(".disabled { cursor: not-allowed;}"); //next time some modes will be added to the Webinterface. For Layout I included the buttons already...
            client.println("</style></head>");

            client.println("<body><hr noshade>");
            client.println("<h1>State: " + ooState + "&nbsp;&nbsp;&nbsp;&nbsp;Mode: " + mState + "&nbsp;&nbsp;&nbsp;&nbsp;Brightness: " + bri + "</h1>"); //Statusleiste 
            client.println("<hr noshade>");
            
            //Table: onoff,brispe,up,down,mode
            client.println("<table><tr>");
            //off on
            if (ooState=="off") {
              client.println("<td><a href=\"/on\"><button class=\"button\">ON</button></a></td>");
            } else {
              client.println("<td><a href=\"/off\"><button class=\"button\">OFF</button></a></td>");
            } 
            client.println("<td><a href=\"/up\"><button class=\"button\">+</button></a></td>");
            client.println("<td><a href=\"/do\"><button class=\"button\">-</button></a></td>");
            client.println("</tr><tr>");
            client.println("<td><a href=\"/re\"><button class=\"button\" style=\"background-color: rgb(255,0,0);\"></button></a></td>");
            client.println("<td><a href=\"/gr\"><button class=\"button\" style=\"background-color: rgb(0,255,0);\"></button></a></td>");
            client.println("<td><a href=\"/bl\"><button class=\"button\" style=\"background-color: rgb(0,0,255);\"></button></a></td>");
            client.println("</tr><tr>");
            client.println("<td><a href=\"/ye\"><button class=\"button\" style=\"background-color: rgb(255,255,0);\"></button></a></td>");
            client.println("<td><a href=\"cy\"><button class=\"button\" style=\"background-color: rgb(0,255,255);\"></button></a></td>");
            client.println("<td><a href=\"/pi\"><button class=\"button\" style=\"background-color: rgb(255,0,255);\"></button></a></td>");
            client.println("</tr></table>");
            
            client.println("</body></html>");
            
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
