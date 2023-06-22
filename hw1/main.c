#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define max(x, y) x>y ? x:y


int main(int argc, char** argv) {

    // 파일 오픈
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("File open error\n");
        return 0;
    }

    // 출력 파일 오픈
    char s[100] = "result_";
    strcat(s, argv[1]);
    
    FILE *fp_w = fopen(s, "w");
    if (fp_w == NULL) {
        printf("FILE open error\n");
        return 0;
    }


    // 정수로 변환
    int num = atoi(argv[2]);

    // row, column 읽어오기
    int m, n;
    fscanf(fp, "%d %d", &m, &n);

    // 2차원 배열 동적 할당
    int **arr;
    arr= (int**)malloc(sizeof(int*)*m);
    for (int i = 0; i< m; i++) {
        arr[i] = (int*)malloc(sizeof(int) * n);
    }

    // 파일에서 array 읽어오기
    for (int i = 0; i<m; i++) {
        for (int j  =0; j<n; j++) {
            fscanf(fp, "%d", &arr[i][j]);
        }
    }

    // 시간 체크
    double start, end;

    //n^6
    if (num == 1) {
        start = clock();
        int recSum = 0;
        int maxSum = -987654321;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = i; k < m; k++) {
                    for (int h = j; h < n; h++) {
                        recSum=0;
                        for (int p = i; p <= k; p++) {
                            for (int q = j; q <= h; q++) {
                                recSum += arr[p][q];
                            }
                        }
                        if(maxSum<recSum)
                            maxSum=recSum;
                    }
                }
            }
        }
        end = clock();
        double time = end - start;
        
        fprintf(fp_w, "%s\n", argv[1]);
        fprintf(fp_w, "%d\n", num);
        fprintf(fp_w, "%d\n", m);
        fprintf(fp_w, "%d\n", n);
        fprintf(fp_w, "%d\n", maxSum);
        fprintf(fp_w, "%lf\n", time);
    }

    //n^4
    else if (num == 2) {
        start = clock();
        int recSum = 0;
        int recSum2 = 0;
        int maxSum = 0;
        int **sub_arr;
        sub_arr = (int**)malloc(sizeof(int*) * (m+1));
        for (int i = 0; i < m+1; i++) {
            sub_arr[i] = (int*)malloc(sizeof(int) * (n+1));
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j< n; j++) {
                recSum = 0;
                for (int k = 0; k <= i; k++) {
                    for (int h = 0; h <= j; h++) {
                        recSum += arr[k][h];
                    }
                }
                sub_arr[i+1][j+1] = recSum;
            }
        }

        for (int i = 0; i < m+1; i++)
            sub_arr[i][0] = 0;
        for (int i = 0; i < n+1; i++)
            sub_arr[0][i] = 0;

        for (int i = 1; i < m+1; i++) {
            for (int j = 1; j < n+1; j++) {
                recSum2 = 0;
                for (int k = 1; k <= i; k++) {
                    for (int h = 1; h <= j; h++) {
                        recSum2 = sub_arr[i][j] - sub_arr[i][h-1] - sub_arr[k-1][j] + sub_arr[k-1][h-1];
                        if (maxSum < recSum2)
                            maxSum = recSum2;
                    }
                }
            }
        }
        end = clock();
        double time = end - start;
        
        fprintf(fp_w, "%s\n", argv[1]);
        fprintf(fp_w, "%d\n", num);
        fprintf(fp_w, "%d\n", m);
        fprintf(fp_w, "%d\n", n);
        fprintf(fp_w, "%d\n", maxSum);
        fprintf(fp_w, "%lf\n", time);
    }
    
    //n^3
    else if (num == 3) {
        start = clock();
        int curSum;
        int cur2Sum;
        int maxSum = -987654321;


        int *sub2_arr;
        sub2_arr = (int*)malloc(sizeof(int) * m);

        int l, r;
        for (l = 0; l < n; l++) {
            for (r = l; r < n; r++) {
                
                for (int i = 0; i < m; i++) {
                    sub2_arr[i] += arr[i][r];
                }

                int *d_arr;
                d_arr = (int*)malloc(sizeof(int)*m);
                cur2Sum = sub2_arr[0];
                d_arr[0] = sub2_arr[0];
                
                for (int i = 1; i < m; i++) {
                    d_arr[i] = max(d_arr[i-1] + sub2_arr[i], sub2_arr[i]);
                    cur2Sum = max(d_arr[i], cur2Sum);
                }
                maxSum = max(cur2Sum, maxSum);
            }

            for (int i = 0; i < m; i++) {
                sub2_arr[i] = 0;
            }
        }
        end = clock();
        double time = end - start;
        
        fprintf(fp_w, "%s\n", argv[1]);
        fprintf(fp_w, "%d\n", num);
        fprintf(fp_w, "%d\n", m);
        fprintf(fp_w, "%d\n", n);
        fprintf(fp_w, "%d\n", maxSum);
        fprintf(fp_w, "%lf\n", time);
    }

    fclose(fp);
    fclose(fp_w);

    return 0;
}
