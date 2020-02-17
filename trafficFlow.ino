int echoOne = 2;
int echoTwo = 10;
int trigOne = 3;
int trigTwo = 11;

unsigned long int start;
unsigned long int stopp;

void setup() {
  Serial.begin(9600);
  pinMode(echoOne, INPUT);
  pinMode(echoTwo, INPUT);
  pinMode(trigOne, OUTPUT);
  pinMode(trigTwo, OUTPUT);
}

void loop() 
{
    double distanceKm = 0.002;
    double stat = sensorOne();
    double stat2 = sensorTwo();
    bool run;

    while (true)
    {
        run = true;
        stat = sensorOne();

        if (stat < 10)
        {
            start = millis();

            while (run)
            {
                stat2 = sensorTwo();

                if (stat2 < 10)
                {
                    stopp = millis();
                    double time = stopp - start;

                    Serial.print("Time seconds: "); 
                    Serial.println(time / 1000);
                    Serial.print("Speed: ");
                    Serial.print(distanceKm / (((time / 1000) / 60) / 60));
                    Serial.println(" km/h");
                    
                    while (stat2 < 10)
                    {
                        run = false;
                        stat2 = sensorTwo();
                    }
                }
            }
            while (stat < 10)
            {
                stat = sensorOne();
            }
        }
    }
}

double sensorOne()
{
  float duration, distance;
  
  digitalWrite(trigOne, LOW); // Clear state
  delayMicroseconds(2);
  digitalWrite(trigOne, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigOne, LOW);

  duration = pulseIn(echoOne, HIGH);
  distance = (duration / 2) * 0.0343;

  return distance;
}
double sensorTwo()
{
  float duration, distance;
  
  digitalWrite(trigTwo, LOW); // Clear state
  delayMicroseconds(2);
  digitalWrite(trigTwo, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigTwo, LOW);

  duration = pulseIn(echoTwo, HIGH);
  distance = (duration / 2) * 0.0343;

  return distance;
}
