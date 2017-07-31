
/*  Receiver Code 
*   Code to receive data from RF24L01+ and use it to control a servo */

#include <Servo.h>
#include <SPI.h>
#include <RF24.h>

//Radio Configuration

bool radioNumber=0;
RF24 radio(9,10);
byte addresses[][6] = {"Node1","Node2"};
bool role = 0;  //Control transmit/receive

// Create variables to control servo value
struct test{
   int flex1 ;             //Create struct and create variable with that data-type
   int flex2 ;   
   int flex3 ; 
   int flex4 ;   
} go;


Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
Servo myservo2;
Servo myservo3;



int pos = 0;    // variable to store the servo position

int enA = 6;
int in1 = 5;
int in2 = 4;
// motor two
int enB = 3;
int in3 = 7;
int in4 = 2;
//
//unsigned int flex1;
//unsigned int flex2;
//unsigned int flex3;
//unsigned int flex4;// Expected range 0 - 180 degrees

/*-----( Declare Variables )-----*/
int Array[6];  // 2 element array holding Joystick readings

void setup()   /****** SETUP: RUNS ONCE ******/
{
  myservo.attach(17);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(18);
  myservo.attach(19);

//  pinMode(17, OUTPUT);
//  pinMode(18, OUTPUT);
//  pinMode(19, OUTPUT);
  
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("Nrf24L01 Receiver Starting");
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);    // Set the power output to low
    radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1,addresses[1]);
    radio.startListening();
}






void loop() {           //increase for debuggy, decrease to decrease jitter
    delay(200);               //increase for debuggy, decrease to decrease jitter
//    if(radio.available()){
//      Serial.println("Radio Available");
//        radio.read(&flex1,sizeof(flex1));
//        radio.read(&flex2,sizeof(flex2));
//        radio.read(&flex3,sizeof(flex3));
//        radio.read(&flex4,sizeof(flex4));
//        } 
//     else {
//      Serial.println("No radio");
//     }
 if(radio.available()){
        radio.read(&go,sizeof(go));
        } else {
          
        }     
int val1= map(go.flex1, 200, 600, 0, 90);
int val2= map(go.flex2, 200, 600, 0, 90);
int val3= map(go.flex3, 200, 600, 0, 90);
int val4= map(go.flex4, 180, 400, 0, 90);      
    
    Serial.println(val1);
    Serial.println(val2 );
    Serial.println(val3 );
    Serial.println(val4 );



 //Drive forwards 
   if(val1<=50 && val2<=50 && val3<=50 && val4<=50 ){
  analogWrite(enA, 100);
  digitalWrite(in1, LOW );
  digitalWrite(in2, HIGH);
  analogWrite(enB, 100);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
   }
   //Drive backwards
   else if(val1<=50 && val2>=50 && val3>=50 && val4>=50){
  analogWrite(enA, 100);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enB, 100);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); 
   }
  //
  else if (val1<=50 && val2<=50 && val3>=50 && val4>=50){
    for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
                           // waits 15ms for the servo to reach the position
  }
  }

   else if (val1<=50 && val2>=50 && val3<=50 && val4<=50){
    for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo3.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
   }
   }

    
    else if (val1>=50 && val2>=50 && val3>=50 && val4>=50){
  analogWrite(enA, 200);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(enB, 200);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

   }

    }
