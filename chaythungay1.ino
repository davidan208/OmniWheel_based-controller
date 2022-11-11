#include <SoftwareSerial.h>
SoftwareSerial bluetooth(50,51);

#define ENCA 2
#define ENCB A3

#define ENCA2 3
#define ENCB2 A4

#define ENCA3 3
#define ENCB3 A5

#define ENA 10
#define IN11 23
#define IN12 22

#define ENA2 8
#define IN21 27
#define IN22 26

#define ENA3 9
#define IN31 31
#define IN32 30

String docgiatri;

#define PPR 480

int tocdo1 = 0;
int tocdo2 = 0;
int tocdo3 = 0;
int alpha = 45;

unsigned long present = 0;
unsigned long previous = 0;
unsigned long pause = 0;

boolean process = false;
boolean pre_process = false;

boolean chieu = true;
boolean dir = true;
boolean dire = true;

void setup() {
  // put your setup code here, to run once:
  pinMode(ENCA, INPUT);
  pinMode(ENCB, INPUT);
  pinMode(ENCA2, INPUT);
  pinMode(ENCB2, INPUT);
  pinMode(ENCA3, INPUT);
  pinMode(ENCB3, INPUT);
  pinMode(ENA,OUTPUT);
  pinMode(IN11,OUTPUT);
  pinMode(IN12,OUTPUT);
  pinMode(ENA2,OUTPUT);
  pinMode(IN21,OUTPUT);
  pinMode(IN22,OUTPUT);
  pinMode(ENA3,OUTPUT);
  pinMode(IN31,OUTPUT);
  pinMode(IN32,OUTPUT);
  Serial.begin(9600);
  Serial.setTimeout(100);
  bluetooth.begin(9600);
}

void loop() {
//  Tính toán giá trị tốc độ từng động cơ
   if (bluetooth.available() > 0) docgiatri = bluetooth.read();
//  Đứng yên
  if (docgiatri == "83")    // if (docgiatri == "Foward")
  {
    analogWrite(ENA,0);
    analogWrite(ENA2, 0);
    analogWrite(ENA3, 0);    
    digitalWrite(IN11, LOW);    digitalWrite(IN12, LOW);
    digitalWrite(IN21, LOW);    digitalWrite(IN22, LOW);
    digitalWrite(IN31, LOW);    digitalWrite(IN31, LOW);
    pause = millis();
    process = false;
    pre_process = false;
  }
  else if (docgiatri == "76") //R - HINHVUONG
  {
    process = true;
    if (pre_process == true) pre_process = process;
    else if (pre_process == false)
    {
      present = millis();
      previous = pause;
      if (present - previous <= 3000UL)
      {
        analogWrite(ENA , 170);
        analogWrite(ENA2, 85);
        analogWrite(ENA3, 85);
        digitalWrite(IN11, HIGH);  digitalWrite(IN12, LOW);
        digitalWrite(IN21, LOW);  digitalWrite(IN22, HIGH);
        digitalWrite(IN31, LOW);  digitalWrite(IN32, HIGH);
      }
      else if ((present - previous > 3000UL) and (present - previous <= 6000UL))
      {
        analogWrite(ENA , 0);
        analogWrite(ENA2, 148);
        analogWrite(ENA3, 147);
        digitalWrite(IN11, LOW);  digitalWrite(IN12, LOW);
        digitalWrite(IN21, LOW);  digitalWrite(IN22, HIGH);
        digitalWrite(IN31, HIGH);  digitalWrite(IN32, LOW);
      }
      else if ((present - previous > 6000UL) and (present - previous <= 9000UL))
      {
        analogWrite(ENA , 170);
        analogWrite(ENA2, 85);
        analogWrite(ENA3, 85);
        digitalWrite(IN11, LOW);  digitalWrite(IN12, HIGH);
        digitalWrite(IN21, HIGH);  digitalWrite(IN22, LOW);
        digitalWrite(IN31, HIGH);  digitalWrite(IN32, LOW);
      }
      else if ((present - previous > 9000UL) and (present - previous <= 12000UL))
      {
        analogWrite(ENA , 0);
        analogWrite(ENA2, 147);
        analogWrite(ENA3, 148);
        digitalWrite(IN11, LOW);  digitalWrite(IN12, LOW);
        digitalWrite(IN21, HIGH);  digitalWrite(IN22, LOW);
        digitalWrite(IN31, LOW);  digitalWrite(IN32, HIGH);
      }
      else if (present - previous > 6000UL)
      {
        analogWrite(ENA, 0);
        analogWrite(ENA2, 0);
        analogWrite(ENA3, 0);
        pause = millis();
      }
    }
  }
  
//  Đi thẳng
  else if (docgiatri == "70") //F - foward
  {
    analogWrite(ENA,50);
    analogWrite(ENA2, 50);
    analogWrite(ENA3, 50);
    digitalWrite(IN11, HIGH);      digitalWrite(IN12, LOW);
    digitalWrite(IN21, HIGH);      digitalWrite(IN22, LOW);
    digitalWrite(IN31, HIGH);      digitalWrite(IN32, LOW);
  }
  else if (docgiatri == "66") //B - backward
  {
    analogWrite(ENA,50);
    analogWrite(ENA2, 50);
    analogWrite(ENA3, 50);
    digitalWrite(IN11, LOW);      digitalWrite(IN12, HIGH);
    digitalWrite(IN21, LOW);      digitalWrite(IN22, HIGH);
    digitalWrite(IN31, LOW);      digitalWrite(IN32, HIGH);
  }
  
  else if (docgiatri == "82") //L - left
  {
    analogWrite(ENA,  60);
    analogWrite(ENA2, 60);
    analogWrite(ENA3, 60);
    digitalWrite(IN11, LOW);   digitalWrite(IN12, LOW);
    digitalWrite(IN21, LOW);    digitalWrite(IN22, HIGH);
    digitalWrite(IN31, HIGH);    digitalWrite(IN32, LOW);
  }
}
