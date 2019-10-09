#include <Arduino.h>

#include "GPS.hpp"
#include "IMU.hpp"
#include "Altimeter.hpp"
#include "Logger.hpp"
#include "Photocell.hpp"
#include "XBee.hpp"
#include "Rfm95w.hpp"
#include "Health.hpp"

using namespace std;

IMU *bno;

void setup()
{
    // put your setup code here, to run once:
    pinMode(13, OUTPUT);
    Serial.begin(9600);

    bno = new IMU(true);

    bno->init();
}

void loop()
{
    // put your main code here, to run repeatedly:
    digitalWrite(13, HIGH);
    delay(250);

    vector<float> ret = bno->read();

    Serial.print("X: ");
    Serial.print(ret[0], 4);
    Serial.print("\tY: ");
    Serial.print(ret[1], 4);
    Serial.print("\tZ: ");
    Serial.print(ret[2], 4);
    Serial.println("");
}
