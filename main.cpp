#include <stdio.h>
#include <string.h>
#include <iostream>
class detect_position
{
private:
	int x;
	int y;

public:
	detect_position(int startX, int startY) : x(startX), y(startY) {}

	int getX() const { return x; }
	int getY() const { return y; }

	void updatePosition(int newX, int newY) {
		x = newX;
		y = newY;
	}
};

class location_Info {
private:
	char table_location[4][4];
	char kitchen_location[1][1];
	char other_location[8][8];
public:
	void setTableLocation(int x, int y, char location) {
		if (x >= 0 && x < 4 && y >= 0 && y < 4) {
			table_location[x][y] = location;
		}
	}

	void setKitchenLocation(int x, int y, char location) {
		if (x == 0 && y == 0) {
			kitchen_location[x][y] = location;
		}
	}

	void setOtherLocation(int x, int y, char location) {
		if (x >= 0 && x < 8 && y >= 0 && y < 8) {
			other_location[x][y] = location;
		}
	}

	char getLocation(const detect_position& pos) {
		int xPos = pos.getX();
		int yPos = pos.getY();

		// table_location���� ��ġ Ȯ��
		if (xPos >= 0 && xPos < 4 && yPos >= 0 && yPos < 4) {
			return table_location[xPos][yPos];
		}

		// kitchen_location���� ��ġ Ȯ��
		if (xPos == 0 && yPos == 0) {
			return kitchen_location[xPos][yPos];
		}

		// other_location���� ��ġ Ȯ��
		if (xPos >= 0 && xPos < 8 && yPos >= 0 && yPos < 8) {
			return other_location[xPos][yPos];
		}

		return ' ';  // �ش��ϴ� ��ġ�� ���� ��� ���� ��ȯ
	}
};

class Order
{
private:
	char menu[20][10];
	int sum;

public:
	int menu_sum(int sum);
};

class Screen
{
private:
	int display_info;
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
		// �ִ� �Ÿ� ��� ���� ����
		std::cout << "Calculating shortest route..." << std::endl;
		// ��� ����� distance�� �Ҵ�
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
		// ��ֹ� ���� ���� ����
		std::cout << "Detecting obstacles..." << std::endl;
		// ��ֹ� ���� ����� ���� ���� ����
		bool obstacleDetected = true;

		if (obstacleDetected) {
			// ��ֹ��� �����Ǹ� ���ߵ��� ����
			std::cout << "Obstacle detected. Stopping." << std::endl;
		}
		else {
			// ��ֹ��� �������� ������ �����̵��� ����
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

