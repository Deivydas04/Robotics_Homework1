#include <Servo.h>

Servo barrierServo;

// Pins
const int servoPin = 9;
const int trigPin = 7;
const int echoPin = 6;
const int buzzerPin = 5;
const int redLedPin = 4;
const int greenLedPin = 3;

// Servo positions
const int closedAngle = 0;
const int openAngle = 90;

// Detection distances
const int openDistance = 150;
const int closeDistance = 170;

// Close barrier after this long without detecting an object
const unsigned long noObjectCloseDelay = 2000;

bool barrierOpen = false;

// Stores the last time an object was detected
unsigned long lastObjectDetectedTime = 0;

void setup()
{
  barrierServo.attach(servoPin);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(buzzerPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);

  Serial.begin(9600);

  // Start closed
  barrierServo.write(closedAngle);

  digitalWrite(redLedPin, HIGH);
  digitalWrite(greenLedPin, LOW);

  noTone(buzzerPin);

  delay(500);
}

void loop()
{
  float distance = measureDistance();

  if (distance > 0)
  {
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    // Object is close enough to open barrier
    if (distance <= openDistance)
    {
      // Remember when we last saw an object
      lastObjectDetectedTime = millis();

      if (!barrierOpen)
      {
        openBarrier();
      }
    }

    // Object has moved far enough away
    else if (distance >= closeDistance && barrierOpen)
    {
      closeBarrier();
    }
  }
  else
  {
    Serial.println("No object detected");

    // If barrier is open and nothing has been detected
    // for 2 seconds, close it
    if (barrierOpen &&
        millis() - lastObjectDetectedTime >= noObjectCloseDelay)
    {
      closeBarrier();
    }
  }

  delay(100);
}

float measureDistance()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  // Wait max 30 ms for echo
  long duration = pulseIn(echoPin, HIGH, 30000);

  // No echo
  if (duration == 0)
  {
    return -1;
  }

  // Convert echo duration to centimeters
  return duration * 0.0343 / 2.0;
}

void openBarrier()
{
  Serial.println("Opening barrier...");

  // Higher pitch while opening
  tone(buzzerPin, 1200);

  digitalWrite(redLedPin, LOW);
  digitalWrite(greenLedPin, HIGH);

  barrierServo.write(openAngle);

  delay(500);

  noTone(buzzerPin);

  barrierOpen = true;

  // Start timeout from when barrier opens
  lastObjectDetectedTime = millis();

  Serial.println("Barrier open");
}

void closeBarrier()
{
  Serial.println("Closing barrier...");

  // Lower pitch while closing
  tone(buzzerPin, 600);

  digitalWrite(redLedPin, HIGH);
  digitalWrite(greenLedPin, LOW);

  barrierServo.write(closedAngle);

  delay(500);

  noTone(buzzerPin);

  barrierOpen = false;

  Serial.println("Barrier closed");
}
