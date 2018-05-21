#include "motors.hpp"
#include "encoder.hpp"
#include "odometry.hpp"

void setup(){
  encoder_left.begin();
  encoder_right.begin();
  // Right motor turns to the other side
  dcMotorRight.setClockwise(false);
  
  nh.initNode();
  nh.subscribe(subMotorLeft);
  nh.subscribe(subMotorRight);
  nh.advertise(encoder_left_pub);
  nh.advertise(encoder_right_pub);
  nh.advertise(odom_pub);
  
  last_time = nh.now();

  fillOdometryMsg();
}

void loop(){
  current_time = nh.now();
  
  if((current_time.toNsec() - last_time.toNsec())/1E9 >= 1.0/rate)
  {
    encodersLogic();
    odometry();
    last_time = current_time;
  }
  nh.spinOnce();
}
