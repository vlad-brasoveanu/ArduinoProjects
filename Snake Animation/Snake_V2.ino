
#include <LedControl.h>

#define START 0  //start index for matrix
#define END 7    //end index for matrix
#define DELAY 25 //speed of animation

int DIN = 12;
int CS = 11;
int CLK = 10;

LedControl lc=LedControl(DIN, CLK, CS, 1);

void setup(){

  lc.shutdown(0,false);
  lc.setIntensity(0,1);
  lc.clearDisplay(0);
}

void function(int right, int left)
{
  for(int i = START; i <= END; i++)
  {
    if(i % 2 == 0)
      {
        lc.setLed(0, i, right, 1);
        delay(DELAY);
      }
    else
      {
        lc.setLed(0, i, left, 1);
        delay(DELAY);
      }
  }
  for(int i = START; i <= END; i++)
  {
    if(i % 2 == 0)
      {
        lc.setLed(0, i, right, 0);
        delay(DELAY);
      }
    else
      {
        lc.setLed(0, i, left, 0);
        delay(DELAY);
      }
  }
}

void loop(){
  function(START+1, START);
  function((START+END)/2 + 1, (START+END)/2);
  function(END, END-1);
}

