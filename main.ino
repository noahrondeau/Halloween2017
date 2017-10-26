

// these constants won't change:
const int sensor = A0; // the piezo is connected to analog pin 0
const int LED1 = 2;
const int LED2 = 4;
const int LED3 = 7;
const int LED4 = 8;
const int LED5 = 10;

const int led1Thresh = 10;
const int led2Thresh = 20;
const int led3Thresh = 30;
const int led4Thresh = 40;
const int led5Thresh = 50;


// these variables will change:
int sensorReading = 0;      // variable to store the value read from the sensor pin
int led1State = LOW;
int led2State = LOW;
int led3State = LOW;
int led4State = LOW;
int led5State = LOW;

void setup()
{
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  
  Serial.begin(9600);       // use the serial port
}

void loop()
{
  // read the sensor and store it in the variable sensorReading:
  sensorReading = analogRead(sensor);
  
  Serial.println(sensorReading);

  if (sensorReading >= led1Thresh)
    led1State =  HIGH;
  else
    led1State = LOW;
  
  if (sensorReading >= led2Thresh)
    led2State =  HIGH;
  else
    led2State = LOW;
  
  if (sensorReading >= led3Thresh)
    led3State =  HIGH;
  else
    led3State = LOW;
    
  if (sensorReading >= led4Thresh)
    led4State =  HIGH;
  else
    led4State = LOW;

  if (sensorReading >= led5Thresh)
    led5State =  HIGH;
  else
    led5State = LOW;
  
  digitalWrite(LED1, led1State);
  digitalWrite(LED2, led2State);
  digitalWrite(LED3, led3State);
  digitalWrite(LED4, led4State);
  digitalWrite(LED5, led5State);

  delay(10);  // delay to avoid overloading the serial port buffer
}

