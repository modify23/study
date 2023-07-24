#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <chrono>

using namespace std;
int num = 1;

class dayNnight {
private:
	int select_dayNnight = 0;
	string day = "주간권";
	string night = "야간권";
	//string dayNnight_save[10];
	vector<string> dayNnight_save;

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
		if (select_dayNnight == 1) dayNnight_save.push_back(day);
		else if (select_dayNnight == 2) dayNnight_save.push_back(night);
		return 0;
	}

	vector<string> get_dayNnight_save() {
		return dayNnight_save;
	}
};

class Birthdate {
private:
	int registrationBirth = 0;
	int registrationCentury = 0;

public:
	pair<int, int> CustomerBirthdate() {
		cout << "주민번호 앞자리(6자리)를 입력해주세요 : " << endl;
		cin >> registrationBirth;
		cout << "주민번호 뒷자리 첫번째까지 입력해 주세요 : " << endl;
		cin >> registrationCentury;

		// Convert current time to 'tm' struct
		auto now = chrono::system_clock::now();
		time_t end_time = chrono::system_clock::to_time_t(now);
		struct tm* end_tm = localtime(&end_time);

		int currentYear = end_tm->tm_year + 1900;
		int currentMonth = end_tm->tm_mon + 1;
		int currentDay = end_tm->tm_mday;

		int birthYear = registrationBirth / 10000;
		int birthMonth = (registrationBirth / 100) % 100;
		int birthDay = registrationBirth % 100;

		int century = (registrationCentury == 1 || registrationCentury == 2 || registrationCentury == 5 || registrationCentury == 6) ? 1900 : 2000;
		int birthYearFull = century + birthYear;

		cout << "birthYearFull" << birthYearFull << "century" << century << endl;

		// Check if the birthdate is in the future compared to the current date
		if (birthYearFull > currentYear || (birthYearFull == currentYear && birthMonth > currentMonth) || (birthYearFull == currentYear && birthMonth == currentMonth && birthDay > currentDay)) {
			cout << "주민번호가 현재 시간보다 앞서있습니다. 다시 입력해주세요." << endl;
			return CustomerBirthdate(); // Recursively call the function to re-enter the birthdate
		}

		while (registrationBirth < 100000 || registrationBirth > 999999) {
			cout << "잘못된 주민번호입니다. 다시 입력해주세요: " << endl;
			return CustomerBirthdate();
		}
		while (((registrationBirth / 100) % 100) < 0 || ((registrationBirth / 100) % 100) > 13) {
			cout << "잘못된 주민번호입니다. 다시 입력해주세요: " << endl;
			return CustomerBirthdate();
		}
		while ((registrationBirth % 100) < 0 || (registrationBirth % 100) > 31) {
			cout << "잘못된 주민번호입니다. 다시 입력해주세요: " << endl;
			return CustomerBirthdate();
		}
		while (registrationCentury < 0 || registrationCentury > 9) {
			cout << "잘못된 주민번호입니다. 다시 입력해주세요: " << endl;
			return CustomerBirthdate();
		}
		return make_pair(registrationBirth, registrationCentury);
	}

};

class Age {
private:
	int age = 0;
	//string age_save[10];
	vectir<string> age_save;
public:
	int CustomerAge(int registrationBirth, int registrationCentury) {
		auto now = chrono::system_clock::now();
		time_t end_time = chrono::system_clock::to_time_t(now);

		int birthYear = registrationBirth / 10000;
		int birthMonth = (registrationBirth / 100) % 100;
		int birthDay = registrationBirth % 100;

		int century = (registrationCentury == 1 || registrationCentury == 2 || registrationCentury == 5 || registrationCentury == 6) ? 1900 : 2000;
		int birthYearFull = century + birthYear;

		struct tm birth_tm = { 0 };
		birth_tm.tm_year = birthYear - 1900;
		birth_tm.tm_mon = birthMonth - 1;
		birth_tm.tm_mday = birthDay;

		// Convert current time to 'tm' struct
		struct tm* end_tm = localtime(&end_time);

		// Calculate the age based on the difference in years
		int age = end_tm->tm_year + 1900 - birthYearFull;

		// Adjust age if the birth date has not yet occurred this year
		if (end_tm->tm_mon < birth_tm.tm_mon || (end_tm->tm_mon == birth_tm.tm_mon && end_tm->tm_mday < birth_tm.tm_mday)) {
			age--;
		}
		cout << "만나이: " << age << "세" << endl;

		if (age >= 19 || age <= 64) age_save.push_back("대인");
		else if (age >= 13 || age <= 18)  age_save.push_back("청소년");
		else if (age >= 3 || age <= 12)  age_save.push_back("소인");
		else if (age >= 65)  age_save.push_back("경로");
		else if (age <= 2)  age_save.push_back("유아(무료)");

		return age;
	}

	vector<string> get_age_save() {
		return age_save;
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
	double price_save[10] = { 0, };
	double customer_price_save[10] = { 0, };
public:
	double setPrice(int age, int discountType, int select_dayNnight) {
		if (age >= 19 || age <= 64) Price_col_age = 0;
		else if (age >= 13 || age <= 18) Price_col_age = 1;
		else if (age >= 3 || age <= 12) Price_col_age = 2;
		else if (age >= 65) Price_col_age = 3;


		if (select_dayNnight == 1) Price_row = 0;
		else if (select_dayNnight == 2) Price_row = 1;

		if (discountType == 1) discount = 1;
		else if (discountType == 2) discount = 0.6;
		else if (discountType == 3) discount = 0.5;
		else if (discountType == 4) discount = 0.8;
		else if (discountType == 5) discount = 0.85;

		customer_price = price[Price_row][Price_col_age] * discount;
		if (age <= 2) customer_price = 0;

		price_save[num - 1] = price[Price_row][Price_col_age];
		customer_price_save[num - 1] = customer_price;

		return customer_price;
	}

	double* get_price_save() {
		return price_save;
	}

	double* get_customer_price_save() {
		return customer_price_save;
	}

};

class discount {
private:
	int discountType = 0;
	string discountType_save[10];

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
			cout << "잘못된 선택입니다. 다시 입력해주세요: " << endl;
			cin >> discountType;
		}

		if (discountType == 1) discountType_save[num - 1] = "없음";
		else if (discountType == 2) discountType_save[num - 1] = "40%";
		else if (discountType == 3) discountType_save[num - 1] = "50%";
		else if (discountType == 4) discountType_save[num - 1] = "20%";
		else if (discountType == 5) discountType_save[num - 1] = "15%";

		return discountType;
	}

	string* get_discountType_save() {
		return discountType_save;
	}
};

class OrderCount {
private:
	int ticketCount_save[10] = { 1, };
public:
	void addTicket() {
		cout << "총 몇 장을 같은 가격으로 추가 발권하시겠습니까? " << endl;
		cin >> ticketCount_save[num - 1];
	}
	int* get_TicketCount_save() {
		return ticketCount_save;
	}
};

class receipt {
public:
	void display_receipt_top() {
		cout << "===============영수증=================\n" << endl;
		cout << "No.\t권종\t나이\t정가\t할인률\t가격\t티켓수량" << endl;
	}
	void display_receipt(string dayNnight_save[], string age_save[], double price_save[], double customer_price_save[], string discountType_save[], int get_TicketCount_save[]) {
		for (int i = 0; i < num; i++) {
			cout << (i + 1) << "\t"; // No
			cout << dayNnight_save[i] << "\t"; // 권종
			cout << age_save[i] << "\t"; // 나이
			cout << price_save[i] << "\t"; // 정가
			cout << discountType_save[i] << "\t";
			cout << customer_price_save[i] << "원" << "\t"; // 가격
			cout << get_TicketCount_save[i] << "장" << endl; // 티켓수량
			cout << endl;
		}
	}
	void display_receipt_bot() {
		cout << "=====================================" << endl;
	}
};

int main() {
	dayNnight d;
	Birthdate b;
	discount dc;
	Age a;
	receipt r;
	OrderCount orderCount; // 추가 발권을 위한 OrderCount 객체 생성
	ticket_price tp;

	while (true) {
		int select_dayNnight = d.sel_ticket();
		pair<int, int> registrationData = b.CustomerBirthdate();
		int registrationBirth = registrationData.first;
		int registrationCentry = registrationData.second;
		int age = a.CustomerAge(registrationBirth, registrationCentry);
		int discountType = dc.set_discountType();
		double customer_price = tp.setPrice(age, discountType, select_dayNnight);

		int addMore;
		cout << "더 발권하시겠습니까? : " << endl;
		cout << " 1 : 동일 내용으로 추가 발권" << endl;
		cout << " 2 : 다른 내용으로 추가 발권" << endl;
		cout << " 3 : 종료" << endl;
		cin >> addMore;
		if (addMore == 1) {
			orderCount.addTicket();
			continue;
		}
		else if (addMore == 2) {
			++num;
			continue;
		}
		else if (addMore == 3) {
			vector<string> dayNnight_save = d.get_dayNnight_save();
			//string* dayNnight_save = d.get_dayNnight_save();
			string* age_save = a.get_age_save();
			double* customer_price_save = tp.get_customer_price_save();
			double* price_save = tp.get_price_save();
			string* discountType_save = dc.get_discountType_save();
			r.display_receipt_top();
			r.display_receipt(dayNnight_save, age_save, price_save, customer_price_save, discountType_save, orderCount.get_TicketCount_save());
			r.display_receipt_bot();
			break;
		}
	}

	return 0;
}
