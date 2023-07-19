#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdbool.h>


class dayNnight {
private :
	int ticket;

public : 
	int sel_ticket() {
		printf("권종을 선택하세요\n");
		printf("1. 주간권\n");
		printf("2. 야간권\n");
		scanf_s("%d", &ticket); 

		while ((ticket != 1) && (ticket != 2)) { 
			printf("다시 선택해주세요\n"); 
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
		printf("주민번호 7자리를 입력해주세요");
		scanf_s("%d", &birthdate);
		check = birthdate % 10;
		while (birthdate < 1000000 || birthdate > 9999999 || check == 0 || check == 9 ) {
			printf("잘못된 주민번호입니다. 다시 입력해주세요: ");
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
	
	printf("선택한 티켓 : %d\n", slected_ticket);
	printf("주민번호 : %d\n", birth);
	return 0;
}