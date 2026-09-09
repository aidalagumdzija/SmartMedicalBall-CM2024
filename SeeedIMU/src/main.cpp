#include <Arduino.h>
#include <Adafruit_TinyUSB.h>
#include <LSM6DS3.h>
#include <Wire.h>

LSM6DS3 imu(I2C_MODE, 0x6A);

void setup()
{
    Serial.begin(115200);

    while (!Serial)
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
    Serial.println();

    pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);

    Serial.print("Accel X: ");
    Serial.print(imu.readFloatAccelX(), 3);
    Serial.print(" g   Y: ");
    Serial.print(imu.readFloatAccelY(), 3);
    Serial.print(" g   Z: ");
    Serial.print(imu.readFloatAccelZ(), 3);
    Serial.println(" g");

    Serial.print("Gyro  X: ");
    Serial.print(imu.readFloatGyroX(), 2);
    Serial.print(" dps   Y: ");
    Serial.print(imu.readFloatGyroY(), 2);
    Serial.print(" dps   Z: ");
    Serial.print(imu.readFloatGyroZ(), 2);
    Serial.println(" dps");

    Serial.print("Temp: ");
    Serial.print(imu.readTempC(), 1);
    Serial.println(" C");

    Serial.println("------------------------------");

    delay(500);
    //hej 1
}