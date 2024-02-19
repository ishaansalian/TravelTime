#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <TimeLib.h>
#include <SoftwareSerial.h>

// button1 - add
// button2 - sub
// button3 - func
// button4 - direction

int check;
int counter = 0;
const int led = 0;
int edit = 1;

const int button1 = 5;
const int button2 = 4;
const int button3 = 14;
const int button4 = 12;

SoftwareSerial espSerial(3, 1);

String busOrgNumbs[5] = {"B43", "31", "30", "33", "35"};
String busDesc = "No Name";
int buses[5] = {10043, 30031, 30030, 30033, 30035};
String directions[5][2] = {{"E", "W"}, {"N", "S"}, {"N", "S"}, {"N", "S"}, {"UP", "DWN"}};
int buttonPin[2] = {0, 0};     // bus_index, stop
int buttonPinFunc = 0;
int buttonPinDirection = 0;
int stopIds[30];
String stopNames[30];
int busChange = 1;
int remainingMinutes = 0;

const char *ssid = "SALANI-LAPTOP 0740";
const char *password = "664r8{X1";

const char *apiUrl = "http://bustracker.pvta.com/InfoPoint/rest/RouteDetails/GetStopsForRouteDirection?routeId=30031&direction=N&timepointsOnly=true";

// Connect your controller to WiFi
void connectToWiFi() {

  // Connect to WiFi Network
  Serial.begin(9600);
  Serial.println("");
  Serial.print("Connecting to WiFi");
  Serial.println("...");
  WiFi.begin(ssid, password);
  int retries = 0;
  while ((WiFi.status() != WL_CONNECTED)) {
    retries++;
    delay(500);
    Serial.print(".");
  }
  Serial.println("Here!");
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println(F("WiFi connected!"));
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }
  Serial.println("Setup ready");
}

void getStops(int routeId, String direct) {

  WiFiClient client;
  HTTPClient http;

  String url = "http://bustracker.pvta.com/InfoPoint/rest/RouteDetails/GetStopsForRouteDirection?routeId=" + String(routeId) + "&direction=" + direct + "&timepointsOnly=true";

  Serial.println(url);
  http.useHTTP10(true);
  Serial.println("Sending HTTP GET request...");
  Serial.println(String(routeId));
  http.begin(client, url);

  int httpCode = http.GET();
  if (httpCode > 0) {
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();

    // Parse JSON
      DynamicJsonDocument doc(10000);
      deserializeJson(doc, payload);

      int i = 0;

      for (const JsonVariant& stop : doc.as<JsonArray>()) {
        String description = stop["Description"];
        int stopId = stop["StopId"];

        stopNames[i] = description;
        stopIds[i] = stopId;
        i++;
        
      }
  } else {
      Serial.println("HTTP request failed");
      busChange = 1;
    }
  } else {
    Serial.println("HTTP request failed");
    busChange = 1;
  }

  http.end();
}

int convertToMinutes(const String &dateString) {
  // Extract the epochMilliseconds part from the date string
  int startIndex = dateString.indexOf('(') + 1;
  int endIndex = dateString.indexOf('-', startIndex) - 3;
  String timestampString = dateString.substring(startIndex, endIndex);

  int epochSeconds = timestampString.toInt(); 
  int epochMinutes = epochSeconds/60;
  
  return epochMinutes;
}

void getTime(int stopID, int routeId, String direct) {

  WiFiClient client;
  HTTPClient http;

  String url = "http://bustracker.pvta.com/InfoPoint/rest/SignageStopDepartures/GetSignageDeparturesByStopId?stopId=" + String(stopID);

  Serial.println(url);
  http.useHTTP10(true);
  Serial.println("Sending HTTP GET request...");
  http.begin(client, url);

  int httpCode = http.GET();
  if (httpCode > 0) {
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();

    // Parse JSON
      DynamicJsonDocument doc(10000);
      deserializeJson(doc, payload);

      int earliestTime = 2147483646; // Initialize with a large value

      // Iterate through the JSON data
      JsonArray routeDirections = doc[0]["RouteDirections"];
      for (JsonVariant direction : routeDirections) {
        String currentDirection = direction["Direction"].as<String>();
        int currentRouteId = atoi(direction["RouteId"]);
    
        if (currentDirection.equals(direct) && currentRouteId == routeId) {
          JsonArray departures = direction["Departures"];
          for (JsonVariant departure : departures) {

            busDesc = departure["DisplayText"].as<String>();
            
            int edtMinutes = convertToMinutes(departure["EDT"].as<String>());
            int luMinutes = convertToMinutes(departure["LastUpdated"].as<String>());

            int timeDifferenceMinutes = edtMinutes - luMinutes;
            
            // Update earliestTime if the current departure has a smaller time difference
            if (timeDifferenceMinutes < earliestTime) {
              earliestTime = timeDifferenceMinutes;
            }
          }
        }
      }

      remainingMinutes = earliestTime;
      Serial.print("remainingMinutes: ");
      Serial.println(remainingMinutes);
      
    } else {
      Serial.println("HTTP request failed");
    }
  } else {
    Serial.println("HTTP request failed");
  }

  http.end();
}

void infoDump(int busNum, int routeId, String direct, int stopNum){

  getStops(routeId, direct);

  delay(1000);

  getTime(stopIds[stopNum], routeId, direct);

  delay(1000);

  printDisplay(busOrgNumbs[busNum], busDesc, stopNames[stopNum], remainingMinutes);

}

void printDisplay(String busNumb, String busDesc, String stopName, int timeMin) {

  if(busDesc.equals("No Name")){
    busDesc = "Error";
  }
  if(stopName.equals("")){
    stopName = "Error";
  }
 
  espSerial.println("PRINT: 1." + busNumb + " 2." + busDesc + " 3." + stopName);
  espSerial.println("TIME: " + String(timeMin));
}


void setup() {
  connectToWiFi();
  Serial.begin(9600);
  espSerial.begin(9600);

  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);
  pinMode(led, OUTPUT);
  
}

void loop() {

  if (digitalRead(button1) == HIGH) {
    edit = 1;
    digitalWrite(led, HIGH);
    Serial.println("1 True");
    buttonPin[buttonPinFunc] = buttonPin[buttonPinFunc]+1;
    if ((buttonPinFunc == 0) && (buttonPin[0] == 5)){
      buttonPin[0] = 0;
    }
    for (int i=0; i < 30; i++){
      stopNames[i] = "";
      stopIds[i] = -1;
    }
    if (buttonPinFunc == 0){
      busDesc = "No Name";
      buttonPin[1] = 0;
    }
  }


  if (digitalRead(button2) == HIGH) {
    edit = 1;
    digitalWrite(led, HIGH);
    Serial.println("2 True");
    buttonPin[buttonPinFunc] = buttonPin[buttonPinFunc]-1;
    if ((buttonPinFunc == 0) && (buttonPin[0] == -1)){
      buttonPin[0] = 5;
    }
    for (int i=0; i < 30; i++){
      stopNames[i] = "";
      stopIds[i] = -1;
    }
    if (buttonPinFunc == 0){
      busDesc = "No Name";
      buttonPin[1] = 0;
    }
  }

  
  if (digitalRead(button3) == HIGH) {
    edit = 1;
    digitalWrite(led, HIGH);
    Serial.println("3 True");
    buttonPinFunc = (buttonPinFunc+1)%2;
    // glow LED
  }

  if (digitalRead(button4) == HIGH) {
    edit = 1;
    digitalWrite(led, HIGH);
    Serial.println("4 True");
    buttonPinDirection = (buttonPinDirection+1)%2;
    for (int i=0; i < 30; i++){
      stopNames[i] = "";
      stopIds[i] = -1;
    }
    if (buttonPinFunc == 0){
      busDesc = "No Name";
      buttonPin[1] = 0;
    }
  }


  if((edit == 1) || (counter >= 100000)){
    counter = 0;
    edit = 0;
    infoDump(buttonPin[0], buses[buttonPin[0]], directions[buttonPin[0]][buttonPinDirection], buttonPin[1]);// routeId (Bus), direction, stopNum
    digitalWrite(led, LOW);
    delay(5000);
  }

  counter++;
  
  
}
