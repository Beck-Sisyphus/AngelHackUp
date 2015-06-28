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

void outputDataToMonitor()
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

