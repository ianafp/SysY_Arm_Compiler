
void HELLO() {
  putch(72);
  putch(101);
  putch(108);
  putch(108);
  putch(111);
  putch(44);
  putch(32);
  putch(87);
  putch(111);
  putch(114);
  putch(108);
  putch(100);
  putch(33);
  putch(10);
  return ;
}

int main() 
{
  int a = 5;
  
  while(a > 0)
  {
    putint(a);
    putch(10);
    HELLO();
    a = a - 1;
  }
  int t = getch();
  putint(t);
  putch(10);
  return 0;
}