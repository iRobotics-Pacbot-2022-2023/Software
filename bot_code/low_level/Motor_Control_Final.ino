// Classes START


//Motor Class
class Motor {

  public:

    int Speed; //Speed pin on the Teensy

    int Direction; //Direction pin on the Teensy

    int EC1; //Encoder 1 

    int EC2; //Encoder 2

    Motor(int S_pin, int D_pin, int C1, int C2) {

      Speed = S_pin;

      Direction = D_pin;

      EC1= C1;

      EC2 = C2;

    }};


//Classes END


//Functions START

//Function to Initialize the Motor pins and the Motor Object in void setup()
void Motor_Initialize(Motor M1) {
  pinMode(M1.Speed, OUTPUT);

  pinMode(M1.Direction,OUTPUT);

  pinMode(M1.EC1, INPUT);

  pinMode(M1.EC2, INPUT);
}


//Function to control the speed of an individual motor
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


//Bot Directional Control Functions


void Bot_Up(unsigned int speed, Motor top_left, Motor top_right, Motor bottom_left, Motor bottom_right) {
  Serial.print("Going up at speed: ");
  Serial.println(speed);
  MotorControl(speed, true, top_left.Speed, top_left.Direction );
  MotorControl(speed, false, top_right.Speed, top_right.Direction );
  MotorControl(speed, true, bottom_left.Speed, bottom_left.Direction );
  MotorControl(speed, false, bottom_right.Speed, bottom_right.Direction );
}

void Bot_Down(unsigned int speed, Motor top_left, Motor top_right, Motor bottom_left, Motor bottom_right) {
  Serial.print("Going down at speed: ");
  Serial.println(speed);
  MotorControl(speed, false, top_left.Speed, top_left.Direction );
  MotorControl(speed, true, top_right.Speed, top_right.Direction );
  MotorControl(speed, false, bottom_left.Speed, bottom_left.Direction );
  MotorControl(speed, true, bottom_right.Speed, bottom_right.Direction );
}

void Bot_Left(unsigned int speed, Motor top_left, Motor top_right, Motor bottom_left, Motor bottom_right) {
  Serial.print("Going left at speed: ");
  Serial.println(speed);
  MotorControl(speed, true, top_left.Speed, top_left.Direction );
  MotorControl(speed, true, top_right.Speed, top_right.Direction );
  MotorControl(speed, false, bottom_left.Speed, bottom_left.Direction );
  MotorControl(speed, false, bottom_right.Speed, bottom_right.Direction );
}

void Bot_Right(unsigned int speed, Motor top_left, Motor top_right, Motor bottom_left, Motor bottom_right) {
  Serial.print("Going right at speed: ");
  Serial.println(speed);
  MotorControl(speed, false, top_left.Speed, top_left.Direction );
  MotorControl(speed, false, top_right.Speed, top_right.Direction );
  MotorControl(speed, true, bottom_left.Speed, bottom_left.Direction );
  MotorControl(speed, true, bottom_right.Speed, bottom_right.Direction );
}


void Bot_Bottom_Left(unsigned int speed,Motor top_left, Motor top_right, Motor bottom_left, Motor bottom_right) {
  
  MotorControl( speed,true, top_left.Speed, top_left.Direction );
  MotorControl(0, false, top_right.Speed, top_right.Direction );
  MotorControl( 0, false, bottom_left.Speed, bottom_left.Direction );
  MotorControl( speed,false, bottom_right.Speed, bottom_right.Direction );
}

void Bot_Bottom_Right(unsigned int speed,Motor top_left, Motor top_right, Motor bottom_left, Motor bottom_right) {
  
  MotorControl(0, false, top_left.Speed, top_left.Direction );
  MotorControl(190, false, top_right.Speed, top_right.Direction );
  MotorControl(speed, true, bottom_left.Speed, bottom_left.Direction );
  MotorControl( 0,false, bottom_right.Speed, bottom_right.Direction );
}

void Bot_Top_Left(unsigned int speed,Motor top_left, Motor top_right, Motor bottom_left, Motor bottom_right) {
  
  MotorControl( 0, false, top_left.Speed, top_left.Direction );
  MotorControl(190, true, top_right.Speed, top_right.Direction );
  MotorControl(255, false, bottom_left.Speed, bottom_left.Direction );
  MotorControl(0, false, bottom_right.Speed, bottom_right.Direction );
}

void Bot_Top_Right(unsigned int speed,Motor top_left, Motor top_right, Motor bottom_left, Motor bottom_right) {
  
  MotorControl( 255,false, top_left.Speed, top_left.Direction );
  MotorControl( 0,false, top_right.Speed, top_right.Direction );
  MotorControl( 0, false, bottom_left.Speed, bottom_left.Direction );
  MotorControl( 190,true, bottom_right.Speed, bottom_right.Direction );
}

// Functions END



// Initialization of Objects START

Motor M1 = Motor(12,23,0,1);
Motor M2 = Motor(10,11,0,1);
Motor M3 = Motor(5,6,0,1);
Motor M4 = Motor(8,9,0,1);

//Initialization of Objects END





void setup() {

  Serial.begin(57600);
  //Motor Initialization
  Serial.println("Working!");

  Motor_Initialize(M1);
  Motor_Initialize(M2);
  Motor_Initialize(M3);
  Motor_Initialize(M4);

}
 

void loop() {
      Bot_Up(125, M1,M2,M3,M4);
      
}
