#include <Arduino.h>
#include <Adafruit_TinyUSB.h>
#include <bluefruit.h>
#include <LSM6DS3.h>
#include <Wire.h>
#include <math.h>

LSM6DS3 imu(I2C_MODE, 0x6A);
BLEUart bleuart; // Bluetooth "seriell port"

float ax, ay, az; // Acceleration i g-krafter
float atot; // Total acceleration

bool sampleTimer();
void getIMUdata();
void printToBluetooth();
void printToSerialMonitor();

enum ballState {
    IDLE,
    MOVING,
    IMPACT
};

// ----- Starta Bluetooth advertising ---------------------------------
void startAdvertising() {
    Bluefruit.Advertising.addFlags( // BLE-flaggor
        BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE
    );
    Bluefruit.Advertising.addTxPower(); // Lägg med sändareffekt
    Bluefruit.Advertising.addService(bleuart); // Lägg till Nordic UART Service
    Bluefruit.ScanResponse.addName(); // Enhetsnamnet läggs i scan response
    Bluefruit.Advertising.restartOnDisconnect(true); // Börja annonsera igen automatiskt efter disconnect
    Bluefruit.Advertising.setInterval(32, 244); // Advertising-intervall
    Bluefruit.Advertising.setFastTimeout(30); // Kör snabb advertising i 30 sekunder
    Bluefruit.Advertising.start(0); // 0 = annonsera tills någon ansluter
}


// ----- Setup ---------------------------------------------
void setup() {
    Serial.begin(115200);

    // Vänta INTE för alltid på USB Serial.
    // Annars kommer programmet stanna här när du kör utan kabel.
    unsigned long startTime = millis();

    while (!Serial && millis() - startTime < 3000) {
        delay(10);
    }

    Serial.println("Startar IMU...");

    if (imu.begin() != 0) {
        Serial.println("FEL: Kunde inte starta IMU.");

        while (1)
        {
            delay(1000);
        }
    }

    Serial.println("IMU hittad och startad!");

    pinMode(LED_BUILTIN, OUTPUT);

    // ----- Bluetooth ---------------------------------------------
    Serial.println("Startar Bluetooth...");
    Bluefruit.begin();
    Bluefruit.setTxPower(4); // Sändareffekt i dBm
    Bluefruit.setName("XIAO-IMU"); // Namnet som syns på telefon/dator
    bleuart.begin(); // Starta Nordic UART Service
    startAdvertising(); // Börja advertising

    Serial.println("Bluetooth startat.");
    Serial.println("Sök efter: XIAO-IMU");

}

// ----- Loop ---------------------------------------------
void loop() {
    // Kontrollera om det är dags att ta ett nytt sample
    if (!sampleTimer()) {
        return;
    }

    //Get IMU data
    getIMUdata();

    //Print data to bluetooth and serial monitor
    printToBluetooth();
    printToSerialMonitor();

    
}

// ----- Hjälpfunktioner ---------------------------------------------
String stateToString(ballState state) {
    switch (state) {
        case IDLE:
            return "IDLE";
        case MOVING:
            return "MOVING";
        case IMPACT:
            return "IMPACT";
        default:
            return "UNKNOWN";
    }
}

bool sampleTimer() {
    static unsigned long lastSampleTime = 0;
    unsigned long currentMillis = millis();

    // Sample every 100 ms (10 Hz)
    if (currentMillis - lastSampleTime >= 100) {
        lastSampleTime = currentMillis;
        return true;
    }
    return false;
}

void getIMUdata() {
    // Läs av accelerometer
    ax = imu.readFloatAccelX();
    ay = imu.readFloatAccelY();
    az = imu.readFloatAccelZ();

    // Beräkna total acceleration
    atot = sqrt(ax * ax + ay * ay + az * az);
}

void printToBluetooth() {
    //bleuart.printf("A:%.2f,%.2f,%.2f\n", ax, ay, az);
        if (atot > 2) {
            bleuart.println("IMPACT!");
        }
    bleuart.printf("Atot: %.2f\n", atot);
}

void printToSerialMonitor() {
    if (atot > 2) {
        Serial.println("IMPACT!");
    }
    Serial.printf("Atot: %.2f \n", atot);
}