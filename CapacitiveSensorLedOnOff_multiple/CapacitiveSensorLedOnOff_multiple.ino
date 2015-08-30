#include <CapacitiveSensor.h>


/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Uses a high value resistor e.g. 10M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 */
int ledPin_sleep =  11;
int ledPin_play =  8;
int ledPin_relax =  9;
int ledPin_work =  10;
int ledPin_leave =  12;
int state_sleep = LOW;
int state_play = LOW;
int state_relax = LOW;
int state_work = LOW;
int count = 1;

CapacitiveSensor   cs_2_4 = CapacitiveSensor(2, 4);       // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   cs_2_6_play = CapacitiveSensor(2, 6);       // 10M resistor between pins 4 & 6, pin 6 is sensor pin, add a wire and or foil
CapacitiveSensor   cs_2_8_relax = CapacitiveSensor(2, 8);       // 10M resistor between pins 4 & 8, pin 8 is sensor pin, add a wire and or foil
CapacitiveSensor   cs_2_5_work = CapacitiveSensor(2, 5);  

void setup()
{
  //cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
  Serial.begin(9600);
  pinMode(ledPin_sleep, OUTPUT);
  pinMode(ledPin_play , OUTPUT);
  pinMode(ledPin_relax , OUTPUT);
  pinMode(ledPin_work , OUTPUT);
}

void loop()
{
  long start = millis();
  long total1 =  cs_2_4.capacitiveSensor(20);
  long total2 =  cs_2_6_play.capacitiveSensor(20);
  long total3 =  cs_2_8_relax.capacitiveSensor(20);
  long total4 =  cs_2_5_work.capacitiveSensor(20);
//sensorState = digitalRead(capacitiveSensor);

  Serial.println(millis() - start);        // check on performance in milliseconds
  Serial.print("\t");                    // tab character for debug windown spacing

  Serial.print("total1");
  Serial.print("\t");
  
  Serial.print(total1);                  // print sensor output 1
  Serial.print("\t");
  Serial.print("total2");
  Serial.print("\t");
  Serial.print(total2);                  // print sensor output 2
 Serial.print("\t");
  Serial.print("total3");
  Serial.print("\t");
  Serial.print(total3);                // print sensor output 3
  
  Serial.print("\t");
  Serial.print("total4");
  Serial.print("\t");
  Serial.println(total4);  
  
  if (total1 > 600 && state_sleep == LOW) {//originally 200 for both low and high
    state_sleep = HIGH;

    digitalWrite (ledPin_sleep,  !digitalRead(ledPin_sleep));  //LED on
      

  }
  
 if (total1 < 600 && state_sleep == HIGH)   // only set the state low when the cap sense is really lower 
  {
    state_sleep = LOW;
  } 

  /////play////
  else if (total2 > 100 && state_play == LOW) {//originally 200 for both low and high
    state_play = HIGH;

    digitalWrite (ledPin_play,  !digitalRead(ledPin_play));  //LED on
      

  }
  
 if (total2 < 100 && state_play == HIGH)   // only set the state low when the cap sense is really lower 
  {
    state_play = LOW;
  } 
  
  ////////relax///////
 else if (total3 > 600 && state_relax == LOW) {//originally 200 for both low and high
    state_relax = HIGH;

    digitalWrite (ledPin_relax,  !digitalRead(ledPin_relax));  //LED on
      

  }
  
 if (total3 < 600 && state_relax == HIGH)   // only set the state low when the cap sense is really lower 
  {
    state_relax = LOW;
  } 
  
  /////work/////

   else if (total4 > 200 && state_work == LOW) {//originally 200 for both low and high
    state_work = HIGH;

    digitalWrite (ledPin_work,  !digitalRead(ledPin_work));  //LED on
      
  }
  
 if (total4 < 200 && state_work == HIGH)   // only set the state low when the cap sense is really lower 
  {
    state_work = LOW;
  } 
 
  delay(100);                             // arbitrary delay to limit data to serial port
}
