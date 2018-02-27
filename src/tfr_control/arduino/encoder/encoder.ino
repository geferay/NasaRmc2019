/*
 * rosserial Publisher Example
 * Prints "hello world!"
 */

#include <ros.h>
#include <tfr_msgs/DrivebaseVelocity.h>

#include <quadrature.h>

ros::NodeHandle nh;

tfr_msgs::DrivebaseVelocity velocities{};
ros::Publisher drivebase_publisher{"drivebase_velocity", &velocities};

//encoder level constants
const double GEARBOX_PPR = 4096.0; //pulse per revolution
const double GEARBOX_RPM = 0.876; //revolutions per meter

//pin constants
const int GEARBOX_LEFT_A = 2;
const int GEARBOX_LEFT_B = 3;

//encoders
Quadrature gearbox_left{GEARBOX_PPR, GEARBOX_LEFT_A, GEARBOX_LEFT_B};

//algorithm constants
float rate{1/50.0};

void setup()
{
    nh.initNode();
    nh.advertise(drivebase_publisher);
    nh.getParam("~rate", &rate);
    
}

void loop()
{
    velocities.timestamp = nh.now();
    velocities.left_vel = gearbox_left.getVelocity();
    drivebase_publisher.publish(&velocities);
    nh.spinOnce();
    delay(rate);
}
