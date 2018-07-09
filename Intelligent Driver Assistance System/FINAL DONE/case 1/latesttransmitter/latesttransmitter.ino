#include <VirtualWire.h>
const int led_pin = 11;
const int transmit_pin = 12;
const int receive_pin = 2;
const int transmit_en_pin = 3;
void setup()
{
  Serial.begin(9600);
// Initialise the IO and ISR
vw_set_tx_pin(transmit_pin);
vw_set_rx_pin(receive_pin);
vw_set_ptt_pin(transmit_en_pin);
vw_set_ptt_inverted(true); // Required for DR3100
vw_setup(2000); // Bits per sec
} 
byte count = 1;
void loop()
{
   char msg[7] = {60};
   Serial.print(msg);
   Serial.print("\n");
   if (Serial.available()>0)
   switch(Serial.read())
  {
       case 'L':
          msg[0]=65;
          Serial.print(msg[0]);
          Serial.print("\n");
       break;
      case 'R':
        msg[0]=66;
        Serial.print(msg[0]);
        Serial.print("\n");
       break;
      case 'B':
        msg[0]=67;
        Serial.print(msg[0]);
        Serial.print("\n");
       break;
       case 'P':
        msg[0]=68;
        Serial.print(msg[0]);
        Serial.print("\n");
       break;
       case 'S':
        msg[0]=69;
        Serial.print(msg[0]);
        Serial.print("\n");
       break;
      case 'O':
        msg[0]=30;
        Serial.print(msg[0]);
        Serial.print("\n");
       break;
     case 'N':
        msg[0]=80;
        Serial.print(msg[0]);
        Serial.print("\n");
       break;
    
  }



msg[6] = count;
digitalWrite(led_pin, HIGH); // Flash a light to show transmitting
vw_send((uint8_t *)msg, 7);
vw_wait_tx(); // Wait until the whole message is gone
digitalWrite(led_pin, LOW);
delay(5000);
count = count + 1;
}
