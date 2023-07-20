#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <iostream>
#include <chrono>

using namespace std;

class dayNnight {
private:
	int select_dayNnight = 0;
	string day = "�ְ���";
	string night = "�߰���";
	string ticket_dayNnight;

public:
	int sel_ticket() {
		cout << "������ �����ϼ���" << endl;
		cout << "1\t" << day << endl;
		cout << "2\t" << night << endl;
		cin >> select_dayNnight;

		while ((select_dayNnight != 1) && (select_dayNnight != 2)) {
			cout << "�ٽ� �������ּ���" << endl;
			cin >> select_dayNnight;
		}

		return select_dayNnight;
	}
};

class Birthdate {
private:
	int birthdate = 0;
	int code = 0;
	
public:
	int CustomerBirthdate() {
		cout << "�ֹι�ȣ ���ڸ�(6�ڸ�)�� �Է����ּ��� : " << endl;
		cin >> birthdate;
		cout << "�ֹι�ȣ ���ڸ� ù��°���� �Է��� �ּ��� : " << endl;
		cin >> code;
		while (birthdate < 100000 || birthdate > 999999 || code < 0 || code > 9) {
			cout << "�߸��� �ֹι�ȣ�Դϴ�. �ٽ� �Է����ּ���: " << endl;
			cin >> birthdate;
			cin >> code;
		}
		return birthdate;
	}

};

class Age {
private:
	int age = 0;
public :
	int CustomerAge(int birthdate) {
		auto now = chrono::system_clock::now();
		time_t end_time = chrono::system_clock::to_time_t(now);

		int birthYear = birthdate / 10000;
		int birthMonth = (birthdate / 100) % 100;
		int birthDay = birthdate % 100;

		struct tm birth_tm = { 0 };
		birth_tm.tm_year = birthYear;
		birth_tm.tm_mon = birthMonth;
		birth_tm.tm_mday = birthDay;
		time_t birth_time = mktime(&birth_tm);

		double seconds = difftime(end_time, birth_time);
		int age = static_cast<int>(seconds) / (60 * 60 * 24 * 365);

		cout << "Current Time and Date: " << ctime(&end_time);
		cout << "������: " << age << "��" << endl;

		return age;
	}
};

class ticket_price {
private:
	double price[2][4] = {
		{56000, 47000, 44000, 44000},
		{46000, 40000, 37000, 37000}
	};
	double customer_price = 0;
	int Price_col_age = 0;
	int Price_row = 0;
	double discount = 0;
public:
	double setPrice(int age, int discountType, int select_dayNnight) {
		if (age >= 19 || age <= 64) Price_col_age = 0;
		else if(age >= 13 || age <= 18) Price_col_age = 1;
		else if (age >= 13 || age <= 18) Price_col_age = 2;
		else if (age >= 13 || age <= 18) Price_col_age = 3;

		if (select_dayNnight == 1) Price_row = 0;
		else if (select_dayNnight == 2) Price_row = 1;

		if (discountType == 1) discount = 1;
		else if (discountType == 2) discount = 0.6;
		else if (discountType == 3) discount = 0.5;
		else if (discountType == 4) discount = 0.8;
		else if (discountType == 5) discount = 0.85;

		customer_price = price[Price_row][Price_col_age] * discount;
		return customer_price;
	}

};

class discount {
private:
	int discountType = 0;
public:
	int set_discountType() {
		cout << "��� ������ �����ϼ���" << endl;
		cout << "1. ���� (���̿��� �ڵ� ó��)" << endl;
		cout << "2. �����" << endl;
		cout << "3. ����������" << endl;
		cout << "4. ���ڳ�" << endl;
		cout << "5. �ӻ��" << endl;
		cin >> discountType;
		while (discountType < 1 || discountType > 5) {
			cout << "�߸��� �����Դϴ�. �ٽ� �Է����ּ���: " <<endl;
			cin >> discountType;
		}
		return discountType;
	}
};

class OrderCount {
	
};

class receipt {
public :
	void display_receipt(double customer_price, int age) {
		cout << "===========������============" << endl;
		cout << age << endl;
		cout << customer_price << endl;
		cout << "============================" << endl;
	}
};

int main() {
	dayNnight d;
	Birthdate b;
	discount dc;
	Age a;
	receipt r;

	int birth = b.CustomerBirthdate();
	int select_dayNnight = d.sel_ticket();
	int age = a.CustomerAge(birth);
	int discountType = dc.set_discountType();

	ticket_price tp;
	double customer_price = tp.setPrice(age, discountType, select_dayNnight);

	r.display_receipt(customer_price, age);
	

	return 0;
}
