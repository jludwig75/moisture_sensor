#pragma once



class Chirp {
  public:
    Chirp(int sda, int scl, int pwr);
    void begin();
    void read_sensors(unsigned long & moisture_level, unsigned long & temperature, unsigned long & light_level);
  protected:
    void power_on();
    void power_off();
    void reset_device();
  private:
    int _sda;
    int _scl;
    int _pwr;
};

