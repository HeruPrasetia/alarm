#include <Wire.h>         //I2C library
#include <RtcDS3231.h>    //RTC library

RtcDS3231 rtcObject;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(1000);
  rtcObject.Begin();      //Starts I2C
  RtcDateTime currentTime = RtcDateTime(20,06,26,22,33,0);  //manually define date and time object
  rtcObject.SetDateTime(currentTime);                       //configure the RTC with object
}

void loop() {
  // put your main code here, to run repeatedly:
  RtcDateTime currentTime = rtcObject.GetDateTime();    //get the time from the RTC

  char str[15];   //declare a string as an array of chars 

  sprintf(str, "%d/%d/%d %d:%d:%d",     //%d allows to print an integer to the string
                currentTime.Year(),    //get year method
                currentTime.Month(),   //get month method
                currentTime.Day(),     //get day method
                currentTime.Hour(),    //get hour method
                currentTime.Minute(),  //get minute method
                currentTime.Second()   //get second method
  );

  Serial.print("RTC: ");
  Serial.println(str);
  delay(1000);
}
