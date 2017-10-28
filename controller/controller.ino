#include <RingBuf.h>


/*=============== constants =================*/

// Piezo Pin: analog 0
const int sensorPin = A0;

// Number of LED columns and rows
const int colWidth = 2;
const int colHeight = 5;

//GPIO pins used for LED matrix
const int ledPins[colWidth][colHeight] = {{2,3,4,5,6},{8,9,10,11,12}};

// analog value thresholds for led activation
const int ledThreshold[colHeight] = {10,20,30,40,50};

// Delay for loop
const int samplePeriod = 20; // milliseconds
const int bufferSize = 64;


/*=============== Class Defs =================*/

/* Class Light:
 * Manages updating an LED state
 */
class Light
{
public:
  
  /* Constructor
   * @param pin: the pin the LED is connected to
   * @param threshold: the analog input value the LED should trigger at
   */
  Light(int pin, int threshold)
    : m_pin(pin)
    , m_threshold(threshold)
    , m_state(LOW)
  {
    pinMode(m_pin, OUTPUT);
    digitalWrite(m_pin, LOW);
  }
  
  /* function update
   * @param value: a value to test against the LED's saved threshold value
   *               results in turning on the LED if larger, off if smaller
   */
  void update(int value)
  {
    if (value >= m_threshold)
      m_state = HIGH;
    else
      m_state = LOW;
      
    digitalWrite(m_pin, m_state);
  }

private:
  int m_pin;
  int m_threshold;
  int m_state;
};

class Sensor
{
public:
  Sensor(int pin, int buflen)
    : m_pin(pin)
    , m_buflen(buflen)
  {
    m_pBuffer = RingBuf_new(sizeof(int), m_buflen);
  }

  ~Sensor()
  {
    RingBuf_delete(m_pBuffer);
  }

  int read()
  {
    m_latest = analogRead(m_pin);
    int last = 0;
    int throwaway; // value for throw away
    
    if (m_pBuffer->isFull(m_pBuffer))
      last = (int)m_pBuffer->pull(m_pBuffer, &throwaway);
    
    // in theory should check queue fullness, 
    // but its now garanteed not to be full since we just popped from the end
    m_pBuffer->add(m_pBuffer, &m_latest);
    
    m_sum = m_sum + m_latest - last;
    m_average = m_sum / m_buflen;

    return m_latest;
  }

  int filter()
  {
    return m_average;
  }
  
private:
  int m_pin;
  RingBuf* m_pBuffer;
  int m_buflen;
  int m_latest = 0;
  int m_sum = 0;
  int m_average = 0;
};


/*=============== Global Vars =================*/
// Sensor object managing sensor reads, conversion and filtering
Sensor sensor(sensorPin, bufferSize);

// matrix of Light objects
Light* lights[colWidth][colHeight];


void setup()
{
  // set up LEDs
  for (int i = 0; i < colWidth; i++)
  {
    for (int j = 0; j < colHeight; j++)
    {
      lights[i][j] = new Light(ledPins[i][j], ledThreshold[j]);
    }
  }
  
  Serial.begin(9600);
}

void loop()
{
  // read the sensor and store it in the variable sensorReading:
  int sensorReading = sensor.read();
  int filteredReading = sensor.filter();
  
  Serial.println("Sensor:");
  Serial.println(sensorReading);
  //Serial.println("Filter:");
  //Serial.println(filteredReading);
  

  // light the LEDs row by row
  for ( int j = 0; j < colHeight; j++)
  {
    for (int i = 0; i < colWidth; i++)
    {
      lights[i][j]->update(sensorReading);
    }
  }

  delay(samplePeriod);  // delay to avoid overloading the serial port buffer
}

