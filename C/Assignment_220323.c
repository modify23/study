#include <stdio.h>
int main(void) {
  char font[8];
  int a, b;
  font[0] = 0xf4;
  font[1] = font[2] = 0x14;
  font[3] = 0x17;
  for(a=4; a<=7; a++) font[a] = 0x14;
 printf("font : \n\n");
  for(b = 0; b<=7; b++){
    for(a = 7; a>=0; a--) {
      if ( ((font[b]>>a)&1) == 1) printf("*");
      else printf(" ");
    }
    printf("\n");
  }
 printf("\n\n상하 반전 : \n\n");
 for(b = 7; b>=0; b--){
    for(a = 7; a>=0; a--) {
      if ( ((font[b]>>a)&1) == 1) printf("*");
      else printf(" ");
    }
    printf("\n");
  }
  printf("\n\n좌우 반전 : \n\n");
  for(b = 0; b<=7; b++){
    for(a = 0; a<=7; a++) {
      if ( ((font[b]>>a)&1) == 1) printf("*");
      else printf(" ");
    }
    printf("\n");
  }
  printf("\n\n90도 회전 : \n\n");
  for(a = 7; a>=0; a--){
    for(b = 7; b>=0; b--) {
      if ( ((font[b]>>a)&1) == 1) printf("*");
      else printf(" ");
    }
    printf("\n");
  }
  printf("\n\n-90도 회전 : \n\n");
  for(a = 0; a<=7; a++){
    for(b = 0; b<=7; b++) {
      if ( ((font[b]>>a)&1) == 1) printf("*");
      else printf(" ");
    }
    printf("\n");
  }
}