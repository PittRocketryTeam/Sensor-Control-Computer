#include "XBeePro.hpp"

//Initiate objects  
XBee xbee_pro = XBee(); 
XBeeResponse response = XBeeResponse();
uint8_t payload[] = {0 , 0}; 
Tx16Request tx16 = Tx16Request(0x1874, payload, sizeof(payload)); 
Rx16Response rx16 = Rx16Response();
Rx64Response rx64 = Rx64Response();
TxStatusResponse txStatus = TxStatusResponse();
//Testing idk
int statusLed = 11;
int errorLed = 12; 
int dataLed = 10; 

//data and option 
uint8_t data = 0; 
uint8_t option = 0; 

XBeePro::XBeePro() : 
    Transceiver()
{

}

bool XBeePro::init()
{
    response.init(); //This should init things
        //Check the status code 

    if(response.getErrorCode() == NO_ERROR) {
        Serial.println("Initialization is succcessful.\n");
        return true;
    }  
    else{
        Serial.println("Xbee_pro init failed");
        return false;
    }
    return false; 
}

std::vector<float> XBeePro::receive()
{
    std::vector<float> ret(1, 0);
    xbee_pro.readPacket(); //Read the packet 
    if(xbee_pro.getResponse().isAvailable()){ 
        if(xbee_pro.getResponse().getApiId() == RX_16_RESPONSE){
                //Recieved a 16 bit message 
                xbee_pro.getResponse().getRx16Response(rx16); 
                option = rx16.getOption(); 
                data = rx16.getData(0); //Get the data from the beginning

                Serial.println("Data received... Here is data");
                Serial.println(data); 
                //I guess you flash the led to signal that you will be writing the message has been received 
                Serial.println("Recieved packet. Now writing...");
                //analogWrite(dataLed, data);
        }
        else{
                Serial.println("Did not receive packet. ERROR"); 
        }
    }
    else if(xbee_pro.getResponse().isError()){
        Serial.println("Error reading packet. Error code: " + xbee_pro.getResponse().getErrorCode()); 
    }
    return ret;
}

bool XBeePro::transmit(Data data)
{
    //Just send the timestamp data for now 
    *payload = {(uint8_t)data.timestamp};
    xbee_pro.send(tx16);
    return false;
}

void XBeePro::enable()
{
    //Setup
    pinMode(statusLed, OUTPUT);
    pinMode(errorLed, OUTPUT); 
    pinMode(dataLed,  OUTPUT);
    Serial.begin(9600); 
    xbee_pro.setSerial(Serial); 
}

void XBeePro::disable()
{

}
