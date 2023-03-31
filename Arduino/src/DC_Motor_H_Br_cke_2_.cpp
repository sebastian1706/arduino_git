




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

//Touch_Sensor
int buttonPin = 12;

//Variablen des Zwischenspeichers:
int buttonPushCounter = 0;   //Zählt Tastendrücke
int buttonState = 0;         //Aktueller Tastenstatus
int lastButtonState = 0;     //Vorheriger Tastenstatus
unsigned long previousMillis = 0; //Speichert vergangene Zeit
const long interval = 500; //Intervall wo Tasterdrücke registriert wurden

bool k = false;
bool f = false;

int i= 0;


void setup() 
{
 
  Serial.begin(9600); 
  
  Motor_1.setup(10,9,8); //Motoren // right
  Motor_2.setup(5,7,6);            // left

  IR.setup(A0); //IR_Sensor
  
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() 
{
  unsigned long currentMillis = millis(); //Zählt Millisekunden
  buttonState = digitalRead(buttonPin); //Taster an buttonPin wird gelesen und in Zwischenspeicher buttonState gespeichert
 
  if (buttonState != lastButtonState)  //Wenn buttonState nicht gleich lastButtonState, dann...
  {  
    if (buttonState == LOW)  //Wenn buttonState gleich gedrückt, dann...
    {  
      buttonPushCounter ++; //buttonPushCounter +1
      lastButtonState = buttonState; //Speichert buttonState in lastButtonState
      previousMillis = currentMillis; //Speichere jetzige Millisekunden in previousMillis
      delay(50);
    }
    else 
    {
      lastButtonState = buttonState;
    }
  }

  if (currentMillis - previousMillis >= interval && buttonState == lastButtonState) 
  {
    if (buttonPushCounter == 1)
    {
      k=true;
    }

    if (buttonPushCounter == 2)
    {
      f=true;
    }

    if (buttonPushCounter == 3)
    {
      f=false;
    }
    buttonPushCounter = 0;
  }
  
 
 if (k==true)
 {
      Motor_1.set_Speed(-175);
      Motor_2.set_Speed(175);
      
      IR.kalibrieren(IR_Min, IR_Max, IR_mean);
    
      Motor_1.set_Speed(0);
      Motor_2.set_Speed(0);
      
      Serial.println(IR_Min);
      Serial.println(IR_Max);
      Serial.println(IR_mean);
      k=false;
  }
    

 else if (f==true) //weiß:höherer Wert; schwarz: niedrigere Wert
 { 
    Serial.println(IR_Min);
    Serial.println(IR_Max);
    int kp = 12;
    int speeed = 150;
    Motor_1.set_Speed(speeed);
    Motor_2.set_Speed(speeed);
    int ir_wert = IR.readIR(); // Messen des Istwertes
    int e = IR_mean - ir_wert; // Regelabweichung = Sollwert - Istwert
    int deltaSpeed = kp*e; // Änderung der Geschwindigkeit = Proportionalitätsfaktor mal Regelabweichung
    int leftSpeed  = speeed - deltaSpeed;  // Drehzahl linkes Rad
    int rightSpeed = speeed + deltaSpeed;  // Drehzahl rechtes Rad
    leftSpeed = constrain(leftSpeed,0,255);
    rightSpeed = constrain(rightSpeed,0,255);
    Motor_1.set_Speed(rightSpeed);
    Motor_2.set_Speed(leftSpeed);
    Serial.println(e);  
 }
}
