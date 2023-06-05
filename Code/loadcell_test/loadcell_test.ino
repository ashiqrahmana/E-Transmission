#include <LiquidCrystal.h>
#define DT A6
#define SCK A7
#define sw 9

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

long sample=0;
float val=0;
long count=0;
 
unsigned long readCount(void)
{
  unsigned long Count;
  unsigned char i;
  pinMode(DT, OUTPUT);
  digitalWrite(DT,HIGH);
  digitalWrite(SCK,LOW);
  Count=0;
  pinMode(DT, INPUT);
  while(digitalRead(DT));
  for (i=0;i<24;i++)
  {
    digitalWrite(SCK,HIGH);
    Count=Count<<1;
    digitalWrite(SCK,LOW);
    if(digitalRead(DT))
    Count++;
  }
  digitalWrite(SCK,HIGH);
  Count=Count^0x800000;
  digitalWrite(SCK,LOW);
  return(Count);
}
 
void setup()
{
pinMode(SCK, OUTPUT);
pinMode(sw, INPUT_PULLUP);
Serial.begin(9600);
Serial.println(" Weight ");
Serial.println(" Measurement ");
delay(1000);
calibrate();
}
 
void loop()
{
count= readCount();
int w=(((count-sample)/val)-2*((count-sample)/val));
//Serial.print("Measured Weight");
Serial.println(w);
//Serial.println("g ");
 
if(digitalRead(sw)==0)
{
val=0;
sample=0;
w=0;
count=0;
calibrate();
}
}
 
void calibrate()
{
  Serial.println("Calibrating...");
  Serial.println("Please Wait...");
  for(int i=0;i<100;i++){
    count=readCount();
    sample+=count;
  }
  sample/=100;
  Serial.print("Put 1000g & wait");
  count=0;
  while(count<100)
  {
    count=readCount();
    count=sample-count;
  }
  Serial.println("Please Wait....");
  delay(2000);
  for(int i=0;i<100;i++)
  {
    count=readCount();
    val+=sample-count;
  }
  val=val/100.0;
  val=val/1000.0; // put here your calibrating weight
}
