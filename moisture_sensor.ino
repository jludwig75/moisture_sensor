#include "wifi_station.h"
#include "Chirp.h"
#include "MoistureSensorApp.h"
#include "Config.h"
#include "wifi_station.h"

Chirp chirp(CHIRP_SDA_PIN, CHIRP_SCL_PIN, CHIRP_PWR_PIN);

MoistureSensorApp app(&chirp,
                      WEB_SERVER_TEMPLATE_DIR,
                      WEB_SERVER_PORT,
                      CHIRP_SENSOR_READ_INTERVAL_SECONDS);

void setup() {
  Serial.begin(115200);
  Serial.print("\nStarting sketch...\n");

  bool wifi_connected = connect_wifi("Caradhras", "Speak friend.", 20); // About 10 seconds
  if (!wifi_connected)
  {
    Serial.println("Failed to start WiFi! Continuing without WiFi");
  }
  
  app.begin();
}


void loop() {
  app.on_loop();
}
