#include <LiquidCrystal.h>
const int rs=13,en=10,d4=9,d5=8,d6=3,d7=4;
const int ir=2;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);
const int trig=12;
const int echo=11;
const int in1=A2;
const int in2=5;
const int in3=6;
const int in4=7;
float rev=0;
int rpm;
int oldtime;
int time1;
void isr()
{
  time1=millis()-oldtime;
 rpm=(1/time1)*60000;
 oldtime=millis();
  //rev++;
}
long mti(long microsec)
{
  return microsec/74/2;
}

long mtc(long microsec)
{
  return microsec/29/2;
}
void setup() {
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(ir,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2),isr,RISING);
  Serial.begin(9600);
  lcd.begin(16,2);
  
}

void loop() {
 long duration,dist_inches,dist_cm;
 digitalWrite(trig,LOW);
 delayMicroseconds(2);
 digitalWrite(trig,HIGH);
  delayMicroseconds(15);
 digitalWrite(trig,LOW);

 duration=pulseIn(echo,HIGH);

 ///convert the time into a distance
 dist_inches=mti(duration);
 dist_cm=mtc(duration);
delay(1000);
 //detachInterrupt(2);
 
 //rev=0;
 
 

 if(dist_cm>=100){
  analogWrite(A0,255);
  analogWrite(A1,255);
  }
  else if(dist_cm>=80){
  analogWrite(A0,230);
  analogWrite(A1,230);
  }
  else if(dist_cm>=60){
  analogWrite(A0,200);
  analogWrite(A1,200);
  }
//  else if(dist_cm>=40){
//  analogWrite(A0,150);
//  analogWrite(A1,150);
//  }
//  else if(dist_cm>=25){
//  analogWrite(A0,110);
//  analogWrite(A1,110);
//  }
  else{
    analogWrite(A0,150);
    analogWrite(A1,150);
    }
    lcd.clear();
lcd.setCursor(0,0);
lcd.print(dist_cm);
lcd.setCursor(10,0);
lcd.print("cm");
lcd.setCursor(2,1);
lcd.print(rpm);
lcd.setCursor(10,1);
lcd.print("rpm");
attachInterrupt(2,isr,RISING);

 Serial.println(rpm);


 Serial.print(dist_inches);
 Serial.println("in. ");
 Serial.print(dist_cm);
 Serial.println("cm");
 delayMicroseconds(100);
 if(dist_cm>20)
 {
  digitalWrite(5,LOW);
  analogWrite(A2,255);
  digitalWrite(6,HIGH);
  digitalWrite(7,LOW);
 }

 else if(dist_cm<20)
 {
  digitalWrite(5,HIGH);
  analogWrite(A2,0);
  digitalWrite(6,HIGH);
  digitalWrite(7,LOW);
 }
 //attachInterrupt(2,isr,RISING);
}