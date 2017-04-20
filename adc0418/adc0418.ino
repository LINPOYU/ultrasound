#include <stdint.h>

const int MaxSampleCount = 30000;
//uint16_t samples[MaxSampleCount];
//uint32_t interval[MaxSampleCount];
char buffer[100];
//char buffer[1];

void setup() {
  SerialUSB.begin(0);
  while(!SerialUSB);
  // initialize serial communication at 115200 bits per second:
  //Serial.begin(9600);
}

void loop() {
  //Wait until Matlab signals start
  while(SerialUSB.read() == 5);
  //while(Serial.read() == 5);
  //ReadSendMatlab();  // For testing using MatLab
  //ReadSend1();    // Test read 1-channel
  //ReadSend4();    // Test read 4-channel
  //SamplingRateTest1(); // Test samples per second (function call)
  //SamplingRateTest2(); // Test samples per second (while loop)
  ReadSendBatch(); // Batch send
  //ReadIntervalTest();
  //ReadSendBatch(MaxSampleCount); // Batch send
}

void ReadIntervalTest()
{
  /*static uint8_t interval[MaxSampleCount];
  static int sampleCount = 1;
  
  int current, last = 0;
  for(int i=1;i<MaxSampleCount;i++){
    analogRead(A0);
    current = micros();
    interval[i] = current - last;
    last = current;
    sprintf(buffer, "%d\r\n", interval[i]);
    SerialUSB.print(buffer);
    }*/

    
    
  /*for (int i = 3 ; i < MaxSampleCount ; i++) {
    sprintf(buffer, "%d\r\n", interval[i]);
    SerialUSB.print(buffer);
  }*/

  
  static uint8_t interval[MaxSampleCount];
  static int sampleCount = 1;
  
  int current, last = 0;
  while (sampleCount < MaxSampleCount){
    //analogRead(A0);
    current = micros();
    interval[sampleCount++] = current - last;
    last = current;
  }
  
  for (int i = 3 ; i < MaxSampleCount ; i++) {
    sprintf(buffer, "%d\r\n", interval[i]);
    SerialUSB.print(buffer);
    //Serial.print(buffer);
  }
}

void ReadSendMatlab()
{
  int sensorValue = analogRead(A0);  
  sprintf(buffer, "%d\r\n", sensorValue);
  SerialUSB.print(buffer);
  //Serial.print(buffer);
}
  
void ReadSendBatch()
{
  static uint16_t samples[MaxSampleCount];
  static int sampleCount = 0;
  while (sampleCount < MaxSampleCount) {
    samples[sampleCount++] = analogRead(A0);
    //delay(1);
  }
  
  for (int i = 0 ; i < MaxSampleCount ; i++) {
    sprintf(buffer, "%d\r\n", samples[i]);
    SerialUSB.print(buffer);
    //Serial.print(buffer);
  }
  
}

/*void ReadSendBatch(int MaxSampleCount)
{
  static int sampleCount = 0;
  while (sampleCount < MaxSampleCount) {
    samples[sampleCount++] = analogRead(A0);
    //delay(1);
  }
  
  for (int i = 0 ; i < MaxSampleCount ; i++) {
    sprintf(buffer, "%d\r\n", samples[i]);
    //SerialUSB.print(buffer);
    Serial.print(buffer);
  }

}*/
  
void ReadSend1()
{
  int sensorValue = analogRead(A0);  
  sprintf(buffer, "%d\r\n", sensorValue);
  SerialUSB.print(buffer);
  //Serial.print(buffer);
}

void ReadSend4()
{
  int sensorValue = analogRead(A0);
  int sensorValue2 = analogRead(A1);
  int sensorValue3 = analogRead(A2);
  int sensorValue4 = analogRead(A3);  
  sprintf(buffer, "%d\t%d\t%d\t%d\t\r\n", sensorValue, sensorValue2, sensorValue3, sensorValue4);
  SerialUSB.print(buffer);
  //Serial.print(buffer);
}

void SamplingRateTest1()
{
  static int currentTime = 0;
  static int lastTime = 0;
  static int sampleCount = 0;
  int sensorValue = analogRead(A0);
  
  sampleCount++;
  currentTime = millis();
  
  if (currentTime - lastTime >= 1000)
  {
    lastTime = currentTime;
    SerialUSB.print(sampleCount);
    SerialUSB.print("\t\r\n");
    //Serial.print(sampleCount);
    //Serial.print("\t\r\n");
    sampleCount = 0;
  }
}

void SamplingRateTest2()
{
  int sampleCount = 0;
  int sensorValue;
  int startTime = millis();
  
  while(millis() - startTime < 1000) 
  {
    sensorValue = analogRead(A0);
    sampleCount++;
  }
  
  SerialUSB.println(sampleCount);
  //Serial.println(sampleCount);
}
