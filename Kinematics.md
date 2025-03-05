Hear I'll be explaining the kinematics of the quadrupedal robot

As the regular quadrupedal dog, this partical robot consists of 12 servo motors; by three for each leg. The first joint is geared, the others are simply connected to servo. 

In this project's goal is to create simple quadrupedal dog. So by this, the kinematics are solved with just trigonometry. Even if we use more complex structure, the servo motors (SG90) hasn't got position feedback and not prices for complex application.

Let's examine the kinematics seperately for each plane:

## Y and Z Plane

![Y and Z Plane Image](/media/Y%20and%20Z.png)

Here in Y and Z plane, the joint points are similar to the trapezoid shape. line of A and Z are parallel and D is independent line. The goal is to get the angle omega and multiply it to required gear ratio. 

Before calculating angles, we should define the line D. To do so, by drawing a vertical line from second joint, we get right triangle with sides of Y and Z - A. By this, we can calculate the hypotenuce D with pythogorian theorem.

By drawing a line across the trapezoid, we split the angle omega and get alpha and beta angles. We calculate the angle alpha by the tangent rule. To get the angle beta, we should use the sinus rule. Finally by adding these angles we can get the angle omega. 

```c++
// Defining comstants in compile time
#define A 28.4

#define GR 35.5/16.5
```

```c++
// Calculating the angles on Y and Z plane
double D = sqrt(msg->y * msg->y + (msg->z - A) * (msg->z - A));
double alpha = atan(msg->y / A);
leg_angle_.omega = GR * atan(msg->y / A) 
                        + asin(sin(alpha) * msg->z / D);
```

## X and Y Plane

![X and Y Plane Image](/media/X%20and%20Y.png)

On this plane, we have two joints. The goal is to get theta and phi.

Drawing a line across from joint to end point, we get triangle and right triangle. Here the hypotenuse G can be evaluted by pythogorean theorem. 

The line G also splits the angle theta to alpha and beta angles. To find each, we use the tangent and sinus correspondingly.

The angle phi can be calculated by cosinus rule.

```c++
// Defining comstants in compile time
#define E 51.0
#define F 61.0
```

```c++
// Calculating the angles on X and Y plane
double G = sqrt(D * D + msg->x * msg->x);
leg_angle_.phi = acos((G * G - E * E - F * F) / (-2 * E * F));

leg_angle_.theta = atan(msg->x / D) + asin(F * sin(leg_angle_.phi) / G);
```

## The Complete IK Method
After completing the equations, now we are able to combine to a method. In this method we use LegPos and LegAngle custom messages. These messages are defined as below:
```
# LegAngles
float64 omega
float64 theta
float64 phi
```
```
# LegPos
float64 x
float64 y
float64 z
```

The constants should defined at compile time.
```C++
// Defining Constants
#define A 28.4
#define E 51.0
#define F 61.0

#define GR 35.5/16.5
```

Here in the mehtod solve_IK, we take the LegPos as parameter and return the LegAngles.
```C++
robot_interfaces::msg::LegAngles solve_IK(
    const robot_interfaces::msg::LegPos::SharedPtr msg) 
    {
        robot_interfaces::msg::LegAngles leg_angle_;

        // Y and Z plane
        double D = sqrt(msg->y * msg->y + (msg->z - A) * (msg->z - A));
        double alpha = atan(msg->y / A);
        leg_angle_.omega = GR * atan(msg->y / A) 
                                + asin(sin(alpha) * msg->z / D);

        // X and Y plane
        double G = sqrt(D * D + msg->x * msg->x);
        leg_angle_.phi = acos((G * G - E * E - F * F) / (-2 * E * F));

        leg_angle_.theta = atan(msg->x / D) + asin(F * sin(leg_angle_.phi) / G);

        return leg_angle_;
    }
```
