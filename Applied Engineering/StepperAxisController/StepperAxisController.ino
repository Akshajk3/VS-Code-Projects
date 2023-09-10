#include <Stepper.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

#define STEPS 200

#define STARTING_POS 270

Adafruit_BNO055 bno = Adafruit_BNO055(55);

Stepper stepper(STEPS, 4, 5, 6, 7);

int counter = 0;
int oldDifference = 0;

void setup(void)
{
  Serial.begin(9600);

  if(!bno.begin())
  {
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

  delay(1000);

  bno.setExtCrystalUse(true);
  stepper.setSpeed(60);
}

void loop(void)
{
  sensors_event_t event; 
  bno.getEvent(&event);

  int degrees = event.orientation.x;

  int steps = degrees / 1.8;

  int difference  = 150 - steps;

  //Serial.print(event.orientation.x, 4);
  Serial.println("Steps: " + String(steps));

  if(counter != difference)
  {
    if(difference > 0)
    {
      moveMotor(1);
      counter +=  1;
    }
    if(difference < 0)
    {
      moveMotor(-1);
      counter -= 1;
    }
  }

  if(oldDifference != difference)
  {
    oldDifference = difference;
    counter = 0;
  }

//  if(counter == difference)
//  {
//    counter = 0;
//  }

  if(counter <= -100)
  {
    counter = -100;
  }
  if(counter >= 100)
  {
    counter = 100;
  }
  Serial.println("Counter: " + String(counter));
  //stepper.step(0 - steps);


  //stepper.step(event.orientation.x, 4);
  delay(100);
}

void moveMotor(int dir)
{
  stepper.step(dir);
}
