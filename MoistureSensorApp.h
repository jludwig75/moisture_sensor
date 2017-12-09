#pragma once

#include "OOWebServer.h"


class Chirp;


class MoistureSensorApp : public OOWebServer<MoistureSensorApp> {
  public:
    MoistureSensorApp(Chirp *chirp, const String &templates_base_dir, int port, unsigned sensor_read_interval_seconds);
    void server_begin();
    void on_loop();
  private:
    void check_sensors();
    Chirp *_chirp;
    unsigned _sensor_read_interval_seconds;
    unsigned long _last_sensor_read_time = 0;
};

