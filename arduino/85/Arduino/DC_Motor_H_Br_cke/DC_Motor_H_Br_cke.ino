


class DC_Motor
{
  private:
  int EN;
  int IN1;
  int IN2;
  
  public:

  void setup(int PWM_Pin, int INA, int INB)
  {
    
    EN = PWM_Pin;
    IN1 = INA;
    IN2 = INB;

    pinMode(EN, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
  };

  void set_Speed(int Speed) // -255 bis 255 
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
};

class IR_Sensor
{
 private:
  int A;
  
 public:

 void setup(int Signal_Pin) //Analog_Pin
 {
    A = Signal_Pin;
    pinMode(A, INPUT);
 }

 int readIR()
 {
    int IR_Wert = analogRead(A);

    return IR_Wert;
 }

 void kalibrieren(int &IR_Min_ret, int &IR_Max_ret, int &IR_mean_ret)
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
};



//Motoren
DC_Motor Motor_1;
DC_Motor Motor_2;

//IR_Sensoren
IR_Sensor IR;
int IR_Min;
int IR_Max;
int IR_mean;

int i= 0;


void setup() 
{
 
  Serial.begin(9600); 
  
  Motor_1.setup(10,9,8); //Motoren // right
  Motor_2.setup(5,7,6);            // left

  IR.setup(A0); //IR_Sensor
  /*irrecv.enableIRIn(); //IR_Receiver
  pinMode(RECV_PIN, INPUT);*/
}

void loop() 
{
 /*if(IrReceiver.decode())
 {
    switch(IrReceiver.decodedIRData.decodedRawData)
    {
        case 3927310080: //+
          k=true;
          Serial.println("+");
          break;
                            
        case 4161273600: //-
          k=false;
          Serial.println("-");
          break;                
        
         case 3208707840: // Pfeiltaste nach vorne
          f=true;
          Serial.println("follow true");
          break;

         case 3141861120: // Pfeiltaste nach hinten
          f=false;
          Serial.println("follow false");
          break;
          
         case 3910598400: //0
          Motor_1.set_Speed(0);
          Motor_2.set_Speed(0); 
          Serial.println("vorwärts");
          break;

        default:   
          Serial.println("Fehler");
          break;    
    }
    IrReceiver.resume();*/
 

 
    if( i==0)
    { 
      
      Motor_1.set_Speed(-175);
      Motor_2.set_Speed(175);
      
      IR.kalibrieren(IR_Min, IR_Max, IR_mean);
      
      Motor_1.set_Speed(0);
      Motor_2.set_Speed(0);
      i++;
      
    }
  
    Serial.println(IR_Min);
    Serial.println(IR_Max);
    int kd = 10;
    int kp = 9;
    int e_alt = 0;
    int speeed = 175;
    Motor_1.set_Speed(speeed);
    Motor_2.set_Speed(speeed);
    int ir_wert = IR.readIR(); // Messen des Istwertes
    int e = IR_mean - ir_wert; // Regelabweichung = Sollwert - Istwert
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
