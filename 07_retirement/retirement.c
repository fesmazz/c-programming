#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct _retire_info retire_info;

typedef struct {
  int age;
  double savings;
} savings;

savings acc_balance (int start, double initial, retire_info info){
  savings r;
  int i; 
  double balance;
  balance = initial; 
  for(i = 0; i < info.months; i++) {
    printf("Age %3d month %2d you have $%.2f\n", start/12, start%12, balance);
    balance = (balance * info.rate_of_return) + info.contribution;
    start++;
  }
  r.age = start;
  r.savings = balance;
  return r;
}


void retirement(int startAge,     //in months
		double initial,   //initial savings in dollars
		retire_info working,   //info about working
		retire_info retired)   //info about being retirent
{
  savings r;
  r = acc_balance(startAge, initial, working);
  acc_balance(r.age, r.savings, retired);
}

int main(void) {
  retire_info working, retired;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 1 + 0.045 / 12;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 1 + 0.01 / 12;
  
  retirement(327, 21345, working, retired);
  return 0;
}

  
