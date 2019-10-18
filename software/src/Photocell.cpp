#include "Photocell.hpp"

#define PHOTOCELL_DIMENSIONS 3

Photocell::Photocell() : 
    Sensor()
{

}

Photocell::~Photocell()
{
    
}

//While using testing code with the sensor, a button was used to simulate separation of the rocket and code was written based off this
// In place of gathering launch data from other sensors


bool Photocell::init()
{
    /*
    //All the pins the photocells are connected to
    int photocellPin1 = 0; 
    int photocellPin2 = 1;
    int photocellPin3 = 4;
    int photocellPin4 = 23;

    int mode = 0;
    int baseline;


    void setup(void) {
        Serial.begin(9600);
        pinMode(0, INPUT);
    }
    */
    return true;
}

Data Photocell::read(Data data)
{
    
    std::vector<float> ret(PHOTOCELL_DIMENSIONS, 0);
    {
        /*
        void loop(void) {
        //int raw = ((analogRead(0)+analogRead(1)+analogRead(4)+analogRead(23))/4) //Average of all Photocell readings

        if (digitalRead(4) == LOW)
        {
            mode = !mode;
            delay(1000);
        }
        
        }
        */
        //return ret;
    }
    // TODO: Set data.photocellData.brightness

    return data;
}

Data Photocell::poll(Data data)
{
    /*
    std::vector<float> ret(PHOTOCELL_DIMENSIONS, 0);
    {
        if (mode === 0) //prelaunch
        {
            baseline = raw;
            Serial.print("baseline: ");
            Serial.println(baseline);
        }
        else if (mode == 1) //Indicates launch
        {
            int diff = raw - baseline;
            Serial.print("Launch ");
            Serial.println(diff)
        }
    }
    delay(500)

    // TODO: Set data.photocellData.brightness
    */
    return data;
}

void Photocell::enable()
{

}

void Photocell::disable()
{

}
