#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <iostream>
#include <chrono>

using namespace std;
int num = 1;

class dayNnight {
private:
	int select_dayNnight = 0;
	string day = "�ְ���";
	string night = "�߰���";
	string dayNnight_save[10];

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
		if (select_dayNnight == 1) dayNnight_save[num-1] = day;
		else if (select_dayNnight == 2) dayNnight_save[num - 1] = night;
		return 0;
	}

	string* get_dayNnight_save() {
		return dayNnight_save;
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
		while (birthdate < 100000 || birthdate > 999999 ) {
			cout << "�߸��� �ֹι�ȣ�Դϴ�. �ٽ� �Է����ּ���: " << endl;
			cin >> birthdate;
			cin >> code;
		}
		while (((birthdate / 100) % 100) < 0 || ((birthdate / 100) % 100) > 13) {
			cout << "�߸��� �ֹι�ȣ�Դϴ�. �ٽ� �Է����ּ���: " << endl;
			cin >> birthdate;
			cin >> code;
		}
		while ((birthdate % 100) < 0 || (birthdate % 100) > 31) {
			cout << "�߸��� �ֹι�ȣ�Դϴ�. �ٽ� �Է����ּ���: " << endl;
			cin >> birthdate;
			cin >> code;
		}
		while (code < 0 || code > 9) {
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
	string age_save[10];
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

		//cout << "Current Time and Date: " << ctime(&end_time);
		cout << "������: " << age << "��" << endl;

		if (age >= 19 || age <= 64) age_save[num-1] = "����";
		else if (age >= 13 || age <= 18) age_save[num - 1] = "û�ҳ�";
		else if (age >= 3 || age <= 12) age_save[num - 1] = "����";
		else if (age >= 65) age_save[num - 1] = "���";
		else if (age >= 2) age_save[num - 1] = "����(����)";

		return age;
	}

	string* get_age_save() {
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
		else if(age >= 13 || age <= 18) Price_col_age = 1;
		else if (age >= 3 || age <= 12) Price_col_age = 2;
		else if(age >= 65) Price_col_age = 3;
		

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

		if (discountType == 1) discountType_save[num - 1] = "����";
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
	int ticketCount = 0;
public:
	void addTicket() {
		ticketCount++;
	}
	int getTicketCount() {
		return ticketCount;
	}
};

class receipt {
public :
	void display_receipt_top() {
		cout << "===============������=================\n" << endl;
		cout << "No.\t����\t����\t����\t���η�\t����\tƼ�ϼ���" << endl;
	}
	void display_receipt(string dayNnight_save[], string age_save[], double price_save[], double customer_price_save[], string discountType_save[], int ticketCount) {
		for (int i = 0; i < num; i++) {
			cout << (i+1) << "\t"; // No
			cout << dayNnight_save[i] << "\t"; // ����
			cout << age_save[i] << "\t"; // ����
			cout << price_save[i] << "\t"; // ����
			cout << discountType_save[i] << "\t";
			cout << customer_price_save[i] << "��" << "\t" ; // ����
			//cout << ticketCount << "��" << endl; // Ƽ�ϼ���
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
	OrderCount orderCount; // �߰� �߱��� ���� OrderCount ��ü ����
	ticket_price tp;

	int ticketCount = 0;

	while (true) {
		int select_dayNnight = d.sel_ticket();
		int birth = b.CustomerBirthdate();
		int age = a.CustomerAge(birth);
		int discountType = dc.set_discountType();
		double customer_price = tp.setPrice(age, discountType, select_dayNnight);

		char addMore;
		cout << "�� �߱��Ͻðڽ��ϱ�? (Y/N): ";
		cin >> addMore;
		if (addMore == 'Y' || addMore == 'y') {
			num++;
			continue;
		}
		else {
			string* dayNnight_save = d.get_dayNnight_save();
			string* age_save = a.get_age_save();
			double* customer_price_save = tp.get_customer_price_save();
			double* price_save = tp.get_price_save();
			string* discountType_save = dc.get_discountType_save();
			r.display_receipt_top();
			r.display_receipt(dayNnight_save, age_save, price_save, customer_price_save, discountType_save, orderCount.getTicketCount());
			r.display_receipt_bot();
			break; 
		}
	}

	return 0;
}
