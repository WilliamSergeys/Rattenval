/*
Dit is een programma om een sevo motor te testen. Hier gaat de servo voortdurent van 0 tot 180 graden draaien
en omgekeert zonder te stopp.
*/

#include <Servo.h>

Servo myservo;  // maakt een servo object om de sevo motor te kunnen controleren
// twelve servo objects can be created on most boards
int ledPin = 8;// define LED Interface
int sensorPin = 3; // define the obstacle avoidance sensor interface
int sensorVal = 0;// define numeric variables val -> slaagt knopstatus op
int pos = 0;    // variabele om de plaats van de servo bij te houden.

int stepDelay = 1; // pauzes tussen hoekveranderingen van servo (één graad)
int resetDelay = 1000; // pauze vooraller systeem zich reset en opnieuw naar sensor luisterd

void setup()
{
  Serial.begin(9600);
  Serial.println("Program started!");
  Serial.println("Starting setup ...");

  myservo.attach(9);  // maakt de servo op pin 9 vast aan het servo object
  pinMode(ledPin, OUTPUT) ;// define LED as output interface
  pinMode(sensorPin, INPUT);// define the obstacle avoidance sensor output interface

  Serial.println("  Done!");

}

void loop()
{
  sensorVal = digitalRead(sensorPin) ;// digital interface will be assigned a value of 3 to read val

  if (sensorVal == HIGH) // When the obstacle avoidance sensor detects a signal, LED flashes
  {
    Serial.println("Sensor triggered!");
    digitalWrite(ledPin, HIGH); // test led

    Serial.println("Moving servo back and forth ...");
    for (pos = 0; pos <= 180; pos += 1)  // gaat van 0 to 180 graden
    {
    // in stappen van 1 graden
      myservo.write(pos);              // zegt de servo om naar de positie van variabele 'pos' te gaan
      delay(stepDelay);                       // wacht ...ms voor de servo om op zijn plaats te graken
    }
    for (pos = 180; pos >= 0; pos -= 1)  // gaat van 180 to 0 graden
    {
      myservo.  write(pos);              // zegt de servo om naar de positie van variabele 'pos' te gaan
      delay(stepDelay);                       // wacht ...ms voor de servo om op zijn plaats te graken
    }
    Serial.println("  Done!");

    while (sensorVal == LOW)
    {
      delay(resetDelay);
      sensorVal = digitalRead(sensorPin);
    }

    Serial.println("Resetting...");

    digitalWrite(ledPin, LOW);
  }
}
