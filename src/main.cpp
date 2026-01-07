#include <Arduino.h>
#include <Bounce2.h>

// --------------------
// Pin configuration
// --------------------
constexpr uint8_t PIN_BUTTON = D3;
constexpr uint8_t PIN_LED    = D10;

// --------------------
// Objects & State
// --------------------
Bounce buttonDebounce;
bool isLedOn = false;

// --------------------
// Helper function
// --------------------
void updateLed() {
  digitalWrite(PIN_LED, isLedOn ? HIGH : LOW);
}

// --------------------
// Arduino setup
// --------------------
void setup() {
  Serial.begin(115200);
  delay(2000);

  pinMode(PIN_LED, OUTPUT);
  updateLed();  // set initial LED state

  pinMode(PIN_BUTTON, INPUT_PULLUP);
  buttonDebounce.attach(PIN_BUTTON);
  buttonDebounce.interval(25);

  Serial.println("System initialized. Waiting for button press...");
}

// --------------------
// Arduino loop
// --------------------
void loop() {
  buttonDebounce.update();

  if (buttonDebounce.fell()) {   // detect button press (active LOW)
    isLedOn = !isLedOn;           // toggle LED state
    updateLed();

    Serial.print("LED status changed: ");
    Serial.println(isLedOn ? "ON" : "OFF");
  }
}