#pragma once
#include <random>

float rand0to1();

/*Col_Disk struct is used
* to create circles around
* all visible GameObjects.
* Col_Disks will be used to check 
* collisions between the GameObjects.
*/
struct Col_Disk {
public:
	float center_x, center_y;
	float r;
};