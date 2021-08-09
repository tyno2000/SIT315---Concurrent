// C++ code
//

int lowTemp = 0;
int highTemp = 0;
int celsius = 0;
int fahrenheit = 0;
int btn_pin = 2;

void setup()
{
  pinMode(btn_pin, INPUT);
  pinMode(A0, INPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  
  attachInterrupt(digitalPinToInterrupt(btn_pin), toggle, FALLING);
}

void loop()
{
  lowTemp = 20;
  highTemp = 35;
  celsius = map(((analogRead(A0) - 20) * 3.04), 0, 1023, -40, 125);
  if (celsius < lowTemp)
  {
  	Serial.print(celsius);
  	Serial.println(" C Cold ");
    DangerTemp();
  }
  else if (celsius >= lowTemp && celsius <= highTemp)
  {
    Serial.print(celsius);
  	Serial.println(" C Normal ");
    SafeTemp();
  }
  else if (celsius > highTemp)
  {
    Serial.print(celsius);
  	Serial.println(" C Hot ");
    DangerTemp();
  }
}

void SafeTemp()
{
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);
}

void DangerTemp()
{
  digitalWrite(13, HIGH);
  delay(300);
  digitalWrite(13, LOW);
  delay(300);
}

void toggle()
{
  fahrenheit = celsius * 1.8 + 32;
  Serial.print(fahrenheit);
  Serial.println(" F");
}