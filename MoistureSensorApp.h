#pragma once

#include "OOWebServer.h"


class Chirp;


class MoistureSensorApp : public OOWebServer<MoistureSensorApp> {
  public:
    MoistureSensorApp(Chirp *chirp, const String &templates_base_dir, int port, unsigned sensor_read_interval_seconds);
    void server_begin();
    void on_loop();
  private:
    void handle_root();
    
    void check_sensors(bool check_now = false);
    
    Chirp *_chirp;
    unsigned _sensor_read_interval_seconds;
    unsigned long _last_sensor_read_time = 0;

    unsigned long _moisture_level;
    unsigned long _temperature;
    unsigned long _light_level;
};

