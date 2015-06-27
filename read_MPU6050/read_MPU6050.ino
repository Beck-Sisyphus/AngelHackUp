#include <Wire.h>

const int MPU = 0x68;  // I2C address of the MPU-6050

int AcX[7] = {0, 0, 0, 0, 0, 0, 0};
int AcY[7] = {0, 0, 0, 0, 0, 0, 0};
int AcZ[7] = {0, 0, 0, 0, 0, 0, 0};
int Tmp[7] = {0, 0, 0, 0, 0, 0, 0};
int GyX[7] = {0, 0, 0, 0, 0, 0, 0};
int GyY[7] = {0, 0, 0, 0, 0, 0, 0};
int GyZ[7] = {0, 0, 0, 0, 0, 0, 0};

int AcXAvg = 0;
int AcYAvg = 0;
int AcZAvg = 0;
int GyXAvg = 0;
int GyYAvg = 0;
int GyZAvg = 0;

void setup()
{
    Wire.begin();
    Wire.beginTransmission(MPU);
    Wire.write(0x6B);  // PWR_MGMT_1 register
    Wire.write(0);     // set to zero (wakes up the MPU-6050)
    Wire.endTransmission(true);
    Serial.begin(9600);
    Serial.println("STARTING");
}

void loop()
{
    readMPU6050();
    avgArrays();
    outputData();
    reset();
}

void readMPU6050()
{
    for (int i = 0; i <= 6; i++) {
        Wire.beginTransmission(MPU);
        Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
        Wire.endTransmission(false);
        Wire.requestFrom(MPU, 14, true);  // request a total of 14 registers
        AcX[i] = Wire.read() << 8 | Wire.read();  // 0x3B (ACCEL_XOUT_H)   &   0x3C (ACCEL_XOUT_L)    
        AcY[i] = Wire.read() << 8 | Wire.read();  // 0x3D (ACCEL_YOUT_H)   &   0x3E (ACCEL_YOUT_L)
        AcZ[i] = Wire.read() << 8 | Wire.read();  // 0x3F (ACCEL_ZOUT_H)   &   0x40 (ACCEL_ZOUT_L)
        Tmp[i] = Wire.read() << 8 | Wire.read();  // 0x41 (TEMP_OUT_H)     &   0x42 (TEMP_OUT_L)
        GyX[i] = Wire.read() << 8 | Wire.read();  // 0x43 (GYRO_XOUT_H)    &   0x44 (GYRO_XOUT_L)
        GyY[i] = Wire.read() << 8 | Wire.read();  // 0x45 (GYRO_YOUT_H)    &   0x46 (GYRO_YOUT_L)
        GyZ[i] = Wire.read() << 8 | Wire.read();  // 0x47 (GYRO_ZOUT_H)    &   0x48 (GYRO_ZOUT_L)
        delay(333);
    }   
}

int avgArrays()
{
    for (int i = 0; i <= 6; i++) {
        AcXAvg += AcX[i];
        AcYAvg += AcY[i];
        AcZAvg += AcZ[i];
        GyXAvg += GyX[i];
        GyYAvg += GyY[i];
        GyZAvg += GyZ[i];
    }
    AcXAvg /= 7;
    AcYAvg /= 7;
    AcZAvg /= 7;
    GyXAvg /= 7;
    GyYAvg /= 7;
    GyZAvg /= 7;
}

void outputData()
{
    Serial.print(AcXAvg);
    Serial.print(", ");
    Serial.print(AcYAvg);
    Serial.print(", ");
    Serial.print(AcZAvg);
    Serial.print(", ");
    Serial.print(GyXAvg);
    Serial.print(", ");
    Serial.print(GyYAvg);
    Serial.print(", ");
    Serial.println(GyZAvg);
}

void reset()
{
    AcXAvg = 0;
    AcYAvg = 0;
    AcZAvg = 0;
    GyXAvg = 0;
    GyYAvg = 0;
    GyZAvg = 0;
}
