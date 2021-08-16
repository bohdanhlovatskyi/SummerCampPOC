//Mario's Ideas
//MAX7219 - using Led Control library to display 8x8 bitmap
#include <LedControl.h>

int DIN = 11;
int CS = 7;
int CLK = 13;
LedControl lc=LedControl(DIN, CLK, CS,0);

int Cat[8] ={B10001000,B11111000,B10101000,B01110001,B00100001,B01111001,B01111101,B10111110 };
byte Apple [8]={B00011000,B00001000,B01110110,B11111111,B11111111,B11111111,B01111010,B00110100};

void setup() {
  lc.shutdown(0,false);
  lc.setIntensity(0,0);
  lc.clearDisplay(0);
}
  
void loop(){
  for(int i=0;i<8;i++) lc.setRow(0,i,Apple[i]);
  delay(5000);
  lc.clearDisplay(0);
  for(int i=0;i<8;i++) lc.setRow(0,i,Cat[i]);
  delay(5000);
  lc.clearDisplay(0);
}

