#include <Arduino.h>
#include "ELMduino.h"


// Hardware Serial 2 pins
#define RXD2 16
#define TXD2 17

ELM327 myELM327;


uint32_t rpm = 0;


void setup()
{
  Serial.begin(115200);
  Serial2.begin(38400, SERIAL_8N1, RXD2, TXD2);
  myELM327.begin(Serial2, false, 2000);
}


void loop()
{
  float tempRPM = myELM327.rpm();
  float speed = myELM327.kph();

  if (myELM327.nb_rx_state == ELM_SUCCESS)
  {
    rpm = (uint32_t)tempRPM;
    Serial.print("RPM: "); Serial.print(rpm);
    Serial.print("\tSpeed: "); Serial.println(speed);
  }
  else if (myELM327.nb_rx_state != ELM_GETTING_MSG)
    myELM327.printError();
}