// Classes and Functions START

class Motor {

  public:

    int Speed;

    int Direction;

    int EC1;

    int EC2;

    Motor(int S_pin, int D_pin, int C1, int C2) {

      Speed = S_pin;

      Direction = D_pin;

      EC1= C1;

      EC2 = C2;

    }};
void Motor_Initalize(Motor M1) {
  pinMode(M1.Speed, OUTPUT);

  pinMode(M1.Direction,OUTPUT);

  pinMode(M1.EC1, INPUT);

  pinMode(M1.EC2, INPUT);
}

void MotorControl(unsigned int speed, bool direction, int S_pin, int D_pin){

  //speed should be between 0 - 255

  //direction is HIGH for one direction and LOW for the other one

  // S_pin = Speed Control Analog Pin

  //D_pin = Direction contorl Digital Pin

 

  if(speed>255 || speed< 0) {

      Serial.println("Value between 0-255 please!");

  }

  else{

  analogWrite(S_pin, speed);

  digitalWrite(D_pin, direction);

  }

}


void Bot_Up(unsigned int speed, Motor left, Motor right, Motor top, Motor bottom) {
  Serial.print("Going up at speed: ");
  Serial.println(speed);
  MotorControl(speed, true, left.Speed, left.Direction );
  MotorControl(speed, true, right.Speed, right.Direction );
  MotorControl(0, true, top.Speed, top.Direction );
  MotorControl(0, true, bottom.Speed, bottom.Direction );
}

void Bot_Down(unsigned int speed, Motor left, Motor right, Motor top, Motor bottom) {
  Serial.print("Going down at speed: ");
  Serial.println(speed);
  MotorControl(speed, false, left.Speed, left.Direction );
  MotorControl(speed, false, right.Speed, right.Direction );
   MotorControl(0, true, top.Speed, top.Direction );
  MotorControl(0, true, bottom.Speed, bottom.Direction );
}

void Bot_Left(unsigned int speed, Motor left, Motor right, Motor top, Motor bottom) {
  Serial.print("Going left at speed: ");
  Serial.println(speed);
  MotorControl(speed, true, top.Speed, top.Direction );
  MotorControl(speed, true, bottom.Speed, bottom.Direction );
   MotorControl(0, false, left.Speed, left.Direction );
  MotorControl(0, false, right.Speed, right.Direction );
}

void Bot_Right(unsigned int speed, Motor left, Motor right, Motor top, Motor bottom) {
  Serial.print("Going right at speed: ");
  Serial.println(speed);
  MotorControl(speed, false, top.Speed, top.Direction );
  MotorControl(speed, false, bottom.Speed, bottom.Direction );
   MotorControl(0, false, left.Speed, left.Direction );
  MotorControl(0, false, right.Speed, right.Direction );
}

// Classes and Functions END


// Initialization START

Motor M1 = Motor(2,1,9,10);
Motor M2 = Motor(4,3,9,10);
Motor M3 = Motor(6,5,9,10);
Motor M4 = Motor(8,7,9,10);

//Initialization END





void setup() {

  // put your setup code here, to run once:

  Serial.begin(57600);

  Serial.println("Working!");
  Motor_Initalize(M1);
  Motor_Initalize(M2);
  Motor_Initalize(M3);
  Motor_Initalize(M4);


}
 

void loop() {
      
         MotorControl(255, false, M4.Speed, M4.Direction );

}
