#include <CapacitiveSensor.h>


/*
 * Capacitive sensor switch for London Design Festival 2015 - 41 A House for London
 * Francesco Anselmo francesco.anselmo@arup.com
 * Uses a high value resistor e.g. 10M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 */

int threshold = 60;

int ledPin1 =  8;
int state1 = LOW;
int ledPin2 =  9;
int state2 = LOW;
int ledPin3 =  10;
int state3 = LOW;
int ledPin4 =  11;
int state4 = LOW;
int ledPin5 =  12;
int state5 = LOW;
int count = 1;

CapacitiveSensor cs_2_3 = CapacitiveSensor(2, 3);  // 10M resistor between pins 3 & 2, pin 3 is sensor pin, add a wire and or foil if desired
CapacitiveSensor cs_2_4 = CapacitiveSensor(2, 4);  // 10M resistor between pins 3 & 2, pin 4 is sensor pin, add a wire and or foil if desired
CapacitiveSensor cs_2_5 = CapacitiveSensor(2, 5);  // 10M resistor between pins 3 & 2, pin 5 is sensor pin, add a wire and or foil if desired
CapacitiveSensor cs_2_6 = CapacitiveSensor(2, 6);  // 10M resistor between pins 3 & 2, pin 6 is sensor pin, add a wire and or foil if desired
CapacitiveSensor cs_2_7 = CapacitiveSensor(2, 7);  // 10M resistor between pins 3 & 2, pin 7 is sensor pin, add a wire and or foil if desired


void setup()
{
  //cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
  Serial.begin(9600);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(ledPin5, OUTPUT);
}

void loop()
{
  long start = millis();
  long total1 =  cs_2_3.capacitiveSensor(30);
  long total2 =  cs_2_4.capacitiveSensor(30);
  long total3 =  cs_2_5.capacitiveSensor(30);
  long total4 =  cs_2_6.capacitiveSensor(30);
  long total5 =  cs_2_7.capacitiveSensor(30);

  Serial.print(millis() - start);        // check on performance in milliseconds
  Serial.print("\t");                    // tab character for debug windown spacing

  printSerial(total1, state1, ledPin1);
  printSerial(total2, state2, ledPin2);
  printSerial(total3, state3, ledPin3);
  printSerial(total4, state4, ledPin4);
  printSerial(total5, state5, ledPin5);

  Serial.println("");

  processCapSensor(total1, state1, ledPin1);
  processCapSensor(total2, state2, ledPin2);
  processCapSensor(total3, state3, ledPin3);
  processCapSensor(total4, state4, ledPin4);
  processCapSensor(total5, state5, ledPin5);
 
  delay(100);                             // arbitrary delay to limit data to serial port
}

void printSerial(int total, int state, int ledPin) {
  Serial.print(total);                  
  Serial.print("\t");
  Serial.print(state);                  
  Serial.print("\t");
  Serial.print(digitalRead(ledPin));                  
  Serial.print("\t");
}

void processCapSensor(int total, int state, int ledPin) {
  if (total > threshold && state == LOW) {
    state = HIGH;
    digitalWrite (ledPin, !digitalRead(ledPin));  
    //digitalWrite (ledPin, state);  
  }
  
 if (total < threshold && state == HIGH)   
  {
    state = LOW;
    //digitalWrite (ledPin, !digitalRead(ledPin));  //LED off
    //digitalWrite (ledPin, state);  
  } 
}



