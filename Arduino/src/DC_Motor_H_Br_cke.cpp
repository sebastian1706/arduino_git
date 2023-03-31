
#include <Arduino.h>
#include "DC_Motor_H_Br_cke.h"



  void DC_Motor::setup(int PWM_Pin, int INA, int INB)
  {
    
    EN = PWM_Pin;
    IN1 = INA;
    IN2 = INB;

    pinMode(EN, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
  };

  void DC_Motor::set_Speed(int Speed) // -255 bis 255 
  {
    if (Speed <= -100)
    { 
    analogWrite(EN, abs(Speed)); //PWM
    digitalWrite(IN1, LOW); //Drehrichtung
    digitalWrite(IN2, HIGH);
    }

    else if (Speed >= 100)
    {
      analogWrite(EN, abs(Speed)); //PWM
      digitalWrite(IN1, HIGH); //Drehrichtung
      digitalWrite(IN2, LOW);
    }

     else if (Speed == 0)
    {
      analogWrite(EN, abs(Speed)); //PWM
      digitalWrite(IN1, LOW); //Drehrichtung
      digitalWrite(IN2, LOW);
    } 
  }




 void IR_Sensor::setup(int Signal_Pin) //Analog_Pin
 {
    A = Signal_Pin;
    pinMode(A, INPUT);
 }

 int IR_Sensor::readIR()
 {
    int IR_Wert = analogRead(A);

    return IR_Wert;
 }

 void IR_Sensor::kalibrieren(int &IR_Min_ret, int &IR_Max_ret, int &IR_mean_ret)
 {
    //Maximalwert
    int i = 0;
    int IR_Max;
    while (i<30000)
    {
      int Wert = this->readIR();
      
      if (Wert > IR_Max)
      {
        IR_Max = Wert;
        
      }
      i++;
    }
  
    //Minimalwert
    i = 0;
    int IR_Min;
    while (i<30000)
    {
      int Wert = this->readIR();
      if (Wert < IR_Min)
      {
        IR_Min = Wert;
        
      }
      i++;
    }
    
    IR_Min_ret = IR_Min;
    IR_Max_ret = IR_Max;
    IR_mean_ret = (IR_Max+IR_Min)/2;
 }   