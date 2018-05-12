#include "motors.hpp"
#include "encoder.hpp"
#include "odometry.hpp"

uint32_t lastTime;
uint16_t period(50);

void setup(){
  pinMode(encoder_left_pin, INPUT);
  pinMode(encoder_right_pin, INPUT);
  encoder_left.begin();
  encoder_right.begin();
  
  nh.initNode();
  nh.subscribe(subMotorLeft);
  nh.subscribe(subMotorRight);
  nh.advertise(encoder_left_pub);
  nh.advertise(encoder_right_pub);
  nh.advertise(odom_pub);

  initial_left_motor_angle = read2angle( encoder_left.getRawRotation() );
  initial_right_motor_angle = read2angle( encoder_right.getRawRotation() );
  
  last_time = nh.now();

  fillOdometryMsg();
}

void loop(){
  const uint32_t currentTime = millis();
  if((currentTime - lastTime) >= period)
  {
    lastTime = currentTime;
    encodersLogic();
    odometry();
  }
  nh.spinOnce();
  delay(1);
}
