const int MAX_SIZE = 10000;
int nums[MAX_SIZE];

void swap(int a[], int i, int j) {
  int temp = a[i];
  a[i] = a[j];
  a[j] = temp;
  return;
}

int partition(int arr[], int low, int high) {
  int pivot = arr[high];
  int i = low - 1;
  int j = low;

  while (j < high) {
    if (arr[j] <= pivot) {
      i = i + 1;
      swap(arr, i, j);
    }
    j = j + 1;
  }

  swap(arr, i + 1, high);

  return low - 1;
}

int local[4][4];

int main() 
{

  int i;
  int j;
  i = 0;
  while (i < 4) {
    j = 0;
    while (j < 4) {
      putint(local[i][j]);
      putch(32);
      j = j + 1;
    }
    putch(10);
    i = i + 1;
  }
  
  return 0;
}