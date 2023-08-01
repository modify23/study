#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
#define joystick_SW 2
#define joystick_VRY A1
#define AlarmSW 3

int time1, time2, press_time, unpress_time, last_press_time;
int hh = 0, mm = 0, ss = 0;
int AlarmHH = 0, AlarmMM = 0, AlarmSS= 0;
int flag =0, setTime = 0, setAlarm = 0;
int SW_reading;
int AlarmSW_reading;
unsigned long lastDebounceTime = 0;  // 디바운스 시간 기록 변수
unsigned long debounceDelay = 50;    // 디바운스 시간(밀리초 단위)

String ampm = "AM";
LiquidCrystal_I2C lcd(0x27, 16, 2);

enum CLOCK_MODE{
  NORMAL_STATE,
  TIME_SETTING,
  ALARM_TIME_SETTING,
  MUSIC_SELECT
};
enum CLOCK_MODE mode_flag = NORMAL_STATE;


void button_isr()
{
  Serial.print(SW_reading);
  Serial.print("==>");
  Serial.print(millis());
  Serial.print(":");

  AlarmSW_reading = digitalRead(AlarmSW);
  SW_reading = digitalRead(joystick_SW);

  if(AlarmSW_reading == 0 && SW_reading == 1 )
    mode_flag = ALARM_TIME_SETTING;

  if(SW_reading == 0 )
  {
    time1 = millis();
    unpress_time = time1 - time2;
    Serial.print("UN: ");
    Serial.println(unpress_time);
    
  }

  else{
    time2 = millis();
    last_press_time = press_time;
    press_time = time2 - time1;
    Serial.print("PR: ");    
    Serial.println(press_time);
    if(press_time>1000){
      Serial.println("LONG Key");
      //mode_flag = ALARM_TIME_
      SETTING;
    }
    
    if(mode_flag== NORMAL_STATE && last_press_time<500 && press_time<500 && unpress_time<500){
      Serial.println("Double click");
      mode_flag = MUSIC_SELECT;
    }
    else mode_flag = TIME_SETTING;
  }
}


void setup() {
  
  Serial.begin(9600);
  pinMode(joystick_SW, INPUT_PULLUP);
  attachInterrupt(0,button_isr,CHANGE);

  pinMode(AlarmSW, INPUT_PULLUP);
  attachInterrupt(1,button_isr,CHANGE);

  lcd.clear();
	lcd.begin(); // I2C LCD를 초기화 합니다.
	lcd.backlight(); // I2C LCD의 백라이트를 켜줍니다.
  
}

void loop() {
  Serial.println(AlarmSW_reading);
  
  if(mode_flag == NORMAL_STATE){
    CLK_NORMAL_STATE();
  }
  if(mode_flag == TIME_SETTING){
    CLK_TIME_SETTING();
  }
  if(mode_flag == ALARM_TIME_SETTING) {
    CLK_ALARM_TIME_SETTING();
    }
  if(mode_flag == MUSIC_SELECT) {
    CLK_MUSIC_SELECT();
    }
}

void CLK_NORMAL_STATE(){
  time_update();
  display_time(hh,mm,ss);
  lcd.setCursor(0,0);		    	
	lcd.print("---CLOCK---");
}

void time_update(){
  static unsigned long previousMillis = 0;
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 1000) {
    previousMillis = currentMillis;
    ss++;
      if (ss == 60) {ss = 0; mm++;}
      if (mm == 60) {mm = 0; hh++;}
      if (hh == 24) {hh = 0; } 
  }
  if (hh >= 12 ) {ampm = "PM";}
  if (hh <= 11 ) {ampm = "AM";}
}

void CLK_TIME_SETTING(){
  SW_reading = digitalRead(joystick_SW);

  lcd.setCursor(0,0);		    	
	lcd.print("TIME_SETTING");
  Serial.println("TIME_SETTING");
  display_time(hh,mm,ss);
  delay(100);

  if(digitalRead(joystick_SW) == 1) flag = 0;
  if(digitalRead(joystick_SW) == 0 ) {
    flag = 1;
    setTime = setTime+1;
  }
  Serial.print("set Mode : ");
  Serial.println(setTime);
  Serial.print("analogRead : ");
  Serial.println(analogRead(joystick_VRY));

  if(analogRead(joystick_VRY)<20){
    if (setTime==1) { hh=hh+1; delay(100); }
    if (setTime==2) { mm=mm+1; delay(100); }
    if (setTime==3) { ss=ss+1; delay(100); }
    if(hh>23)hh=0; if(mm>59)mm=0; if(ss>59)ss=0;
  }

  if(analogRead(joystick_VRY)>1000){
    if (setTime==1) { hh=hh-1; delay(100); }
    if (setTime==2) { mm=mm-1; delay(100); }
    if (setTime==3) { ss=ss-1; delay(100); }
    if(hh<0) hh=23; if(mm<0) mm=59; if(ss<0) ss=59; 
  }

  if(setTime == 4){
    lcd.setCursor (0,0); lcd.print ("Set Time Finish ");
    delay (1000);
    lcd.clear();
    setTime = 0;
    mode_flag = NORMAL_STATE;
  }

}

void display_time(int hh, int mm, int ss){
	lcd.setCursor(0,1);
  lcd.print(ampm); lcd.print(" ");
  lcd.print((hh/10)%10); lcd.print(hh % 10); lcd.print(":");
  lcd.print((mm/10)%10); lcd.print(mm % 10); lcd.print(":");
  lcd.print((ss/10)%10); lcd.print(ss % 10); lcd.print(" "); 
}

void CLK_ALARM_TIME_SETTING(){
  SW_reading = digitalRead(joystick_SW);
  lcd.setCursor(0,0);
  lcd.print("SET_ALARM");
  Serial.println("ALARM_TIME_SETTING");
  display_time(AlarmHH,AlarmMM,AlarmSS);
  delay(100);
  
  if(digitalRead(joystick_SW) == 1) flag = 0;
  if(digitalRead(joystick_SW) == 0 ) {
    flag = 1;
    setAlarm = setAlarm+1;
  }
  

  if(analogRead(joystick_VRY)<20){
    if (setAlarm==1) { AlarmHH=AlarmHH+1; delay(100); }
    if (setAlarm==2) { AlarmMM=AlarmMM+1; delay(100); }
    if (setAlarm==3) { AlarmSS=AlarmSS+1; delay(100); }
    if(AlarmHH>23)AlarmHH=0; if(AlarmMM>59)AlarmMM=0; if(AlarmSS>59)AlarmSS=0;
  }

  if(analogRead(joystick_VRY)>1000){
    if (setAlarm==1) { AlarmHH=AlarmHH-1; delay(100); }
    if (setAlarm==2) { AlarmMM=AlarmMM-1; delay(100); }
    if (setAlarm==3) { AlarmSS=AlarmSS-1; delay(100); }
    if(AlarmHH<0) AlarmHH=23; if(AlarmMM<0) AlarmMM=59; if(AlarmSS<0) AlarmSS=59; 
  }

  if(setAlarm == 4){
    lcd.setCursor (0,0); lcd.print ("Set AlArm Finish ");
    delay (1000);
    lcd.clear();
    setAlarm = 0;
    mode_flag = NORMAL_STATE;
  }

}

void CLK_MUSIC_SELECT(){
  lcd.setCursor(0,0);
  lcd.print("MUSIC_SELECT");
  Serial.println("MUSIC_SELECT");
}




