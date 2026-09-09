#include <Arduino.h>
#include <Adafruit_TinyUSB.h>
#include <bluefruit.h>
#include <LSM6DS3.h>
#include <Wire.h>

LSM6DS3 imu(I2C_MODE, 0x6A);

// Bluetooth "seriell port"
BLEUart bleuart;


// --------------------------------------------------
// Starta Bluetooth advertising
// --------------------------------------------------
void startAdvertising()
{
    // BLE-flaggor
    Bluefruit.Advertising.addFlags(
        BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE
    );

    // Lägg med sändareffekt
    Bluefruit.Advertising.addTxPower();

    // Lägg till Nordic UART Service
    Bluefruit.Advertising.addService(bleuart);

    // Enhetsnamnet läggs i scan response
    Bluefruit.ScanResponse.addName();

    // Börja annonsera igen automatiskt efter disconnect
    Bluefruit.Advertising.restartOnDisconnect(true);

    // Advertising-intervall
    Bluefruit.Advertising.setInterval(32, 244);

    // Kör snabb advertising i 30 sekunder
    Bluefruit.Advertising.setFastTimeout(30);

    // 0 = annonsera tills någon ansluter
    Bluefruit.Advertising.start(0);
}


// --------------------------------------------------
// Setup
// --------------------------------------------------
void setup()
{
    Serial.begin(115200);

    // Vänta INTE för alltid på USB Serial.
    // Annars kommer programmet stanna här när du kör utan kabel.
    unsigned long startTime = millis();

    while (!Serial && millis() - startTime < 3000)
    {
        delay(10);
    }

    Serial.println("Startar IMU...");

    if (imu.begin() != 0)
    {
        Serial.println("FEL: Kunde inte starta IMU.");

        while (1)
        {
            delay(1000);
        }
    }

    Serial.println("IMU hittad och startad!");

    pinMode(LED_BUILTIN, OUTPUT);

    // --------------------------------------------------
    // Bluetooth
    // --------------------------------------------------

    Serial.println("Startar Bluetooth...");

    Bluefruit.begin();

    // Sändareffekt i dBm
    Bluefruit.setTxPower(4);

    // Namnet som syns på telefon/dator
    Bluefruit.setName("XIAO-IMU");

    // Starta Nordic UART Service
    bleuart.begin();

    // Börja advertising
    startAdvertising();

    Serial.println("Bluetooth startat.");
    Serial.println("Sök efter: XIAO-IMU");
}


// --------------------------------------------------
// Loop
// --------------------------------------------------
void loop()
{
    static unsigned long previousMillis = 0;

    // 100 ms = 10 Hz
    if (millis() - previousMillis < 100)
    {
        return;
    }

    previousMillis = millis();

    // Läs IMU
    float ax = imu.readFloatAccelX();
    float ay = imu.readFloatAccelY();
    float az = imu.readFloatAccelZ();

    float gx = imu.readFloatGyroX();
    float gy = imu.readFloatGyroY();
    float gz = imu.readFloatGyroZ();

    float temp = imu.readTempC();


    // --------------------------------------------------
    // USB Serial
    // --------------------------------------------------

    Serial.print("A: ");
    Serial.print(ax, 3);
    Serial.print(", ");
    Serial.print(ay, 3);
    Serial.print(", ");
    Serial.print(az, 3);

    Serial.print(" | G: ");
    Serial.print(gx, 2);
    Serial.print(", ");
    Serial.print(gy, 2);
    Serial.print(", ");
    Serial.print(gz, 2);

    Serial.print(" | T: ");
    Serial.println(temp, 1);


    // --------------------------------------------------
    // Bluetooth
    // --------------------------------------------------

if (Bluefruit.connected())  {
    bleuart.print("AX: ");
    bleuart.print(ax, 3);

    bleuart.print("  AY: ");
    bleuart.print(ay, 3);

    bleuart.print("  AZ: ");
    bleuart.print(az, 3);

    bleuart.print("  GX: ");
    bleuart.print(gx, 2);

    bleuart.print("  GY: ");
    bleuart.print(gy, 2);

    bleuart.print("  GZ: ");
    bleuart.print(gz, 2);

    bleuart.print("  TEMP: ");
    bleuart.println(temp, 1);
}
}