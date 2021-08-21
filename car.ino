#include <Servo.h>
#include <HCSR04.h>

#define pinServo 4
#define trig 3
#define echo 2

HCSR04 hc(trig, echo);
float distanceArr[6];
// 30 cm thresholddistance is found via excessive experiments
float thresholddistance = 30.0;

Servo myServo;
int servoArray[6] = {0, 25, 50, 110, 145, 180};

int motor_left[] = {7, 6};
int motor_right[] = {11, 10};

void brake(void);
void drive_forward(void);
void slight_left(void);
void slight_right(void);
void turn_left(void);
void turn_right(void);
void turn_around(void);
void scan_around(void);


void setup() {
  Serial.begin(9600);
  myServo.attach(pinServo);

  for (int i = 0; i < 2; i++)
  {
    pinMode(motor_left[i], OUTPUT);
    pinMode(motor_right[i], OUTPUT);
  }
}


void loop(){
  float distancefront = hc.dist();
  Serial.print("Current forward distance: ");
  Serial.print(distancefront); Serial.print("; ");
  Serial.print("Threshold distaance: ");
  Serial.println(thresholddistance);
  
 
  if ((distancefront > thresholddistance) && (distancefront < 1000))
  {
      drive_forward();
      delay(1000);
      Serial.println("Distance exceeded the threshold. The car has driven forward");
  } else {
      brake();
      scan_around();

      if ((distanceArr[1] > 1000) && (distanceArr[2] > 1000) && (distanceArr[3] > 1000) && (distanceArr[4] > 1000) && (distanceArr[5] > 1000) && (distanceArr[6] > 1000))
      {
        Serial.println("All the distances exceed 1000; Restarted the Loop");
        return -1 ;
      }

      //якщо у положеннях 25 і 50 градусів відстань більша за 30 (замість 30 могли написати thresholddistance)
      else if (((distanceArr[1]) > thresholddistance) && ((distanceArr[2]) > thresholddistance))
      {
        slight_right();
        drive_forward();
        delay(1000);
        Serial.println("2");
      }

      else if (((distanceArr[0]) > thresholddistance) && ((distanceArr[1]) > thresholddistance))
      {
        turn_right();
        drive_forward();
        delay(1000);
        Serial.println("3");
      }
  
      else if (((distanceArr[3]) > thresholddistance) && ((distanceArr[4]) > thresholddistance))
      {
        slight_left();
        drive_forward();
        delay(1000);
        Serial.println("4");
      }
 
      else if (((distanceArr[4]) > thresholddistance) && ((distanceArr[5]) > thresholddistance))
      {
        turn_left();
        drive_forward();
        delay(1000);
        Serial.println("5");
      }

      else
      {
        turn_around();
        brake();
        slight_left();
        //їдемо вперед
        drive_forward();
        delay(1000);
        Serial.println("6");
      }
    }

  // return the servo in the initial position
  myServo.write(50);  
}

void brake()
{
  digitalWrite(motor_left[0], LOW);
  digitalWrite(motor_left[1], LOW);
  digitalWrite(motor_right[0], LOW);
  digitalWrite(motor_right[1], LOW);
}

void drive_forward()
{
  digitalWrite(motor_left[0], LOW);
  delayMicroseconds(400);
  digitalWrite(motor_left[1], HIGH);
  delayMicroseconds(1000 - 400);
  digitalWrite(motor_right[0], LOW);
  delayMicroseconds(1000 - 400);
  digitalWrite(motor_right[1], HIGH);
  delayMicroseconds(400);
}

void slight_left()
{
  digitalWrite(motor_left[0], LOW);
  digitalWrite(motor_left[1], HIGH);
  digitalWrite(motor_right[0], LOW);
  digitalWrite(motor_right[1], LOW);
  delay(600);
}

void slight_right()
{
  digitalWrite(motor_left[0], LOW);
  digitalWrite(motor_left[1], LOW);
  digitalWrite(motor_right[0], LOW);
  digitalWrite(motor_right[1], HIGH);
  delay(600);
}

void turn_left()
{
  digitalWrite(motor_left[0], LOW);
  digitalWrite(motor_left[1], HIGH);
  digitalWrite(motor_right[0], LOW);
  digitalWrite(motor_right[1], LOW);
  delay(900);
}

void turn_right()
{
  digitalWrite(motor_left[0], LOW);
  digitalWrite(motor_left[1], LOW);
  digitalWrite(motor_right[0], LOW);
  digitalWrite(motor_right[1], HIGH);
  delay(900);
}

void turn_around()
{
  digitalWrite(motor_left[0], HIGH);
  digitalWrite(motor_left[1], LOW);
  digitalWrite(motor_right[0], HIGH);
  digitalWrite(motor_right[1], LOW);
  delay(600);
}

void scan_around() {
    for (int i = 0; i < 6; i++) {
      myServo.write(servoArray[i]);
      delay(100);

      distanceArr[i] = hc.dist();

      //цей шматок просто, аби вивести ту відстань у монітор порта
      Serial.print("distanceArr[");
      Serial.print(i);
      Serial.print("] = ");
      Serial.println(distanceArr[i]);
      delay(100);
    }
}

