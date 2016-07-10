#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
SoftwareSerial mySerial(0, 1);
const int gaspin_mq2 = A0;
const int gaspin_mq7 = A1;
float RO1,RO2,sensorValue1=0,sensorValue2=0,sensorVoltage1,sensorVoltage2;
int RL1=5000, RL2=10000;
void setup()
{
// put your setup code here, to run once:
Serial.begin(9600);
lcd.begin(16, 2);
mySerial.begin(9600);
float Rs_air1,Rs_air2;
//Finding RO2 for MQ 2
for(int i=1;i<=100;i++)
sensorValue1+=analogRead(gaspin_mq2);
sensorValue1=sensorValue1/100; // Finding the average value of 100
sensorValues of sensor
Serial.print("Pure air reading for MQ 2 = ");
Serial.println(sensorValue1);
Serial.println();
sensorVoltage1 = sensorValue1*5.0/1024;
Rs_air1 = RL1*(5-sensorVoltage1)/sensorVoltage1;
RO1 = (Rs_air1/9.8); //Ratio of Rs/Ro is 9.8 for air as mentioned in the
graph in the datasheet
//Finding RO2 for MQ 7
for(int i=1;i<=100;i++)
sensorValue2+=analogRead(gaspin_mq7);
sensorValue2=sensorValue2/100;
Serial.print("Pure air reading for MQ 7 = ");
Serial.println(sensorValue2);
Serial.println();
sensorVoltage2=(sensorValue2*5.0)/1024;
Rs_air2 = RL2*(5-sensorVoltage2)/sensorVoltage2;
RO2 = (Rs_air2/9.8); //Ratio of Rs/Ro is 9.8 for air as mentioned in the
graph in the datasheet
}
void loop()
{
lcd.begin(16,2);
float Rs_gas1,Rs_gas2,ratio1,ratio2;
//Code for MQ2
sensorValue1=analogRead(gaspin_mq2);
Serial.print("LPG gas reading = ");
Serial.println(sensorValue1);
sensorVoltage1=(sensorValue1*5.0)/1024;
Rs_gas1=RL1*(5-sensorVoltage1)/(sensorVoltage1);
ratio1=Rs_gas1/RO1;
Serial.print("Rs/Ro = ");
Serial.println(ratio1);
//Adjusting the cursor of LCD and printing to it
lcd.setCursor(0, 0);
lcd.print("LPG ");
lcd.setCursor(4,0);
lcd.print(ratio1);
if(ratio1>=0.15 && ratio1<=1.75 ){ // Between 200ppm to 10000ppm
delay(2000);
mySerial.println("ATD9714827200;");
Serial.println("ATD9714827200;");
lcd.setCursor(0,1);
lcd.print("Calling ");
delay(5000);
}
//Code for MQ7
sensorValue2 = analogRead(gaspin_mq7);
Serial.print("CO gas reading = ");
Serial.println(sensorValue2);
sensorVoltage2 = sensorValue2*5.0/1024; //Voltage
Rs_gas2 = RL2*(5.0-sensorVoltage2)/sensorVoltage2; //Ohm
ratio2 = Rs_gas2/RO2;
Serial.print("Rs/Ro = ");
Serial.println(ratio2);
//Adjusting the cursor of LCD and printing to it
lcd.setCursor(0,1);
lcd.print("CO ");
lcd.setCursor(4,1);
lcd.print(ratio2);
if(ratio2>=0.7 && ratio2<=1.7) //Between 200ppm to 1000ppm
{
delay(2000);
mySerial.println("ATD9099028100;");
Serial.println("ATD9099028100;");
lcd.setCursor(0,0);
lcd.print("Calling ");
delay(5000);
}
Serial.println();
delay(7000);
}
