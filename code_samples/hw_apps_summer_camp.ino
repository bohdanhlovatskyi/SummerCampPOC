#include "LedControl.h"
#include "Adafruit_VL53L0X.h"
/*
 pin 12 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to LOAD 
 */
LedControl lc=LedControl(12,11,10,1);
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

#define delaytime 1000
#define size_matrix 8

byte square_2[size_matrix] = {byte(0), byte(0), byte(0), B00011000, B00011000, byte(0), byte(0), byte(0)};
byte square_4[size_matrix] = {byte(0), byte(0), B00111100, B00100100, B00100100, B00111100, byte(0), byte(0)};
byte square_6[size_matrix] = {byte(0), B01111110, B01000010, B01000010, B01000010, B01000010, B01111110, byte(0)};
byte square_8[size_matrix] = {B11111111, B10000001, B10000001, B10000001, B10000001, B10000001, B10000001, B11111111};
                                             
void writeSquare(byte square_array[size_matrix]);

void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness in range (0, 15)*/
  lc.setIntensity(0,0);
  /* and clear the display */
  lc.clearDisplay(0);

  //settings for VL53L0X and Serial
  Serial.begin(115200);

  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }
  
  Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  // power 
  Serial.println(F("VL53L0X API Simple Ranging example\n\n")); 
}

void loop() {
  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    Serial.print("Distance (mm): ");
    Serial.println(measure.RangeMilliMeter);
    fromDistanceToSquare(measure.RangeMilliMeter);
  } else {
    Serial.println(" out of range ");
  }
}

void writeSquare(int num_matrix, byte square_array[size_matrix]){
  for (int i=0; i<size_matrix; i++){
    lc.setRow(num_matrix, i, square_array[i]);
  }
  delay(delaytime);
  lc.clearDisplay(0);
  delay(delaytime);
}

void fromDistanceToSquare(int distance){
  if (distance < 20){
    writeSquare(0, square_2);
  } else if (distance < 50){
    writeSquare(0, square_4);
  } else if (distance < 100){
    writeSquare(0, square_6);
  }else{
    writeSquare(0, square_8);
  }
}
