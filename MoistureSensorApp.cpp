#include "MoistureSensorApp.h"

#include "Chirp.h"


MoistureSensorApp::MoistureSensorApp(Chirp *chirp, const String &templates_base_dir, int port, unsigned sensor_read_interval_seconds) :
  OOWebServer<MoistureSensorApp>(templates_base_dir, port),
  _chirp(chirp),
  _sensor_read_interval_seconds(sensor_read_interval_seconds),
  _last_sensor_read_time(0)
{
}

void MoistureSensorApp::server_begin()
{
  _chirp->begin();
}

void MoistureSensorApp::on_loop()
{
  check_sensors();
  handleClient();
}

void MoistureSensorApp::check_sensors()
{
  unsigned long t = millis();

  if (((t - _last_sensor_read_time) / 1000) > _sensor_read_interval_seconds)
  {
    unsigned long moisture_level;
    unsigned long temperature;
    unsigned long light_level;
    
    _chirp->read_sensors(moisture_level, temperature, light_level);
    Serial.printf("Moisture: %lu, Temperature: %lu, Light Level: %lu\n", moisture_level, temperature, light_level);
    _last_sensor_read_time = t;
  }
}

