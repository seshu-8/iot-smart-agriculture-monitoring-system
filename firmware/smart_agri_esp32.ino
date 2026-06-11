/**
 * @file smart_agri_esp32.ino
 * @brief Production IoT Edge Firmware for Smart Agriculture System.
 * Handles sensor sampling, threshold evaluations, edge actuation loops,
 * and data streaming via Wi-Fi networks to cloud servers.
 */

#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

// Hardware Pin Definitions Matrix
#define DHTPIN 15          // Digital Input for DHT22 Environmental Array
#define DHTTYPE DHT22      // Specified Sensor Subclass
#define SOIL_PIN 34        // Analog Input for Soil Moisture Simulation
#define LDR_PIN 35         // Analog Input for Solar Radiation Simulation
#define WATER_LVL_PIN 32   // Analog Input for Water Reservoir Simulation
#define PUMP_RELAY_PIN 2   // Digital Output Driver for Water Actuator

// Environment Configuration Metrics
const char* WIFI_SSID = "Wokwi-GUEST";     // Target Network Identifier for Wokwi Environment
const char* WIFI_PASSWORD = "";            // Open Authentication Layout
const char* TS_SERVER = "http://api.thingspeak.com/update";
const String TS_API_KEY = "YOUR_THINGSPEAK_WRITE_API_KEY"; // <-- Update with your key

// System Ingestion Control Guard
unsigned long precedingTelemetryEpoch = 0;
const unsigned long telemetryTransmissionInterval = 15000; // 15s Cloud Update Throttle

// System Safety Control Thresholds
const float SOIL_DRY_THRESHOLD = 40.0;     // Run irrigation below 40% moisture
const float CRITICAL_TEMP_LIMIT = 40.0;    // High-heat flag limit
const float MIN_WATER_RESERVOIR = 20.0;    // Low-water safety cutoff point

DHT dhtEngine(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(115200);
    Serial.println("\n==================================================");
    Serial.println("[SYSTEM INIT] Booting Smart Agriculture Core...");
    Serial.println("==================================================");
    
    pinMode(PUMP_RELAY_PIN, OUTPUT);
    digitalWrite(PUMP_RELAY_PIN, LOW); // Fail-safe default: Pump OFF
    
    dhtEngine.begin();
    
    // Connect to local network gateway
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("[NET INIT] Connecting to Network Node");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\n[NET OK] Connected to Gateway successfully.");
    Serial.print("[NET IP] Edge IP Address allocation: ");
    Serial.println(WiFi.localIP());
}

void loop() {
    // 1. Data Acquisition Phase (Non-blocking reads)
    float airHumidity = dhtEngine.readHumidity();
    float airTemperature = dhtEngine.readTemperature();
    
    // Read raw ADC signals (0 to 4095 range)
    int rawSoilLevel = analogRead(SOIL_PIN);
    int rawSolarLight = analogRead(LDR_PIN);
    int rawWaterLevel = analogRead(WATER_LVL_PIN);
    
    // Convert raw ADC readings to percentage values
    float normalizedSoilMoisture = (1.0 - ((float)rawSoilLevel / 4095.0)) * 100.0;
    float normalizedLightIntensity = (((float)rawSolarLight / 4095.0)) * 100.0;
    float normalizedWaterLevel = (((float)rawWaterLevel / 4095.0)) * 100.0;
    
    // Handle transient read errors gracefully
    if (isnan(airHumidity) || isnan(airTemperature)) {
        Serial.println("[WARN] DHT Sensor returned invalid telemetry frame. Retrying...");
        delay(2000);
        return;
    }
    
    // 2. Local Control & Safety Logic Phase (Edge Computing)
    int pumpStatusFlag = 0;
    
    if (normalizedSoilMoisture < SOIL_DRY_THRESHOLD) {
        // Safety check: Ensure the reservoir has enough water before starting the pump
        if (normalizedWaterLevel > MIN_WATER_RESERVOIR) {
            digitalWrite(PUMP_RELAY_PIN, HIGH);
            pumpStatusFlag = 1;
            Serial.println("[ACTUATION] Low Soil Moisture detected. Activating Pump.");
        } else {
            digitalWrite(PUMP_RELAY_PIN, LOW);
            pumpStatusFlag = 0;
            Serial.println("[CRITICAL] Low Moisture but Water Reservoir is EMPTY. Pump locked out for safety!");
        }
    } else {
        digitalWrite(PUMP_RELAY_PIN, LOW);
        pumpStatusFlag = 0;
    }
    
    if (airTemperature > CRITICAL_TEMP_LIMIT) {
        Serial.println("[ALERT] Critical Thermal Threshold exceeded in agricultural zone!");
    }
    
    // 3. Local Hardware Telemetry Reporting
    Serial.println("\n----------------- TELEMETRY FRAME -----------------");
    Serial.printf("Air Temp   : %.2f °C\n", airTemperature);
    Serial.printf("Air Humid  : %.2f %%\n", airHumidity);
    Serial.printf("Soil Moist : %.2f %%\n", normalizedSoilMoisture);
    Serial.printf("Light Int  : %.2f %%\n", normalizedLightIntensity);
    Serial.printf("Water Level: %.2f %%\n", normalizedWaterLevel);
    Serial.printf("Pump State : %s\n", pumpStatusFlag ? "ACTIVE (ON)" : "INACTIVE (OFF)");
    Serial.println("---------------------------------------------------");
    
    // 4. Cloud Streaming Infrastructure Control Loop
    unsigned long currentEpoch = millis();
    if (currentEpoch - precedingTelemetryEpoch >= telemetryTransmissionInterval) {
        precedingTelemetryEpoch = currentEpoch;
        
        if (WiFi.status() == WL_CONNECTED) {
            HTTPClient httpGateway;
            
            // Construct the HTTP POST endpoint payload string
            String networkPayload = String(TS_SERVER) + "?api_key=" + TS_API_KEY 
                                  + "&field1=" + String(airTemperature)
                                  + "&field2=" + String(airHumidity)
                                  + "&field3=" + String(normalizedSoilMoisture)
                                  + "&field4=" + String(normalizedLightIntensity)
                                  + "&field5=" + String(pumpStatusFlag);
                                  
            httpGateway.begin(networkPayload);
            int functionalHttpResponse = httpGateway.GET();
            
            if (functionalHttpResponse > 0) {
                Serial.printf("[CLOUD OK] Telemetry synchronized. Response Code: %d\n", functionalHttpResponse);
            } else {
                Serial.printf("[ERROR] Network post transaction failed. Code: %s\n", httpGateway.errorToString(functionalHttpResponse).c_str());
            }
            httpGateway.end();
        } else {
            Serial.println("[NET WARN] Local link dropped. Buffering cloud update.");
        }
    }
    
    delay(2000); // Standard polling delay loop execution pacing
}