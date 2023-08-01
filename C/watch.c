//시계만들기
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#define MODE_CLOCK      0
#define MODE_ALARM      1
#define MODE_ALARM_SET  2
char mode = MODE_CLOCK;
char al_en = 0;
char alarm_call = 0;
char fnd_screen[6];
char num[4];
char watch_info[5];  // watch_info = {hour, min, sec, al_hour, al_min};

void realtimeset(char num[]);
char ttl7447(char input[]); //BCD to seg
void ttl7490(char dev, char clk, char r0, char r1, char output[]); //4-bit binary counter
void set_mode();
void mode_clock(char mode, int clk_gen, char num[]);
void time_sec(int clk_gen, char num[]);
void time_min(char num[]);
void time_hour(char num[]);
void dispAlarm(char hour, char min);
void disp_screen();
void fnd2screen(char i, char num);
char dev_realtime(char dev);
void cnvt(char num, char reverse_bin[]);
char cnvt1(char num[]);
bool alarm_check();


int main(void) {
    int cnt = 0;
    int clk_gen = 0;
    realtimeset(num); //초기 시간 설정
    while (1) {
        if (_kbhit()) {
            set_mode();
        }
        if (++cnt == 5) {
            clk_gen++;
            mode_clock(mode, clk_gen, num);
            cnt = 0;
            if (alarm_check()) printf("%c", 7);
        }
        Sleep(100);
    }
    return 0;
}
bool alarm_check() {
    if (al_en == 1)
        if ((watch_info[2] == 0) && (watch_info[0] == watch_info[3]) && (watch_info[1] == watch_info[4])) 
            alarm_call = 1;
        
    if (alarm_call) return true;
    else return false;
}
void disp_screen()
{
    char i, j, k;
    char ch = '#';
    if (al_en == 1) ch = '@';
    if (mode == MODE_ALARM_SET) ch = '*';
    for (i = 1; i <= 5; i++) {
        switch (i) {
        case 1:
            for (k = 0; k <= 5; k++) {
                if (((fnd_screen[k] >> 6) & 0x01) == 1) printf("  %c%c%c  ", ch, ch, ch);
                else if (((fnd_screen[k] >> 6) & 0x01) == 0) printf("       ");
            }
            printf("\n");
            break;
        case 2:
            for (j = 1; j <= 3; j++) {
                for (k = 0; k <= 5; k++) {
                    if (((fnd_screen[k] >> 1) & 0x01) == 1) printf(" %c   ", ch);
                    else if (((fnd_screen[k] >> 1) & 0x01) == 0) printf("     ");
                    if (((fnd_screen[k] >> 5) & 0x01) == 1) printf("%c ", ch);
                    else if (((fnd_screen[k] >> 5) & 0x01) == 0) printf("  ");
                } printf("\n");
            }
            break;
        case 3:
            for (k = 0; k <= 5; k++) {
                if (((fnd_screen[k] >> 0) & 0x01) == 1) printf("  %c%c%c  ", ch, ch, ch);
                else if (((fnd_screen[k] >> 0) & 0x01) == 0) printf("       ");
            }
            printf("\n");
            break;
        case 4:
            for (j = 1; j <= 3; j++) {
                for (int k = 0; k <= 5; k++) {
                    if (((fnd_screen[k] >> 2) & 0x01) == 1) printf(" %c   ", ch);
                    else if (((fnd_screen[k] >> 2) & 0x01) == 0) printf("     ");
                    if (((fnd_screen[k] >> 4) & 0x01) == 1) printf("%c ", ch);
                    else if (((fnd_screen[k] >> 4) & 0x01) == 0) printf("  ");
                }
                printf("\n");
            }
            break;
        case 5:
            for (k = 0; k <= 5; k++) {
                if (((fnd_screen[k] >> 3) & 0x01) == 1) printf("  %c%c%c  ", ch, ch, ch);
                else if (((fnd_screen[k] >> 3) & 0x01) == 0) printf("       ");
            }
            break;
        }
    }
    printf("\n\n***키 안내***");
    printf("\n알람 시간 설정 키 : space");
    printf("\n알람 시간 설정 완료 키 : Enter");
    printf("\n알람 활성화 키 : a");
    printf("\n#: 알람비활성화 @: 알람활성화 *: 알람시간 설정");
    printf("\n알람 종료 키 : s");
}
void set_mode() {
    static char order = 0;
    char ch;
    static char al_hour = 12, al_min = 0;
    ch = _getch();
    if (ch == ' ') {
        mode = MODE_ALARM_SET;
        order = 0;
        system("cls");
        dispAlarm(al_hour, al_min);
    }
    else if (ch == '\r') {
        if (mode == MODE_ALARM_SET)
            mode = MODE_CLOCK;
    }
    else if (ch == 'a') {
        if (al_en == 0) al_en = 1;
        else al_en = 0;
    }
    else if (ch == 's') {
        alarm_call = 0;
    }
    else if (mode == MODE_ALARM_SET) {
        if (order == 0) al_hour = (ch - '0') * 10;
        else if (order == 1) al_hour += (ch - '0');
        else if (order == 2) al_min = (ch - '0') * 10;
        else if (order == 3) al_min += (ch - '0');
        if (++order == 4) order = 0;
        system("cls");
        dispAlarm(al_hour, al_min);
        watch_info[3] = al_hour;
        watch_info[4] = al_min;
    }
}
void mode_clock(char mode, int clk_gen, char num[]) {
    time_sec(clk_gen, num);
    if (mode == MODE_CLOCK) {
        system("cls");
        disp_screen();
    }
}
void time_sec(int clk_gen, char num[]) {
    static char sec = 0;
    ttl7490(0, clk_gen % 2, 0, 0, num);
    if (clk_gen % 2 == 0) {
        fnd2screen(0, ttl7447(num));
        sec = cnvt1(num);
        ttl7490(1, num[3], 0, 0, num);
        if (num[2] == 1 && num[1] == 1)
            ttl7490(1, num[3], 1, 0, num);
        fnd2screen(1, ttl7447(num));
        sec += cnvt1(num) * 10;
        watch_info[2] = sec;
        time_min(num);
    }
}
void time_min(char num[]) {
    static char min = 0;
    ttl7490(2, num[2], 0, 0, num);
    fnd2screen(2, ttl7447(num));
    min = cnvt1(num);
    ttl7490(3, num[3], 0, 0, num);
    if (num[2] == 1 && num[1] == 1)
        ttl7490(3, num[3], 1, 0, num);
    fnd2screen(3, ttl7447(num));
    min += cnvt1(num) * 10;
    watch_info[1] = min;
    time_hour(num);
}
void time_hour(char num[]) {
    char num1[4];
    static char hour = 0;
    ttl7490(4, num[2], 0, 0, num);
    fnd2screen(4, ttl7447(num));
    hour = cnvt1(num);
    ttl7490(5, num[3], 0, 0, num1);
    if (num[2] == 1 && num[1] == 0 && num[0] == 0 && num1[1] == 1) {
        ttl7490(4, num[2], 1, 0, num);
        fnd2screen(4, ttl7447(num));
        ttl7490(5, num[3], 1, 0, num1);
    }
    fnd2screen(5, ttl7447(num1));
    hour += cnvt1(num1) * 10;
    watch_info[0] = hour;
}
void realtimeset(char num[]) {
    ttl7490(0, 0, 1, 1, num);
    ttl7490(1, 0, 1, 1, num);
    ttl7490(2, 0, 1, 1, num);
    ttl7490(3, 0, 1, 1, num);
    ttl7490(4, 0, 1, 1, num);
    ttl7490(5, 0, 1, 1, num);
} // set r0 & r1 = 1 -> real time
void cnvt(char num, char reverse_bin[]) {
    int i;
    for (i = 0; i < 4; i++)
        reverse_bin[i] = (num >> i) & 0x01;
}
char cnvt1(char num[])
{
    int i;
    char val = 0;
    for (i = 0; i < 4; i++)
        val |= (num[i] << i);
    return val;
}
void fnd2screen(char dev_num, char fnd) {
    fnd_screen[5 - dev_num] = fnd;
}
char dev_realtime(char dev) {
    time_t timer = time(NULL);
    struct tm* t = localtime(&timer);
    int real_time[6] = { 0, };
    real_time[5] = (t->tm_hour) / 10;
    real_time[4] = (t->tm_hour) % 10;
    real_time[3] = (t->tm_min) / 10;
    real_time[2] = (t->tm_min) % 10;
    real_time[1] = (t->tm_sec) / 10;
    real_time[0] = (t->tm_sec) % 10;
    return real_time[dev];
}
char ttl7447(char input[]) {
    int i;
    char num = 0;
    char fnd_dec[10] = { 126,48,109,121,51,91,95,112,127,123 };
    for (i = 0; i < 4; i++)
        num |= (input[i] << i);
    return fnd_dec[num];
    /*
    char fnd[10][7] = {
     a b c d e f g     Num DEC
    {1,1,1,1,1,1,0}, // 0, 126
    {0,1,1,0,0,0,0}, // 1, 48
    {1,1,0,1,1,0,1}, // 2, 109
    {1,1,1,1,0,0,1}, // 3, 121
    {0,1,1,0,0,1,1}, // 4, 51
    {1,0,1,1,0,1,1}, // 5, 91
    {1,0,1,1,1,1,1}, // 6, 95
    {1,1,1,0,0,0,0}, // 7, 112
    {1,1,1,1,1,1,1}, // 8, 127
    {1,1,1,1,0,1,1}  // 9, 123
    };
    */
}
void ttl7490(char dev, char clk, char r0, char r1, char output[]) {
    static char oldclk[6] = { 0, }, num[6] = { 0, };
    int i;
    // realtime set
    if (r0 == 1 && r1 == 1) {
        num[dev] = 0;
        for (i = 0; i < 4; i++)
            num[dev] = dev_realtime(dev);
    }
    else if (r0 == 1 && r1 == 0) num[dev] = 0;
    else if (r0 == 0 && r1 == 1) num[dev] = 1;
    else if (r0 == 0 && r1 == 0) {
        if (oldclk[dev] == 1 && clk == 0) { //falling edge
            if (++num[dev] == 10) num[dev] = 0;
        }
        oldclk[dev] = clk;
    }
    for (i = 0; i < 4; i++) output[i] = ((num[dev] >> i) & 0x01);
}
void dispAlarm(char hour, char min) {
    char num[4];
    cnvt(hour / 10, num);
    fnd2screen(5, ttl7447(num));
    cnvt(hour % 10, num);
    fnd2screen(4, ttl7447(num));
    cnvt(min / 10, num);
    fnd2screen(3, ttl7447(num));
    cnvt(min % 10, num);
    fnd2screen(2, ttl7447(num));
    cnvt(0, num);
    fnd2screen(1, ttl7447(num));
    fnd2screen(0, ttl7447(num));
    disp_screen();
}