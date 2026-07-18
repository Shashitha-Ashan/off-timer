#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ESPmDNS.h>

const char* ssid = "wifi ssid";
const char* password = "wifi password";

const int RELAY_PIN = 2;

AsyncWebServer server(80);

bool shouldShutdown = false;
bool shouldTest = false;


void setup() {
  Serial.begin(115200);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected! IP Address: ");
  Serial.println(WiFi.localIP());

  if (!MDNS.begin("esp32-device")) {
    Serial.println("mDNS failed");
    return;
  }

  MDNS.addService("http", "tcp", 80);

  MDNS.addServiceTxt("http", "tcp", "device", "esp32");
  MDNS.addServiceTxt("http", "tcp", "type", "presence");

  Serial.println("mDNS Started");

  server.on("/turn-off", HTTP_GET, [](AsyncWebServerRequest* request) {
    Serial.println("API Called: /turn-off received!");
    request->send(200, "text/plain", "OK");
    shouldShutdown = true;
  });

  server.on("/test", HTTP_GET, [](AsyncWebServerRequest* request) {
    Serial.println("API Called: /test received!");
    request->send(200, "text/plain", "OK");
    shouldTest = true;
  });

  server.begin();

  Serial.println("Web server started successfully.");
}

void loop() {
  if (shouldShutdown) {
    executeShutdown();
    shouldShutdown = false;
  }

  if (shouldTest) {
    testConnection();
    shouldTest = false;
  }
}
void executeShutdown() {
  Serial.println("Executing physical turn off sequence...");

  digitalWrite(RELAY_PIN, HIGH);
}


void testConnection() {
  Serial.println("Executing test connection...");

  digitalWrite(RELAY_PIN, LOW);
  delay(1000);
  digitalWrite(RELAY_PIN, HIGH);
}
