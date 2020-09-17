#include <iostream>
#include <math.h>
#include <string.h>
#include "robot.hh"

using std::cout;
using std::endl;

const double goal_x = 20.0;
const double goal_y = 0.0;
bool done = false;

void callback(Robot *robot)
{
    double dx = goal_x - robot->pos_x;
    double dy = goal_y - robot->pos_y;
    double goalAngle = atan2(dy, dx);
    double robotAngle = atan2(robot->pos_y, goal_x);

    cout << endl;
    cout << "robot x =" << robot->pos_x << endl;
    cout << "robot y =" << robot->pos_y << endl;
    cout << "dx =" << dx << endl;
    cout << "dy =" << dy << endl;
    cout << "goalAngle =" << goalAngle << endl;
    cout << "robotAngle =" << robotAngle << endl;
    cout << "dif =" << robotAngle - goalAngle << endl;

    if (abs(dx) < 0.75 && abs(dy) < 0.75)
    {
        cout << "we win!" << endl;
        robot->set_vel(0.0);
        robot->set_turn(0.0);
        robot->done();
        return;
    }

    bool turn = false;
    bool ahead = false;

    for (LaserHit hit : robot->hits)
    {
        if (hit.range < 1.5)
        {
            if (hit.angle < 0.5 || hit.angle > (6.2 - 0.5))
            {
                turn = true;
            }
        }
        if (hit.range < 3)
        {
            if (hit.angle < 0.5 || hit.angle > (6.2 - 0.5))
            {
                ahead = true;
            }
        }
    }

    // there is an object in the way
    if (turn)
    {
        std::cout << "Go right to avoid object" << std::endl;

        // turn right
        robot->set_vel(3.0);
        robot->set_turn(0.5);
    }
    else // no object present move back towards going straight down middle
    {
        // dont change angle too quickly if something is ahead of almost going the right direction
        if (abs(robotAngle - goalAngle) > .1 || ahead)
        {
            robot->set_vel(3.0);
            robot->set_turn((robotAngle - goalAngle) / 4);
        }
        else // go forward!
        {
            robot->set_vel(6.0);
            robot->set_turn(robotAngle - goalAngle);
        }
    }
}

int main(int argc, char *argv[])
{
    cout << "making robot" << endl;
    Robot robot(argc, argv, callback);
    robot.do_stuff();

    return 0;
}
