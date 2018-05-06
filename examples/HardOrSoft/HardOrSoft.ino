#include <SoftwareSerial.h>
#include <AnySerial.h>

SoftwareSerial SoftSerial(10,11);
AnySerial * as_hw;
AnySerial * as_sw;

void setup()
{
  Serial.begin(9600);
  as_hw = new AnySerial(&Serial);
  as_sw = new AnySerial(&SoftSerial);
  as_sw->print("SW: Setup ");as_sw->println(" finished");as_sw->flush();
  as_hw->print("HW: setup");as_hw->println(" finished");as_hw->flush();
}

void loop()
{
  as_sw->println("SW: loop");
  as_hw->println("HW: loop");
  delay(500);
}


