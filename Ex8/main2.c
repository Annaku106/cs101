#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define COUNTER_FILE "counter.bin"
#define MAX_LOTTO_NUM 7
#define MAX_LOTTO_NUMSET 5

void init_file() {
    int write_array[1] = {0};
    FILE *fp = fopen(COUNTER_FILE, "r");
    if (fp == NULL) {
        FILE *tmpfp = fopen(COUNTER_FILE, "wb+");
        fwrite(write_array, sizeof(int), 1, tmpfp);
        fclose(tmpfp);
    } else {
        fclose(fp);
    }
}

int get_counter() {
    int read_array[1];
    FILE *tmpfp = fopen(COUNTER_FILE, "rb");
    fread(read_array, sizeof(int), 1, tmpfp);
    fclose(tmpfp);
    return read_array[0];
}

int num_in_numset(int num, int numset[], int Len) {
    int ret = 0;
    for (int i = 0; i < Len; i++) {
        if (num == numset[i]) {
            ret = 1;
            break;
        }
    }
    return ret;
}

void print_lotto_row(FILE *tmpfp, int n) {
    int numset[MAX_LOTTO_NUM];
    fprintf(tmpfp, "[%d]: ", n);

    // 產生前 6 個號碼 (1~69)
    for (int i = 0; i < MAX_LOTTO_NUM - 1; ) {
        int num = (rand() % 69) + 1;
        if (num_in_numset(num, numset, i)) {
            continue;
        } else {
            numset[i] = num;
            i++;
        }
    }

    // 產生第 7 個號碼 (1~10)
    while (1) {
        int num = (rand() % 10) + 1;
        if (num_in_numset(num, numset, MAX_LOTTO_NUM - 1)) {
            continue;
        } else {
            numset[MAX_LOTTO_NUM - 1] = num;
            break;
        }
    }

    // 排序前六個號碼
    for (int i = 0; i < MAX_LOTTO_NUM - 2; ++i) {
        for (int j = i + 1; j < MAX_LOTTO_NUM - 1; ++j) {
            if (numset[j] < numset[i]) {
                int temp = numset[i];
                numset[i] = numset[j];
                numset[j] = temp;
            }
        }
    }

    // 印出號碼
    for (int i = 0; i < MAX_LOTTO_NUM; i++) {
        fprintf(tmpfp, "%02d ", numset[i]);
    }
    fprintf(tmpfp, "\n");
}

void set_counter(int counter) {
    int write_array[1];
    write_array[0] = counter;
    FILE *tmpfp = fopen(COUNTER_FILE, "wb");
    fwrite(write_array, sizeof(int), 1, tmpfp);
    fclose(tmpfp);
}

void print_lottofile(int num_set, int counter, char lotto_file[]) {
    time_t curtime;
    time(&curtime);
    srand((unsigned) time(NULL));

    FILE *tmpfp = fopen(lotto_file, "w+");
    fprintf(tmpfp, "======== lotto649 ========\n");
    fprintf(tmpfp, "=======+ No.%05d +=======\n", counter);
    fprintf(tmpfp, "= %.*s=\n", 24, ctime(&curtime));

    for (int i = 0; i < MAX_LOTTO_NUMSET; i++) {
        if (i < num_set) {
            print_lotto_row(tmpfp, i + 1);
        } else {
            fprintf(tmpfp, "[%d]: -- -- -- -- -- -- --\n", i + 1);
        }
    }

    fprintf(tmpfp, "======== csie@CGU ========\n");
    fclose(tmpfp);
}

void do_lotto_main(int counter) {
    char lotto_file[32];
    int num_set = 0;

    sprintf(lotto_file, "lotto[%05d].txt", counter);
    printf("歡迎光臨長庚樂透彩購買機台\n");
    printf("請問您要買幾組樂透彩(1~5): ");
    scanf("%d", &num_set);
    if (num_set < 1 || num_set > 5) {
        printf("輸入錯誤！請輸入 1~5 之間的數字。\n");
        return;
    }

    print_lottofile(num_set, counter, lotto_file);
    printf("已為您購買的 %d 組樂透組合輸出至 %s\n", num_set, lotto_file);
}

int main() {
    init_file();
    int counter = get_counter();
    counter++;
    set_counter(counter);
    do_lotto_main(counter);
    return 0;
}
