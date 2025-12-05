#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


// LCR 190. 加密运算
// a ^ b得到不进位的加法
// (a & b) << 1得到进位的加法
// int addWithoutArithmetic(int a, int b) {
//     while (b != 0) {
//         int carry = (unsigned int)(a & b) << 1;     // 处理进位
//         a = a ^ b;          // 不进位加法
//         b = carry;          // 下一循环中处理进位加法，知道某一次无需进位，则完成，退出循环
//     }
//     return a;
// }

// int main() {
//     int dataA, dataB;
//     printf("%d\n", addWithoutArithmetic(dataA, dataB));
//     return 0;
// }







// LCR 191. 按规则计算统计结果
// 粗略的实现：前缀后缀相乘法
// int* statisticalResult(int* arrayA, int arrayAsize) {
//     // 前缀数组p[]和后缀数组r[]
//     int *p = (int *)malloc(arrayAsize * sizeof(int));
//     int *r = (int *)malloc(arrayAsize * sizeof(int));

//     // 获取p和r
//     p[0] = 1;
//     r[0] = 1;
//     for (int i = 1; i < arrayAsize; i++) {
//         p[i] = p[i - 1] * arrayA[i - 1];
//     }
//     for (int j = 1; j < arrayAsize; j++) {
//         r[j] = r[j - 1] * arrayA[arrayAsize - j];
//     }

//     int *resultArray = (int *)malloc(arrayAsize * sizeof(int));
//     for (int i = 0; i < arrayAsize; i++) {
//         resultArray[i] = p[i] * r[arrayAsize - i - 1];
//     }

//     return resultArray;
// }

// int main() {
//     int arrayA[5] = {2, 4, 6, 8, 10};
//     int arrayAsize = 5;

//     int *result = statisticalResult(arrayA, arrayAsize);

//     for (int i = 0; i < arrayAsize; i++) {
//         printf("%d\n", result[i]);
//     }
//     return 0;
// }

// 看看AI的吧，孬子
// 使用前后缀乘积 - O(n)复杂度
int* statisticalResult(int* arrayA, int arrayASize) {
    if (arrayA == NULL || arrayASize <= 0) {
        return NULL;
    }

    int *arrayB = (int *)malloc(arrayASize * sizeof(int));
    if (arrayB == NULL) {
        return NULL;
    }

    // 特殊情况处理
    if (arrayASize == 1) {
        arrayB[0] = 1;
        return arrayB;
    }

    // 计算前缀乘积
    int *prefix = (int *)malloc(arrayASize * sizeof(int));
    int *suffix = (int *)malloc(arrayASize * sizeof(int));

    prefix[0] = 1;
    for (int i = 1; i < arrayASize; i++) {
        // 检查乘法是否溢出
        // 细节： 不使用乘法来判断是否超出INT_MAX，防止出错
        if (prefix[i - 1] != 0 && arrayA[i - 1] > INT_MAX / prefix[i - 1]) {
            free(prefix);
            free(suffix);
            free(arrayB);
            return NULL;    // 溢出
        }
        prefix[i] = prefix[i - 1] * arrayA[i - 1];
    }

    suffix[arrayASize - 1] = 1;
    for (int i = arrayASize - 2; i >= 0; i--) {
        // 检查乘法是否溢出
        if (suffix[i + 1] != 0 && arrayA[i + 1] > INT_MAX / suffix[i+1]) {
            free(prefix);
            free(suffix);
            free(arrayB);
            return NULL;        // 溢出
        }
        suffix[i] = suffix[i + 1] * arrayA[i + 1];
    }

    // 计算结果
    for (int i = 0; i < arrayASize; i++) {
        // 检查乘法是否溢出
        if (prefix[i] != 0 && suffix[i] > INT_MAX / prefix[i]) {
            free(prefix);
            free(suffix);
            free(arrayB);
            return NULL;        // 溢出
        }
        arrayB[i] = prefix[i] * suffix[i];
    }

    free(prefix);
    free(suffix);
    return arrayB;
}