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
	string day = "주간권";
	string night = "야간권";
	string ticket_dayNnight;

public:
	int sel_ticket() {
		cout << "권종을 선택하세요" << endl;
		cout << "1\t" << day << endl;
		cout << "2\t" << night << endl;
		cin >> select_dayNnight;

		while ((select_dayNnight != 1) && (select_dayNnight != 2)) {
			cout << "다시 선택해주세요" << endl;
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
		cout << "주민번호 앞자리(6자리)를 입력해주세요 : " << endl;
		cin >> birthdate;
		cout << "주민번호 뒷자리 첫번째까지 입력해 주세요 : " << endl;
		cin >> code;
		while (birthdate < 100000 || birthdate > 999999 || code < 0 || code > 9) {
			cout << "잘못된 주민번호입니다. 다시 입력해주세요: " << endl;
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
		cout << "만나이: " << age << "세" << endl;

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
		cout << "우대 사항을 선택하세요" << endl;
		cout << "1. 없음 (나이우대는 자동 처리)" << endl;
		cout << "2. 장애인" << endl;
		cout << "3. 국가유공자" << endl;
		cout << "4. 다자녀" << endl;
		cout << "5. 임산부" << endl;
		cin >> discountType;
		while (discountType < 1 || discountType > 5) {
			cout << "잘못된 선택입니다. 다시 입력해주세요: " <<endl;
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
		cout << "===========영수증============" << endl;
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
