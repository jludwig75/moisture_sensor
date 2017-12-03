#include <Wire.h>

void writeI2CRegister8bit(int addr, int value) {
  Wire.beginTransmission(addr);
  Wire.write(value);
  Wire.endTransmission();
}

unsigned int readI2CRegister16bit(int addr, int reg) {
  Wire.beginTransmission(addr);
  Wire.write(reg);
  Wire.endTransmission();
  delay(20);
  Wire.requestFrom(addr, 2);
  unsigned int t = Wire.read() << 8;
  t = t | Wire.read();
  return t;
}

class Chirp {
  public:
    Chirp(int sda, int scl, int pwr) : _sda(sda), _scl(scl), _pwr(pwr) {
    }
    void begin() {
      pinMode(_pwr, OUTPUT);
      Wire.begin(_sda, _scl);
    }
    void read_sensors() {
      power_on();
      reset_device();
   
      unsigned long capacitance = 0xFFFF;
    
      while((capacitance = readI2CRegister16bit(0x20, 0)) == 0xFFFF) {
        delay(1000);
        Serial.print(".");
      }
      
      Serial.print("Reading device sensors...\n");
      Serial.print(capacitance); //read capacitance register
      Serial.print(", ");
      //delay(100);
      Serial.print(readI2CRegister16bit(0x20, 5)); //temperature register
      Serial.print(", ");
      writeI2CRegister8bit(0x20, 3); //request light measurement 
      //delay(600);
      Serial.println(readI2CRegister16bit(0x20, 4)); //read light register

      power_off();
    }
  protected:
    void power_on() {
      // Turn on Chirp
      digitalWrite(14, HIGH);
      delay(100);
    }
    void power_off() {
      digitalWrite(14, LOW);
    }
    void reset_device() {
      Serial.print("Resetting device...\n");
      writeI2CRegister8bit(0x20, 6); //reset
      Serial.print("Device reset\n");
    }
  private:
    int _sda;
    int _scl;
    int _pwr;
};

Chirp chirp(12, 13, 14);

void setup() {
  Serial.begin(115200);
  Serial.print("\nStarting sketch...\n");
  chirp.begin();
}


void loop() {
  chirp.read_sensors();
  delay(10000);
}
