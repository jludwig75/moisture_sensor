#include "wifi_station.h"
#include "Chirp.h"
#include "MoistureSensorApp.h"
#include "Config.h"


Chirp chirp(CHIRP_SDA_PIN, CHIRP_SCL_PIN, CHIRP_PWR_PIN);

MoistureSensorApp app(&chirp,
                      WEB_SERVER_TEMPLATE_DIR,
                      WEB_SERVER_PORT,
                      CHIRP_SENSOR_READ_INTERVAL_SECONDS);

void setup() {
  Serial.begin(115200);
  Serial.print("\nStarting sketch...\n");
  app.begin();
}


void loop() {
  app.on_loop();
}
