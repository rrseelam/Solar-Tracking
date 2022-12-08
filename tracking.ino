// Solar Tracking Code
// takes input from 4 photresistors
// determines needed movement
// commands servo movement in respective function


#include <Servo.h>


// servo initialization
Servo servo_base;
Servo servo_panel;


// photoresistor values
int north = 0; 
int south = 0;
int east = 0;
int west = 0;

int counter = 0;


// servo angle values
int servo_base_angle = 0;
int servo_panel_angle = 0;


// setup run at program start
// initializes pins and servos
// resets position
// updates photores reading
void setup() {
  pinMode(A0, INPUT); // Photres North
  pinMode(A1, INPUT); // Photres South
  pinMode(A2, INPUT); // Photres East
  pinMode(A3, INPUT); // Photres West
  servo_base.attach(9);
  servo_panel.attach(10);
  Serial.begin(9600);
  reset_servos();
  update_reading();
}


// resets servos to resting position
// resets angle values
void reset_servos() {
  servo_base.write(100);
  servo_panel.write(100);
  servo_base_angle = 90;
  servo_panel_angle = 90;
}


// updates the photores readings
void update_reading() {
  north = analogRead(A0);
  south = analogRead(A1);
  east = analogRead(A2);
  west = analogRead(A3);
}


// updates panel angle (north-south)
bool update_angle() {
  update_reading();
  if(north > (south + 20) && servo_panel_angle < 180) {
    servo_panel.write(++servo_panel_angle);
    Serial.println("north");
  } 

  else if(south > (north + 20) && servo_panel_angle > 0){  
    servo_panel.write(--servo_panel_angle);
    Serial.println("south");
  }
}


// updates base angle rotation
bool update_rotation() {
  update_reading();

  //Serial.println("Servo Base Angle:" + servo_base_angle);

  if(east > (west + 20)) {
    // while( (east - west) > 20) {
    //   update_reading();
    if(servo_panel_angle > 90) {
      if(servo_base_angle > 0){
        servo_base.write(--servo_base_angle);
      }
      //if(servo_panel_angle < 150)servo_panel.write(++servo_panel_angle);
    } else {
      if(servo_base_angle < 180){
        servo_base.write(++servo_base_angle);
      }
      //if(servo_panel_angle > 30)servo_panel.write(--servo_panel_angle);
    }


      // servo_base.write(--servo_base_angle);
      // if(servo_panel_angle > 30) servo_base.write(--servo_panel_angle);
      Serial.println("east");
    // }
  }

  else if(west > (east + 20)) {
    if(servo_panel_angle > 90) {
      if(servo_base_angle < 180){
        servo_base.write(++servo_base_angle);
      }
      //if(servo_panel_angle < 150) servo_panel.write(++servo_panel_angle);
    } else {
      if(servo_base_angle > 0){
        servo_base.write(--servo_base_angle);
      }
      //if(servo_panel_angle > 30) servo_panel.write(--servo_panel_angle);
    }
    //if(servo_panel_angle < 150) servo_base.write(++servo_panel_angle);
    Serial.println("west");
  }

  //Serial.println("Servo Base Angle:" + servo_base_angle);
}

void print_readings(){
  Serial.print("north:");
  Serial.println(north);
  Serial.print("south:");
  Serial.println(south);
  Serial.print("east:");
  Serial.println(east);
  Serial.print("west:");
  Serial.println(west);
  Serial.print("base:");
  Serial.println(servo_base_angle);
  Serial.print("panel:");
  Serial.println(servo_panel_angle);
  Serial.println();
  Serial.println();
  
}

\
void update_servo_positions(){
  update_rotation();
  update_angle();
  Serial.println(servo_base_angle);
}


// loop to constantly update angle
// updates east-west alignment intermittently 
// updates north-south constantly 
// added delay to conserve power
void loop() {

  update_reading();
  update_servo_positions();

  delay(50);
  if(counter++ % 8000 == 0) {
    print_readings();
  }
}



