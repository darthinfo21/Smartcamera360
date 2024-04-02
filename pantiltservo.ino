#include <ESP8266WiFi.h>
#include <Servo.h>

// WiFi credentials
const char* ssid = "abcd";
const char* password = "12345678";

// Servo pin assignments
const int panPin = D1;  // GPIO 14
const int tiltPin = D2; // GPIO 12

// Create servo objects
Servo panServo;
Servo tiltServo;

WiFiServer server(80);

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);

  // Initialize servos
  panServo.attach(panPin);
  tiltServo.attach(tiltPin);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  // Print IP address
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Start server
  server.begin();
  Serial.println("Server started");
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.println("New client");
  while (!client.available()) {
    delay(1);
  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // Handle HTTP requests for pan and tilt adjustments
  if (request.indexOf("/pan") != -1) {
    int pos = request.indexOf("deg=");
    if (pos != -1) {
      String panValueStr = request.substring(pos + 4);
      int panValue = panValueStr.toInt();
      panServo.write(panValue);
    }
  } else if (request.indexOf("/tilt") != -1) {
    int pos = request.indexOf("deg=");
    if (pos != -1) {
      String tiltValueStr = request.substring(pos + 4);
      int tiltValue = tiltValueStr.toInt();
      tiltServo.write(tiltValue);
    }
  }

  // Send HTTP response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println();

  // HTML page with sliders for controlling servos
  client.println("<!DOCTYPE html><html>");
  client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  client.println("<title>Pan-Tilt Control</title></head><body>");
  client.println("<h1>Pan-Tilt Control</h1>");
  client.println("<p>Pan: <input type=\"range\" min=\"0\" max=\"180\" value=\"90\" id=\"panSlider\" oninput=\"updatePan(this.value)\"></p>");
  client.println("<p>Tilt: <input type=\"range\" min=\"0\" max=\"180\" value=\"90\" id=\"tiltSlider\" oninput=\"updateTilt(this.value)\"></p>");
  client.println("<script>");
  client.println("function updatePan(value) {");
  client.println("  var xhttp = new XMLHttpRequest();");
  client.println("  xhttp.open(\"GET\", \"/pan?deg=\" + value, true);");
  client.println("  xhttp.send();");
  client.println("}");
  client.println("function updateTilt(value) {");
  client.println("  var xhttp = new XMLHttpRequest();");
  client.println("  xhttp.open(\"GET\", \"/tilt?deg=\" + value, true);");
  client.println("  xhttp.send();");
  client.println("}");
  client.println("</script>");
  client.println("</body></html>");

  Serial.println("Client disconnected");
}
