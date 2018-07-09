#include <VirtualWire.h>


const int break_pin = 7;
const int lturn_pin = 8;
const int rreak_pin = 9;
const int overalertpin = 10;

const int transmit_pin = 12;
const int receive_pin = 11;
const int transmit_en_pin = 3;

int speedv=40;

int times=0;

void setup()
{
    delay(1000);
    Serial.begin(9600);  // Debugging only
    //Serial.println("setup");

   
    pinMode(break_pin, OUTPUT); 
    pinMode(lturn_pin, OUTPUT); 
    pinMode(rreak_pin, OUTPUT); 
    pinMode(overalertpin,OUTPUT);
    
    // Initialise the IO and ISR
    vw_set_tx_pin(transmit_pin);
    vw_set_rx_pin(receive_pin);
    vw_set_ptt_pin(transmit_en_pin);
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(2000);  // Bits per sec

    vw_rx_start();       // Start the receiver PLL running
}

void loop()
{
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;

    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
        int i;

        
        // Message with a good checksum received, print it.
        //Serial.print("Got: ");
        

        /*
        for (i = 0; i < buflen; i++)
        {
            Serial.print(buf[i]);
            Serial.print(' ');
        }
        
        Serial.println();
        */
        //Serial.println(buf[0]);
        if (buf[0]==60)
        {
            
        }
        else if (buf[0]==65)
        {
               Serial.print(0);
               Serial.print(',');
               Serial.print(0);
               Serial.print('!');
               //Left turn
               digitalWrite(lturn_pin, HIGH);
               times=times+1;
          
        }
        else if (buf[0]==66)
        {
             // right pin
               Serial.print(1);
               Serial.print(',');
               Serial.print(0);
               Serial.print('!');
              digitalWrite(rreak_pin, HIGH);
              times=times+1;
          
        }
        else if (buf[0]==67)
        {
            // breaking
               Serial.print(2);
               Serial.print(',');
               Serial.print(0);
               Serial.print('!');
            digitalWrite(break_pin, HIGH); 
            times=times+1;
        }
        else if (buf[0]==30)
        {
             digitalWrite(overalertpin, HIGH); 
            // over speed case
            Serial.print(4);
            Serial.print(',');
            Serial.print(30);
            Serial.print('!');
        }
        else if (buf[0]==80)
        {
           digitalWrite(overalertpin, LOW); 
           // not over speeding 
          
        }

        

        
    }

    if (times>=10)
    {
               Serial.print(3);
               Serial.print(',');
               Serial.print(0);
               Serial.print('!');
      
    }
    delay(3000);
    digitalWrite(break_pin, LOW);
    digitalWrite(lturn_pin, LOW);
    digitalWrite(rreak_pin, LOW);
    digitalWrite(overalertpin, LOW); 
    
    
    
}
