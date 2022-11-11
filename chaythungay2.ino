#include <SoftwareSerial.h>
SoftwareSerial bluetooth(50,52);

// Động cơ 1 - thay đổi theo bảng xanh
#define ENA  5
#define IN11  33
#define IN12  31
#define ENCA 20
#define ENCB 21

// Động cơ 2 - thay đổi theo bảng xanh
#define ENA2  7
#define IN21  28
#define IN22  29
#define ENCA2 18
#define ENCB2 19

// Động cơ 3 - thay đổi theo bảng xanh
#define ENA3  11
#define IN31  25
#define IN32  23
#define ENCA3 2
#define ENCB3 3
String docgiatri = "115";

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
   Serial.println(docgiatri);
   if (docgiatri == "119") //w 
   {
      analogWrite(ENA, 0);  analogWrite(ENA2, 60);  analogWrite(ENA3, 60);
      digitalWrite(IN11, LOW);  digitalWrite(IN12, LOW);
      digitalWrite(IN21, HIGH); digitalWrite(IN22, LOW);
      digitalWrite(IN31, LOW);  digitalWrite(IN32, HIGH);
   }
   else if (docgiatri == "115") //s
   {
      analogWrite(ENA, 0);  analogWrite(ENA2, 0); analogWrite(ENA3,0);
      digitalWrite(IN11, LOW);  digitalWrite(IN12, LOW);
      digitalWrite(IN21, LOW);  digitalWrite(IN22, LOW);
      digitalWrite(IN31, LOW);  digitalWrite(IN32, LOW);
      pause = millis();
   }
   else if (docgiatri == "97") //a
   {
      analogWrite(ENA, 80);  analogWrite(ENA2, 40);  analogWrite(ENA3, 40);
      digitalWrite(IN11, LOW);  digitalWrite(IN12, HIGH);
      digitalWrite(IN21, HIGH); digitalWrite(IN22, LOW);
      digitalWrite(IN31, HIGH); digitalWrite(IN32, LOW);
   }
   else if (docgiatri == "100") // d
   {
//      analogWrite(ENA, 170);  analogWrite(ENA2, 85);  analogWrite(ENA3, 85);
      analogWrite(ENA, 80);  analogWrite(ENA2, 40);  analogWrite(ENA3, 40);
      digitalWrite(IN11, HIGH); digitalWrite(IN12, LOW);
      digitalWrite(IN21, LOW);  digitalWrite(IN22, HIGH);
      digitalWrite(IN31, LOW);  digitalWrite(IN32, HIGH);
   }
   else if (docgiatri == "120") // x
   {
      analogWrite(ENA, 0);  analogWrite(ENA2, 60);  analogWrite(ENA3, 60);
      digitalWrite(IN11, LOW);  digitalWrite(IN12, LOW);
      digitalWrite(IN21, LOW);  digitalWrite(IN22, HIGH);
      digitalWrite(IN31, HIGH); digitalWrite(IN32, LOW);
   }
   else if (docgiatri == "49")  // 1 
   {
      analogWrite(ENA, 148);  analogWrite(ENA2, 148);  analogWrite(ENA3, 148);
      digitalWrite(IN11, HIGH);  digitalWrite(IN12, LOW);
      digitalWrite(IN21, HIGH);  digitalWrite(IN22, LOW);
      digitalWrite(IN31, HIGH);  digitalWrite(IN32, LOW);
   }
   else if (docgiatri == "50")  //2
   {
      analogWrite(ENA, 148);  analogWrite(ENA2, 148);  analogWrite(ENA3, 148);
      digitalWrite(IN11, LOW);  digitalWrite(IN12, HIGH);
      digitalWrite(IN21, LOW);  digitalWrite(IN22, HIGH);
      digitalWrite(IN31, LOW);  digitalWrite(IN32, HIGH);
   }
   else if (docgiatri == "101") //e
   {
      analogWrite(ENA, 70);  analogWrite(ENA2, 0);  analogWrite(ENA3, 70);
      digitalWrite(IN11, HIGH);  digitalWrite(IN12, LOW);
      digitalWrite(IN21, LOW); digitalWrite(IN22, LOW);
      digitalWrite(IN31, LOW);  digitalWrite(IN32, HIGH);
   }
   else if (docgiatri == "99") //c
   {
      analogWrite(ENA, 70);  analogWrite(ENA2, 70);  analogWrite(ENA3, 0);
      digitalWrite(IN11, HIGH);  digitalWrite(IN12, LOW);
      digitalWrite(IN21, LOW); digitalWrite(IN22, HIGH);
      digitalWrite(IN31, LOW);  digitalWrite(IN32, LOW);
   }
   else if (docgiatri == "113") //q
   {
      analogWrite(ENA, 70);  analogWrite(ENA2, 70);  analogWrite(ENA3, 0);
      digitalWrite(IN11, LOW);  digitalWrite(IN12, HIGH);
      digitalWrite(IN21, HIGH); digitalWrite(IN22, LOW);
      digitalWrite(IN31, LOW);  digitalWrite(IN32, LOW);
   }
   else if (docgiatri == "122") //z
   {
      analogWrite(ENA, 70);  analogWrite(ENA2, 0);  analogWrite(ENA3, 70);

      digitalWrite(IN11, LOW);  digitalWrite(IN12, HIGH);
      digitalWrite(IN21, LOW); digitalWrite(IN22, LOW);
      digitalWrite(IN31, HIGH);  digitalWrite(IN32, LOW);
   }
   /// Tự hành quá trình
   else if (docgiatri == "51")  //3 - Hinh tam giac deu
   {
      interrupts();
      present = millis();
      if (present - pause < 1000UL)
      {
          analogWrite(ENA, 133);  analogWrite(ENA2, 67); analogWrite(ENA3, 67);
          digitalWrite(IN11, HIGH);   digitalWrite(IN12, LOW);
          digitalWrite(IN21, LOW);    digitalWrite(IN22, HIGH);
          digitalWrite(IN31, LOW);    digitalWrite(IN32, HIGH);
      }
      else if ((present - pause >= 1000UL) and (present - pause) < 2000UL)
      {
          analogWrite(ENA, 67);  analogWrite(ENA2, 133); analogWrite(ENA3, 67);
          digitalWrite(IN11, LOW);    digitalWrite(IN12, HIGH);
          digitalWrite(IN21, HIGH);    digitalWrite(IN22, LOW);
          digitalWrite(IN31, LOW);    digitalWrite(IN32, HIGH);
      }
      else if ((present - pause >= 2000UL) and (present - pause) < 3000UL)
      {
          analogWrite(ENA, 67);   analogWrite(ENA2,67);   analogWrite(ENA3, 133);
          digitalWrite(IN11, LOW);    digitalWrite(IN12, HIGH);
          digitalWrite(IN21, LOW);    digitalWrite(IN22, HIGH);
          digitalWrite(IN31, HIGH);    digitalWrite(IN32, LOW);
      }
      else pause = present;
   }
   else if (docgiatri == "52") //4 - Hình vuông
   {
//      interrupts();
      present = millis();
      if (present - pause < 1000UL)
      {
          analogWrite(ENA, 133);  analogWrite(ENA2, 67); analogWrite(ENA3, 67);
          digitalWrite(IN11, HIGH);   digitalWrite(IN12, LOW);
          digitalWrite(IN21, LOW);    digitalWrite(IN22, HIGH);
          digitalWrite(IN31, LOW);    digitalWrite(IN32, HIGH);
      }
      else if ((present - pause >= 1000UL) and (present - pause) < 2000UL)
      {
          analogWrite(ENA, 0);  analogWrite(ENA2, 115); analogWrite(ENA3, 115);
          digitalWrite(IN11, LOW);    digitalWrite(IN12, LOW);
          digitalWrite(IN21, HIGH);    digitalWrite(IN22, LOW);
          digitalWrite(IN31, LOW);    digitalWrite(IN32, HIGH);
      }
      else if ((present - pause >= 2000UL) and (present - pause) < 3000UL)
      {
          analogWrite(ENA, 133);  analogWrite(ENA2, 67); analogWrite(ENA3, 67);
          digitalWrite(IN11, LOW);   digitalWrite(IN12, HIGH);
          digitalWrite(IN21, HIGH);    digitalWrite(IN22, LOW);
          digitalWrite(IN31, HIGH);    digitalWrite(IN32, LOW);
      }
      else if ((present - pause >= 3000UL) and (present - pause) < 4000UL)
      {
          analogWrite(ENA, 0);  analogWrite(ENA2, 115); analogWrite(ENA3, 115);
          digitalWrite(IN11, LOW);    digitalWrite(IN12, LOW);
          digitalWrite(IN21, LOW);    digitalWrite(IN22, HIGH);
          digitalWrite(IN31, HIGH);    digitalWrite(IN32, LOW);
      }
      else pause = present;
   }
   else if (docgiatri == "48")  //0 - ngoi sao
   {
      interrupts();
      present = millis();
      if (present - pause < 1000UL) // 36 do
      {
          analogWrite(ENA, 138);  analogWrite(ENA2, 18);  analogWrite(ENA3, 155);
          digitalWrite(IN11, HIGH);   digitalWrite(IN12, LOW);
          digitalWrite(IN21, HIGH);   digitalWrite(IN22, LOW);
          digitalWrite(IN31, LOW);    digitalWrite(IN32, HIGH);
      }
      else if ((present - pause >= 1000UL) and (present - pause < 2000UL)) // 180 do
      {
          analogWrite(ENA, 170);   analogWrite(ENA2, 85);    analogWrite(ENA3, 85);
          digitalWrite(IN11, LOW);    digitalWrite(IN12, HIGH);
          digitalWrite(IN21, HIGH);   digitalWrite(IN22, LOW);
          digitalWrite(IN31, HIGH);   digitalWrite(IN32, LOW);
      }
      else if ((present - pause >= 2000UL) and (present - pause < 3000UL)) // 324 do
      {
          analogWrite(ENA, 138);  analogWrite(ENA2, 155);   analogWrite(ENA3, 18);
          digitalWrite(IN11, HIGH);   digitalWrite(IN12, LOW);
          digitalWrite(IN21, LOW);    digitalWrite(IN22, HIGH);
          digitalWrite(IN31, HIGH);   digitalWrite(IN32, LOW);  
      }
      else if ((present - pause >= 3000UL) and (present - pause < 4000UL)) // 108 do
      {
          analogWrite(ENA, 53);  analogWrite(ENA2, 166);   analogWrite(ENA3, 114);
          digitalWrite(IN11, LOW);   digitalWrite(IN12, HIGH);
          digitalWrite(IN21, HIGH);    digitalWrite(IN22, LOW);
          digitalWrite(IN31, LOW);   digitalWrite(IN32, HIGH);  
      }
      else if ((present - pause >= 4000UL) and (present - pause < 5000UL)) // 252 do
      {
          analogWrite(ENA, 53);   analogWrite(ENA2, 114);   analogWrite(ENA3, 166);
          digitalWrite(IN11, LOW);    digitalWrite(IN12, HIGH);
          digitalWrite(IN21, LOW);   digitalWrite(IN22, HIGH);
          digitalWrite(IN31, HIGH);    digitalWrite(IN32, LOW);
      }
      else pause = present;
   }
   else if (docgiatri == "57") // 9 - hình tròn.
   {
      interrupts();
      present = millis();
      if (present - pause < 100) //  0 độ
      {
          analogWrite(ENA,  233);    analogWrite(ENA2,  117);    analogWrite(ENA3, 117);
          digitalWrite(IN11, HIGH);   digitalWrite(IN12, LOW);
          digitalWrite(IN21, LOW);   digitalWrite(IN22, HIGH);
          digitalWrite(IN31, LOW);   digitalWrite(IN32, HIGH);
      }
      else if ((present - pause >= 100) and (present - pause < 200)) // 10 độ
      {
          analogWrite(ENA,  230);    analogWrite(ENA2,  80);    analogWrite(ENA3, 150);
          digitalWrite(IN11, HIGH);   digitalWrite(IN12, LOW);
          digitalWrite(IN21, LOW);   digitalWrite(IN22, HIGH);
          digitalWrite(IN31, LOW);   digitalWrite(IN32, HIGH);
      }
      else if ((present - pause >= 200) and (present - pause < 300)) // 20 độ
      {
          analogWrite(ENA,  219);    analogWrite(ENA2,  41);    analogWrite(ENA3, 179);
          digitalWrite(IN11, HIGH);   digitalWrite(IN12, LOW);
          digitalWrite(IN21, LOW);   digitalWrite(IN22, HIGH);
          digitalWrite(IN31, LOW);   digitalWrite(IN32, HIGH);
      }
      else if ((present - pause >= 300) and (present - pause < 400)) // 30 độ
      {
          analogWrite(ENA,  202);    analogWrite(ENA2,  0);    analogWrite(ENA3, 202);
          digitalWrite(IN11, HIGH);   digitalWrite(IN12, LOW);
          digitalWrite(IN21, LOW);   digitalWrite(IN22, LOW);
          digitalWrite(IN31, LOW);   digitalWrite(IN32, HIGH);
      }
      else if ((present - pause >= 400) and (present - pause < 500)) // 40 độ
      {
          analogWrite(ENA,  179);    analogWrite(ENA2,  41);    analogWrite(ENA3, 219);
          digitalWrite(IN11, HIGH);   digitalWrite(IN12, LOW);
          digitalWrite(IN21, HIGH);   digitalWrite(IN22, LOW);
          digitalWrite(IN31, LOW);   digitalWrite(IN32, HIGH);
      }
      else if ((present - pause >= 500) and (present - pause < 600)) // 50 độ
      {
          analogWrite(ENA,  150);    analogWrite(ENA2,  80);    analogWrite(ENA3, 230);
          digitalWrite(IN11, HIGH);   digitalWrite(IN12, LOW);
          digitalWrite(IN21, HIGH);   digitalWrite(IN22, LOW);
          digitalWrite(IN31, LOW);   digitalWrite(IN32, HIGH);
      }
      else if ((present - pause >= 600) and (present - pause < 700)) // 60 độ
      {
          analogWrite(ENA,  117);    analogWrite(ENA2,  117);    analogWrite(ENA3, 233);
          digitalWrite(IN11, HIGH);   digitalWrite(IN12, LOW);
          digitalWrite(IN21, HIGH);   digitalWrite(IN22, LOW);
          digitalWrite(IN31, LOW);   digitalWrite(IN32, HIGH);
      }
      else if ((present - pause >= 700) and (present - pause < 800)) // 70 độ
      {
          analogWrite(ENA,  80);    analogWrite(ENA2,  150);    analogWrite(ENA3, 230);
          digitalWrite(IN11, HIGH);   digitalWrite(IN12, LOW);
          digitalWrite(IN21, HIGH);   digitalWrite(IN22, LOW);
          digitalWrite(IN31, LOW);   digitalWrite(IN32, HIGH);
      }
      else if ((present - pause >= 800) and (present - pause < 900)) // 80 độ
      {
          analogWrite(ENA,  41);    analogWrite(ENA2,  179);    analogWrite(ENA3, 219);
          digitalWrite(IN11, HIGH);   digitalWrite(IN12, LOW);
          digitalWrite(IN21, HIGH);   digitalWrite(IN22, LOW);
          digitalWrite(IN31, LOW);   digitalWrite(IN32, HIGH);
      }
      else if ((present - pause >= 900) and (present - pause < 1000)) // 90 độ
      {
          analogWrite(ENA,  0);    analogWrite(ENA2,  202);    analogWrite(ENA3, 202);
          digitalWrite(IN11, LOW);   digitalWrite(IN12, LOW);
          digitalWrite(IN21, HIGH);   digitalWrite(IN22, LOW);
          digitalWrite(IN31, LOW);   digitalWrite(IN32, HIGH);
      }
      else if ((present - pause >= 1000) and (present - pause < 1100)) // 100 độ
      {
          analogWrite(ENA,  41);    analogWrite(ENA2,  219);    analogWrite(ENA3, 179);
          digitalWrite(IN11, LOW);   digitalWrite(IN12, HIGH);
          digitalWrite(IN21, HIGH);   digitalWrite(IN22, LOW);
          digitalWrite(IN31, LOW);   digitalWrite(IN32, HIGH);
      }
      else if ((present - pause >= 1100) and (present - pause < 1200)) // 110 độ
      {
          analogWrite(ENA,  80);    analogWrite(ENA2,  230);    analogWrite(ENA3, 150);
          digitalWrite(IN11, LOW);   digitalWrite(IN12, HIGH);
          digitalWrite(IN21, HIGH);   digitalWrite(IN22, LOW);
          digitalWrite(IN31, LOW);   digitalWrite(IN32, HIGH);
      }
      else if ((present - pause >= 1200) and (present - pause < 1300)) // 120 độ
      {
          analogWrite(ENA,  117);    analogWrite(ENA2,  233);    analogWrite(ENA3, 117);
          digitalWrite(IN11, LOW);   digitalWrite(IN12, HIGH);
          digitalWrite(IN21, HIGH);   digitalWrite(IN22, LOW);
          digitalWrite(IN31, LOW);   digitalWrite(IN32, HIGH);
      }
      else if ((present - pause >= 1300) and (present - pause < 1400)) // 130 độ
      {
          analogWrite(ENA,  150);    analogWrite(ENA2,  230);    analogWrite(ENA3, 80);
          digitalWrite(IN11, LOW);   digitalWrite(IN12, HIGH);
          digitalWrite(IN21, HIGH);   digitalWrite(IN22, LOW);
          digitalWrite(IN31, LOW);   digitalWrite(IN32, HIGH);
      }
      else if ((present - pause >= 1400) and (present - pause < 1500)) // 140 độ
      {
          analogWrite(ENA,  179);    analogWrite(ENA2,  219);    analogWrite(ENA3, 41);
          digitalWrite(IN11, LOW);   digitalWrite(IN12, HIGH);
          digitalWrite(IN21, HIGH);   digitalWrite(IN22, LOW);
          digitalWrite(IN31, LOW);   digitalWrite(IN32, HIGH);
      }
      else if ((present - pause >= 1500) and (present - pause < 1600)) // 150 độ
      {
          analogWrite(ENA,  202);    analogWrite(ENA2,  202);    analogWrite(ENA3, 0);
          digitalWrite(IN11, LOW);   digitalWrite(IN12, HIGH);
          digitalWrite(IN21, HIGH);   digitalWrite(IN22, LOW);
          digitalWrite(IN31, LOW);   digitalWrite(IN32, LOW);
      }
      else if ((present - pause >= 1600) and (present - pause < 1700)) // 160 độ
      {
          analogWrite(ENA,  219);    analogWrite(ENA2,  179);    analogWrite(ENA3, 41);
          digitalWrite(IN11, LOW);   digitalWrite(IN12, HIGH);
          digitalWrite(IN21, HIGH);   digitalWrite(IN22, LOW);
          digitalWrite(IN31, HIGH);   digitalWrite(IN32, LOW);
      }
      else if ((present - pause >= 1700) and (present - pause < 1800)) // 170 độ
      {
          analogWrite(ENA,  230);    analogWrite(ENA2,  150);    analogWrite(ENA3, 80);
          digitalWrite(IN11, LOW);   digitalWrite(IN12, HIGH);
          digitalWrite(IN21, HIGH);   digitalWrite(IN22, LOW);
          digitalWrite(IN31, HIGH);   digitalWrite(IN32, LOW);
      }
      else if ((present - pause >= 1800) and (present - pause < 1900)) // 180 độ
      {
          analogWrite(ENA,  233);    analogWrite(ENA2,  117);    analogWrite(ENA3, 117);
          digitalWrite(IN11, LOW);   digitalWrite(IN12, HIGH);
          digitalWrite(IN21, HIGH);   digitalWrite(IN22, LOW);
          digitalWrite(IN31, HIGH);   digitalWrite(IN32, LOW);
      }
      else if ((present - pause >= 1900) and (present - pause < 2000)) // 190 độ
      {
          analogWrite(ENA,  230);    analogWrite(ENA2,  80);    analogWrite(ENA3, 150);
          digitalWrite(IN11, LOW);   digitalWrite(IN12, HIGH);
          digitalWrite(IN21, HIGH);   digitalWrite(IN22, LOW);
          digitalWrite(IN31, HIGH);   digitalWrite(IN32, LOW);
      }
      else if ((present - pause >= 2000) and (present - pause < 2100)) // 200 độ
      {
          analogWrite(ENA,  219);    analogWrite(ENA2,  41);    analogWrite(ENA3, 179);
          digitalWrite(IN11, LOW);   digitalWrite(IN12, HIGH);
          digitalWrite(IN21, HIGH);   digitalWrite(IN22, LOW);
          digitalWrite(IN31, HIGH);   digitalWrite(IN32, LOW);
      }
      else if ((present - pause >= 2100) and (present - pause < 2200)) // 210 độ
      {
          analogWrite(ENA,  202);    analogWrite(ENA2,  0);    analogWrite(ENA3, 202);
          digitalWrite(IN11, LOW);   digitalWrite(IN12, HIGH);
          digitalWrite(IN21, LOW);   digitalWrite(IN22, LOW);
          digitalWrite(IN31, HIGH);   digitalWrite(IN32, LOW);  
      }
      else if ((present - pause >= 2200) and (present - pause < 2300)) // 220 độ
      {
          analogWrite(ENA,  179);    analogWrite(ENA2,  41);    analogWrite(ENA3, 219);
          digitalWrite(IN11, LOW);   digitalWrite(IN12, HIGH);
          digitalWrite(IN21, LOW);   digitalWrite(IN22, HIGH);
          digitalWrite(IN31, HIGH);   digitalWrite(IN32, LOW);
      }
      else if ((present - pause >= 2300) and (present - pause < 2400)) // 230 độ
      {
          analogWrite(ENA,  150);    analogWrite(ENA2,  80);    analogWrite(ENA3, 230);
          digitalWrite(IN11, LOW);   digitalWrite(IN12, HIGH);
          digitalWrite(IN21, LOW);   digitalWrite(IN22, HIGH);
          digitalWrite(IN31, HIGH);   digitalWrite(IN32, LOW);
      }
      else if ((present - pause >= 2400) and (present - pause < 2500)) // 240 độ
      {
          analogWrite(ENA,  117);    analogWrite(ENA2,  117);    analogWrite(ENA3, 233);
          digitalWrite(IN11, LOW);   digitalWrite(IN12, HIGH);
          digitalWrite(IN21, LOW);   digitalWrite(IN22, HIGH);
          digitalWrite(IN31, HIGH);   digitalWrite(IN32, LOW);
      }
      else if ((present - pause >= 2500) and (present - pause < 2600)) // 250 độ
      {
          analogWrite(ENA,  80);    analogWrite(ENA2,  150);    analogWrite(ENA3, 230);
          digitalWrite(IN11, LOW);   digitalWrite(IN12, HIGH);
          digitalWrite(IN21, LOW);   digitalWrite(IN22, HIGH);
          digitalWrite(IN31, HIGH);   digitalWrite(IN32, LOW);
      }
      else if ((present - pause >= 2600) and (present - pause < 2700)) // 260 độ
      {
          analogWrite(ENA,  41);    analogWrite(ENA2,  179);    analogWrite(ENA3, 219);
          digitalWrite(IN11, LOW);   digitalWrite(IN12, HIGH);
          digitalWrite(IN21, LOW);   digitalWrite(IN22, HIGH);
          digitalWrite(IN31, HIGH);   digitalWrite(IN32, LOW);
      }
      else if ((present - pause >= 2700) and (present - pause < 2800)) // 270 độ
      {
          analogWrite(ENA,  0);    analogWrite(ENA2,  202);    analogWrite(ENA3, 202);
          digitalWrite(IN11, LOW);   digitalWrite(IN12, LOW);
          digitalWrite(IN21, LOW);   digitalWrite(IN22, HIGH);
          digitalWrite(IN31, HIGH);   digitalWrite(IN32, LOW);
      }
      else if ((present - pause >= 2800) and (present - pause < 2900)) // 280 độ
      {
          analogWrite(ENA,  41);    analogWrite(ENA2,  219);    analogWrite(ENA3, 179);
          digitalWrite(IN11, HIGH);   digitalWrite(IN12, LOW);
          digitalWrite(IN21, LOW);   digitalWrite(IN22, HIGH);
          digitalWrite(IN31, HIGH);   digitalWrite(IN32, LOW);
      }
      else if ((present - pause >= 2900) and (present - pause < 3000)) // 290 độ
      {
          analogWrite(ENA,  80);    analogWrite(ENA2,  230);    analogWrite(ENA3, 150);
          digitalWrite(IN11, HIGH);   digitalWrite(IN12, LOW);
          digitalWrite(IN21, LOW);   digitalWrite(IN22, HIGH);
          digitalWrite(IN31, HIGH);   digitalWrite(IN32, LOW);
      }
      else if ((present - pause >= 3000) and (present - pause < 3100)) // 300 độ
      {
          analogWrite(ENA,  117);    analogWrite(ENA2,  233);    analogWrite(ENA3, 117);
          digitalWrite(IN11, HIGH);   digitalWrite(IN12, LOW);
          digitalWrite(IN21, LOW);   digitalWrite(IN22, HIGH);
          digitalWrite(IN31, HIGH);   digitalWrite(IN32, LOW);
      }
      else if ((present - pause >= 3100) and (present - pause < 3200)) // 310 độ
      {
          analogWrite(ENA,  150);    analogWrite(ENA2,  230);    analogWrite(ENA3, 80);
          digitalWrite(IN11, HIGH);   digitalWrite(IN12, LOW);
          digitalWrite(IN21, LOW);   digitalWrite(IN22, HIGH);
          digitalWrite(IN31, HIGH);   digitalWrite(IN32, LOW);
      }
      else if ((present - pause >= 3200) and (present - pause < 3300)) // 320 độ
      {
          analogWrite(ENA,  179);    analogWrite(ENA2,  219);    analogWrite(ENA3, 41);
          digitalWrite(IN11, HIGH);   digitalWrite(IN12, LOW);
          digitalWrite(IN21, LOW);   digitalWrite(IN22, HIGH);
          digitalWrite(IN31, HIGH);   digitalWrite(IN32, LOW);
      }
      else if ((present - pause >= 3300) and (present - pause < 3400)) // 330 độ
      {
          analogWrite(ENA,  202);    analogWrite(ENA2,  202);    analogWrite(ENA3, 0);
          digitalWrite(IN11, HIGH);   digitalWrite(IN12, LOW);
          digitalWrite(IN21, LOW);   digitalWrite(IN22, HIGH);
          digitalWrite(IN31, LOW);   digitalWrite(IN32, LOW);
      }
      else if ((present - pause >= 3400) and (present - pause < 3500)) // 340 độ
      {
          analogWrite(ENA,  219);    analogWrite(ENA2,  179);    analogWrite(ENA3, 41);
          digitalWrite(IN11, HIGH);   digitalWrite(IN12, LOW);
          digitalWrite(IN21, LOW);   digitalWrite(IN22, HIGH);
          digitalWrite(IN31, LOW);   digitalWrite(IN32, HIGH);
      }
      else if ((present - pause >= 3500) and (present - pause < 3600)) // 350 độ
      {
          analogWrite(ENA,  230);    analogWrite(ENA2,  150);    analogWrite(ENA3, 80);
          digitalWrite(IN11, HIGH);   digitalWrite(IN12, LOW);
          digitalWrite(IN21, LOW);   digitalWrite(IN22, HIGH);
          digitalWrite(IN31, LOW);   digitalWrite(IN32, HIGH);
      }
      else pause = present;
   }
}
