#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fp;
    char line[256];
    char date[50];
    int win[3], num;
    int ticket[5][7]; // 最多五張、每張七個號碼
    int i, j, k;

    printf("請輸入中獎號碼三個：");
    scanf("%d %d %d", &win[0], &win[1], &win[2]);
    printf("輸入中獎號碼為：%02d %02d %02d\n", win[0], win[1], win[2]);

    fp = fopen("lotto.txt", "r");
    if (!fp) {
        printf("找不到 lotto.txt 檔案！\n");
        return 1;
    }

    // 讀取日期
    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, "March") || strstr(line, "Jan") || strstr(line, "Feb")) {
            strcpy(date, line);
            break;
        }
    }

    // 讀取每張彩券
    i = 0;
    while (fgets(line, sizeof(line), fp) && i < 5) {
        if (line[0] == '[') {
            char *ptr = strchr(line, ':');
            if (ptr) {
                ptr++;
                for (j = 0; j < 7; j++) {
                    if (sscanf(ptr, "%d", &num) == 1) {
                        ticket[i][j] = num;
                        ptr = strchr(ptr, ' ');
                        if (!ptr) break;
                        ptr++;
                    } else {
                        ticket[i][j] = -1;
                    }
                }
                i++;
            }
        }
    }

    printf("以下為中獎彩卷：\n");
    for (i = 0; i < 5; i++) {
        int match = 0;
        for (j = 0; j < 7; j++) {
            for (k = 0; k < 3; k++) {
                if (ticket[i][j] == win[k]) match++;
            }
        }
        if (match >= 3) {
            printf("售出時間：%s[%d]: ", date, i + 1);
            for (j = 0; j < 7; j++) {
                if (ticket[i][j] != -1)
                    printf("%02d ", ticket[i][j]);
                else
                    printf("-- ");
            }
            printf("\n");
        }
    }

    fclose(fp);
    return 0;
}
