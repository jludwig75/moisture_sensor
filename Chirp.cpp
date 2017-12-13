#include "Chirp.h"

#include <Arduino.h>
#include <HardwareSerial.h>
#include <Wire.h>


#define MAX_RETRY_ATTEMPTS  12


static void writeI2CRegister8bit(int addr, int value) {
  Wire.beginTransmission(addr);
  Wire.write(value);
  Wire.endTransmission();
}

static unsigned int readI2CRegister16bit(int addr, int reg) {
  Wire.beginTransmission(addr);
  Wire.write(reg);
  Wire.endTransmission();
  delay(20);
  Wire.requestFrom(addr, 2);
  unsigned int t = Wire.read() << 8;
  t = t | Wire.read();
  return t;
}


Chirp::Chirp(int sda, int scl, int pwr) : _sda(sda), _scl(scl), _pwr(pwr) {
}

void Chirp::begin() {
  pinMode(_pwr, OUTPUT);
  power_off();
  delay(100);
  Wire.begin(_sda, _scl);
}

void Chirp::read_sensors(unsigned long & moisture_level, unsigned long & temperature, unsigned long & light_level) {
  power_on();
  delay(250);
  reset_device();
  delay(100);

  unsigned long capacitance = 0xFFFF;

  unsigned attempts = 0;

  while(attempts < MAX_RETRY_ATTEMPTS && (capacitance = readI2CRegister16bit(0x20, 0)) >= 0xFFFF) {
    delay(250);
    Serial.print(".");
    attempts++;
  }

  moisture_level = capacitance;
  
  //Serial.print("Reading device sensors...\n");
  //Serial.print(capacitance); //read capacitance register
  //Serial.print(", ");
  //delay(100);
  temperature = 0;//readI2CRegister16bit(0x20, 5);
  //Serial.print(temperature); //temperature register
  //Serial.print(", ");
  //writeI2CRegister8bit(0x20, 3); //request light measurement 
  //delay(600);
  light_level = 0;//readI2CRegister16bit(0x20, 4);
  //Serial.println(light_level); //read light register

  power_off();
}

void Chirp::power_on() {
  // Turn on Chirp
  digitalWrite(14, HIGH);
  delay(100);
}

void Chirp::power_off() {
  digitalWrite(14, LOW);
}

void Chirp::reset_device() {
  //Serial.print("Resetting device...\n");
  writeI2CRegister8bit(0x20, 6); //reset
  //Serial.print("Device reset\n");
}

