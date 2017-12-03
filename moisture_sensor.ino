#include "wifi_station.h"
#include "Chirp.h"



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
