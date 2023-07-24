#include <stdio.h>
#include <string.h>
#include <iostream>
#include <utility>

using namespace std;

class location_Info {
public:
	pair<double, double> table_location[5];
	pair<double, double> kitchen_location[1];
	pair<double, double> other_location[20];

	void set_location() {};
};

class detect_position : public location_Info {
private:
	pair<double, double> Pos_X_Y; // xPos, yPos

public:
	pair<double, double> detect_sensor() {
		return Pos_X_Y;
	}

	pair<double, double> detect_location() {
        for (int i = 0; i < sizeof(table_location) / sizeof(table_location[0]); i++) {
            if (Pos_X_Y == table_location[i])
                return table_location[i]; 
        }
        for (int i = 0; i < sizeof(other_location) / sizeof(other_location[0]); i++) {
            if (Pos_X_Y == other_location[i])
                return other_location[i]; 
        }
        if (Pos_X_Y == kitchen_location[0])
            return kitchen_location[0]; 
        return make_pair(-1.0, -1.0); // return (-1, -1) if no matching location is found
    }
};



class Order
{
private:
	char menu[10];
	char menu_cost[10];
	int sum;

public:
	int menu_sum(int sum);
};

class Screen
{
private:
	int display_info;
	int display_menu;
	bool display_check;
public:
	Screen(int screen);
};

class check
{
private:
	bool from_customer;
	bool from_kitchen;

public:
	void communication();
};

class shortest_route
{
private:
	int distance;

public:
	shortest_route() : distance(0) {}

	void calculation() {
		// 최단 거리 계산 로직 구현
		std::cout << "Calculating shortest route..." << std::endl;
		// 계산 결과를 distance에 할당
		distance = 10;
	}

	int getDistance() const { return distance; }
};


class detect_obstacle
{
private:
	int camera;
	int lidar;
	int ultrasonic_sensor;

public:
	detect() : camera(0), lidar(0), ultrasonic_sensor(0) {}

	void detect_xy() {

	}

	void detect_obstacle() {
		// 장애물 감지 로직 구현
		std::cout << "Detecting obstacles..." << std::endl;
		// 장애물 감지 결과에 따라 변수 설정
		bool obstacleDetected = true;

		if (obstacleDetected) {
			// 장애물이 감지되면 멈추도록 동작
			std::cout << "Obstacle detected. Stopping." << std::endl;
		}
		else {
			// 장애물이 감지되지 않으면 움직이도록 동작
			std::cout << "No obstacle detected. Moving." << std::endl;
		}
	}
};

class state_bot
{
private:
	int trayCapacity;
public:
	state_bot(int trayCapacity) : trayCapacity(trayCapacity) {}

	void move();
	void stop();
};


int main()
{
	return 0;
}