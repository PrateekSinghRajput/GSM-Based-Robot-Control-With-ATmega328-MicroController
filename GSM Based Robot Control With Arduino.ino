#include <LiquidCrystal.h>
#define EN1 10
#define IN1 8
#define IN2 7
#define EN2 9
#define IN3 6
#define IN4 5

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
unsigned char GSMDataLen;
char AppState;
String SerialCommand = "";
boolean CommandReceived;

void setup()

{

  delay(500);

  pinMode(EN1, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
  SerialCommand.reserve(150);
  Stop();

  GSMDataLen = 0;
  AppState = 1;
  CommandReceived = 0;
  SerialCommand = "";
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F(" GSM Controlled "));
  lcd.setCursor(0, 1);
  lcd.print(F(" Robotic Vehicle"));
  delay(2000);
  lcd.setCursor(0, 0);
  lcd.print(F("      By       "));
  lcd.setCursor(0, 1);
  lcd.print(F("JustDoElectronics"));
  delay(2500);
  Serial.print(F("AT\r\n"));
}

void loop()

{

  switch (AppState)

  {

    case 1:

      {

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(F("   -*Status*-   "));
        lcd.setCursor(0, 1);
        lcd.print(F("Waiting for SMS."));
        AppState = 2;
        break;
      }

    case 2:

      {
        if (CommandReceived)

        {
          CommandReceived = 0;
          GSMDataLen = SerialCommand.length();
          if (SerialCommand.charAt(2) == 'R' && SerialCommand.charAt(3) == 'I' && SerialCommand.charAt(4) == 'N' && SerialCommand.charAt(5) == 'G')

          {
            Serial.print(F("ATH0\r\n"));
            lcd.setCursor(0, 1);
            lcd.print(F("  Hangup call ! "));
            delay(2000);
          }
          if (SerialCommand.charAt(2) == '+' && SerialCommand.charAt(3) == 'C' && SerialCommand.charAt(4) == 'M' && SerialCommand.charAt(5) == 'T')

          {
            if (SerialCommand.charAt(GSMDataLen - 4) == 'F')

            {
              lcd.setCursor(0, 0);
              lcd.print(F(" Cmd. Received  "));
              lcd.setCursor(0, 1);
              lcd.print(F(" Move  Forward "));
              Forward();
              delay(3000);
              Stop();
              delay(2000);
            }

            if (SerialCommand.charAt(GSMDataLen - 4) == 'B')
            {
              lcd.setCursor(0, 0);
              lcd.print(F(" Cmd. Received  "));
              lcd.setCursor(0, 1);
              lcd.print(F(" Move – Reverse "));
              Reverse();
              delay(3000);
              Stop();
              delay(2000);
            }
            if (SerialCommand.charAt(GSMDataLen - 4) == 'L')
            {
              lcd.setCursor(0, 0);
              lcd.print(F(" Cmd. Received  "));
              lcd.setCursor(0, 1);
              lcd.print(F(" Move – Left    "));
              RotateLeft();
              delay(3000);
              Stop();
              delay(2000);
            }
            if (SerialCommand.charAt(GSMDataLen - 4) == 'R')
            {
              lcd.setCursor(0, 0);
              lcd.print(F(" Cmd. Received  "));
              lcd.setCursor(0, 1);
              lcd.print(F(" Move – Right   "));
              RotateRight();
              delay(3000);
              Stop();
              delay(2000);
            }
          }
          SerialCommand = "";

          AppState = 1;
        }

        break;
      }
  }
}

void serialEvent()

{

  char InCh;
  while (Serial.available())
  {

    InCh = (char)Serial.read();
    SerialCommand += InCh;
    delay(1);
  }
  SerialCommand += '\0';
  CommandReceived = true;
}

void Stop()

{
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 0);
}

void Forward()

{
  digitalWrite(EN1, 1);
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  digitalWrite(EN2, 1);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
}
void Reverse()

{
  digitalWrite(EN1, 1);
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(EN2, 1);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
}
void RotateRight()

{
  digitalWrite(EN1, 1);
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  digitalWrite(EN2, 1);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
}

void RotateLeft()

{

  digitalWrite(EN1, 1);
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(EN2, 1);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
}