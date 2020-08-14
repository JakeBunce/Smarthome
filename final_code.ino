#include <SoftwareSerial.h>
#include <SimpleDHT.h>
#include <Servo.h> 
Servo myservo; 
SimpleDHT11 dht11;
int lvl;
int pinDHT11 = 6;
int pirPin = 7;    
int ledPin = 8;
int bluetoothTx = 10; // bluetooth tx to 10 pin
int bluetoothRx = 11; // bluetooth rx to 11 pin

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
char Incoming_value = 0;
void setup()
{
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(pirPin, LOW);
  myservo.attach(9);
  pinMode(13, OUTPUT);  
  bluetooth.begin(9600);
  Serial.begin(9600);

  }
 

void loop()
{
  if(bluetooth.available()> 0 ) 
  {
    int servopos = bluetooth.read(); 
    Serial.println(servopos); 
    myservo.write(servopos); 
  }
  
     if(digitalRead(pirPin) == HIGH){
       digitalWrite(ledPin, LOW);  
       }
 
     if(digitalRead(pirPin) == LOW){      
       digitalWrite(ledPin, HIGH);    
        }
     
  
}
