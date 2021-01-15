// Import installed libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
// The 'pipe' or 'frequency'
// Same for sender and receiver
const uint64_t pipe = 0xE8E8F0F0E1LL; // Declare object & Create Radio
RF24 radio(8, 10);
//Declare Variable 'rocket'
//as a 2 element array
int receive[6];
void setup() {
  radio.begin();
  radio.openReadingPipe(1,pipe);
  radio.startListening();
  Serial.begin(9600);
 
 
  pinMode(3, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
}
void loop() {
  // put your main code here, to run repeatedly:
  radio.read(receive, sizeof(receive));
  analogWrite(receive[4], 0);
  analogWrite(receive[5], 0);
  analogWrite(receive[0], receive[1]);
  analogWrite(receive[2], receive[3]);
  Serial.print(receive[0]);
  Serial.println(receive[4]);
  if(receive[1] == 0 && receive[0] == 0)
  {
    analogWrite(3, 0);
    analogWrite(9, 0);
    analogWrite(5, 0);
    analogWrite(6, 0);
  }
}
