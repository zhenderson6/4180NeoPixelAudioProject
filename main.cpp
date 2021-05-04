/*
 * Adafruit NeoPixel 8x8 matrix Audio Visulizer Project
 * Zachary Henderson
 * Spring 2021 
 * Section A
 */

#include "mbed.h"
#include "NeoMatrix.h"

#define Color(r, g, b)  ((r&0xFF)<<16 | (g&0xFF) << 8 | (b&0xFF))   // pack colors

#define Red     (Color(255,0,0))
#define Green   (Color(0,255,0))
#define Blue    (Color(0,0,255))

NeoArr array(p18, 1);   // Initialize the array

class microphone
{
public :
    microphone(PinName pin);
    float read();
    operator float ();
private :
    AnalogIn _pin;
};
microphone::microphone (PinName pin):
    _pin(pin)
{
}
float microphone::read()
{
    return _pin.read();
}
inline microphone::operator float ()
{
    return _pin.read();
}

microphone mymicrophone(p16);

int hueToRGB(float h);
void float2LED(float value)
{
    float fnumLED = abs((value - 0.5)/3.3)*100; // can mess with this scaling for better LED output
    int numLED = (int)fnumLED;
    if (numLED > 8) numLED = 8;
    
    static float dh = 360.0 / 5;
    static float x = 0;
    
    for(int i = 0; i < numLED; i++){
        int c = hueToRGB((dh * i) - x);
        array.setPixel(0, 1, 1, 0xff0000);
        array.setPixel(0, i+1, i+1, 0xff0000);
        array.setPixel(0, i+2, i+2, 0xff0000);
        array.setPixel(0, i+3, i+3, 0xff0000);
        array.setPixel(0, i+4, i+4, 0xff0000);
        array.setPixel(0, i+5, i+5, 0xff0000);
        }
    for(int i = numLED; i < 8; i++){
        array.setPixel(0, 1, 1, 0xff0000);
        array.setPixel(0, i+1, i+1, 0xff0000);
        array.setPixel(0, i+2, i+2, 0xff0000);
        array.setPixel(0, i+3, i+3, 0xff0000);
        array.setPixel(0, i+4, i+4, 0xff0000);
        }
    x += 1;
    if (x > 360)
        x = 0;
}

// same thing but for the mic
void mic2LED(int mic){
    static float dh = 360.0 / 5;
    static float x = 0;
    
    int numLED = 0;
    if(mic == 0) numLED = 0;
    else if(mic == 1) numLED = 1;
    else if(mic == 2) numLED = 2;
    else if(mic == 3) numLED = 3;
    else if(mic == 4) numLED = 4;
    else if(mic == 5) numLED = 5;
    else if(mic == 6) numLED = 6;
    else if(mic == 7) numLED = 7;
    else if(mic == 8) numLED = 8;
    
    for(int i = 0; i < numLED; i++){
        int c = hueToRGB((dh * i) - x);
        for(int n=0; n<1; n++){
        for(int i=-8; i<8; i+=2){
        array.drawLine(0, i+n%2,0,i+7+n%2,7,rand()%255,rand()%255,rand()%255);
                    }
                }
    x += 1;
    if (x > 360)
        x = 0; 
}

unsigned short max_range = 0xFFFF;
// function that calls above functions
{
    //for(int i = 0; i < 60; i++){
        float sample;
        float average = 0.67/3.3;//initial DC bias level
        
        int buffer[20];
        
        while(1){
            if (src) {
            // this part works for DAC PCM output //
            float test = (float)waver.dac_data/max_range;
            pc.printf("--%f", abs((test - 0.5)/3.3));
            float2LED(test);
            array.write();
            }
            //------------------------------------//
            else {
            //microphone setup //
            int centervalue;
            for(int i = 0; i < 20; i++){
                sample = mymicrophone;
                //subtract 0.67V DC bias
                average = 0.9999*average + 0.0001*sample;
                
                int micvalue = int(abs((sample - average)*300.0));
                if(i == 1){
                    centervalue = micvalue;
                }
                buffer[i] = micvalue;
                if(i > 10){
                    if(micvalue == buffer[1] && micvalue == buffer[2] && micvalue == buffer[3] &&
                        micvalue == buffer[4] && micvalue == buffer[5] && micvalue == buffer[6] && 
                        micvalue == buffer[7] && micvalue == buffer[8] && micvalue == buffer[9]){
                              centervalue = buffer[1];
                              }
                    }
                int offset = micvalue-centervalue;
                mic2LED(2+offset);
                wait(1.0/4000.0);
                }
                n+=1;
                wait_ms(100);
            array.write();
            }
        }


int main()
{
    
    float bright = 0.2; // 20% brightness for the LED Array 

    array.setBrightness(bright);    // set brightness to default 0.2
    array.clear();

    while (true)
    {
           //Horizontal Scroll ZACH
           for(int i=7;i>=-6;i--){
                char c = 'Z';
                array.clear();
                array.drawChar(0,i,0,c, 255,255,255);
                array.write();
                wait_ms(100);
            }
            for(int i=7;i>=-6;i--){
                char c = 'A';
                array.clear();
                array.drawChar(0,i,0,c, 255,0,255);
                array.write();
                wait_ms(100);
            }
            for(int i=7;i>=-6;i--){
                char c = 'C';
                array.clear();
                array.drawChar(0,i,0,c, 128,255,128);
                array.write();
                wait_ms(100);
            }
            for(int i=7;i>=-6;i--){
                char c = 'H';
                array.clear();
                array.drawChar(0,i,0,c, 0,255,0);
                array.write();
                wait_ms(100);
            }    
///////////////////////////     
// Scrolling Thanks for watching the demo 
                for(int i=7;i>=-6;i--){
                char c = 'T';
                array.clear();
                array.drawChar(0,i,0,c, 128,255,128);
                array.write();
                wait_ms(100);
                }
                                for(int i=7;i>=-6;i--){
                char c = 'H';
                array.clear();
                array.drawChar(0,i,0,c, 255,255,0);
                array.write();
                wait_ms(100);
                }
                                for(int i=7;i>=-6;i--){
                char c = 'A';
                array.clear();
                array.drawChar(0,i,0,c, 255,0,255);
                array.write();
                wait_ms(100);
                }
                                for(int i=7;i>=-6;i--){
                char c = 'N';
                array.clear();
                array.drawChar(0,i,0,c, 255,128,128);
                array.write();
                wait_ms(100);
                }
                                for(int i=7;i>=-6;i--){
                char c = 'K';
                array.clear();
                array.drawChar(0,i,0,c, 255,255,128);
                array.write();
                wait_ms(100);
                }
                                for(int i=7;i>=-6;i--){
                char c = 'S';
                array.clear();
                array.drawChar(0,i,0,c, 255,255,255);
                array.write();
                wait_ms(100);
                }
                        // Shrink and grow rectangle
        for(int i=0; i<4; i++){
            array.clear();
            array.drawFilledRect(0,i,i,7-i,7-i,rand()%255,rand()%255,rand()%255);
            array.write();
            wait_ms(250);
            }
        for(int i=0; i<4; i++){
            array.clear();
            //array.drawRect(0,3-i,3-i,4+i,4+i,Blue);
            array.drawFilledRect(0,3-i,3-i,4+i,4+i,rand()%255,rand()%255,rand()%255);
            array.write();
            wait_ms(250);
            }
        }
    }
}

