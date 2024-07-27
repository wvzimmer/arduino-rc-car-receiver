/* YourDuinoStarter Example: nRF24L01 Receive Joystick values

 - WHAT IT DOES: Receives data from another transceiver with
   2 Analog values from a Joystick or 2 Potentiometers
   Displays received values on Serial Monitor
 - SEE the comments after "//" on each line below
 - CONNECTIONS: nRF24L01 Modules See:
 http://arduino-info.wikispaces.com/Nrf24L01-2.4GHz-HowTo
   1 - GND
   2 - VCC 3.3V !!! NOT 5V
   3 - CE to Arduino pin 9
   4 - CSN to Arduino pin 10
   5 - SCK to Arduino pin 13
   6 - MOSI to Arduino pin 11
   7 - MISO to Arduino pin 12
   8 - UNUSED
   
 - V1.00 11/26/13
   Based on examples at http://www.bajdi.com/
   Questions: terry@yourduino.com */

/*-----( Import needed libraries )-----*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h> 
/*-----( Declare Constants and Pin Numbers )-----*/
#define CE_PIN   9
#define CSN_PIN  10

// #define LED_PIN  A5
#define LED_PIN  7

RF24 radio(CE_PIN, CSN_PIN); // Create a Radio

const byte address[6] = "00001";
uint8_t radio_buffer[32] = {0};
const uint8_t buffer_size = sizeof(radio_buffer);
Servo myservo;

void setup()   /****** SETUP: RUNS ONCE ******/
{
  Serial.begin(115200);
  Serial.println("Nrf24L01 Receiver Starting");

  radio.begin();
  radio.openReadingPipe(0, address);
  radio.startListening();

  myservo.attach(3);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  
  myservo.write(0);
delay(2000);
  myservo.write(90);
delay(2000);
  myservo.write(180);
delay(2000);
  digitalWrite(LED_PIN, HIGH);
  delay(200);
  digitalWrite(LED_PIN, LOW);
  delay(200);
  digitalWrite(LED_PIN, HIGH);
  delay(200);
  digitalWrite(LED_PIN, LOW);
  delay(200);
  digitalWrite(LED_PIN, HIGH);
  delay(200);
  digitalWrite(LED_PIN, LOW);
  myservo.write(0);
}


void loop()   /****** LOOP: RUNS CONSTANTLY ******/
{
  int val; 
  
  // digitalWrite(LED_PIN, LOW);
  if(radio.available())
  {
    // digitalWrite(LED_PIN, HIGH);
    radio.read(&radio_buffer, buffer_size);
    if(radio_buffer[12]== 1)
      digitalWrite(5, HIGH);
    else {
      digitalWrite(5, LOW);
      if(radio_buffer[11]== 1)
        digitalWrite(6, HIGH);
      else
        digitalWrite(6, LOW);
    }

    if(radio_buffer[10]== 1)
      digitalWrite(LED_PIN, HIGH);
    else
      digitalWrite(LED_PIN, LOW);
    
    Serial.print("val: ");
    // Serial.print(radio_buffer[17]);
    val=(uint8_t)radio_buffer[17];
    // Serial.print(val);
    val = map(val, 0, 255, 0, 180);     // scale it to use it with the servo (value between 0 and 180) 
    Serial.print(val);
    Serial.print("\n--------\n");
    myservo.write(val);
  }
  else {
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
  }
}


