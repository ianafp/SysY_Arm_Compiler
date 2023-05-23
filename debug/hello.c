/*
 test block comment
 2
 3
 4
*/

// void f() {
//   half(1,2);
// }

int half(int x, int y) {
  // half(1, 2);
  // sb();
  // sb(1,2);
  return 22 / 2;
}

int main() {
  // test line comment
  // return 3+3-((-1)*2+3/(!5)-10%3) || (5+2>3-3);
  
  if (2) {
    3+2;
  } else {
    5+2;
  }

  if (3) 2; if (2) 1; else 0;

  if (10 || 5 && 2) {
    3+2-5*2;
  }

  while (2 || 3 && 1) {
    3+2;
    1-5*2;
  }
  while (1 && 2 && 3) {
    1+3*5;
  }

  return 0;
}