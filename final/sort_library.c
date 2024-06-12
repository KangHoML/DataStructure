#include "sort_library.h"

// sort fucntion
void select_sort(void *base, int n_elem, int size, FCMP fcmp) {
    int min_idx;

    for (int i = 0; i < n_elem - 1; i++) {
        min_idx = i;

        for (int j = i + 1; j < n_elem ; j++) {
            if (fcmp(BASE(j), BASE(min_idx)) < 0) min_idx = j;
        }
        
        swap(BASE(i), BASE(min_idx), size);
    }
}

void bubble_sort(void *base, int n_elem, int size, FCMP fcmp) {
    for (int i = 0; i < n_elem - 1; i++) {
        for (int j = 1; j < n_elem - i; j++) {
            if (fcmp(BASE(j-1), BASE(j)) > 0) swap(BASE(j-1), BASE(j), size);
        }
    }
}

void insert_sort(void *base, int n_elem, int size, FCMP fcmp) {
    void *t = malloc(size);
    int j;

    for (int i = 1; i < n_elem; i++) {
        memcpy(t, BASE(i), size);
        j = i;

        while(j > 0 && fcmp(BASE(j-1), t) > 0) {
            memcpy(BASE(j), BASE(j-1), size);
            j--;
        }

        memcpy(BASE(j), t, size);
    }

    free(t);
}

void shell_sort(void *base, int n_elem, int size, FCMP fcmp) {
    void *t = malloc(size);
    int l, step;
    
    step = 3;
    for (int i = (n_elem - 1) / step; i > 0;  i /= step) {
        for (int j = 0; j < i; j++) {
            for(int k = j + i; k < n_elem; k += i) {
                memcpy(t, BASE(k), size);
                l = k;

                while(l > i - 1 && fcmp(BASE(l-i), t) > 0) {
                    memcpy(BASE(l), BASE(l-i), size);
                    l -= i;
                }

                memcpy(BASE(l), t, size);
            }
        }
    }

    free(t);
}

void quick_sort(void *base, int n_elem, int size, FCMP fcmp) {
    int low, high;
    int left, right;

    // 초기화
    init_stack();
    left = 0, right = n_elem - 1;
    push(right);
    push(left);

    while(top >= 0) {
        // 양 끝 값 가져오기
        left = pop();
        right = pop();

        // 종료 조건 (insertion과 함께 사용할 경우, 해당 부분 수정)
        if (right - left + 1 <= 1) continue;

        // pivot을 기준으로 divide (pivot = right)
        low = left, high = right - 1;
        while(1) {
            // 각 커서 이동
            while(low <= right && fcmp(BASE(low), BASE(right)) < 0) low++;
            while(high >= left && fcmp(BASE(high), BASE(right)) > 0) high--;

            // 한 번 수행 성고
            if (low >= high) break;

            // low와 high 바꾸어주기
            swap(BASE(low), BASE(high), size);
        }

        // 최종 low와 pivot의 위치와 교환
        swap(BASE(low), BASE(right), size);

        // divide된 배열 중 큰 배열 push
        push(right);
        push(low + 1);

        // divide된 배열 중 작은 배열 push
        push(low - 1);
        push(left);
    }
}

// heap sort function
void _upheap(void *base, int h_elem, int size, FCMP fcmp) {
    int c = h_elem;
    void *t = malloc(size);

    memcpy(t, BASE(h_elem), size);
    while(c > 1 && fcmp(BASE(c/2), t) <= 0) {
        memcpy(BASE(c), BASE(c/2), size);
        c /= 2;
    }
    memcpy(BASE(c), t, size);

    free(t);
}

void _downheap(void *base, int h_elem, int p, int size, FCMP fcmp) {
    int c;
    void *t = malloc(size);

    memcpy(t, BASE(p), size);
    while(p <= h_elem / 2) {
        c = p * 2;

        if (c < h_elem && fcmp(BASE(c), BASE(c + 1)) < 0) c++;

        if (fcmp(t, BASE(c)) >= 0) break;

        memcpy(BASE(p), BASE(c), size);
        p = c;
    }
    memcpy(BASE(p), t, size);

    free(t);
}

void _insert(void *base, void *value, int *h_elem, int size, FCMP fcmp) {
    memcpy(BASE(++(*h_elem)), value, size);
    _upheap(base, *h_elem, size, fcmp);
}

void _extract(void *base, void *value, int *h_elem, int size, FCMP fcmp) {
    memcpy(value, BASE(1), size);
    memcpy(BASE(1), BASE((*h_elem)--), size);
    _downheap(base, *h_elem, 1, size, fcmp);
}

void up_heap_sort(void *base, int n_elem, int size, FCMP fcmp) {
    int h_elem;
    void *t = malloc(size);
    _shift(base, n_elem, size, 1);
    
    h_elem = 0;
    for (int i = 1; i <= n_elem; i++) {
        _insert(base, BASE(i), &h_elem, size, fcmp);
    }

    for (int i = h_elem; i > 0; i--) {
        _extract(base, t, &h_elem, size, fcmp);
        memcpy(BASE(i), t, size);
    }

    _shift(base, n_elem, size, 0);

    free(t);
}

void dn_heap_sort(void *base, int n_elem, int size, FCMP fcmp) {
    int h_elem;

    _shift(base, n_elem, size, 1);

    // 마지막 인터벌 노드부터 재정비
    h_elem = n_elem;
    for (int i = h_elem / 2; i > 0; i--) {
        _downheap(base, h_elem, i, size, fcmp);
    }

    while(h_elem > 1) {
        swap(BASE(1), BASE(h_elem), size);
        _downheap(base, --h_elem, 1, size, fcmp);
    }

    _shift(base, n_elem, size, 0);
}

// util function
void sort(void *dst, void *src, int n_elem, int size, FCMP fcmp, void(* fptr)(void *, int, int, FCMP)) {
    for (int i = 0; i < n_elem; i++) {
        memcpy(DST(i), SRC(i), size);
    }

    fptr(dst, n_elem, size, fcmp);
}

void _shift(void *base, int n_elem, int size, int r) {
    if (r == 1) {
        for (int i = n_elem; i > 0; i--) {
            memcpy(BASE(i), BASE(i-1), size);
        }
    }

    else {
        for (int i = 1; i <= n_elem; i++) {
            memcpy(BASE(i-1), BASE(i), size);
        }
    }
}