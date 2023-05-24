void Swap(int arr[],int i,int j)
{
  int temp = arr[i];
  arr[i] = arr[j];
  arr[j] = temp;
  i = j*4;
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