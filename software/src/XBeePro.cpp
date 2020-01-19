#include "XBeePro.hpp"
#include <HardwareSerial.h>

//data and option 
uint8_t data = 0; 
uint8_t option = 0; 

XBeePro::XBeePro() : 
    Transceiver()
{
        //Initiate objects  
    xbee_pro = XBee(); 
    response = XBeeResponse();
    payload = {0}; 
    // 64-bit addressing: This is the SH + SL address of remote XBee
    XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x4008b490);
    // unless you have MY on the receiving radio set to FFFF, this will be received as a RX16 packet
    tx64 = Tx64Request(addr64, payload, sizeof(payload));
    rx64 = Rx64Response();
    txStatus = TxStatusResponse();
}


XBeePro::~XBeePro()
{

}

bool XBeePro::init()
{
    response.init(); //This should init things
        //Check the status code 
    Serial1.begin(9600);
    if(response.getErrorCode() == NO_ERROR) {
        Serial.println("Xbee_pro init is succcessful.\n");
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
   // Serial.println("XBP read Packet");
    if(xbee_pro.getResponse().isAvailable()){ 
        Serial.println("XBP is avaliable");
        if(xbee_pro.getResponse().getApiId() == RX_64_RESPONSE){
                //Recieved a 64 bit message 
                xbee_pro.getResponse().getRx64Response(rx64); 
                option = rx64.getOption(); 
                data = rx64.getData(0); //Get the data from the beginning

                Serial.println("Data received... Here is data");
                Serial.println(data); 
        }
        else{
                Serial.println("ERROR: Did not receive packet."); 
        }
    }
    else if(xbee_pro.getResponse().isError()){
        Serial.println("Error reading packet. Error code: " + xbee_pro.getResponse().getErrorCode()); 
    }
    return ret;
}

bool XBeePro::transmit(Data data)
{
    payload = (uint8_t *)&data;
    xbee_pro.send(tx64);
    return false;
}

void XBeePro::enable()
{ 
    xbee_pro.setSerial(Serial1); 
    response.reset(); 
}

void XBeePro::disable()
{

}
