
#include <IRremote.h>

int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN); 
decode_results results;

bool k = false;
bool f = false;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  if(IrReceiver.decode())
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
          
          Serial.println("vorwärts");
          break;

        default:   
          Serial.println("Fehler");
          break;    
    }
    IrReceiver.resume();
  }
}
