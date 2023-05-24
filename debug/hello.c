const int MAX_SIZE = 10000;
int nums[MAX_SIZE];

void swap(int a[], int i, int j) {
  int temp = a[i];
  a[i] = a[j];
  a[j] = temp;
}

int main() 
{
  int local[4][4] = {{1},{2,3}};

  local[0][0] = 1;
  local[1][0] = 2;
  local[1][2] = 3;
  putch(local[2][3]);
  return 0;
}