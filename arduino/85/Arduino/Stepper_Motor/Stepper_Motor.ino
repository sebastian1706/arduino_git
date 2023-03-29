


#include <Stepper.h> 
int SPU = 2048; // Schritte pro Umdrehung.
Stepper Motor(SPU, 3,5,4,6); 

int Sensor_Pin = 12;
int Touch_status = 0;
int steps = 0;
int n = 0;

void setup() //Hier beginnt das Setup.
{
  Serial.begin(9600);
  Motor.setSpeed(15); // Angabe der Geschwindigkeit in Umdrehungen pro Minute.
  pinMode(Sensor_Pin, INPUT);

}
void loop() {
  Touch_status = digitalRead(Sensor_Pin);

  while(Touch_status == LOW)
  {
   delay(1);
   Touch_status = digitalRead(Sensor_Pin);
  }
  Motor.step(1);
  steps = steps+1;

  if (steps==2048)
  {
    n = n+1;
  };
  
  Serial.print(n);
}
