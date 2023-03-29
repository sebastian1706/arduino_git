
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
      Serial.println(Wert);
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

IR_Sensor IR;
int IR_Min;
int IR_Max;
int IR_mean;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
 IR.setup(A0);

}

void loop() {
  // put your main code here, to run repeatedly:
 /*int i = 0;
    int IR_Max=0;
    while (i<30000)
    {
      int Wert = IR.readIR();
      
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
      int Wert = IR.readIR();
      if (Wert < IR_Min)
      {
        IR_Min = Wert;
        
      }
      i++;
    }
    IR_mean = (IR_Max+IR_Min)/2;
    Serial.println(IR_Max);
    Serial.println(IR_Min);
    Serial.println(IR_mean);
    Serial.println("ENde");*/
  IR.kalibrieren(IR_Min, IR_Max, IR_mean);
  Serial.println(IR_Max);
  Serial.println(IR_Min);
  Serial.println(IR_mean);
  Serial.println("ENde");
  
  
  
}
