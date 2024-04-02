#include <stdio.h>
#include <stdlib.h>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

void main() {
    FILE* fp;
    int score;
    int num = 0;
    float avg = 0.0;

    fp = fopen("score.txt", "w");
    while(1) {
        printf("input score: ");
        scanf("%d", &score);
        if (score < 0) break;
        fprintf(fp, "%d\n", score);
    }
    fclose(fp);

    fp = fopen("score.txt", "r");
    if (fp != NULL) {
        int* a_score = (int*)malloc(70*sizeof(int));
        
        while(fscanf(fp, "%d", a_score + num) != EOF) {
            num++;
        }

        for (int i = 0; i < num; i++) {
            avg += *(a_score +i);
        }

        avg /= (float)num;
        printf("avg = %f\n", avg);

        free(a_score);
    }
    fclose(fp);
}