int currentValue;
int maxValue;
int minValue;
unsigned long timer;
int timer2;

float brightness;
int hue;
int saturation;

const int ShiftPWM_latchPin=8;
const bool ShiftPWM_invertOutputs = false;
const bool ShiftPWM_balanceLoad = false;

#include <ShiftPWM.h>

int sampleSpan = 5; // Amount in milliseconds to sample data
//int lightSpan = 5;

int volume; // this roughly goes from 0 to 700
int threshold;



unsigned char maxBrightness = 255;
unsigned char pwmFrequency = 75;
int numRegisters = 2;
int numRGBleds = numRegisters*8/3;




void setup(){
  Serial.begin(9600);

  ShiftPWM.SetAmountOfRegisters(numRegisters);
  ShiftPWM.SetPinGrouping(1);
  ShiftPWM.Start(pwmFrequency,maxBrightness);


  resetValues();

  
  
}



void loop()
{    
    threshold = map(analogRead(A1),0,1024,0,200);
    

   currentValue = analogRead(A0);
    
   

    if (currentValue < minValue) {
        minValue = currentValue;
    } 
    if (currentValue > maxValue) {
        maxValue = currentValue;
    }

    
    if (millis() - timer >= sampleSpan) {
        volume = maxValue - minValue;
        brightness = 0;
        Serial.println(volume);

        resetValues();
    }

      if(volume > threshold){
        brightness = map(volume,0,200,0,255);
  
        Serial.println("yes");
   
      }


      if(brightness<=0){
        brightness = 0;
      }
      

      
      ShiftPWM.SetHSV(random(numRGBleds),random(360),255,brightness);

      //brightness = 0;   
  

    
}




void resetValues()
{
    currentValue = analogRead(A0);
    maxValue = 0;
    minValue = 1024;
    timer = millis(); 
}


