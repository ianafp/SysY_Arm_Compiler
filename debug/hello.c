const int MAX_SIZE = 10000;
int nums[MAX_SIZE];

void swap(int a[], int i, int j) {
  int temp = a[i];
  a[i] = a[j];
  a[j] = temp;
}

int main() 
{
  int local[4][4];
  local[2][1] = 7;
  putch(local[2][3]);
  return 0;
}