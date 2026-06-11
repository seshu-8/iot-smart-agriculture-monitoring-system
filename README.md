# IoT-Enabled Smart Agriculture Monitoring System

An industrial-grade, edge-to-cloud cyber-physical precision farming architecture designed to automate microclimate data collection and field irrigation control. This system uses an ESP32 microcontroller to execute localized edge control loops, streams real-time data over Wi-Fi, logs history locally with a Python pipeline, and displays analytics on a cloud dashboard.

## 📌 Problem Statement & Core Value
Manual field monitoring across large agricultural operations leads to significant water waste, delayed irrigation response times, and reduced crop yields. This project addresses these challenges by implementing an automated infrastructure that optimizes water use through sensor feedback loops. It includes dry-run protection for water pumps and tracks environmental data to identify microclimate anomalies before they affect crop health.

## 🛠️ System Architecture & Data Flow
- **Edge Layer:** A virtual ESP32 microcontroller reads data from a DHT22 climate sensor, an analog soil moisture sensor, a solar radiation photoresistor, and a reservoir level sensor.
- **Control Automation Loop:** Local firmware evaluates environmental thresholds to actuate an irrigation relay pump while enforcing system safety overrides if the water reservoir drops below 20%.
- **Network Telemetry Interface:** Data is packetized and transmitted via HTTP requests over Wi-Fi to cloud analytics platforms.
- **Local Data Pipeline:** A standalone Python engine logs structured datasets to local storage for long-term historical analysis.

## 📦 Project Structural Layout
├── firmware/
│   └── smart_agri_esp32.ino    # Production embedded C++ firmware for the ESP32
├── python_simulation/
│   └── mock_telemetry_gen.py   # Automated data validation generator
├── data/
│   └── telemetry_logs.csv      # Appended historical record log file
├── main.py                     # Central Python pipeline execution engine
├── requirements.txt            # Python environment dependency configuration
└── .gitignore                  # Excludes temporary execution files and keys


## 🚀 Installation & System Configuration

### 1. Embedded Firmware Deployment (Wokwi Engine)
1. Copy the code from `firmware/smart_agri_esp32.ino`.
2. Open a blank ESP32 simulator canvas on [Wokwi](https://wokwi.com).
3. Paste the code into the editor tab, configure your network settings, and add your ThingSpeak Write API Key.
4. Press **Start Simulation** to run the virtual edge hardware.

### 2. Local Analytics Pipeline Setup
Run these setup commands in your terminal interface:
```bash
python3 -m venv venv
source venv/activate  # On Windows use: .\venv\Scripts\activate
pip install -r requirements.txt
python main.py
📊 Sample System Output Logs
[CYCLE #02] Profile: DRY_SOIL | Time: 2026-06-08 22:30:12
 -> Env Matrix : Temp: 27.4°C | Humidity: 62.1%
 -> Soil Status: Moisture: 28.3% | Tank Level: 84.2%
 -> System State: Actuator Pump is ACTIVE (ON)
   [ALERT] Soil moisture low. Triggering Active Irrigation System.

[CYCLE #04] Profile: EMPTY_TANK | Time: 2026-06-08 22:30:15
 -> Env Matrix : Temp: 31.2°C | Humidity: 58.4%
 -> Soil Status: Moisture: 19.5% | Tank Level: 12.1%
 -> System State: Actuator Pump is INACTIVE (OFF)
   [CRITICAL] Low moisture detected but blocked by Low Water Safety Lockout!
🎓 Learning Outcomes
Developed embedded firmware applications for the ESP32 using C++.

Designed localized edge computing logic to protect physical hardware assets from dry-run damage.

Built a Python data logging pipeline to process structured telemetry.

Configured end-to-end cloud data ingestion pipelines over Wi-Fi networks.


---

## 1️⃣2️⃣ PROOF BUILDING STRATEGY (6-DAY PROGRESSION PLAN)

Follow this structured, 6-day build schedule to show regular repository activity on GitHub. Recruiters appreciate a consistent, methodical commit history over a single, large code dump.

### Day 1: Setup and Architecture Specification
* **Objective:** Define the system requirements, build your project's folder structure, and set up your ThingSpeak channels.
* **Action:** Commit your baseline directory structure along with a preliminary `README.md` defining the project's goals.
* **Commit Message:** `docs: establish core project architecture and document system requirements in README`

### Day 2: Virtual Circuit Layout Design
* **Objective:** Wire the virtual ESP32 sensor grid on the Wokwi canvas.
* **Action:** Map out all component pins, test the virtual connections, and export the hardware layout schema to `circuit_diagram/wokwi_diagram.json`.
* **Commit Message:** `hw: design and verify virtual ESP32 sensor canvas layout schema`

### Day 3: Embedded Data Acquisition Framework
* **Objective:** Write the core firmware logic to read sensor values.
* **Action:** Build the data acquisition loops for the DHT22 and analog sensors, convert the raw signals into standard units, and print them to the serial monitor.
* **Commit Message:** `firmware: implement non-blocking sensor acquisition loops and ADC normalization scaling`

### Day 4: Edge Automation Logic Integration
* **Objective:** Add edge intelligence and safety cutoffs to the system.
* **Action:** Implement threshold check statements to control the irrigation pump relay automatically and deploy the low-water safety lockout system.
* **Commit Message:** `firmware: embed closed-loop irrigation automation and water tank safety lockout`

### Day 5: Cloud Networking & Telemetry Deployment
* **Objective:** Connect your edge devices to the cloud network layer.
* **Action:** Initialize the ESP32 Wi-Fi stack connection code and configure HTTP payload transfers to push live field measurements to ThingSpeak.
* **Commit Message:** `net: integrate Wi-Fi stack and configure telemetry payload streaming to ThingSpeak cloud`

### Day 6: Analytics Pipeline Data Validation
* **Objective:** Build the local data pipeline and complete the project documentation.
* **Action:** Write the `main.py` Python processing script to handle local CSV logging, capture final system screenshots for the repository, and update the deployment guides.
* **Commit Message:** `analytics: deploy local python data logger pipeline and complete validation documentation`

---

## 1️⃣3️⃣ SCREENSHOTS / OUTPUTS TO CAPTURE

To prove your project works, take these specific screenshots and save them in the `images/` directory of your repository. Reference them in your final documentation:

1.  **Project Root Structure:** Capture your clean development workspace layout within your code editor (e.g., VS Code file explorer view) showing all folders and project files in place.
2.  **Virtual Circuit Layout Schematic:** Take a high-resolution screenshot of the compiled Wokwi wiring canvas showing the ESP32 connected to the sensors and relay.
3.  **Active Operational Telemetry Logs:** Capture the Wokwi serial monitor showing data frames printing systematically at 2-second intervals.
4.  **Active Irrigation System Activation Alert:** Take a screenshot of the terminal window displaying an active irrigation pump command alongside a red warning label when soil moisture drops below 40%.
5.  **Safety Interlock Activation:** Capture the console output showing the safety cutoff in action—low soil moisture present, but the pump blocked because the water level is empty.
6.  **ThingSpeak Cloud Dashboard Charts:** Take a screenshot of your live web browser interface showing the real-time time-series charts updating as you adjust the simulation sliders.
7.  **Persistent CSV Database Spreadsheet:** Open your `data/telemetry_logs.csv` file in a spreadsheet viewer to show rows of clean, structured data with proper column names and timestamps.

---

## 1️⃣4️⃣ INTERVIEW PREPARATION

Be ready to answer these technical questions when presenting this project during technical hiring loops.

### Q1: Can you provide an overview of your IoT project?
* **HR Explanation:** "I built an automated Smart Agriculture system designed to help farmers optimize water consumption and monitor crop health using modern technology. The system measures vital environmental factors like soil moisture and temperature, automatically irrigates fields when needed, and uploads all data to a web dashboard so it can be managed from anywhere. This project demonstrates my ability to design practical, end-to-end solutions combining software development, cloud networking, and hardware design."
* **Technical Explanation:** "I developed an edge-to-cloud cyber-physical system centered around an ESP32 edge computing platform. The firmware is written in modular C++ and handles data collection from a variety of digital and analog sensors (DHT22, LDR, and custom analog probes) using non-blocking execution loops. It runs local real-time threshold check algorithms to actuate an irrigation pump via a relay module while enforcing a low-water safety lockout system at the edge. Telemetry payloads are packaged and transmitted over a Wi-Fi stack using HTTP POST requests to a ThingSpeak cloud engine. Additionally, I built a secondary local Python data pipeline that logs streaming information into an optimized CSV format for historical analytics and system health validation."

### Q2: Why did you choose the ESP32 microcontroller over an Arduino UNO or a Raspberry Pi?
* **Technical Explanation:** "An Arduino UNO lacks native network connectivity, which requires adding expensive network shields and increases power consumption, making it impractical for true edge deployments. A Raspberry Pi runs a full operating system, which provides excellent computing power but draws too much current, has higher hardware costs, and faces data corruption risks if power is suddenly lost in the field. The ESP32 is the ideal choice for this application because it features a native, power-efficient Wi-Fi and Bluetooth stack, includes ample analog-to-digital converter channels, supports hardware sleep modes for battery operation, and delivers excellent processing performance at a low cost."

### Q3: How did you scale and normalize the raw values from your analog sensors into standard units?
* **Technical Explanation:** "The ESP32 features a $12$-bit Analog-to-Digital Converter (ADC), meaning it reads raw input voltages between $0\text{V}$ and $3.3\text{V}$ and converts them into digital values ranging from $0$ to $4095$. In my firmware, I used a linear normalization formula to map these raw numbers into clean percentages ($0\%$ to $100\%$):
$$\text{Percentage} = \left( \frac{\text{Raw Reading}}{4095} \right) \times 100$$
For inverse relationship devices like the soil moisture probe—where lower resistance means more water and results in a lower voltage reading—I modified the formula to invert the output scale:
$$\text{Moisture \%} = \left(1.0 - \frac{\text{Raw Reading}}{4095}\right) \times 100$$
This ensures that completely dry conditions read as $0\%$ and fully saturated soil registers as $100\%$."

### Q4: What is edge computing in the context of your project, and why is it important here?
* **Technical Explanation:** "Edge computing means processing critical logic directly on local devices at the edge of the network, rather than relying on remote cloud servers. In my system, the soil moisture checks and pump safety cutoffs are evaluated immediately on the ESP32. This ensures that irrigation control functions instantly without network delay. More importantly, if the internet connection goes down, the farm's irrigation loops continue running safely because the critical decision logic does not depend on cloud connectivity."

### Q5: What is a 'dry-run' condition, and how does your system handle it?
* **Technical Explanation:** "A dry-run condition occurs when an automated system tries to run a water pump when the supply reservoir is empty. Running a centrifugal pump without fluid causes immediate overheating and permanent mechanical damage. To prevent this, I implemented an interleaved safety loop in the firmware. Even if the soil is dry and requires water, the pump relay cannot turn on unless the reservoir sensor confirms the water level is above $20\%$. If the tank is empty, the system locks out the pump and prints an emergency warning to the console."

### Q6: Why did you use non-blocking timing structures based on `millis()` instead of simple `delay()` functions?
* **Technical Explanation:** "The standard `delay()` function stops the entire processor, halting all operations until the timer completes. If I used a $15$-second `delay()` to pace cloud updates, the microcontroller would be frozen during that time—unable to read sensors, check safety thresholds, or turn off the water pump in an emergency. By using `millis()` timing loops instead, I created a non-blocking architecture. The processor runs at full speed to monitor safety sensors constantly, and only runs the cloud transmission code when the elapsed time matches the target window."

### Q7: If your project needs to connect to an external server, how do you protect secret API keys when sharing code on GitHub?
* **Technical Explanation:** "You should never commit private credentials or API keys directly to public repositories, as unauthorized users can scrape them and exploit your cloud accounts. To protect my keys, I separated my secrets from the main code. In a production environment, I store these configurations in a hidden local environment file (`.env`) that is ignored by Git using rules in the `.gitignore` file. For public display on GitHub, I include a clean template file named `.env.example`, which shows users the variables they need to configure without exposing my private keys."

### Q8: How would you modify your architecture to support hundreds of independent sensor nodes scattered across a large farm?
* **Technical Explanation:** "Direct Wi-Fi connections do not scale well over large geographic areas because Wi-Fi signals have limited range and each device consumes significant battery power. To scale this system to hundreds of nodes, I would switch to a star network topology using **LoRaWAN (Long Range Wide Area Network)** or a mesh network using **Zigbee**. In this layout, low-power sensor nodes run on small batteries, sleep most of the time, and wake up briefly to transmit data over long distances using sub-GHz frequencies to a central gateway. The gateway then collects all these sensor messages and uploads them to the cloud over a single high-speed cellular or internet link."

### Q9: Your Python script logs data locally to a CSV file. What are the limitations of this approach, and how would you fix them for a production system?
* **Technical Explanation:** "Using a standard flat CSV file works well for simple prototyping, but it scales poorly because file sizes grow over time. CSV files lack indexing options, which makes reading data slower as the log grows, and they run into file-lock crashes if multiple scripts try to read and write to the file at the same time. In a production system, I would replace the CSV file with a time-series database engine like **InfluxDB** or an enterprise relational database like **PostgreSQL**. These database tools handle concurrent read/write streams reliably, compress data efficiently, and can process queries across millions of rows instantly."

### Q10: How do you handle network drops or cloud timeouts in your firmware to ensure reliable operation?
* **Technical Explanation:** "In my firmware, I wrapped all network requests in conditional checks that verify connection status using the `WiFi.status()` framework before attempting to send data. If a connection drop occurs, the system skips the cloud upload loop to prevent the firmware from freezing while waiting for a timeout. The local irrigation control logic continues running normally on the edge processor. In a production upgrade, I would add a local non-volatile memory buffer, such as an SD card or the ESP32's built-in Flash memory, to store offline logs during an internet outage and upload them later once the network reconnects."