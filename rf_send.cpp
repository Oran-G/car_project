// Import installed libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
// The 'pipe' or 'frequency'
// Same for sender and receiver
const uint64_t pipe = 0xE8E8F0F0E1LL; // Declare object & Create Radio
RF24 radio(8, 10);
//Declare Variable 'elephant' //as a 2 element array
 
void setup() {
 radio.begin();
 radio.openWritingPipe(pipe);
 Serial.begin(9600);
}
 
int updownp = A1;
int leftrightp = A0;
int rf = 3;
int rb = 5;
int lf = 9;
int lb = 6;
int se[6];
 
void loop() {
   
  int l = map(analogRead(updownp), 0, 1024, 0, 510);
  int r = l;
  int c = map(analogRead(leftrightp), 0, 1024, -128, 128);
 
  l -= c;
  r += c;
  //  write to correct pin
  //  Serial.println(l);
  if (l < 255)
  {
    analogWrite(lb, l);
    se[0] = lb;
    se[1] = l;
    se[4] = lf;
    if (l < 0)
    {
      se[0] = lf;
      se[1] = -l;
      se[4] = lb;
    }
  }
  else
  {
    analogWrite(lf, l - 255);
    se[0] = lf;
    if (l > 510)
    {
      l = 510;
    }
    se[1] = l - 255;
    se[4] = lb;
  }
  Serial.println(se[1]);
  Serial.println(se[3]);
  if (r < 255)
  {
    se[2] = rb;
    se[3] = r;
    se[5] = rf;
    if (r < 0)
    {
      se[2] = rf;
      se[3] = -r;
      se[5] = rb;
    }
  }
  else
  {
    se[2] = rf;
    if (r > 510)
    {
      r = 510;
    }
    se[3] = r - 255;
    se[5] = rb;
  }
  radio.write(se, sizeof(se));

}
