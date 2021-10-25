/**
 * @file inversekinematics.cpp
 * @author Markose Jacob, Pooja Kabra  
 * @version 2.0
 * @date 2021-10-24
 * @copyright Copyright (c) 2021
 * 
 * @section InverseKinematics class
 * 
 * @brief This class uses the Ackermann method to calculte the headings and 
 * speed for each of the front wheels which taking into consideration the
 * physical limits of the robot. It then calculates the global heading
 * and linear speed for the robot.
 */

#include "../include/inversekinematics.hpp"
#include <math.h>
#include <time.h>
#define PI 3.14159265

/**
 * @brief This method calculates individual wheel headings in degree by 
 *        processing the heading PID output and caps them if not feasible.
 * 
 * @param actual_heading Heading PID output in degree
 * @param dt time step
 * @param direction turn direction left, right, straight if neither
 * @param car robot
 * @return ackermann::InverseKinematics::headings contains inner and outer heading
 */
ackermann::InverseKinematics::headings
ackermann::InverseKinematics::calculateWheelHeadings(double actual_heading,
double dt, char direction, Robot &car) {
    double inner_inc = 0, outer_inc = 0;
    double w = car.getTrackLength();
    double l = car.getWheelBase();

    if (direction == 'l') {
        /* calculate tenatative increment to be made to inner wheel
        heading for the time step dt */
        inner_inc = atan2(2 * l * sin(actual_heading * PI/180),
                        2 * l * cos(actual_heading * PI/180) - w *
                        sin(actual_heading * PI/180));
        inner_inc = inner_inc * 180 / PI;

        /* calculate tenatative increment to be made to outer wheel
        heading for the time step dt */
        outer_inc = atan2(2 * l * sin(actual_heading * PI/180),
        2 * l * cos(actual_heading * PI/180) + w * sin(actual_heading *
        PI/180));
        outer_inc = outer_inc * 180 / PI;

        /* if increment for inner wheel is over limit */
        if (inner_inc > car.getThetaIncrPerSecMax() * dt) {
            inner_inc = car.getThetaIncrPerSecMax() * dt;  // cap the increment

            // find corresponding actual heading
            actual_heading = ((PI/2) -
            atan2((1 / tan(inner_inc * (PI/180))+(w/2 * l)), 1)) * 180/PI;

            // recalculate outer wheel heading increment
            outer_inc = atan2(2 * l * sin(actual_heading * PI/180),
                          2 * l * cos(actual_heading * PI/180) + w *
                          sin(actual_heading * PI/180));
            outer_inc = outer_inc * 180/PI;
        }
    } else if (direction == 'r') {
        /* calculate increment to be made to inner wheel heading
         for the time step dt */
        inner_inc = atan2(2 * l * sin(actual_heading * PI/180),
                      2 * l * cos(actual_heading * PI/180) + w *
                      sin(actual_heading * PI/180));
        inner_inc = inner_inc * 180 / PI;

        /* calculate increment to be made to outer wheel heading
        for the time step dt */
        outer_inc = atan2(2 * l * sin(actual_heading * PI/180),
                      2 * l * cos(actual_heading * PI/180) - w *
                      sin(actual_heading * PI/180));
        outer_inc = outer_inc * 180 / PI;

        /* if increment for outer wheel is over limit */
        if (outer_inc > car.getThetaIncrPerSecMax() * dt) {
            outer_inc = car.getThetaIncrPerSecMax() * dt;  // cap the increment
            // find corresponding actual heading
            actual_heading = ((PI / 2) -
            atan2((1 / tan(inner_inc * (PI/180)) -
            (w / 2 * l)), 1)) * 180 / PI;
            // recalculate inner wheel heading increment
            inner_inc = atan2(2 * l * sin(actual_heading * PI/180),
                          2 * l * cos(actual_heading * PI/180) - w *
                          sin(actual_heading * PI/180));
            inner_inc = outer_inc * 180 / PI;
        }
    } else {
        /* straight moving */
        inner_inc = 0;
        outer_inc = 0;
    }

    /* update inner and outer wheel headings of robot with
    increments to current */
    car.setInnerWheelHeading(car.getInnerWheelHeading() + inner_inc);
    car.setOuterWheelHeading(car.getOuterWheelHeading() + outer_inc);

    std::cout << "Inner wheel heading(deg): " << car.getInnerWheelHeading()
    << std::endl;
    std::cout << "Outer wheel heading(deg): " << car.getOuterWheelHeading()
    << std::endl;

    /* return increments (degree)*/
    headings head;
    head.inner = inner_inc;
    head.outer = outer_inc;

    return head;
}

/**
 * @brief This method calculates inner and outer wheel speeds, both linear in m/s
 *        and angular in rps for the robot, by processing the heading PID output and capping 
 *        them if not feasible.
 * 
 * @param actual_heading Heading PID output in degree
 * @param actual_speed Speed PID output in degree
 * @param dt  time step
 * @param direction turn direction left, right, straight if neither
 * @param car robot
 * @return ackermann::InverseKinematics::speed contains inner and outer linear speeds
 */
ackermann::InverseKinematics::speed
ackermann::InverseKinematics::calculateWheelSpeeds(double actual_heading,
double actual_speed, double dt, char direction, Robot &car) {
    double r = 0, angular_speed = 0, iws_inc = 0, ows_inc = 0,
    iww_inc = 0, oww_inc = 0;
    // maximum rotation wheel motor can rotate in a sec
    double rps_max = dt * car.getRpsMax();
    double wheel_r = car.getWheelRadius();

    /* Calculate Turning radius */
    r = (car.getWheelBase() / sin(actual_heading * PI/180));
    /* (Theorotical) angular speed of robot */
    angular_speed = actual_speed / r;
    /* Tentative inner and outer wheel speed increments in m/s */
    iws_inc = angular_speed * (car.getWheelBase() /
    (sin(car.getInnerWheelHeading() * PI/180)));
    ows_inc = angular_speed * (car.getWheelBase() /
    (sin(car.getOuterWheelHeading() * PI/180)));
    /* Tentative inner and outer wheel speed increments in rps */
    iww_inc = iws_inc / wheel_r;
    oww_inc = ows_inc / wheel_r;

    if (direction == 'r') {
        /* if increment for inner wheel is over limit */
        if (iww_inc > rps_max) {
            iww_inc = rps_max;  // cap the increment
            iws_inc = rps_max * wheel_r;  // recalculate linear increment
            /* recalculate angular speed and corresponding outer wheel
            speed increment */
            angular_speed = iws_inc / (car.getWheelBase() /
            (sin(car.getInnerWheelHeading() * PI/180)));
            ows_inc = angular_speed * (car.getWheelBase() /
            (sin(car.getOuterWheelHeading() * PI/180)));
            oww_inc = ows_inc / wheel_r;
        }
    } else if (direction == 'l') {
        /* if increment for outer wheel is over limit */
        if (oww_inc > rps_max) {
            oww_inc = rps_max;  // cap the increment
            ows_inc = rps_max * wheel_r;  // recalculate linear increment
            /* recalculate angular speed and corresponding inner wheel
            speed increment */
            angular_speed = ows_inc / (car.getWheelBase() /
            (sin(car.getOuterWheelHeading() * PI/180)));
            iws_inc = angular_speed * (car.getWheelBase() /
            (sin(car.getInnerWheelHeading() * PI/180)));
            iww_inc = iws_inc / wheel_r;
        }
    } else {
        if (angular_speed > rps_max) {
            angular_speed = rps_max;  // cap angular speed
            actual_speed = angular_speed * r;  // recalculate actual speed
        }

        /* Final feasible increment values */
        oww_inc = angular_speed;
        iww_inc = angular_speed;
        iws_inc = actual_speed;
        ows_inc = actual_speed;
    }

    /* update inner and outer wheel angular speed of robot
    with increments to current */
    car.setInnerWheelRps(car.getInnerWheelRps() + iww_inc);
    car.setOuterWheelRps(car.getOuterWheelRps() + oww_inc);
    /* update inner and outer wheel linear speed of robot
    with increments to current */
    car.setInnerWheelSpeed(car.getInnerWheelSpeed() + iws_inc);
    car.setOuterWheelSpeed(car.getOuterWheelSpeed() + ows_inc);

    std::cout << "Inner wheel linear speed(m/s): " << car.getInnerWheelSpeed()
    << std::endl;
    std::cout << "Outer wheel linear speed(m/s): " << car.getOuterWheelSpeed()
    << std::endl;

    /* return speed increments(m/s) */
    speed spd;
    spd.inner_speed = iws_inc;
    spd.outer_speed = ows_inc;

    return spd;
}

/**
 * @brief This method calculates updates for global heading and speed and updates
 *        the sensor with those values.
 * 
 * @param inner_heading_incr increase in inner wheel heading in dt time in degrees
 * @param outer_heading_incr increase in inner wheel heading in dt time in degrees
 * @param sensor sensor (passsed by reference in call)
 * @param car robot (passsed by reference in call)
 * @param dt time step duration of the iteration in seconds
 */
void ackermann::InverseKinematics::calculateNewRobotHeadingandSpeed(
    double inner_heading_incr, double outer_heading_incr, Sensor &sensor,
    Robot &car, double dt) {
    double dist_left = 0;   // distance that the left wheel travels in dt time
    double dist_right = 0;  // distance that the right wheel travels in dt time
    double theta = 0;       // global heading
    /* distance = speed x time */
    dist_left = car.getInnerWheelSpeed() * dt;
    dist_right = car.getOuterWheelSpeed() * dt;

    /* updating co-ordinates of left and right wheels */
    car.yl = sin(inner_heading_incr) * dist_left + car.yl;
    car.xl = cos(inner_heading_incr) * dist_left + car.xl;
    car.yr = sin(outer_heading_incr) * dist_right + car.yr;
    car.xr = cos(outer_heading_incr) * dist_right + car.xr;

    /* finding theta from 2 points on a line */
    theta = 180 - 180 / PI * atan2(car.xr - car.xl, car.yr - car.yl);

    /* updating the sensor for heading */
    sensor.setActualHeading(theta);

    /* calculating linear speed of robot */
    double robot_speed = (car.getInnerWheelSpeed() +
    car.getOuterWheelSpeed()) / 2;

    /* updating the sensor for speed */
    sensor.setActualSpeed(robot_speed);

    /* reading updated values back from the sensor */
    std::cout << "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*"
    << "-*-*-*-*-*-*-*-*-*-*-" << std::endl;
    std::cout << "Actual heading of robot is: " << sensor.getActualHeading()
    << " deg" << std::endl;
    std::cout << "Actual speed of robot is: " << sensor.getActualSpeed()
    << " m/s" << std::endl;
    std::cout << "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*"
    <<"-*-*-*-*-*-*-*-*-*-*-" << std::endl;
    /* push current values to the sensor record (will be used for plotting) */
    sensor.actual_heading_record.push_back(sensor.getActualHeading());
    sensor.actual_speed_record.push_back(sensor.getActualSpeed());
    sensor.time_record.push_back(clock());
}
