/* Transmitter Code
*  Code to read Joystick position and transmit it with a RF24L01+ to a receiver 
*/
#include <SPI.h>
#include <RF24.h>

// Radio Configuration

RF24 radio(9,10);
byte addresses[][6] = {"Node1","Node2"};
bool radioNumber=1;


//put your values here

int flexSensorPin1 = A0;
int flexSensorPin2 = A1;
int flexSensorPin3 = A2;
int flexSensorPin4 = A3;


struct test{
int flex1;
int flex2;
int flex3;
int flex4;
}go;





void setup()   /****** SETUP: RUNS ONCE ******/
{
    Serial.begin(9600);                   // Get ready to send data back for debugging purposes
    radio.begin();                        // Get the transmitter ready
    radio.setPALevel(RF24_PA_LOW);        // Set the power to low
    radio.openWritingPipe(addresses[1]);  // Where we send data out
    radio.openReadingPipe(1,addresses[0]);// Where we receive data back
}//--(end setup )---

// Decide where you are going to plug the joystick into the circuit board.




void loop() {



go.flex1=analogRead(flexSensorPin1);
go.flex2=analogRead(flexSensorPin2);
go.flex3=analogRead(flexSensorPin3);
go.flex4=analogRead(flexSensorPin4);

    radio.stopListening();                                 // Stop listening and begin transmitting                                        // quite a long delay -- causes jittering of servo
//    if(radio.write(&flex1, sizeof(flex1)),Serial.println("sent flex1")); 
//    if(radio.write(&flex1, sizeof(flex2)),Serial.println("sent flex2"));
//    if(radio.write(&flex3, sizeof(flex3)),Serial.println("sent flex3"));
//    if(radio.write(&flex4, sizeof(flex4)),Serial.println("sent flex4")); 
(radio.write(&go, sizeof(go))); 

    radio.startListening();     // Get ready to receive confirmation from receiver
    Serial.println(go.flex1);
    Serial.println(go.flex2);
    Serial.println(go.flex3);
    Serial.println(go.flex4);
   delay(200); 
  }     


