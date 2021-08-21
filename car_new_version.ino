int motor_left[] = {9, 8};
int motor_right[] = {11, 10};

void brake(void);
void drive_forward(void);
void turn_left(void);
void turn_right(void);
void turn_around(void);

char Incoming_value;

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
  if(Serial.available() > 0)  
  {
    Incoming_value = Serial.read();
    switch (Incoming_value){
      case 'F':
        drive_forward();
        break;
      case 'R':
        turn_right();
        break;
      case 'B':
        turn_around();
        break;
      case 'L':
        turn_left();
        break; 
      default:
        brake();
        break;
    }
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
  digitalWrite(motor_left[1], HIGH);
  digitalWrite(motor_right[0], LOW);
  digitalWrite(motor_right[1], HIGH);
}

void slight_left()
{
  digitalWrite(motor_left[0], LOW);
  digitalWrite(motor_left[1], HIGH);
  digitalWrite(motor_right[0], LOW);
  digitalWrite(motor_right[1], LOW);
}

void slight_right()
{
  digitalWrite(motor_left[0], LOW);
  digitalWrite(motor_left[1], LOW);
  digitalWrite(motor_right[0], LOW);
  digitalWrite(motor_right[1], HIGH);
}

void turn_right()
{
  digitalWrite(motor_left[0], LOW);
  digitalWrite(motor_left[1], HIGH);
  digitalWrite(motor_right[0], LOW);
  digitalWrite(motor_right[1], LOW);
}

void turn_left()
{
  digitalWrite(motor_left[0], LOW);
  digitalWrite(motor_left[1], LOW);
  digitalWrite(motor_right[0], LOW);
  digitalWrite(motor_right[1], HIGH);
}

void turn_around()
{
  digitalWrite(motor_left[0], HIGH);
  digitalWrite(motor_left[1], LOW);
  digitalWrite(motor_right[0], HIGH);
  digitalWrite(motor_right[1], LOW);
}
