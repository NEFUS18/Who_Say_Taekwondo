//3.6.16

//헤더 선언
#include<Wire.h>
#include <LiquidCrystal_I2C.h>

//I2C LCD 선언 (2004)
LiquidCrystal_I2C lcd(0x27, 20, 4);

//전역변수와 핀번호 변수 설정
unsigned long int f_time, l_time;

#define led_1 10
#define led_2 11
#define led_3 12
#define btn 4
#define res_btn 5
#define trig 7
#define echo 8

void setup() {
  //LED, 초음파센서, 버튼 핀모드 설정
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
  pinMode(led_3, OUTPUT);
  pinMode(btn, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  //LCD사용 설정
  lcd.begin();
  lcd.backlight();
  lcd.clear();

  //기본 LCD테마 표시
  lcd.setCursor(0, 0); // 칸, 줄
  lcd.print("-Did Somebody Say T?");
  lcd.setCursor(0, 1); // 칸, 줄
  lcd.print("Speed : ");
  lcd.setCursor(0, 2); // 칸, 줄
  lcd.print("Score : ");
  lcd.setCursor(0, 3);
  lcd.print("--------- 2021 NeFus");

  //촛불 다 켜기
  digitalWrite(led_1, HIGH);
  digitalWrite(led_2, HIGH);
  digitalWrite(led_3, HIGH);
}

void loop() {
  int spd = 0, dist = 100;
  int btnState = digitalRead(btn);
  int reset_btn = digitalRead(res_btn);

  //스타트 버튼이 눌렸을때
  if (btnState == LOW) {
//    Serial.println("preset");
    f_time = millis(); //시간 기록

    while (true) {
      digitalWrite(trig, HIGH); //trig에서 초음파 쏘기
      delayMicroseconds(10); //10마이크로초 대기
      digitalWrite(trig, LOW); //trig초음파 쏘기 그만
      dist = pulseIn(echo, HIGH) * 34 / 2 / 1000; //거리계산

      if (dist <= 11) break; //촛불앞에 손이 닿았을때
    }

    l_time = millis(); //시간 기록

    spd = l_time - f_time; //속도라는말보단 시간 차이가 맞다. (나중시간 - 처음시간)

    //걸린 시간에 따라 촛불 켜지는 갯수 결정
    if (spd <= 500) {
      digitalWrite(led_1, LOW);
      digitalWrite(led_2, LOW);
      digitalWrite(led_3, LOW);

      lcd.setCursor(8, 2);
      lcd.print("3");
    }
    else if (spd > 500 && spd <= 1500) {
      digitalWrite(led_1, LOW);
      digitalWrite(led_2, LOW);

      lcd.setCursor(8, 2);
      lcd.print("2");
    }
    else if (spd > 1500) {
      digitalWrite(led_1, LOW);

      lcd.setCursor(8, 2);
      lcd.print("1");
    }
    else {
      Serial.println("spd err");
    }
    //LCD에 시간 표시
//    Serial.println(spd);
    lcd.setCursor(8, 1);
    lcd.print(spd);

  }
  //리셋버튼이 눌리면 촛불 다 켜기
  if (reset_btn == LOW) {
    Serial.println("reset");
    digitalWrite(led_1, HIGH);
    digitalWrite(led_2, HIGH);
    digitalWrite(led_3, HIGH);
  }
}
