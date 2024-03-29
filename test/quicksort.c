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

  return i + 1;
}

void quick_sort(int arr[], int low, int high) {
  if (low < high) {
    int pivot_index = partition(arr, low, high);

    quick_sort(arr, low, pivot_index - 1);
    quick_sort(arr, pivot_index + 1, high);
  }
  return;
}


int main() 
{

  int N = getint();
    // scanf("%d", &N);
    
    int i = 0;
    while (i < N) {
        nums[i] = getint();
        // scanf("%d", &nums[i]);
        i = i + 1;
    }

    quick_sort(nums, 0, N - 1);

    i = 0;
    while (i < N) {
        putint(nums[i]);
        putch(10);
        i = i + 1;
    }
  
  return 0;
}

