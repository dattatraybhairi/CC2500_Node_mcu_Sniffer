/**
   This code listens Sensortag data for 15 seconds and transmit data to thingsboard.

   Hardware SPI NODEMCU:
   MISO -> GPIO12.
   MOSI -> GPIO13.
   SCLK/SCK -> GPIO14.
   CSN/SS - > GPIO15.

*/

#include "cc2500_REG.h"
#include "cc2500_VAL.h"
#define GPO0 5
#include <SPI.h>

#define PACKET_LENGTH 64    //used while listening 
#define data_channel 50     //change channel here
#define ZM 01
#define No_byets_tx 8
#define sw_a 0      //D3        //for antnna
#define sw_b 2      //D4

#define stepPin  16    //D1    //for stepper motor
#define dirPin   4    //D2

bool received = false;
uint8_t RSSI_offset;

#define tx true
#define rx false
uint8_t sensorPin = A0;
unsigned long currentMillis1 = 0, currentMillis3 = 0;
//long sendInterval = 100; // in milliseconds
byte val = 0;
unsigned long currentMillis;

int16_t rssi_val;
int recv;
int count = 0;
int sensorValue = 0;
#define radioPktBuffer_len 70
uint8_t radioPktBuffer[radioPktBuffer_len];
const uint8_t ZMMacID[6] = {0x5A, 0xC2, 0x15, 0x81, 0x00, ZM};   //81 is for all Rotatting ZM's

/*****************************************************************************************************/
void setup() {

  pinMode(sw_a, OUTPUT);
  pinMode(sw_b, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  Serial.begin(115200);
  pinMode(GPO0, INPUT);
  //Setup
  pinMode(SS, OUTPUT);
  SPI.begin();
  digitalWrite(SS, HIGH);
  Serial.print("\n Starting Code");
  init_CC2500();
  //Read_Config_Regs();
  //switch_antenna(1);
  init_channel(data_channel);
  memcpy(&radioPktBuffer[1], ZMMacID, sizeof(ZMMacID));
  digitalWrite(dirPin, HIGH);




}

void loop() {

    CC2500_listenForPacket();

  if (received)
  {
    received = false;
    send_rx_strobe();
  }
  //===== wait for sync from communicator ==============
//  count = 0;
//  while (1) {
//    sensorValue = analogRead(sensorPin);
//    count++;
//    Serial.println(sensorValue);
//    switch_antenna(1);
//    radioPktBuffer[7] = 1;
//    radioPktBuffer[8] = count;
//    CC2500_sendPacket(No_byets_tx);
//    switch_antenna(2);
//    delay(5);
//    radioPktBuffer[7] = 2;
//    radioPktBuffer[8] = count;
//    CC2500_sendPacket(No_byets_tx);
//    rotate();
//    //delay(10);
//    if (sensorValue <= 28) {
//      sensorValue = analogRead(sensorPin);
//      count = 0;
//    }
//    //delay(1000);
//  }
}


void rotate() {
  for (int i = 0; i <= 0; i++) {

    digitalWrite(stepPin, HIGH);
    delayMicroseconds(15);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(15);
    delay(10);

  }
}
