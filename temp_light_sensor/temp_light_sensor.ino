/*
@Author Alp
Let's make a digital thermometer.. and add a photoresistor to get the temperature and luminance of an area. 
The thermistor conversions and pieces of code could be found on http://playground.arduino.cc/ComponentLib/Thermistor2 .
*/

#include <math.h>
#include <Time.h> 

int thermistorPin = A0; //analog pin 0
double tSaved = 0; //readable Temperature value
double tMax = 0;
double tMin = 100;
int LDR_Pin = A1; //analog pin 1
int lightVal = 0;
double luminance = 0.0; //readable percentage format for luminance.
boolean initFlag = true;
int ledOutPin = 3;
int pushButtonPin = 2;
int buttonState = 0;
int oldButtonState = 1;
int lightState = 1; //readable state of light
int serialSendingDelay = 10*60*1000; //miliseconds - AKA set to 10 minutes
int oldLightState = 0;
unsigned long lastUpdateTime = 0;
int buttonPressed = 0;

double Thermistor(int RawADC) {
 double Temp;
 Temp = log(10000.0*((1024.0/RawADC-1))); 
 Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
 Temp = Temp - 273.15; // Convert Kelvin to Celcius
 return Temp;
}

int lightStateHandler() {
  buttonState = digitalRead(pushButtonPin);
  //Serial.println(buttonState);
  if(oldButtonState != buttonState)
  {
    oldButtonState = buttonState;
    if(oldButtonState==0)
    {
      buttonPressed = 1;
      if(lightState==0)
      {
        lightState = 1;
      }
      else
      {
        lightState = 0;
      }      
      //Serial.println(lightState?"On":"Off");
      digitalWrite(ledOutPin, lightState);
    }
  }
  return buttonPressed;   
}
int getLightState () {
     return lightState;
}

void printAll(){
  double luminance = (1024-lightVal);
//  Serial.print("TIME-");
//  Serial.print(millis()/1000);
//  Serial.print(" ");
//  
  Serial.print(tSaved);
  Serial.print(":");
  Serial.print(getLightState());
  Serial.print(":");
  Serial.println(luminance/10.24);
}


void setup(){
  
  pinMode(ledOutPin, OUTPUT);
  pinMode(pushButtonPin, INPUT);
  Serial.begin(9600);
}

void loop(){
  int LDRReading = analogRead(LDR_Pin); 
  int thermistorReading = analogRead(thermistorPin); 
  double tCurrent = Thermistor(thermistorReading);
  unsigned long currentTime = millis();
  
  buttonPressed = lightStateHandler(); //burda biraz trick var, değeri değiştirmeden önce eski değeri alıyorum. 
  
  if((tCurrent > tSaved+0.15) || (tCurrent < tSaved-0.15)){
    if(tCurrent>tMax) tMax = tCurrent;
    if(tCurrent<tMin) tMin = tCurrent;
    tSaved = tCurrent;
  }
  if((lightVal+15 < LDRReading) || (lightVal-15 > LDRReading))
  {
    lightVal = LDRReading;
  }
  
  if(currentTime>lastUpdateTime+serialSendingDelay)
  {
    printAll();
    lastUpdateTime = currentTime;
  }
  else if(initFlag) {
    printAll();
    initFlag = false;
  }
  else if(buttonPressed == 1)
  {
    printAll();
    lastUpdateTime = currentTime;
    buttonPressed = 0;
  } 
  else
  {
    //do nothing, wait-don't send data.
    delay(100); //just here to slow down the output for easier reading
  }
}
