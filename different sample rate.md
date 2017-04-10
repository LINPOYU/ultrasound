### different sample rate
Use diffenet code ways to get different sample rate about function call & while loop
First:
void ReadTimeTest1()
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
    Serial.print(sampleCount);
    Serial.print("\t\r\n");
    sampleCount = 0;
  }
}

![test1-samplerate](https://cloud.githubusercontent.com/assets/7093141/24867102/be195452-1e3e-11e7-84fe-7849c063d0d4.jpg)
