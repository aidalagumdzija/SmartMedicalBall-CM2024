#include <Arduino.h>
#include <Adafruit_TinyUSB.h>
#include <bluefruit.h>
#include <LSM6DS3.h>
#include <Wire.h>
#include <math.h>

LSM6DS3 imu(I2C_MODE, 0x6A);
BLEUart bleuart; // Bluetooth "seriell port"

//----- Variabler ---------------------------------------------

float ax, ay, az; // Acceleration i g-krafter
float atot; // Total acceleration
int repCounter = 0; // Räknar antal repetitioner

//----- Funktioner ---------------------------------------------

void startAdvertising();
bool sampleTimer();
void getIMUdata();
void printToBluetooth();
void printToSerialMonitor();
void detectBallState();
bool throwingDetected();
bool isBallIdle ();
void updateHistory();   

//----- Konstanter ---------------------------------------------

const float idleMax = 1.2; // Max acceleration i g-krafter för att vara i IDLE
const float idleMin = 0.8; // Min acceleration i g-krafter för att vara i IDLE
const float throwThreshold = 1.5; 
const float impactThreshold = 5.0; 
const float freeFallThreshold = 0.5; 

//----- Array ---------------------------------------------

const int historySize = 5;
float accelerationHistory[historySize] = {0}; // Array för att lagra historiska accelerationsvärden
int historyIndex = 0; // Index för att hålla reda på var i arrayen vi är

//----- Enumerations ---------------------------------------------

enum ballState {
    IDLE,
    THROWING,
    FREE_FALL1,
    IMPACT,
    FREE_FALL2,
    REP_DONE
};

ballState currentState = IDLE;


// ----- Setup & Bluetooth --------------------------------
void setup() {

    if (imu.begin() != 0) {
        while (1)
        {
            delay(1000);
        }
    }

    Bluefruit.begin();
    Bluefruit.setTxPower(4); // Sändareffekt i dBm
    Bluefruit.setName("1.BOB"); // Namnet som syns på telefon/dator
    bleuart.begin(); // Starta Nordic UART Service
    startAdvertising(); // Börja advertising av Bluetooth

    /* 
    // Serial setup 
    Serial.begin(115200);
    // Vänta INTE för alltid på USB Serial.
    // Annars kommer programmet stanna här när du kör utan kabel.
    unsigned long startTime = millis();
    while (!Serial && millis() - startTime < 3000) {
        delay(10);
    }
    Serial.println("Startar IMU...");
    Serial.println("IMU hittad och startad!");
    pinMode(LED_BUILTIN, OUTPUT);
    */
}

// ----- Loop ---------------------------------------------
void loop() {
    // Kontrollera om det är dags att ta ett nytt sample
    if (!sampleTimer()) {
        return;
    }

    getIMUdata();
    updateHistory();
    detectBallState();
    printToBluetooth();
}

// ----- Hjälpfunktioner ---------------------------------------------
bool sampleTimer() {
    static unsigned long lastSampleTime = 0;
    unsigned long currentMillis = millis();

    // Sample every 10 ms (100 Hz)
    if (currentMillis - lastSampleTime >= 10) {
        lastSampleTime = currentMillis;
        return true;
    }
    return false;
}

void detectBallState() {
    switch (currentState) {
    case IDLE:
        if (throwingDetected()) {
            currentState = THROWING;
        }
        break;

    case THROWING:
        if(atot < freeFallThreshold) {
            currentState = FREE_FALL1;
        }
        break;

    case FREE_FALL1:
        if(atot > impactThreshold) {
            currentState = IMPACT;
        }
        break;

    case IMPACT:
        if(atot < freeFallThreshold) {
            currentState = FREE_FALL2;
        }
        break;

    case FREE_FALL2:
        if(isBallIdle()) {
            currentState = REP_DONE;
        }
        break;

    case REP_DONE:
        if(isBallIdle()) {
            bleuart.println("Repetition klar!");
            repCounter++;
            currentState = IDLE;
        }
        break;
    
    default:
        break;
    }
}

bool throwingDetected() {
    int increasingValues = 0;

    for(int i = 0; i < historySize - 1; i++) {  //räkna antalet ökande värden i historiken
        int current = (historyIndex + i) % historySize;
        int next = (historyIndex + i + 1) % historySize;

        if(accelerationHistory[next] > accelerationHistory[current]) {
            increasingValues++;
        }
    }

    if(increasingValues >= 3 && atot > throwThreshold) {  
        return true;
    }
    return false;
}

bool isBallIdle () {
    for(int i = 0; i < historySize; i++) {
        if (accelerationHistory[i] < idleMin || accelerationHistory[i] > idleMax) {
            return false;
        }
    }
    return true;
}

void updateHistory() {
    accelerationHistory[historyIndex] = atot;
    historyIndex++;
    if(historyIndex >= historySize) {
        historyIndex = 0; // Börja om array
    }
}

void getIMUdata() {
    // Läs av accelerometer
    ax = imu.readFloatAccelX();
    ay = imu.readFloatAccelY();
    az = imu.readFloatAccelZ();

    // Beräkna total acceleration
    atot = sqrt(ax * ax + ay * ay + az * az);
}

String stateToString(ballState state) {
    switch (state) {
        case IDLE:
            return "IDLE";
        case THROWING:
            return "THROWING";
        case FREE_FALL1:
            return "FREE_FALL1";
        case IMPACT:
            return "IMPACT";
        case FREE_FALL2:
            return "FREE_FALL2";
        case REP_DONE: 
            return "REP_DONE";
        default:
            return "UNKNOWN";
    }
}

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

void printToBluetooth() {
    if (Bluefruit.connected()) {
        //bleuart.printf("A:%.2f,%.2f,%.2f\n", ax, ay, az);
        //bleuart.printf("Atot: %.2f\n", atot);
        /*
        bleuart.printf("A: %.2f  S: %s  R: %d\r\n",
                         atot, stateToString(currentState).c_str(), repCounter);
                         */
        char buffer[40];

        snprintf(buffer, sizeof(buffer),
                 "A: %.2f  S: %s  R: %d",
                 atot,
                 stateToString(currentState).c_str(),
                 repCounter);

        bleuart.println(buffer);
    }
}