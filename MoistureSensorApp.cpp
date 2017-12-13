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

  on("/", &MoistureSensorApp::handle_root);
}

void MoistureSensorApp::on_loop()
{
  check_sensors();
  handleClient();
}

void MoistureSensorApp::check_sensors(bool check_now)
{
  unsigned long t = millis();

  if (check_now || _last_sensor_read_time == 0 || ((t - _last_sensor_read_time) / 1000) > _sensor_read_interval_seconds)
  {
    _chirp->read_sensors(_moisture_level, _temperature, _light_level);
    Serial.printf("Moisture: %lu, Temperature: %lu, Light Level: %lu\n", _moisture_level, _temperature, _light_level);
    _last_sensor_read_time = t;
  }
}

void MoistureSensorApp::handle_root()
{
  check_sensors(true);
    
  render_page(String("Moisture level = ") + _moisture_level + "\n");
}

