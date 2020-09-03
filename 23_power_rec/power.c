#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y) {
  // x = (unsigned) x;
  //  y = (unsigned) y;
    
  if (y == 0) {
    return 1;
  }
  else if (x == 0) {
    return 0;
  }
  else if (y == 1) {
    return x;
  }
  //  else if (y < 0) {
    //    return 1/power(x, y);
  // }
  else if (x < 0) {
    if (y%2 == 0) {
      return power(x, y);
    }
    else { 
      return  -1 *  power (x, y);
    }
  }
  else {
    return x * power (x, y-1);
  }
}


//int main (void) {
//  unsigned x = power(-2, 3);
//  unsigned y = power(2, 1);
//  printf("x is %d, and y is %d", x, y);

//  return 0;
//    }
