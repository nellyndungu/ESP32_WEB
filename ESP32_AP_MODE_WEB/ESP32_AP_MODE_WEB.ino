// Access point - the stations/devices connect to ESP32
// Good for wireless communication between one ESP32 and other devices without needing a router. 
// Include WiFi, webserver and time libraries
#include <WiFi.h>
#include <WebServer.h>
#include <time.h>
#include "esp_wifi.h"
#include "Webpage.h"

// Set network credentials
const char* ssid = "ESP32_AP";
// Password must be atleast 8 characters
const char* password = "admin@2025";

// Webserver instance to listen o port 80
WebServer server(80);

// Ticket data variables
String ticketName = "";
String ticketTime = "";
String ticketID = "";

//Generate ticket ID
String generateTicket(String name){
  String letters = "";
  name.toUpperCase();
  // Random characters from the name
  if(name.length() >= 2){
    int i1 = random(0, name.length());
    int i2 = random(0, name.length());
    while(i2 == i1 && name.length() > 1 ){
      i2 = random (0, name.length());
    }
    letters += (char)toupper(name[i1]);
    letters += (char)toupper(name[i2]);
  }else{
    // Fallback
    letters = "NA"; 
  }
  // Random digits
  int num = random(100, 999);
  return letters + String(num);
}

// Get the current time
String currentTime(){
  struct  tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    return String(millis()/1000) + "s since boot";
  }
  char buffer[30];
  strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);
  return String(buffer);
}

// Handle homepage
void handleRoot(){
  server.send(200, "text/html", MAIN_page);
}

// Handle ticket generation
void handleGenerate(){
   if (server.hasArg("name")) {
    ticketName = server.arg("name");
    ticketID = generateTicket(ticketName);
    ticketTime = currentTime();

    String html = generateTicketHTML(ticketName, ticketID, ticketTime);
    server.send(200, "text/html", html);
  } else {
    server.send(200, "text/html", MAIN_page);
  }
}
void setup(){
  Serial.begin(115200);
  randomSeed(esp_random());
  Serial.print("Setting AP ...");
  // Clear old WiFi settings first
  WiFi.disconnect(true, true);
  delay(1000);

  //Start ESP32 in Access Point Mode
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  // Print network details
  Serial.println("Access Point Initiated!");
  Serial.println(ssid);
  Serial.print(": ");
  Serial.print(WiFi.softAPIP());

  // NTP Configuration
  configTime(3 * 3600, 0, "pool.ntp.org");

  // Routes
  server.on("/", handleRoot);
  server.on("/generate", handleGenerate);
  server.begin();
  Serial.print("HTTP Server started");

}
void loop(){
  server.handleClient();
// Get number of stations connected
int stationsNum = WiFi.softAPgetStationNum();

//Print the number of connected stations
Serial.print("Connected devices: ");
Serial.println(stationsNum);

if(stationsNum > 0){
  wifi_sta_list_t stationList;
  esp_wifi_ap_get_sta_list (&stationList);
  Serial.printf("Connected devices: %d\n", stationList.num);

for (int i = 0; i < stationList.num; i++) {
    wifi_sta_info_t station = stationList.sta[i];

     Serial.printf("Device %d - MAC: %02X:%02X:%02X:%02X:%02X:%02X\n",
                  i + 1,
                  station.mac[0], station.mac[1], station.mac[2],
                  station.mac[3], station.mac[4], station.mac[5]);
  }
}
delay(500);
}