#include <stdio.h>
#include <stdlib.h>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

void read_file(int *noise_data, int h, int w, char filename[]);
void insert_sort(int *window, int size);
void filtering(int *noise_data, int *recon_data, int h, int w, int k);
void save_file(int *recon_data, int h, int w, char filename[]);

void main() {
    int h, w, k;
    int *noise_data, *recon_data;
    char noise_path[] = "./noise_data.txt";
    char recon_path[] = "./recon_data.txt";

    // initialize
    h = 44, w = 45, k = 5;
    noise_data = (int *)calloc(h * w, sizeof(int));
    recon_data = (int *)calloc(h * w, sizeof(int));

    // read noise file
    read_file(noise_data, h, w, noise_path);

    // filtering
    filtering(noise_data, recon_data, h, w, k);

    // save recon file
    save_file(recon_data, h, w, recon_path);
}

void read_file(int *noise_data, int h, int w, char filename[]) {
    FILE *fp;

    if ((fp = fopen(filename, "r")) == NULL) {
        printf("Failed to open file\n");
        return;
    }

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            fscanf(fp, "%d", &noise_data[i * w + j]);
        }
        fscanf(fp, "\n"); // 엔터로 구분되어 있는 행
    }

    fclose(fp);
}

void insert_sort(int *window, int size) {
    int j, temp;
    
    for (int i = 1; i < size; i++) {
        temp = window[i];
        j = i;

        while(j > 0 && window[j-1] > temp) {
            window[j] = window[j-1];
            j--;
        }

        window[j] = temp;       
    }
}

void filtering(int *noise_data, int *recon_data, int h, int w, int k) {
    int cnt;
    int *window = (int *)calloc(k * k, sizeof(int));

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            cnt = 0;
            
            for (int ii = i - k/2; ii < i + k/2; ii++) {
                for (int jj = j - k/2; jj < j + k/2; jj++) {
                    // 범위 체크
                    if (ii < 0 || ii >= h || jj < 0 || jj >= w) continue;

                    // window에 저장
                    window[cnt] = noise_data[ii * w + jj];
                    cnt++;
                }
            }

            // 정렬
            insert_sort(window, cnt);

            // 중앙 인덱스에 해당하는 값으로 바꾸어 주기
            recon_data[i* w + j] = window[cnt / 2];
        }
    }
}

void save_file(int *recon_data, int h, int w, char filename[]) {
    FILE *fp;

    if ((fp = fopen(filename, "w")) == NULL) {
        printf("Failed to open file\n");
        return;
    }

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            fprintf(fp, "%d\t", recon_data[i * w + j]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
}