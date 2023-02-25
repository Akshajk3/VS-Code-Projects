#include <Servo.h>

Servo x,y;
//resolution of camera
int width = 1280, hieght = 720;
//starting position of the servos
int xpos = 90, ypos = 90;

void setup()
{
  Serial.begin(9600);
  x.attach(9);
  y.attach(10);
  x.write(xpos);
  y.write(ypos);
}

const int angle = 5; // degree of increment or decrement

void loop()
{
  if (Serial.available() > 0)
  {
    int x_mid, y_mid;
    if(Serial.read() == 'X')
    {
      x_mid = Serial.parseInt(); //read center x-coordinate
      if(Serial.read() == 'Y')
      {
        y_mid = Serial.parseInt(); //read center y-coordinate
      }
    }
    if(x_mid > width / 2 + 30)
      xpos += angle;
    if(x_mid < width / 2 + 30)
      xpos -= angle;
    if(y_mid > hieght / 2 + 30)
      ypos += angle;
    if(y_mid < hieght / 2 + 30)
      ypos -= angle;

    // if the servo is outside its range
    /*
    if(xpos >= 180)
      xpos = 180;
    else if(xpos <= 0)
      xpos = 0;
    if(ypos >= 180)
      ypos = 180;
    else if(ypos <= 0)
      ypos = 0;
      */

    //used for testing
    Serial.print("\t");
    Serial.print(x_mid);
    Serial.print("\t");
    Serial.println(y_mid);

    x.write(xpos);
    y.write(ypos);
  }
}