#include <stdio.h>
#include <stdlib.h>
#include "sort_library.h"

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

void read_file(int *src, int h, int w, char filename[]);
void filtering(int *dst, int *src, int h, int w, int k);
void save_file(int *dst, int h, int w, char filename[]);

void main() {
    int h, w, k;
    int *noise_data, *recon_data;
    char noise_path[] = "./noise_data.txt";
    char recon_path[] = "./recon_data.txt";
    
    // initialize
    h = 44, w = 45, k = 7;
    noise_data = (int *)malloc(h * w * sizeof(int));
    recon_data = (int *)malloc(h * w * sizeof(int));

    // read file
    read_file(noise_data, h, w, noise_path);

    // filtering
    filtering(recon_data, noise_data, h, w, k);

    // save file
    save_file(recon_data, h, w, recon_path);
}

void read_file(int *src, int h, int w, char filename[]) {
    FILE *fp;

    fp = fopen(filename, "r");
    if (fp == NULL) return;

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            fscanf(fp, "%d", &src[i * w + j]);
        }
        fscanf(fp, "\n");
    }

    fclose(fp);
}

void filtering(int *dst, int *src, int h, int w, int k) {
    int *window = (int *)malloc(k * k * sizeof(int));
    int cnt;

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            cnt = 0;
            
            for (int ni = i - k/2; ni <= i + k/2; ni++) {
                for (int nj = j - k/2; nj <= j + k/2; nj++) {
                    if (ni < 0 || ni >= h || nj < 0 || nj >= w) continue;
                    window[cnt++] = src[ni * w + nj];
                }
            }

            insert_sort(window, cnt, sizeof(int), intcmp);
            dst[i * w + j] = window[cnt/2];
        }
    }

    free(window);
}

void save_file(int *dst, int h, int w, char filename[]) {
    FILE *fp;

    fp = fopen(filename, "w");
    if (fp == NULL) return;

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            fprintf(fp, "%d\t", dst[i * w + j]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
}