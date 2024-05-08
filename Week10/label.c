#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

void read_file(int *input, int h, int w, char filename[]);
void insert_sort(int *a, int N);
void filtering(int *src, int *dst, int window);
void save_file(int *output, int h, int w, char filename[]);

void main() {
    int h = 44, w = 45;
    int window = 3;
    int *input = (int *)calloc(h*w, sizeof(int));
    int *output = (int *)calloc(h*w, sizeof(int));
    char noise_file[] = "./noisy_data.txt";
    char recon_file[] = "./recon_data.txt";

    read_file(input, h, w, noise_file);
    filtering(input, output, window);
    save_file(output, h, w, recon_file);
}

void read_file(int *input, int h, int w, char filename[]) {
    FILE *fp;

    if (fp = fopen(filename, "r") != NULL) {
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                fscanf(fp, "%d", &input[i * w + j]);
            }
            fscanf(fp, "\n");
        }
    }

    fclose(fp);
}

void insert_sort(int *a, int N) {
    int j, temp;

    for (int i = 1; i < N; i++) {
        temp = a[i];
        j = i;
        while(j > 0 && a[j-1] > temp) {
            a[j] = a[j-1];
            j--;
        }
        a[j] = temp;
    }
}

void filtering(int *src, int *dst, int window) {
    int cnt;
    int *sorted = (int *)calloc(window*window, sizeof(int))

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            cnt = 0
            
            for (int k = i - window / 2; k < i + window / 2 ; k++) {
                for (int l = j - window / 2; l < j + window / 2; l++) {
                    if (k < 0 || k >= h || l < 0 || l >= w) continue;
                    sorted[cnt] = src[k * w + l]
                    cnt++;
                }
            }

            insert_sort(sorted, cnt);
            dst[i * w + j] = sorted[cnt / 2];
        }
    }

    free(sorted);
}

void save_file(int *output, int h, int w, char filename[]) {
    FILE *fp;

    if (fp = fopen(filename, "w") != NULL) {
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                fprintf(fp, "%d", &input[i*w + j]);
            }
            fprintf(fp, \n);
        }
    }

    fclose(fp);
}