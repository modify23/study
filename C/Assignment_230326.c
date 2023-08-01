// ##문제1번

#include <stdio.h>


int main() 
{
  unsigned short a, b = 0;
  char sum = 0;
  char c_in, c_out;
  char i ;
  int result[17];
  
  printf("덧셈할 두 숫자를 입력해주세요 : \n");
  scanf("%hd %hd", &a, &b);

  for(i = 0; i <=15; i++){
    
    //c_in = ((a>>i) & 1) & ((b>>i) & 1);
    sum = ((a>>i) & 1) ^ ((b>>i) & 1) ^ c_out;
    c_out = ((a>>i) & 1) & ((b>>i) & 1) | (((a>>i) & 1) ^ ((b>>i) & 1)) & c_out;
    
    printf("%d %d\n", c_in, sum);
    result[i] = sum;
  }

  result[16] = '\0';

  int check =0 ;
  for(i= 15; i>=0; i--){
    if(result[i] == 1) check = 1;
    if(check ==1) printf("%d", result[i]);
    if(i%4 == 0) printf(" ");
  }

  return 0;
}



// ##문제 2번
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
char puzzle[3][3];
char arr[3][3] = {'1','2','3','4','5','6','7','8','x'};
int i, j;
void display();
void change();
int check();
int main()
{
  char num[] ={'1','2','3','4','5','6','7','8','x'};
  int  temp, rand_idx;
  int  idx = 0;
  char move;
  int  x, y;
  int finish = 0;
// 숫자 랜덤 배치
  srand(time(NULL));
  for(i = 0; i<9 ; i++){
    rand_idx = rand() % 9;
    temp = num[i];
    num[i] = num[rand_idx];
    num[rand_idx] = temp;
  }
  for(int i= 0; i<3; i++){
    for(int j= 0; j<3; j++){
      puzzle[i][j] = num[idx];
      idx++;
    }
  }
/////////////
  printf("\nGame start\n");
  display();
while(finish == 0){
  printf("공백(x)을 이동할 위치의 숫자를 입력해주세요.\n");
  scanf("%c", &move);
  getchar();
  change(move);
  display();
  if(check()) {printf("게임이 끝났습니다.\n"); finish = 1;}
  else finish = 0;
  }
  return 0;
}
/////////////////
void change(move)
{
  int row;
  int col;
  int nx, ny;
  char dx[] = {-1, 0, 0, 1};
  char dy[] = {0, 1, -1, 0};
  for( i = 0; i < 3; i++){
    for ( j = 0; j < 3; j++){
      if (puzzle[i][j] == move ){
        row = i;
        col = j;}
    }
  }
  for( i = 0; i <4 ; i++){
    nx = row + dx[i];
    ny = col + dy[i];
    if(ny <0 || ny >2 || nx <0 || nx >2 ) continue;
    else {
      if( puzzle[nx][ny] == 'x'){
          puzzle[nx][ny] = move;
          puzzle[row][col] = 'x';
          break;
        }
    }
  }
}
/////////////////
void display()
{
  for(int i=0; i<3; i++){
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", puzzle[i][0], puzzle[i][1], puzzle[i][2]);
  }
    printf("---|---|---\n\n");
}
/////////////////
int check (){
  for(i=0; i<3; i++){
    for(j=0; j<3; j++){
      if(puzzle[i][j] != arr[i][j])
      return 0;
    }
  }
  return 1;
}