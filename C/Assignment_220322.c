#include <stdio.h>
int main(void){
  int var = 0;
  int N;
  int i,j,k;
  int data1, data2;
  int mask = 0x0000000f;
  printf("Enter 8 numbers (0 to 15) ");
  for(int i=0; i<8; i++){
    scanf("%d", &N);
    N <<= i*4;
    var |= N;
  }
  printf ("var value : %08X\n", var);
  for(i=0; i<7; i++) {
    for(j=0; j <7; j++){
      data1 = (var>>(j*4)) & mask;
      data2 = (var>>(j+1)*4) & mask;
      if(data1 > data2){
        int temp = (var>>((j+1)*4)) & mask;
        var &= ~(mask<<((j+1)*4));
        var |= (data1<<((j+1)*4));
        var &= ~(mask<<(j*4));
        var |= (temp<<(j*4));
      }
    }
  }
  printf("Sorted var value : %08X\n", var);
}