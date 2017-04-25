#include <stdint.h>

const int MaxSampleCount = 5000;

char buffer[100];


void setup() {
  SerialUSB.begin(0);
  while(!SerialUSB);
  SerialUSB.flush( );
}

void loop() {
  //Wait until Matlab signals start
  while(SerialUSB.read() == -1);
  ReadSendBatch(); // Batch send
}
  
void ReadSendBatch()
{
  static uint16_t samples[MaxSampleCount];
  static int sampleCount = 0;
  while (sampleCount < MaxSampleCount) {
    samples[sampleCount++] = analogRead(A0);
    //delayMicroseconds(1);
    //delay(1);
  }
  
  for (int i = 0 ; i < MaxSampleCount ; i++) {
    sprintf(buffer, "%d\r\n", samples[i]);
    SerialUSB.print(buffer);
    //Serial.print(buffer);
  }
  
}
