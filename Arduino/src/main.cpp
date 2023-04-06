


#include <Arduino.h>
#include "DC_Motor_H_Br_cke.h"

DC_Motor Motor_1;
DC_Motor Motor_2;

IR_Sensor IR;

int irMin, irMax, irMean;
int i;

void setup() 
{
  

  Serial.begin(9600); 
  
  Motor_1.setup(10,9,8); //Motoren // right
  Motor_2.setup(5,7,6);            // left

  IR.setup(A0); //IR_Sensor
}

void loop() 
{
  if( i==0)
    { 
      
      Motor_1.set_Speed(-175);
      Motor_2.set_Speed(175);
      
      IR.kalibrieren(irMin, irMax, irMean);
      
      Motor_1.set_Speed(0);
      Motor_2.set_Speed(0);
      i++;
      
    }
  
    Serial.println(irMin);
    Serial.println(irMax);
    int kd = 10;
    int kp = 9;
    int e_alt = 0;
    int speeed = 175;
    Motor_1.set_Speed(speeed);
    Motor_2.set_Speed(speeed);
    int ir_wert = IR.readIR(); // Messen des Istwertes
    int e = irMean - ir_wert; // Regelabweichung = Sollwert - Istwert
    int differential = e-e_alt;
    e_alt = e;
    int deltaSpeed = kp*e + kd*differential; // Änderung der Geschwindigkeit = Proportionalitätsfaktor mal Regelabweichung
    int leftSpeed  = speeed - deltaSpeed;  // Drehzahl linkes Rad
    int rightSpeed = speeed + deltaSpeed;  // Drehzahl rechtes Rad
    leftSpeed = constrain(leftSpeed,0,255);
    rightSpeed = constrain(rightSpeed,0,255);
    Motor_1.set_Speed(rightSpeed);
    Motor_2.set_Speed(leftSpeed);
    Serial.println(e);  
} 

