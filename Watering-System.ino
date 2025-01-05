#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 4, 3, 2, 1);

const int soilMoisturePin = A1; // Pin connected to the soil moisture sensor
const int relayPin = 7;         // Pin connected to the relay module

const int soilThreshold = 250;  // Threshold for soil moisture (adjust based on your sensor)

// Variables to store sensor readings
int soilMoistureValue = 0;

unsigned long previousMillis = 0; // For non-blocking delay
const long interval = 2000;       // Update interval (milliseconds)

void setup() {
  lcd.begin(16, 2);              // Initialize the LCD
  lcd.print("Plant Watering");   // Display a message on the LCD
  delay(2000);
  lcd.clear();

  pinMode(relayPin, OUTPUT);     // Set relay pin as output
  digitalWrite(relayPin, LOW);  // Ensure relay is OFF initially (active LOW)

  Serial.begin(9600);            // Initialize Serial for debugging
}

void loop() {
  unsigned long currentMillis = millis();

  // Non-blocking update
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Read the soil moisture sensor value
    soilMoistureValue = analogRead(soilMoisturePin);

    // Debugging output
    Serial.print("Soil Moisture: ");
    Serial.println(soilMoistureValue);

    // Update LCD with soil moisture status
    lcd.setCursor(0, 0);
    lcd.print(soilMoistureValue < soilThreshold ? "Soil: Dry      " : "Soil: Wet      ");

    // Control the relay based on soil moisture
    if (soilMoistureValue < soilThreshold) {
      digitalWrite(relayPin, LOW); // Turn ON the relay (pump/device ON)
      lcd.setCursor(0, 1);
      lcd.print("Pump: ON       ");
    } else {
      digitalWrite(relayPin, HIGH); // Turn OFF the relay (pump/device OFF)
      lcd.setCursor(0, 1);
      lcd.print("Pump: OFF      ");
    }
  }
}
