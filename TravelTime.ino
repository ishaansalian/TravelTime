// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 36, en = 37, d4 = 38, d5 = 39, d6 = 40, d7 = 41;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int ledPinFront = 6; // Define the LED pin
const int ledPinBack = 7; // Define the LED pin

const int buttonPin1 = 42; // Button 1 pin
const int buttonPin2 = 43; // Button 2 pin
const int buttonPin3 = 44; // Button 3 pin
const int buttonPin4 = 45; // Button 4 pin


int a = 26;
int b = 28;
int c = 29;
int d = 32;
int e = 31;
int f = 30; 
int g = 27;

int a2 = 22;
int b2 = 23;
int c2 = 33;
int d2 = 34;
int e2 = 35;
int f2 = 25; 
int g2 = 24;

void setup() {
  // Begin serial communication
  Serial.begin(9600);
  Serial1.begin(9600);  // Serial port 1
  Serial2.begin(9600);  // Serial port 2
  Serial3.begin(9600);  // Serial port 3

  lcd.begin(16, 2);
  // Loop through the busList array and print each bus information

  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);

  pinMode(a2, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(c2, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(e2, OUTPUT);
  pinMode(f2, OUTPUT);
  pinMode(g2, OUTPUT);
  }

void printBusInfo(String busNumber, String busName, String stopName) {
  lcd.clear(); // Clear the LCD display
  lcd.setCursor(0, 0);
  lcd.print(busNumber + "  -  " + busName);
  lcd.setCursor(0, 1);
  lcd.print(stopName);
}

// Function to blink the LED twice with a 0.25-second interval
void blinkLED() {
  for (int i = 0; i < 2; i++) {
    digitalWrite(ledPinFront, HIGH); // Turn on the front LED
    digitalWrite(ledPinBack, HIGH); // Turn on the back LED
    delay(250); // Wait for 0.25 seconds
    digitalWrite(ledPinFront, LOW); // Turn off the front LED
    digitalWrite(ledPinBack, LOW); // Turn off the back LED
    delay(250); // Wait for 0.25 seconds
  }
}

void displayDigit1(int digit) {
  switch (digit) {
    case 0:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      break;
    case 1:
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      break;
    case 2:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(g, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(d, HIGH);
      break;
    case 3:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(g, HIGH);
      break;
    case 4:
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    case 5:
      digitalWrite(a, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    case 6:
      digitalWrite(a, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    case 7:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      break;
    case 8:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    case 9:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
      }
  }

  void displayDigit2(int digit) {
  switch (digit) {
    case 0:
      digitalWrite(a2, HIGH);
      digitalWrite(b2, HIGH);
      digitalWrite(c2, HIGH);
      digitalWrite(d2, HIGH);
      digitalWrite(e2, HIGH);
      digitalWrite(f2, HIGH);
      break;
    case 1:
      digitalWrite(b2, HIGH);
      digitalWrite(c2, HIGH);
      break;
    case 2:
      digitalWrite(a2, HIGH);
      digitalWrite(b2, HIGH);
      digitalWrite(g2, HIGH);
      digitalWrite(e2, HIGH);
      digitalWrite(d2, HIGH);
      break;
    case 3:
      digitalWrite(a2, HIGH);
      digitalWrite(b2, HIGH);
      digitalWrite(c2, HIGH);
      digitalWrite(d2, HIGH);
      digitalWrite(g2, HIGH);
      break;
    case 4:
      digitalWrite(b2, HIGH);
      digitalWrite(c2, HIGH);
      digitalWrite(f2, HIGH);
      digitalWrite(g2, HIGH);
      break;
    case 5:
      digitalWrite(a2, HIGH);
      digitalWrite(c2, HIGH);
      digitalWrite(d2, HIGH);
      digitalWrite(f2, HIGH);
      digitalWrite(g2, HIGH);
      break;
    case 6:
      digitalWrite(a2, HIGH);
      digitalWrite(c2, HIGH);
      digitalWrite(d2, HIGH);
      digitalWrite(e2, HIGH);
      digitalWrite(f2, HIGH);
      digitalWrite(g2, HIGH);
      break;
    case 7:
      digitalWrite(a2, HIGH);
      digitalWrite(b2, HIGH);
      digitalWrite(c2, HIGH);
      break;
    case 8:
      digitalWrite(a2, HIGH);
      digitalWrite(b2, HIGH);
      digitalWrite(c2, HIGH);
      digitalWrite(d2, HIGH);
      digitalWrite(e2, HIGH);
      digitalWrite(f2, HIGH);
      digitalWrite(g2, HIGH);
      break;
    case 9:
      digitalWrite(a2, HIGH);
      digitalWrite(b2, HIGH);
      digitalWrite(c2, HIGH);
      digitalWrite(d2, HIGH);
      digitalWrite(f2, HIGH);
      digitalWrite(g2, HIGH);
      break;
      }

  }

void clearDisplay() {
  // Turn off all segments
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);

  digitalWrite(a2, LOW);
  digitalWrite(b2, LOW);
  digitalWrite(c2, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(e2, LOW);
  digitalWrite(f2, LOW);
  digitalWrite(g2, LOW);
}

void loop() {
  // Check if data is available on the main serial port (Serial Monitor)
  if (Serial1.available() > 0) {
    // Read the data
    String receivedData = Serial1.readStringUntil('\n'); // Read until newline character
    String busNumber = "";
    String busName = "";
    String stopName = "";
    int timeMinutes;


    // Print the received data to all serial ports
    //Serial.print(receivedData);
    //Serial2.print(receivedData);
    //Serial3.print(receivedData);

    // Parse and extract information
    if (receivedData.startsWith("PRINT: ")) {
      // Extract information from the PRINT line
      int index1 = receivedData.indexOf("1.");
      int index2 = receivedData.indexOf("2.");
      int index3 = receivedData.indexOf("3.");
      int index4 = receivedData.indexOf("4.");

      busNumber = receivedData.substring(index1 + 2, index2 - 1);
      busName = receivedData.substring(index2 + 2, index3 - 1);
      stopName = receivedData.substring(index3 + 2, index4 - 1);
    } else if (receivedData.startsWith("TIME: ")) {
      // Extract time information
      timeMinutes = receivedData.substring(6).toInt();
    }
      // Print the extracted information
      Serial.println("Bus Number: " + busNumber);
      Serial.println("Bus Name: " + busName);
      Serial.println("Stop Name: " + stopName);
      Serial.println("Time (Minutes): " + timeMinutes);

      lcd.begin(16, 2);
      printBusInfo(busNumber, busName, stopName);
      CountTime(timeMinutes);
      delay(20000); // Delay for 2 seconds before displaying the next bus info
    }
  }

// Actual Time Display Function
void CountTime(int minutes) {
  int tens = minutes/10%10; // 10's digit
  int ones = minutes%10; // 1's digit
  clearDisplay();
  //delay(200);
  displayDigit1(tens);
  displayDigit2(ones);
  //delay(2000); // Adjust delay as needed
  }

// Function to extract a value between two delimiters
String getValue(String data, String delimiter1, String delimiter2) {
  int index1 = data.indexOf(delimiter1) + delimiter1.length();
  int index2 = data.indexOf(delimiter2, index1);
  return data.substring(index1, index2);
}
