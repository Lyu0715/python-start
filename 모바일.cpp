모바일

// 가스 누출 경보기

int gasPin = A0; 				// 가스 센서 출력 단자를 아날로그 입력 A0 핀에 연결
int gLedPin = 5; 				// 초록색 LED의 양극 단자를 디지털 5핀에 연결
int yLedPin = 6; 				// 노란색 LED의 양극 단자를 디지털 6핀에 연결
int rLedPin = 7; 				// 빨간색 LED의 양극 단자를 디지털 7핀에 연결

void setup( )
{
  pinMode(gLedPin, OUTPUT); 		// gLedPin(5번 핀)을 출력 모드로 설정
  pinMode(yLedPin, OUTPUT); 		// yLedPin(6번 핀)을 출력 모드로 설정
  pinMode(rLedPin, OUTPUT); 		// rLedPin(7번 핀)을 출력 모드로 설정 
  Serial.begin(9600); 		             	// 시리얼 모니터를 연결
}

int state = 0; 				// 가스 누출 상태를 저장할 int형 변수 state를 선언하고 초기화함

void loop( )
{
  int gasVal = analogRead(gasPin); 	// 가스 센서 출력을 읽어 들여 gasVal에 저장
  
  if (gasVal > 120){ 			// gasVal > 120이면
    digitalWrite(gLedPin, LOW); 		// gLedPin(5번 핀)에 LOW 값을 출력
    digitalWrite(yLedPin, LOW); 		// yLedPin(6번 핀)에 LOW 값을 출력
    digitalWrite(rLedPin, HIGH);		// rLedPin(7번 핀)에 HIGH 값을 출력
    state = 1; 
  }
  else if (gasVal > 90 && gasVal <= 120){ // 90 < gasVal ≤ 120이면
    digitalWrite(gLedPin, LOW); 		// gLedPin(5번 핀)에 LOW 값을 출력
    digitalWrite(yLedPin, HIGH);		// yLedPin(6번 핀)에 HIGH 값을 출력
    digitalWrite(rLedPin, LOW); 		// rLedPin(7번 핀)에 LOW 값을 출력
    state = 2;
  }
  else{ // gasVal ≤ 90이면
    digitalWrite(gLedPin, HIGH); 		// gLedPin(5번 핀)에 HIGH 값을 출력
    digitalWrite(yLedPin, LOW); 		// yLedPin(6번 핀)에 LOW 값을 출력
    digitalWrite(rLedPin, LOW); 		// rLedPin(7번 핀)에 LOW 값을 출력
    state = 3;
  } 
  
  serialDisplay(state, gasVal);		// 사용자 정의 함수 serialDisplay(  ) 호출 
}

// 사용자 정의 함수
void serialDisplay(int state, int gasVal){ // 매개변수 : int형 state와 gasVal
  Serial.print("GAS Value = "); 		// 시리얼 모니터에 ‘Gas Value = ’를 출력
  Serial.println(gasVal); 			// 시리얼 모니터에 gasVal의 저장 내용을 출력
  
  switch(state){ 				// state에 대한 switch~case 제어문
    case 1: 					// state가 1이면
    	Serial.println(">> Dangerous"); 	// 시리얼 모니터에 ‘>> Dangerous’를 출력
    	break; 				// switch~case 제어문 탈출 
    case 2: 					// state가 2이면
    	Serial.println(">> Little Risk"); 	// 시리얼 모니터에 ‘>> Little Risk’를 출력
    	break; 				// switch~case 제어문 탈출 
    case 3: 					// state가 3이면
    	Serial.println(">> Safe"); 		// 시리얼 모니터에 ‘>> Safe’를 출력
    	break; 				// switch~case 제어문 탈출
    default: 					// state가 1~3 범위 밖이면\
    	break; 				// switch~case 제어문 탈출
  } 
  Serial.println(); 				// 시리얼 모니터에 빈출 출력
  delay(500); 				// 0.5초 동안 지연 
}


// 가위-바위-보 동작 인식 시스템 

#include <LiquidCrystal.h> 			// 라이브러리 포함

// 휨 센서의 신호 단자와 연결한 아두이노의 아날로그 핀 번호를 배열에 저장
int flexPin[5] = {A0, A1, A2, A3, A4}; 		// int형 배열 flexPin에 핀 번호 A0~A4를 저장

// 손가락 모양에 해당하는 값을 배열에 저장
int scissor[5] = {1, 1, 0, 0, 0}; 			// 가위
int rock[5] = {0, 0, 0, 0, 0}; 			// 바위
int paper[5] = {1, 1, 1, 1, 1}; 			// 보

// LiquidCrystal userObject(RS 핀 번호, E 핀 번호, DB4 핀 번호, ..., DB7 핀 번호);
LiquidCrystal lcd(13, 12, 7, 6, 5, 4); 		// LCD 라이브러리를 사용하여 제어할 객체 생성

void setup() { 
  lcd.begin(16, 2); 					// LCD 초기화(16문자 2행 표시)
  lcd.clear(); 						// 화면을 지우고 커서를 (0, 0)으로 이동 
}

String message; 					// String 객체 message를 생성
int state[5] = {}; 					// int형 배열 변수 state의 선언 및 초기화

void loop() {
  for (int i = 0; i < 5; i++){
    if (analogRead(flexPin[i]) < 100) 		// 읽어 들인 휨 센서값이 100보다 작으면
      state[i] = 0; 					// 배열 변수 state의 i번째 요소에 0을 할당
    else 						// 읽어 들인 휨 센서값이 100 이상이면
      state[i] = 1; 					// 배열 변수 state의 i번째 요소에 1을 할당 
  }
  
  // 사용자 함수를 호출하여 가위, 바위, 보 상태 확인
  if (checkState(state, scissor) == 1){ 		// state와 scissor의 요소값이 같으면
    message = "Scissor!"; 				// String 객체 message에 'Scissor!'라는 문자열 저장
  }
  else if (checkState(state, rock) == 1){ 	// state와 rock의 요소값이 같으면 
    message = "Rock!"; 				// message에 ‘Rock!’이라는 문자열 저장
  }
  else if (checkState(state, paper) == 1){	// state와 paper의 요소값이 같으면 
    message = "Paper!"; 				// message에 ‘Paper!’라는 문자열 저장
  }
  else
    message = "Unknown!"; 			// message에 ‘Unknown!’이라는 문자열 저장
  
  // 가위, 바위, 보 결과 출력하기
  lcd.clear(); 						// LCD의 내용을 지우고 커서를 (0, 0)으로 이동
  lcd.print(message); 				// String 객체 message에 저장된 내용을 출력
  delay(500); 					// 0.5초 동안 지연
}

// 두 배열에 저장된 요소값의 비교하는 사용자 함수
int checkState(int arrayA[], int arrayB[]){
  for (int i = 0; i < 5; i++){ 			// for 문, i를 0부터 4까지 1씩 증가시킴
    if (arrayA[i] != arrayB[i]){ 			// 두 배열의 i번째 요소값이 다르면
      return 0; 					// 사용자 함수의 반환 값으로 0을 반환
      break; 						// 제어문(if 문)을 빠져나감
    }
    else 						// 두 배열의 i번째 요소값이 같으면
      continue; 					// continue 아래 명령어를 건너뛰고 for 문 실행
  } 
  return 1; 						// 사용자 함수의 반환 값으로 1을 반환
}



// 초음파 거리 측정 시스템

#include <LiquidCrystal.h> 			// LCD 라이브러리 포함

int TRIG = 9; 					// 초음파 센서의 TRIG 단자를 9번 핀에 연결
int ECHO = 8; 					// 초음파 센서의 ECHO 단자를 8번 핀에 연결

LiquidCrystal lcd(13, 12, 7, 6, 5, 4); 		// LCD 라이브러리로 제어할 객체 생성

void setup() { 
  lcd.begin(16, 2); 					// LCD 초기화(16문자 2행 표시)
  lcd.clear(); 						// LCD의 화면 내용을 지우고 커서를 (0, 0)으로 이동 
  pinMode(TRIG, OUTPUT); 			// TRIG 핀을 출력 모드로 설정
  pinMode(ECHO, INPUT); 			// ECHO 핀을 입력 모드로 설정
}

void loop() {
  digitalWrite(TRIG, LOW); 			// TRIG 핀으로 LOW 값 출력(송신부 출력 없음)
  delayMicroseconds(5); 				// 안정한 동작을 위해 5마이크로초 동안 지연
  digitalWrite(TRIG, HIGH); 			// TRIG 핀으로 HIGH 값 출력
  delayMicroseconds(10); 			// 10마이크로초 동안 지연(송신부에서 초음파 출력)
  digitalWrite(TRIG, LOW); 			// TRIG 핀으로 LOW 값 출력(송신부에서 초음파 출력 중지)
  
  long duration = pulseIn(ECHO, HIGH); 	// ECHO가 HIGH를 유지한 시간을 저장
  float distance = (float) (340.0 * duration / 10000.0) / 2.0; // 편도 거리(cm)
  
  // 측정 결과를 LCD에 출력하기
  lcd.clear(); 						// LCD 화면 내용을 지우고 커서를 (0, 0)으로 이동
  lcd.print("Durat. = "); 				// LCD에 ‘Durat. = ’라는 문자열 출력
  lcd.print(duration); 				// LCD에 반사파가 되돌아오는 데 걸리는 시간 출력
  lcd.print("us"); 					// LCD에 ‘us’라는 문자열 출력
  lcd.setCursor(0,1); 				// 커서를 (0, 1)로 이동
  lcd.print("Dist. = "); 				// LCD에 ‘Dist. = ’라는 문자열 출력
  lcd.print(distance); 				// 물체까지의 거리(편도) 출력
  lcd.print("cm"); 					// LCD에 ‘cm’라는 문자열 출력
  delay(500); 					// 0.5초 동안 지연
}




// 기울기 감지 시스템

int TILT = 8; 			// 기울기 센서의 신호 단자를 8번 핀에 연결
int GLED = 6; 			// GLED의 양극 단자를 6번 핀에 연결
int RLED = 5; 			// RLED의 양극 단자를 5번 핀에 연결

void setup(){
  pinMode(TILT, INPUT);	 	// TILT(8번 핀)를 입력 모드로 설정
  pinMode(GLED, OUTPUT); 	// GLED(6번 핀)를 출력 모드로 설정
  pinMode(RLED, OUTPUT); 	// RLED(5번 핀)를 출력 모드로 설정
}

void loop(){ 
  int tiltVal = digitalRead(TILT); 	// 기울기 센서값을 8번 핀으로 읽어 들임
  
  if (tiltVal == LOW){ 		// 센서가 기울어지지 않으면
    digitalWrite(GLED, HIGH); 	// GLED로 HIGH를 출력
    digitalWrite(RLED, LOW); 	// RLED로 LOW를 출력
    delay(500); 			// 0.5초 지연
  }
  else { 				// 센서가 기울어지면
    digitalWrite(GLED, LOW); 	// GLED로 LOW를 출력
    digitalWrite(RLED, HIGH); 	// RLED로 HIGH를 출력
    delay(500); 			// 0.5초 지연
  }
}




// 디지털 온도계

#include <LiquidCrystal_I2C.h> 			// LCD 라이브러리 포함

int TMP = A0; 					// int형 변수 TMP에 아날로그 입력 핀 번호 A0를 저장

// LiquidCrystal_I2C userObject(i2cAddr, cols, rows); 
LiquidCrystal_I2C lcd(0x20, 16, 2); 		// LCD 라이브러리를 사용하여 제어할 객체 생성

void setup() {
  lcd.init(); 						// LCD 초기화
  lcd.backlight(); 					// 백라이트 켜기
  lcd.clear(); 						// LCD 화면을 지우고 커서를 (0, 0)으로 이동
  lcd.print("Temp. : "); 				// LCD에 ‘Temp. : ’라는 문자열을 출력
}

void loop() {
  int value = analogRead(TMP); 			// A0 핀으로 온도 센서 출력값을 읽어 들임
  
  float temperature = voltToTemp(value); 	// 사용자 함수 voltToTemp를 호출
  
  // LCD에 사용자 정의 함수로부터 반환받은 온도 출력하기
  lcd.setCursor(8, 0); 				// 커서를 (8, 0)으로 이동한다.
  lcd.print(temperature); 				// 사용자 함수로부터 반환된 값을 LCD에 출력 
}

// 사용자 정의 함수
float voltToTemp(int value){
  float voltage = (float) value * 5.0 /1023.0; 	// 읽어 들인 센서값을 전압으로 변환
  float temperature = (float) 100.0 * voltage - 50.0; // 전압 온도 관계식 
  
  return temperature; 				// 사용자 정의 함수의 반환 값
}




// 스마트 가로등

int cds = A0; 		// int형 cds라는 변수에 아날로그 입력 핀 번호 A0를 저장
int LED_R = 11; 		// int형 LED_R이라는 변수에 아두이노 핀 번호 11을 저장
int LED_G = 9; 		// int형 LED_G라는 변수에 아두이노 핀 번호 9를 저장
int LED_B = 10;		// int형 LED_B라는 변수에 아두이노 핀 번호 10을 저장

void setup(){
  Serial.begin(9600); 	// 시리얼 모니터 초기화
}

void loop(){
  int cdsValue = analogRead(cds); 	// 센서값(아날로그 전압)을 읽어 cdsValue에 저장
  
  Serial.print("CDS Value = "); 		// 시리얼 모니터에 출력
  Serial.println(cdsValue); 			// 시리얼 모니터에 읽어 들인 센서값 출력
  
  if (cdsValue > 900){ 			// 센서값이 900보다 크면
    setColor(255,255,255); 		// 사용자 함수 setColor 호출(LED 흰색 켜짐)
  }
  else{ 					// 센서값이 900 이하면
    setColor(0,0,0); 				// 사용자 함수 setColor 호출(LED 꺼짐)
  }
  delay(500); 				// 0.5초 동안 지연
}

// 사용자 정의 함수
void setColor(int redValue, int greenValue, int blueValue){
  analogWrite(LED_R, redValue); 	// redValue에 해당하는 PWM 신호를 11번으로 출력
  analogWrite(LED_G, greenValue); 	// greenValue에 해당하는 PWM 신호를 9번으로 출력
  analogWrite(LED_B, blueValue); 	// blueValue에 해당하는 PWM 신호를 10번으로 출력
}




// 스마트 화분

int SIG = A0; 			// 토양 수분 센서의 SIG 단자를 아날로그 A0 핀에 연결
int G = 8; 				// 파란색 LED의 양극 단자를 디지털 8번 핀에 연결
int Y = 9; 				// 노란색 LED의 양극 단자를 디지털 9번 핀에 연결
int R = 10; 				// 빨간색 LED의 양극 단자를 디지털 10번 핀에 연결

void setup() { 
  // 아두이노의 디지털 8~10번 핀을 출력 모드로 설정
  pinMode(G, OUTPUT);
  pinMode(Y, OUTPUT);
  pinMode(R, OUTPUT); 
  Serial.begin(9600); 		// 시리얼 모니터 초기화
}

void loop() { 
  // 아날로그 A0(SIG) 핀으로 읽어 들인 센서값을 int형 변수 moisture에 저장
  int moisture = analogRead(SIG);
  
  Serial.print("Soil Moisture : ");	// 시리얼 모니터에 ‘Soil Moisture : ’ 문자열 출력
  Serial.print(moisture); 		// 시리얼 모니터에 변수 moisture에 저장된 값을 출력
  
  // 출력 모드로 설정된 아두이노의 디지털 8~12번 핀으로 LOW(0V) 출력
  digitalWrite(G, LOW);
  digitalWrite(Y, LOW);
  digitalWrite(R, LOW);
  
  if (moisture < 100) { 		// 센서 출력값이 100보다 작으면
    digitalWrite(R, HIGH); 		// R(10번) 핀으로 HIGH(5V) 출력
    Serial.println(" >> Dry"); 	// 시리얼 모니터에 ‘ >> Dry’를 출력
  } 
  else if (moisture < 400) { 	// 센서 출력값이 100 이상 400보다 작으면
    digitalWrite(Y, HIGH); 		// Y(9번) 핀으로 HIGH(5V) 출력
    Serial.println(" >> Little Wet"); // 시리얼 모니터에 ‘ >> Little Wet’을 출력
  }
  else { // 센서 출력값이 400 이상이면
    digitalWrite(G, HIGH); 		// G(8번) 핀으로 HIGH(5V) 출력
    Serial.println(" >> Wet");	// 시리얼 모니터에 ‘ >> Wet’을 출력
  }
  delay(500); 			// 0.5초 동안 지연
}




// 압력 측정 시스템

#include <Adafruit_LiquidCrystal.h> 	// LCD 라이브러리 포함

int FSRPIN = A0; 				// int형 변수 FSRPIN(힘 센서)에 아날로그 입력 핀 번호 A0를 저장

// Adafruit_LiquidCrystal userObject(i2cAddr); 
Adafruit_LiquidCrystal lcd(0x20); 	// LCD 라이브러리를 사용하여 제어할 객체 생성

void setup() { 
  lcd.begin(16, 2); 				// LCD 초기화(16문자 2행 표시)
  lcd.clear(); 					// LCD 화면 내용을 지우고 커서를 (0, 0)으로 이동
  lcd.print("Level of Pressure"); 		// 시리얼 모니터에 "Level of Pressure" 출력
}

String message; 				// LCD에 표시할 문자열을 저장할 String 객체 message를 생성

void loop( ) {
  int readVal = analogRead(FSRPIN);	// 힘 센서값을 읽어 들임
  int level = map(readVal, 0, 1023, 0, 10); // 힘 센서 출력 범위 변환 
  
  switch(level){ 				// 정수형 level에 대한 switch~case 제어문 
    case 0: 
    case 1:
    case 2: 					// level 값이 0~2이면
    	message = "Level 0"; 		// message에 ‘Level 0’을 저장
    	break; 				// switch~case 제어문 탈출
    case 3:
    case 4: 					// Level 값이 3~4이면
    	message = "Level 1"; 		// message에 ‘Level 1’을 저장
    	break; 				// switch~case 제어문 탈출
    case 5: 					// level 값이 5이면
    	message = "Level 2"; 		// message에 ‘Level 2’를 저장
    	break; 				// switch~case 제어문 탈출
    case 6: 					// level 값이 6이면
    	message = "Level 3"; 		// message에 ‘Level 3’을 저장
    	break; 				// switch~case 제어문 탈출
    case 7: 					// level 값이 7이면
    	message = "Level 4"; 		// message에 ‘Level 4’를 저장
    	break; 				// switch~case 제어문 탈출 
    default: 					// level 값이 1~7 범위 밖이면
    	message = "Level 5"; 		// message에 ‘Level 5’를 저장
    	break; 				// switch~case 제어문 탈출 
  }
  
  // 압력의 정도를 출력하기 
  lcd.setCursor(0, 1); 			// LCD의 커서를 (0, 1)로 이동
  lcd.print(message); 			// LCD에 message에 저장된 내용을 출력
  delay(300); 				// 0.3초 지연
}





// 침입 감지 시스템

#include <LiquidCrystal.h> 		// 일반적인 LCD 16×2를 위한 라이브러리 포함

int PIR = 8; 					// PIR 센서의 신호 단자를 디지털 8번 핀에 연결
int RLED = 9; 				// Red LED 양극 단자를 디지털 9번 핀에 연결
int GLED = 10; 				// Green LED 양극 단자를 디지털 10번 핀에 연결
String message; 				// String 객체 message를 생성

LiquidCrystal lcd(13, 12, 7, 6, 5, 4); 	// LCD 라이브러리로 제어할 객체(lcd) 생성

void setup(){ 
  pinMode(PIR, INPUT); 			// PIR(8번) 핀을 입력 모드로 선언
  pinMode(RLED, OUTPUT); 		// RLED(9번) 핀을 출력 모드로 선언
  pinMode(GLED, OUTPUT); 		// GLED(10번) 핀을 출력 모드로 선언
  lcd.begin(16, 2); 				// LCD 초기화
  lcd.clear(); 					// LCD 화면 내용 지우고 커서를 (0, 0)으로 이동
  lcd.print("Detection System"); 		// LCD 첫 줄에 ‘Detection System’ 출력
}

void loop(){ 
  int valPir = digitalRead(PIR); 		// PIR 센서값을 읽어 들여 valPir 변수에 저장
  
  if (valPir == HIGH){ 			// PIR 센서값이 HIGH이면
    digitalWrite(RLED, HIGH); 		// 빨간색 LED를 켬
    digitalWrite(GLED, LOW); 		// 초록색 LED를 끔
    message = ">> Detection!!!!"; 	// String 객체 message에 ">> Detection!!!!" 저장
  }
  else{
    digitalWrite(RLED, LOW); 		// 빨간색 LED를 끔
    digitalWrite(GLED, HIGH); 		// 초록색 LED를 켬
    message = ">> Monitoring..."; 	// String 객체 message에 ">> Monitoring..." 저장
  }
  
  // LCD에 침입 결과 출력하기 
  lcd.setCursor(0,1); 			// LCD의 커서를 2행 첫 칸으로 이동
  lcd.print(message); 			// String 객체에 저장된 내용을 LCD 2행에 출력
}



가스센서로부터 가스 값을 읽어오는 함수 = analogRead()