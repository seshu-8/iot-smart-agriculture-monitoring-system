"""
@file main.py
@brief Central Python Pipeline Engine for Smart Agriculture Project.
Handles data simulation, local CSV logging, real-time analytics,
and threshold validation.
"""

import os
import sys
import time
import csv
import random
from datetime import datetime

# System Infrastructure Constants
DATA_DIRECTORY = "./data"
CSV_LOG_FILE_PATH = os.path.join(DATA_DIRECTORY, "telemetry_logs.csv")
SYSTEM_FIELD_COLUMNS = ["Timestamp", "Temperature_C", "Humidity_Pct", "Soil_Moisture_Pct", "Light_Intensity_Pct", "Water_Level_Pct", "Pump_State"]

# System Threshold Safety Configurations
SOIL_DRYNESS_LIMIT = 40.0
HIGH_TEMP_LIMIT = 40.0
RESERVOIR_LOW_LIMIT = 20.0

def initialize_local_storage():
    """Initializes the storage directory and verifies structural headers inside log assets."""
    if not os.path.exists(DATA_DIRECTORY):
        os.makedirs(DATA_DIRECTORY)
        print(f"[INIT] Created local telemetry directory at: {DATA_DIRECTORY}")
        
    if not os.path.exists(CSV_LOG_FILE_PATH):
        with open(CSV_LOG_FILE_PATH, mode='w', newline='', encoding='utf-8') as base_file:
            csv_writer = csv.writer(base_file)
            csv_writer.writerow(SYSTEM_FIELD_COLUMNS)
        print(f"[INIT] Initialized persistent data storage engine at: {CSV_LOG_FILE_PATH}")

def synthesize_sensor_telemetry(force_anomaly=None):
    """
    Generates realistic environmental telemetry for validation.
    Supports force anomalies to test system alerts under edge cases.
    """
    if force_anomaly == "dry_soil":
        soil_moisture = random.uniform(10.0, 35.0)
        temperature = random.uniform(24.0, 30.0)
        water_level = random.uniform(50.0, 90.0)
    elif force_anomaly == "heatwave":
        soil_moisture = random.uniform(45.0, 60.0)
        temperature = random.uniform(42.0, 52.0)
        water_level = random.uniform(40.0, 70.0)
    elif force_anomaly == "empty_tank":
        soil_moisture = random.uniform(15.0, 35.0)
        temperature = random.uniform(25.0, 32.0)
        water_level = random.uniform(5.0, 18.0)
    else:
        # Standard system operational variations
        soil_moisture = random.uniform(35.0, 85.0)
        temperature = random.uniform(22.0, 38.0)
        water_level = random.uniform(15.0, 95.0)

    humidity = random.uniform(40.0, 80.0)
    light_intensity = random.uniform(10.0, 95.0)
    
    return {
        "timestamp": datetime.now().strftime("%Y-%m-%d %H:%M:%S"),
        "temperature": round(temperature, 2),
        "humidity": round(humidity, 2),
        "soil_moisture": round(soil_moisture, 2),
        "light_intensity": round(light_intensity, 2),
        "water_level": round(water_level, 2)
    }

def execute_edge_decision_logic(telemetry_frame):
    """Applies analytic threshold logic to determine pump states and trigger alerts."""
    pump_state = 0
    alert_messages = []
    
    # 1. Soil & Reservoir Evaluation Logic
    if telemetry_frame["soil_moisture"] < SOIL_DRYNESS_LIMIT:
        if telemetry_frame["water_level"] > RESERVOIR_LOW_LIMIT:
            pump_state = 1
            alert_messages.append("[ALERT] Soil moisture low. Triggering Active Irrigation System.")
        else:
            pump_state = 0
            alert_messages.append("[CRITICAL] Low moisture detected but blocked by Low Water Safety Lockout!")
            
    # 2. Temperature Safety Check
    if telemetry_frame["temperature"] > HIGH_TEMP_LIMIT:
        alert_messages.append(f"[WARNING] Ambient heat spike ({telemetry_frame['temperature']}°C) exceeds safety limits.")
        
    return pump_state, alert_messages

def log_telemetry_to_csv(data_frame, pump_state):
    """Appends data records to the historical file registry."""
    with open(CSV_LOG_FILE_PATH, mode='a', newline='', encoding='utf-8') as log_file:
        csv_writer = csv.writer(log_file)
        csv_writer.writerow([
            data_frame["timestamp"],
            data_frame["temperature"],
            data_frame["humidity"],
            data_frame["soil_moisture"],
            data_frame["light_intensity"],
            data_frame["water_level"],
            pump_state
        ])

def run_simulation_engine(cycles=20):
    """Orchestrates the data pipeline loop, logging, and status tracking."""
    print("\n" + "="*60)
    print("      LAUNCHING COGNITIVE SMART AGRI SIMULATION INTERFACE")
    print("="*60)
    initialize_local_storage()
    
    # Test cases to evaluate edge conditions sequentially
    operational_profiles = ["normal", "dry_soil", "heatwave", "empty_tank", "normal"]
    
    for cycle in range(1, cycles + 1):
        # Rotate through operational scenarios to create an interesting data history
        current_profile = operational_profiles[cycle % len(operational_profiles)]
        telemetry_frame = synthesize_sensor_telemetry(force_anomaly=current_profile)
        
        pump_state, active_alerts = execute_edge_decision_logic(telemetry_frame)
        log_telemetry_to_csv(telemetry_frame, pump_state)
        
        # Display operational diagnostics on the dashboard terminal console
        print(f"\n[CYCLE #{cycle:02d}] Profile: {current_profile.upper()} | Time: {telemetry_frame['timestamp']}")
        print(f" -> Env Matrix : Temp: {telemetry_frame['temperature']}°C | Humidity: {telemetry_frame['humidity']}%")
        print(f" -> Soil Status: Moisture: {telemetry_frame['soil_moisture']}% | Tank Level: {telemetry_frame['water_level']}%")
        print(f" -> System State: Actuator Pump is [{'ON' if pump_state == 1 else 'OFF'}]")
        
        if active_alerts:
            for alert in active_alerts:
                print(f"    \033[91m{alert}\033[0m") # Dynamic red console alert highlights
                
        time.sleep(1.5) # Time scaling accelerator for execution testing

    print("\n" + "="*60)
    print(f"[SUCCESS] Pipeline test run completed.\n[INFO] Total records saved to: {CSV_LOG_FILE_PATH}")
    print("="*60 + "\n")

if __name__ == "__main__":
    try:
        run_simulation_engine()
    except KeyboardInterrupt:
        print("\n[INFO] Pipeline engine shut down cleanly by user.")
        sys.exit(0)