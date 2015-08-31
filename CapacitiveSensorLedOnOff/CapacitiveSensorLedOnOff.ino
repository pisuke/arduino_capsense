#include <CapacitiveSensor.h>


/*
 * Capacitive sensor switch for London Design Festival 2015 - 41 A House for London
 * Francesco Anselmo francesco.anselmo@arup.com
 * Uses a high value resistor e.g. 10M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 */

int threshold = 50;
int samples = 50;
long debounceDelay = 2000;    // the debounce time; increase if the output flickers

int ledPin1 =  8;
int state1 = LOW;
int lastreading1 = 0;
int ledPin2 =  9;
int state2 = LOW;
int lastreading2 = 0;
int ledPin3 =  10;
int state3 = LOW;
int lastreading3 = 0;
int ledPin4 =  11;
int state4 = LOW;
int lastreading4 = 0;
int ledPin5 =  12;
int state5 = LOW;
int lastreading5 = 0;
int count = 1;

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
static long lastDebounceTime1 = 0;  // the last time the output pin was toggled
static long lastDebounceTime2 = 0;  // the last time the output pin was toggled
static long lastDebounceTime3 = 0;  // the last time the output pin was toggled
static long lastDebounceTime4 = 0;  // the last time the output pin was toggled
static long lastDebounceTime5 = 0;  // the last time the output pin was toggled


CapacitiveSensor cs_2_3 = CapacitiveSensor(2, 3);  // 10M resistor between pins 3 & 2, pin 3 is sensor pin, add a wire and or foil if desired
CapacitiveSensor cs_2_4 = CapacitiveSensor(2, 4);  // 10M resistor between pins 3 & 2, pin 4 is sensor pin, add a wire and or foil if desired
//CapacitiveSensor cs_2_5 = CapacitiveSensor(2, 5);  // 10M resistor between pins 3 & 2, pin 5 is sensor pin, add a wire and or foil if desired
//CapacitiveSensor cs_2_6 = CapacitiveSensor(2, 6);  // 10M resistor between pins 3 & 2, pin 6 is sensor pin, add a wire and or foil if desired
//CapacitiveSensor cs_2_7 = CapacitiveSensor(2, 7);  // 10M resistor between pins 3 & 2, pin 7 is sensor pin, add a wire and or foil if desired


void setup()
{
  //cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
  Serial.begin(9600);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  //pinMode(ledPin3, OUTPUT);
  //pinMode(ledPin4, OUTPUT);
  //pinMode(ledPin5, OUTPUT);
}

void loop()
{
  long start = millis();
  long total1 =  cs_2_3.capacitiveSensor(samples);
  long total2 =  cs_2_4.capacitiveSensor(samples);
  //long total3 =  cs_2_5.capacitiveSensor(samples);
  //long total4 =  cs_2_6.capacitiveSensor(samples);
  //long total5 =  cs_2_7.capacitiveSensor(samples);

  Serial.print(millis() - start);        // check on performance in milliseconds
  Serial.print("\t");                    // tab character for debug windown spacing

  printSerial(total1, lastreading1, state1, ledPin1, lastDebounceTime1);
  printSerial(total2, lastreading2, state2, ledPin2, lastDebounceTime2);
  //printSerial(total3, lastreading3, state3, ledPin3, lastDebounceTime3);
  //printSerial(total4, lastreading4, state4, ledPin4, lastDebounceTime4);
  //printSerial(total5, lastreading5, state5, ledPin5, lastDebounceTime5);

  Serial.println("");

  lastreading1 = processCapSensor(total1, lastreading1, state1, ledPin1, lastDebounceTime1);
  lastreading2 = processCapSensor(total2, lastreading2, state2, ledPin2, lastDebounceTime2);
  //processCapSensor(total3, lastreading3, state3, ledPin3, lastDebounceTime3);
  //processCapSensor(total4, lastreading4, state4, ledPin4, lastDebounceTime4);
  //processCapSensor(total5, lastreading5, state5, ledPin5, lastDebounceTime5);
 
  delay(100);                             // arbitrary delay to limit data to serial port
}

void printSerial(int total, int lastreading, int state, int ledPin, int lastDebounceTime) {
  Serial.print(millis());                  
  Serial.print("\t");  
  Serial.print(lastDebounceTime);                  
  Serial.print("\t");
  Serial.print(millis() - lastDebounceTime);
  Serial.print("\t");
  Serial.print(total);                  
  Serial.print("\t");
  Serial.print(lastreading);                  
  Serial.print("\t");
  Serial.print(state);                  
  Serial.print("\t");
  Serial.print(digitalRead(ledPin));                  
  Serial.print("\t");
}

int processCapSensor(int total, int lastreading, int state, int ledPin, int lastDebounceTime) {

  // If the switch changed, due to noise or pressing:
  
  if (total != lastreading) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }
  

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

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

    //lastDebounceTime = millis();
    lastreading = total;
  }

  //digitalWrite (ledPin, state);  


  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  

  return(lastreading);

}



