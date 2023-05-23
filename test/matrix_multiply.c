const int MAX_SIZE = 25;

int A[MAX_SIZE][MAX_SIZE];
int B[MAX_SIZE][MAX_SIZE];
int C[MAX_SIZE][MAX_SIZE];

int M_A, N_A, M_B, N_B;

void matrix_multiply() {
    // 计算矩阵乘法
    int i = 0;
    while (i < M_A) {
        int j = 0;
        while (j < N_B) {
            C[i][j] = 0;
            int k = 0;
            while (k < N_A) {
                C[i][j] += A[i][k] * B[k][j];
                k = k+1;
            }
            j = j+1;
        }
        i = i+1;
    }
}

int main() {
    // 读取矩阵A的维度
    scanf("%d %d", &M_A, &N_A);

    // 读取矩阵A的元素
    int i = 0;
    while (i < M_A) {
        int j = 0;
        while (j < N_A) {
            scanf("%d", &A[i][j]);
            j = j+1;
        }
        i = i+1;
    }

    // 读取矩阵B的维度
    scanf("%d %d", &M_B, &N_B);

    // 读取矩阵B的元素
    i = 0;
    while (i < M_B) {
        int j = 0;
        while (j < N_B) {
            scanf("%d", &B[i][j]);
            j = j+1;
        }
        i = i+1;
    }

    // 判断维度是否满足乘法要求
    if (N_A != M_B) {
        printf("Incompatible Dimensions\n");
        return 0;
    }
    // 调用矩阵乘法函数
    matrix_multiply();

    // 输出结果
    i = 0;
    while (i < M_A) {
        int j = 0;
        while (j < N_B) {
            printf("%10d", C[i][j]);
            j = j+1;
        }
        printf("\n");
        i = i+1;
    }

    return 0;
}
