#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdbool.h>


class dayNnight {
private :
	int ticket;

public : 
	int sel_ticket() {
		printf("������ �����ϼ���\n");
		printf("1. �ְ���\n");
		printf("2. �߰���\n");
		scanf_s("%d", &ticket); 

		while ((ticket != 1) && (ticket != 2)) { 
			printf("�ٽ� �������ּ���\n"); 
			scanf_s("%d", &ticket); 
		}

		return ticket;
	}
};

class Birthdate {
private :
	int birthdate;
	int check = 0;
public : 
	int CustomerBirthdate() {
		printf("�ֹι�ȣ 7�ڸ��� �Է����ּ���");
		scanf_s("%d", &birthdate);
		check = birthdate % 10;
		while (birthdate < 1000000 || birthdate > 9999999 || check == 0 || check == 9 ) {
			printf("�߸��� �ֹι�ȣ�Դϴ�. �ٽ� �Է����ּ���: ");
			scanf_s("%d", &birthdate);
			check = birthdate % 10;
		}
		printf("check : %d\n", check);
		return birthdate;
	}
};

class ticket_price {
	int price;
	
};

class discount {

};

class OrderCount {

};

int main() {
	dayNnight d;
	Birthdate b;
	int slected_ticket = d.sel_ticket();
	int birth = b.CustomerBirthdate();
	
	printf("������ Ƽ�� : %d\n", slected_ticket);
	printf("�ֹι�ȣ : %d\n", birth);
	return 0;
}