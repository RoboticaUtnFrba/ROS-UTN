#pragma once

#include <ros.h>
#include <DCMotor.h>
#include <std_msgs/Int16.h>

#include "pinout.h"

DCMotor dcMotorLeft(EN_left, D0_left, D1_left);
DCMotor dcMotorRight(EN_right, D0_right, D1_right);

void dcmotor_left_cb(const std_msgs::Int16& cmd_msg){
    dcMotorLeft.setSpeed(cmd_msg.data);
}

void dcmotor_right_cb(const std_msgs::Int16& cmd_msg){
    dcMotorRight.setSpeed(cmd_msg.data);
}

ros::Subscriber<std_msgs::Int16> subMotorLeft(LEFT_MOTOR_TOPIC, dcmotor_left_cb);
ros::Subscriber<std_msgs::Int16> subMotorRight(RIGHT_MOTOR_TOPIC, dcmotor_right_cb);
