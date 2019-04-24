/*
in dit project gaan we een elektronische ratten/muizen-val maken
wanneer de sensor iets in de val dedecteert
dan draait de servomotor 90° waardoor de deur dichtvalt, de servomotor draait ook onmiddelijk terug
wanneer de pushbotton is ingedrukt, en dus de deur dicht is, geeft de relait voor een 20 tal seconden
230 V gelijkstroom door waardoor de rat sterft

*/

#include <Arduino.h>
#include <Servo.h>


Servo myservo;  // maakt een servo object om de sevo motor te kunnen controleren
// twelve servo objects can be created on most boards
int relait = 7;// drukknop op pin 7
int drukknop = 12; // de drukknop zit in pin 12
int statusknop = 0; // memory plaatje
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

  pinMode(relait, OUTPUT); // relait is OUTPUT
  digitalWrite(relait, LOW); // Relait begint uit
  pinMode(drukknop,INPUT); //De drukknop is een input

  myservo.attach(9);  // maakt de servo op pin 9 vast aan het servo object
  pinMode(ledPin, OUTPUT) ;// define LED as output interface
  pinMode(sensorPin, INPUT);// define the obstacle avoidance sensor output interface

  Serial.println("  Done!");

}

void loop()
{
  sensorVal = digitalRead(sensorPin) ;// digital interface will be assigned a value of 3 to read val

  if (sensorVal == LOW) // When the obstacle avoidance sensor detects a signal, LED flashes
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

  while  (sensorVal == HIGH) {
    statusknop = digitalRead(drukknop); //leest of drukknop ingedrukt is
  }

   if(statusknop == HIGH) { //als de status hoog is brand het lampje

     digitalWrite(relait, HIGH);

     delay(20000);// relait geeft 20 sec elec door

     digitalWrite(relait, LOW);
  }


}
