#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <iostream>
#include <chrono>

using namespace std;

class dayNnight {
private:
	int ticket_type;

public:
	int sel_ticket() {
		cout << "권종을 선택하세요" << endl;
		cout << "1. 주간권" << endl;
		cout << "2. 야간권" << endl;
		cin >> ticket_type;

		while ((ticket_type != 1) && (ticket_type != 2)) {
			cout << "다시 선택해주세요" << endl;
			cin >> ticket_type;
		}

		return ticket_type;
	}
};

class Birthdate {
private:
	int birthdate = 0;
	int code = 0;
	int age = 0;
public:
	int CustomerBirthdate() {
		cout << "주민번호 앞자리를 입력해주세요 : " << endl;
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

	int CustomerAge() {
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
		int years = static_cast<int>(seconds) / (60 * 60 * 24 * 365);

		cout << "Current Time and Date: " << ctime(&end_time);
		cout << "만나이: " << years << "세" << endl;

		return years;
	}
};

class ticket_price {
private:
	int price[2][4] = {
		{56000, 47000, 44000, 44000},
		{46000, 40000, 37000, 37000}
	};
public:
	void setPrice(int birthdate, int discountType, int ticket_type) {

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
			cout << "잘못된 선택입니다. 다시 입력해주세요: ";
			cin >> discountType;
		}
		return discountType;
	}
};

class OrderCount {

};

int main() {
	dayNnight d;
	Birthdate b;
	discount dc;
	//int selected_ticket = d.sel_ticket();
	int birth = b.CustomerBirthdate();
	int time = b.CustomerAge();
	//int dc_type = dc.set_discountType();

	/*
	cout << "선택한 티켓: " << selected_ticket << endl;
	cout << "주민번호: " << birth << endl;
	cout << "만나이: " << time << "세" << endl;
	cout << "우대사항: " << dc_type << endl;
	*/
	

	return 0;
}
