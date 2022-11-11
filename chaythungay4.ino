#include <SoftwareSerial.h>
SoftwareSerial bluetooth(50,52);

// Động cơ 1 - thay đổi theo bảng xanh
#define ENA  5
#define IN11  31
#define IN12  33
#define ENCA 20
#define ENCB 21

// Động cơ 2 - thay đổi theo bảng xanh
#define ENA2  7
#define IN21  29
#define IN22  28
#define ENCA2 18
#define ENCB2 19

// Động cơ 3 - thay đổi theo bảng xanh
#define ENA3  11
#define IN31  23
#define IN32  25
#define ENCA3 2
#define ENCB3 3

char docgiatri = 's';

#define PPR 480

double tocdo1 = 0;
double tocdo2 = 0;
double tocdo3 = 0;

unsigned long present = 0;
unsigned long previous = 0;
unsigned long pause = 0;

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
  Serial.setTimeout(1);
  bluetooth.begin(9600);
}

void loop() {
//  Tính toán giá trị tốc độ từng động cơ
//   noInterrupts();
   if (bluetooth.available() > 0) docgiatri = bluetooth.read();
   switch (docgiatri)
   {
      case 's': // STOP
        analogWrite(ENA, 0);  analogWrite(ENA2, 0); analogWrite(ENA3,0);
        digitalWrite(IN11, LOW);  digitalWrite(IN12, LOW);
        digitalWrite(IN21, LOW);  digitalWrite(IN22, LOW);
        digitalWrite(IN31, LOW);  digitalWrite(IN32, LOW);
        pause = millis();
        break;
      case 'w': // ĐI TỚI
        analogWrite(ENA, 0);  analogWrite(ENA2, 60);  analogWrite(ENA3, 60);
        digitalWrite(IN11, LOW);    digitalWrite(IN12, LOW);
        digitalWrite(IN21, LOW);    digitalWrite(IN22, HIGH);
        digitalWrite(IN31, HIGH);   digitalWrite(IN32, LOW);
        break;
      case 'x': // ĐI LÙI
        analogWrite(ENA, 0);  analogWrite(ENA2, 60);  analogWrite(ENA3, 60);
        digitalWrite(IN11, LOW);    digitalWrite(IN12, LOW);
        digitalWrite(IN21, HIGH);   digitalWrite(IN22, LOW);
        digitalWrite(IN31, LOW);    digitalWrite(IN32, HIGH);
        break;
      case 'd': // SANG PHẢI
        analogWrite(ENA, 120);  analogWrite(ENA2, 60);  analogWrite(ENA3, 60);
        digitalWrite(IN11, LOW);    digitalWrite(IN12, HIGH);
        digitalWrite(IN21, HIGH);   digitalWrite(IN22, LOW);
        digitalWrite(IN31, HIGH);   digitalWrite(IN32, LOW);
        break;
      case 'a': // SANG TRÁI
        analogWrite(ENA, 120);  analogWrite(ENA2, 60);  analogWrite(ENA3, 60);
        digitalWrite(IN11, HIGH);   digitalWrite(IN12, LOW);
        digitalWrite(IN21, LOW);    digitalWrite(IN22, HIGH);
        digitalWrite(IN31, LOW);    digitalWrite(IN32, HIGH);
        break;
      case '1': // XOAY TRÁI
        analogWrite(ENA, 80);  analogWrite(ENA2, 80);  analogWrite(ENA3, 80);
        digitalWrite(IN11, LOW);   digitalWrite(IN12, HIGH);
        digitalWrite(IN21, LOW);   digitalWrite(IN22, HIGH);
        digitalWrite(IN31, LOW);   digitalWrite(IN32, HIGH);
        break;
      case '2': // XOAY PHẢI
        analogWrite(ENA, 80);  analogWrite(ENA2, 80);  analogWrite(ENA3, 80);
        digitalWrite(IN11, LOW);   digitalWrite(IN12, HIGH);
        digitalWrite(IN21, LOW);   digitalWrite(IN22, HIGH);
        digitalWrite(IN31, LOW);   digitalWrite(IN32, HIGH);
        break;
      case 'q':
        analogWrite(ENA, 60); analogWrite(ENA2, 60);  analogWrite(ENA3,0);
        digitalWrite(IN11, HIGH);  digitalWrite(IN12, LOW);
        digitalWrite(IN21, LOW);   digitalWrite(IN22, HIGH);
        digitalWrite(IN31, LOW);   digitalWrite(IN32, LOW);
        break;
      case 'c':
        analogWrite(ENA, 60); analogWrite(ENA2, 60);  analogWrite(ENA3,0);
        digitalWrite(IN11, LOW);   digitalWrite(IN12, HIGH);
        digitalWrite(IN21, HIGH);  digitalWrite(IN22, LOW);
        digitalWrite(IN31, LOW);   digitalWrite(IN32, LOW);
        break;
      case 'e':
        analogWrite(ENA, 60); analogWrite(ENA2, 0);  analogWrite(ENA3,60);
        digitalWrite(IN11, HIGH);  digitalWrite(IN12, LOW);
        digitalWrite(IN21, LOW);   digitalWrite(IN22, LOW);
        digitalWrite(IN31, LOW);   digitalWrite(IN32, HIGH);
        break;
      case 'z':
        analogWrite(ENA, 60); analogWrite(ENA2, 0);  analogWrite(ENA3,60);
        digitalWrite(IN11, LOW);   digitalWrite(IN12, HIGH);
        digitalWrite(IN21, LOW);   digitalWrite(IN22, LOW);
        digitalWrite(IN31, HIGH);  digitalWrite(IN32, LOW);
        break;
   }  
}
