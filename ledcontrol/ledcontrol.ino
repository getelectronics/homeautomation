#include <ESP8266WiFi.h>
 
const char* ssid = "iainhendry"; //change this to your username
const char* password = "iain061271"; //change this to your password
 
WiFiServer server(80);


void setup() 
{
  Serial.begin(115200);
  delay(10);
 
  pinMode(LED_BUILTIN, OUTPUT);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() 
{
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
  if (request.indexOf("/LEDON") != -1) 
  {
    digitalWrite(LED_BUILTIN, LOW);
  } 
  if (request.indexOf("/LEDOFF") != -1)
  {
    digitalWrite(LED_BUILTIN, HIGH); 
  }
 
 
  //this is the web page
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html><head><title>LED Control</title></head><body><div><h2>LED Control</h2>");
  client.println("<br><br>");
  client.println("Click <a href=\"/LEDON\">here</a> turn the Built in LED ON<br>");
  client.println("Click <a href=\"/LEDOFF\">here</a> turn the Built in LED OFF<br>");
  client.println("<br><br>");
  client.println("<form id='F1' action='LEDON'><input class='button' type='submit' value='LED ON' ></form><br>");
  client.println("<form id='F2' action='LEDOFF'><input class='button' type='submit' value='LED OFF' ></form><br>");
  client.println("</div></body>");
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
 
}
