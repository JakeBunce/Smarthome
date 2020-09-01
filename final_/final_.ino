#include <SoftwareSerial.h>
#include <Servo.h> 
#include <Adafruit_Sensor.h>
#include <DHT.h>
Servo myservo;
int length = 1;
int pirPin = 7;    
int ledPin = 8;
int redLed = 12;
int greenLed = 13;
int smokeA1 = A5;
int sensorThres = 400;
int bluetoothTx = 10; // bluetooth tx to 10 pin
int bluetoothRx = 11; // bluetooth rx to 11 pin
char Incoming_value = 0;
#define DHTPIN 5
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

void setup() {
  Serial.println("DHT11 test!");
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(pirPin, LOW);
  myservo.attach(9);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(smokeA1, INPUT);
  pinMode(3, OUTPUT); 
  bluetooth.begin(9600);
  Serial.begin(9600);
  dht.begin();
}

void loop() {

 pinMode (A0 , OUTPUT);
  delay(2000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);


  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C ");
  if (t > 20) {
    Serial.println("Too cold!");
    digitalWrite(A0, LOW);
    delay (1000);
    digitalWrite(A0, HIGH);
  }


  if(digitalRead(pirPin) == HIGH){
  digitalWrite(ledPin, LOW);  
    }

  if(digitalRead(pirPin) == LOW){      
  digitalWrite(ledPin, HIGH);    
  }

  if(bluetooth.available()> 0 ) // receive number from bluetooth
  {
    int servopos = bluetooth.read(); // save the received number to servopos
    Serial.println(servopos); // serial print servopos current number received from bluetooth
    myservo.write(servopos); // roate the servo the angle received from the android app
  }

    if(Serial.available() > 1)  
  {
    Incoming_value = Serial.read();      
    Serial.print(Incoming_value);        
    Serial.print("\n");        
    if(Incoming_value == '1')             
      digitalWrite(3, HIGH);  
    else if(Incoming_value == '0')       
      digitalWrite(3, LOW);   
  }  
    int analogSensor = analogRead(smokeA1);

  Serial.print("Pin A0: ");
  Serial.println(analogSensor);
  // Checks if it has reached the threshold value
  if (analogSensor > sensorThres)
  {
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);

  }
  else
  {
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);

  }
  delay(100);
}
