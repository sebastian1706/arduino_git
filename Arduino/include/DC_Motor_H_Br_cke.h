

class DC_Motor
{
  private:
    int EN;
    int IN1;
    int IN2;
  
  public:

    void setup(int PWM_Pin, int INA, int INB);

    void set_Speed(int Speed);
  
};


class IR_Sensor
{
 private:
  int A;
  
 public:

    void setup(int Signal_Pin);

    int readIR();

    void kalibrieren(int &IR_Min_ret, int &IR_Max_ret, int &IR_mean_ret); 
};