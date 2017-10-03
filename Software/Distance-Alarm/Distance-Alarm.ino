#include <LiquidCrystal.h>
#include <stdio.h>
#define  trigPin1  2
#define  echoPin1  3
#define  trigPin2  4
#define  echoPin2  5
#define  buzzer    7

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

static FILE lcdout = {0} ;

static int lcd_putchar(char ch, FILE* stream) {
  lcd.write(ch);
  return (0);
}

void setup() {
  lcd.begin(16, 2);
  fdev_setup_stream (&lcdout, lcd_putchar, NULL, _FDEV_SETUP_WRITE);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  digitalWrite(trigPin1, LOW);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  digitalWrite(trigPin2, LOW);
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);
}

void loop() {
  long duration_depan, cm_depan;
  long duration_belakang, cm_belakang; 
  String lcdString;
  // baca sensor depan
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration_depan = pulseIn(echoPin1, HIGH);
  cm_depan = microsecondsToCentimeters(duration_depan);
  // baca sensor belakang
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration_belakang = pulseIn(echoPin2, HIGH);
  cm_belakang = microsecondsToCentimeters(duration_belakang);
  lcd.setCursor(0,0);
  fprintf(&lcdout, "Depan = %ld cm           ", cm_depan);
  lcd.setCursor(0,1);
  fprintf(&lcdout, "Belkg = %ld cm           ", cm_belakang);
  ///
  if(cm_depan==50&&cm_belakang==50) {
     lcd.clear();
     lcd.setCursor(0,0);
     fprintf(&lcdout, "Jarak dpn 50 cm ");  
     lcd.setCursor(0,1);
     fprintf(&lcdout, "Jarak blkg 50 cm"); 
     digitalWrite(buzzer, HIGH);
     delay(1000);     
  }
  else if(cm_depan==50||cm_belakang==50){
    if(cm_depan==50) {
       lcd.setCursor(0,0);
       fprintf(&lcdout, "Jarak dpn 50 cm "); 
       lcd.setCursor(0,1);
       fprintf(&lcdout, "                "); 
       digitalWrite(buzzer, HIGH);
       delay(3000);   
    }
    else if(cm_belakang==50) {
       lcd.setCursor(0,0);
       fprintf(&lcdout, "Jarak blkg 50 cm");  
       lcd.setCursor(0,1);
       fprintf(&lcdout, "                "); 
       digitalWrite(buzzer, HIGH);
       delay(3000);
    }    
  }
  else{
    digitalWrite(buzzer, LOW);
  }
  
  delay(200);
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
