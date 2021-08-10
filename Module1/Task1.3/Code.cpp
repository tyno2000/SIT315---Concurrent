// C++ code
//

int lowTemp = 0;
int highTemp = 0;
int celsius = 0;
int led1 = 13;
int fahrenheit = 0;
int btn_pin = 2;
int tempSensor = A0;

int led2 = 12;
int motionSensor = 7;
int state = LOW;
int val = 0;
int btn_pinP = 3;


void setup()
{
  pinMode(btn_pin, INPUT);
  pinMode(tempSensor, INPUT);
  pinMode(led1, OUTPUT);
  
  pinMode(btn_pinP, INPUT);
  pinMode(motionSensor, INPUT);
  pinMode(led2, OUTPUT);
  
  Serial.begin(9600);
  
  attachInterrupt(digitalPinToInterrupt(btn_pinP), Ptoggle, FALLING);
  attachInterrupt(digitalPinToInterrupt(btn_pin), toggle, FALLING);
}

void loop()
{
  lowTemp = 20;
  highTemp = 35;
  celsius = map(((analogRead(tempSensor) - 20) * 3.04), 0, 1023, -40, 125);
  if (celsius < lowTemp)
  {
    Serial.print("Temp: ");
  	Serial.print(celsius);
  	Serial.println(" C Cold ");
    DangerTemp();
  }
  else if (celsius >= lowTemp && celsius <= highTemp)
  {
    Serial.print("Temp: ");
    Serial.print(celsius);
  	Serial.println(" C Normal ");
    SafeTemp();
  }
  else if (celsius > highTemp)
  {
    Serial.print("Temp: ");
    Serial.print(celsius);
  	Serial.println(" C Hot ");
    DangerTemp();
  }
  
  
  val = digitalRead(motionSensor);
  if (val == HIGH) {           
    digitalWrite(led2, HIGH);   
    delay(1000);                
    
    if (state == LOW) {
      Serial.print("Motion detected! "); 
      state = HIGH;       
    }
  } 
  else {
      digitalWrite(led2, LOW); 
      delay(1000);             
      
      if (state == HIGH){
        Serial.print("Motion stopped! ");
        state = LOW;
    }
  }
}

void SafeTemp()
{
  digitalWrite(led1, HIGH);
  delay(1000);
  digitalWrite(led1, LOW);
  delay(1000);
}

void DangerTemp()
{
  digitalWrite(led1, HIGH);
  delay(300);
  digitalWrite(led1, LOW);
  delay(300);
}

void toggle()
{
  fahrenheit = celsius * 1.8 + 32;
  Serial.print("Temp: ");
  Serial.print(fahrenheit);
  Serial.println(" F");
}

void Ptoggle()
{
  state == HIGH;
  Serial.println("PIR interrupt. Motion detected!");
}