#include <VirtualWire.h>

const int pwm = 2 ;  //initializing pin 2 as pwm
const int in_1 = 8 ;
const int in_2 = 9 ;
const int break_pin = 7;
const int lturn_pin = 6;
const int rreak_pin = 13;
const int parking_pin = 4;
const int nstanding_pin = 5;
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
    pinMode(pwm,OUTPUT) ;    //we have to set PWM pin as output
pinMode(in_1,OUTPUT) ;  //Logic pins are also set as output
pinMode(in_2,OUTPUT) ;

   
    pinMode(break_pin, OUTPUT); 
    pinMode(lturn_pin, OUTPUT); 
    pinMode(rreak_pin, OUTPUT); 
    pinMode(parking_pin, OUTPUT);
    pinMode(nstanding_pin, OUTPUT);
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
                       //fast
            //For Clock wise motion , in_1 = High , in_2 = Low

digitalWrite(in_1,HIGH) ;
digitalWrite(in_2,LOW) ;
analogWrite(pwm,255) ;

/*setting pwm of the motor to 255
we can change the speed of rotaion
by chaning pwm input but we are only
using arduino so we are using higest
value to driver the motor  */

//Clockwise for 3/100 secs
delay(10000) ;
//break
digitalWrite(in_1,HIGH) ;
digitalWrite(in_2,HIGH) ;
delay(200);

        
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
        Serial.println(buf[0]);
        if (buf[0]==60)
        {
            
        }
        else if (buf[0]==65)
        {
               Serial.print(0);
               Serial.print(',');
               Serial.print(0);
               Serial.print('!');


             times=times+1;
          
        }
        else if (buf[0]==66)
        {
             // right pin
             Serial.print(1);
             Serial.print(',');
             Serial.print(0);
             Serial.print('!');
               //Right turn
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
               //Speed Breaker
            digitalWrite(break_pin, HIGH); 
            times=times+1;
        }
         else if (buf[0]==68)
        {
               Serial.print(3);
               Serial.print(',');
               Serial.print(0);
               Serial.print('!');
               //No Parking
               digitalWrite(parking_pin, HIGH);
               times=times+1;
          
        }
        else if (buf[0]==69)
        {
               Serial.print(4);
               Serial.print(',');
               Serial.print(0);
               Serial.print('!');
               // Stop
               digitalWrite(nstanding_pin, HIGH);
               times=times+1;
               

          
        }
       else if (buf[0]==30)
        {
          //break
          digitalWrite(in_1,HIGH) ;
            digitalWrite(in_2,HIGH);
            delay(500) ;
          //For Anti Clock-wise motion - IN_1 = LOW , IN_2 = HIGH
            digitalWrite(in_1,LOW) ;
            digitalWrite(in_2,HIGH) ;
            delay(150) ;
            //break
          digitalWrite(in_1,HIGH) ;
            digitalWrite(in_2,HIGH);
            delay(10000) ;
          
             digitalWrite(overalertpin, HIGH); 
            // over speed case
            Serial.print(5);
            Serial.print(',');
            Serial.print(30);
            Serial.print('!');
            }
        else if (buf[0]==80)
        {
           digitalWrite(overalertpin, LOW); 
           // not over speeding 
            Serial.print(6);
            Serial.print(',');
            Serial.print(80);
            Serial.print('!');
          
        }
      

        

        
    }

    if (times>=15)
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
