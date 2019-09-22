#include <MQ2.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//I2C pins declaration
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
int Analog_Input = A0;
int lpg, co, smoke;
int sensorValue;
int GasSensorPin =A0; //Gas Sensor Connection
int buzzerPin=3;

MQ2 mq2(Analog_Input);

void setup(){
  Serial.begin(9600);
  lcd.begin(16,2);//Defining 16 columns and 2 rows of lcd display
  lcd.backlight();
  mq2.begin();
  pinMode(buzzerPin,OUTPUT);
  pinMode(GasSensorPin,INPUT);
  Serial.begin(9600); // sets the serial port to 9600
}
void sms() {
Serial.begin(9600); //Baud rate of the GSM/GPRS Module
Serial.print("\r");
delay(1000);
Serial.print("AT+CMGF=1\r");
delay(1000);
Serial.print("AT+CMGS=\"+8801------\"\r"); //Number to which you want to send the sms
delay(1000);
Serial.print("Gas detected\r"); //The text of the message to be sent
delay(1000);
Serial.write(0x1A);
delay(1000);
}
void loop(){
  float* values= mq2.read(true); //set it false if you don't want to print the values in the Serial
  //lpg = values[0];
  lpg = mq2.readLPG();
  //co = values[1];
  co = mq2.readCO();
  //smoke = values[2];
  smoke = mq2.readSmoke();
  lcd.setCursor(0,0);
  lcd.print("LPG:");
  lcd.print(lpg);
  lcd.print(" CO:");
  lcd.print(co);
  lcd.setCursor(0,1);
  lcd.print("SMOKE:");
  lcd.print(smoke);
  lcd.print(" PPM");
  delay(1000);
sensorValue = analogRead(GasSensorPin); // read analog input pin 0
Serial.println(sensorValue,DEC); // prints the value read
if(sensorValue<300)
{
Serial.println("No gas");
digitalWrite(buzzerPin,LOW);
}
else
{
//Serial.println("Gas detected");
digitalWrite(buzzerPin,HIGH);
sms();
}
delay(100); // wait 100ms for next reading 
}
