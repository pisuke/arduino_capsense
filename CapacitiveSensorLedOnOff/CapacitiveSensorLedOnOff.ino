#include <CapacitiveSensor.h>


/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Uses a high value resistor e.g. 10M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 */
int ledPin =  11;
int state = LOW;
int count = 1;

CapacitiveSensor   cs_2_4 = CapacitiveSensor(2, 4);       // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
//CapacitiveSensor   cs_2_6 = CapacitiveSensor(2, 6);       // 10M resistor between pins 4 & 6, pin 6 is sensor pin, add a wire and or foil
//CapacitiveSensor   cs_2_8 = CapacitiveSensor(2, 8);       // 10M resistor between pins 4 & 8, pin 8 is sensor pin, add a wire and or foil

void setup()
{
  //cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  long start = millis();
  long total1 =  cs_2_4.capacitiveSensor(30);
  //long total2 =  cs_2_6.capacitiveSensor(30);
  //long total3 =  cs_2_8.capacitiveSensor(30);
//sensorState = digitalRead(capacitiveSensor);

  Serial.print(millis() - start);        // check on performance in milliseconds
  Serial.print("\t");                    // tab character for debug windown spacing

  Serial.print(total1);                  // print sensor output 1
  Serial.print("\t");
  //Serial.print("total2");
  //Serial.print(total2);                  // print sensor output 2
  //Serial.println("\t");
  //Serial.print("total3");
 // Serial.println(total3);                // print sensor output 3
  if (total1 > 20 && state == LOW) {// || total2 > 99 || total3 > 99 && state == LOW) {//originally 200 for both low and high
    state = HIGH;

    digitalWrite (ledPin,  !digitalRead(ledPin));  //LED on

  }
  
 if (total1 < 20 && state == HIGH)   // only set the state low when the cap sense is really lower 
  {
    state = LOW;
  } 
 
  delay(100);                             // arbitrary delay to limit data to serial port
}
