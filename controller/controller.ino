

// constants
const int sensor = A0; // the piezo is connected to analog pin 0
const int colWidth = 2;
const int colHeight = 5;
const int ledPins[colWidth][colHeight] = {{2,3,4,5,6},{8,9,10,11,12}}; //GPIO pins used for LED matrix
const int ledThreshold[colHeight] = {10,20,30,40,50}; // analog value thresholds for led activation


// these variables will change:
int sensorReading = 0;      // variable to store the value read from the sensor pin

void setup()
{
  // set up LEDs
  for (int i = 0; i < colWidth; i++)
  {
    for (int j = 0; j < colHeight; j++)
    {
      pinMode(ledPins[i][j], OUTPUT);
      digitalWrite(ledPins[i][j], LOW);
    }
  }
  
  Serial.begin(9600);
}

void loop()
{
  // read the sensor and store it in the variable sensorReading:
  sensorReading = analogRead(sensor);
  
  Serial.println(sensorReading);

  // light the LEDs row by row
  for ( int j = 0; j < colHeight; j++)
  {
    for (int i = 0; i < colWidth; i++)
    {
      if (sensorReading >= ledThreshold[j])
      {
        digitalWrite(ledPins[i][j], HIGH);
      }
      else
      {
        digitalWrite(ledPins[i][j], LOW);
      }
    }
  }

  delay(10);  // delay to avoid overloading the serial port buffer
}

