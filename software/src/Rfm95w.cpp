#include "Rfm95w.hpp"
#include <SPI.h>
#include <RH_RF95.h>

#define RFM95_CS 4
#define RFM95_RST 2
#define RFM95_INT 3

#define TLED 8

// Change to 434.0 or other frequency, must match RX's freq!
#define RF95_FREQ 433.0

// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);

int16_t packetnum = 0;  // packet counter, we increment per xmission

Rfm95w::Rfm95w() :
    Transceiver()
{

}

Rfm95w::~Rfm95w()
{
    
}

bool Rfm95w::init()
{
	pinMode(LED, OUTPUT);
	pinMode(RFM95_RST, OUTPUT);
	digitalWrite(RFM95_RST, HIGH);

	while (!Serial);
	Serial.begin(9600);
	delay(100);

	Serial.println("Arduino LoRa RX Test!");

	// manual reset
	digitalWrite(RFM95_RST, LOW);
	delay(10);
	digitalWrite(RFM95_RST, HIGH);
	delay(10);

	while (!rf95.init()) {
		Serial.println("LoRa radio init failed");
		while (1);
	}
	Serial.println("LoRa radio init OK!");

	// Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM
	if (!rf95.setFrequency(RF95_FREQ)) {
		Serial.println("setFrequency failed");
		while (1);
	}
	Serial.print("Set Freq to: "); Serial.println(RF95_FREQ);

	// Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on

	// The default transmitter power is 13dBm, using PA_BOOST.
	// If you are using RFM95/96/97/98 modules which uses the PA_BOOST transmitter pin, then 
	// you can set transmitter powers from 5 to 23 dBm:
	rf95.setTxPower(23, false);

    return true;
}

std::vector<float> Rfm95w::receive()
{
	std::vector<float> ret(1, 0);
	if (rf95.available())
	{
		// Should be a message for us now   
		uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
		uint8_t len = sizeof(buf);

		if (rf95.recv(buf, &len))
		{
			digitalWrite(LED, HIGH);
			RH_RF95::printBuffer("Received: ", buf, len);
			Serial.print("Got: ");
			Serial.println((char*)buf);
			Serial.print("RSSI: ");
			Serial.println(rf95.lastRssi(), DEC);

			// Send a reply
			uint8_t data[] = "And hello back to you";
			rf95.send(data, sizeof(data));
			rf95.waitPacketSent();
			Serial.println("Sent a reply");
			digitalWrite(LED, LOW);
		}
		else
		{
			Serial.println("Receive failed");
		}
	}
    return ret;
}

bool Rfm95w::transmit(Data data)
{
	Serial.println("Sending to rf95_server");
	// Send a message to rf95_server

	packetnum++; 
	rf95.send((uint8_t*)data, 20); //got to fix this laters

	Serial.println("Waiting for packet to complete..."); delay(10);
	rf95.waitPacketSent();
	// Now wait for a reply
	uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
	uint8_t len = sizeof(buf);

	Serial.println("Waiting for reply..."); delay(10);
	if (rf95.waitAvailableTimeout(1000))
	{
		// Should be a reply message for us now   
		if (rf95.recv(buf, &len))
		{
			Serial.print("Got reply: ");
			Serial.println((char*)buf);
			String str((char*)buf);
			if (str.startsWith("$GPGGA")) {
				digitalWrite(TLED, HIGH);
				delay(200);
				digitalWrite(TLED, LOW);
				delay(200);
				digitalWrite(TLED, HIGH);
				delay(200);
				digitalWrite(TLED, LOW);
				delay(200);
			}
			Serial.print("RSSI: ");
			Serial.println(rf95.lastRssi(), DEC);
		}
		else
		{
			Serial.println("Receive failed");
		}
	}
	else
	{
		Serial.println("No reply, is there a listener around?");
	}
	delay(1000);
    return false;
}

void Rfm95w::enable()
{
	pinMode(powerpin, OUTPUT);
	digitalWrite(HIGH); 
}

void Rfm95w::disable()
{
	pinMode(powerpin, OUTPUT);
	digitalWrite(LOW); 
}
