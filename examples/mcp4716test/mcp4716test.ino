#include <Wire.h>
#include "MCP47x6.h"

// see the .h file for detailed informations
// this is mainly for testing the device, in real life you might use static objects


// dynamic create object with default adress 0x60
MCP47x6base * mcp47x6 = new MCP4726;   // classes are MCP4706, MCP4716 and MCP4726

// dynamic create object with different adress
const byte i2cMCP4716 = 0x60;                                // <-- change this
// MCP47x6base * mcp47x6 = new MCP4716(i2cMCP4716);

byte bits = mcp47x6->getBits();

void setup() {
  Serial.begin(115200);

  Wire.begin();
  //Wire.setClock(400000L);

  if (!mcp47x6->devicepresent()) {
    Serial.println("Device not found");
  } else {
    Serial.print("Device found, ");
    Serial.print(mcp47x6->getBits());
    Serial.print(" bits ");
    Serial.println();
  }

  mcp47x6->setReference(MCP47x6base::supplyunbuff);
}

void loop() {
  static int sawtooth = 0;
  static bool outref = false;

  mcp47x6->setVOut(sawtooth);
  /**/
  sawtooth++;
  if (sawtooth > ((1 << bits) - 1)) {
    sawtooth = 0;

    if (outref) {
      mcp47x6->setReference(MCP47x6base::supplyunbuff);
    } else {
      mcp47x6->setReference(MCP47x6base::refpinunbuff);
    }

    outref = !outref;
  }
  /**/
}

/*
   for this test, Vref is conneced to 3.3V. This should generate an alternating
   sawtooth with 5 V and 3.3 V height.

   Stuff is slow. At least two bytes per bit set. 
 
   Some measurements:
    i2c       100khz     400khz
    4706      12 Hz      34 Hz   
    4716      2.9 Hz     8 Hz
    4726      0.7 Hz     1 Hz
*/



