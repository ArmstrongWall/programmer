/**
 * SIMD (simple instruction, multiple data) examples in vector computation
 * The usage of these vector-processing capabilities in parallel can provide important speedups in certain algorithms
 *
 * compile: g++ -msse2 simd_example.cpp
 * run: ./a.out
 */

#include <cstdio>
#include <xmmintrin.h>

class vectorManip {
public:
    static void vectorAdd(float* a, float* b, float* c, size_t n) {
        __m128 A, B, C;
        for(size_t i = 0; i < n; i += 4) {
            A = _mm_load_ps(&a[i]);
            B = _mm_load_ps(&b[i]);
            C = _mm_add_ps(A, B);
            _mm_store_ps(&c[i], C);
        }
    }

    static void vectorSub(float* a, float* b, float* c, size_t n) {
        __m128 A, B, C;
        for(size_t i = 0; i < n; i += 4) {
            A = _mm_load_ps(&a[i]);
            B = _mm_load_ps(&b[i]);
            C = _mm_sub_ps(A, B);
            _mm_store_ps(&c[i], C);
        }
    }

    static void vectorMultiply(float* a, float* b, float* c, size_t n) {
        __m128 A, B, C;
        for(size_t i = 0; i < n; i += 4) {
            A = _mm_load_ps(&a[i]);
            B = _mm_load_ps(&b[i]);
            C = _mm_mul_ps(A, B);
            _mm_store_ps(&c[i], C);
        }
    }

    static void vectorDiv(float* a, float* b, float* c, size_t n) {
        __m128 A, B, C;
        for(size_t i = 0; i < n; i += 4) {
            A = _mm_load_ps(&a[i]);
            B = _mm_load_ps(&b[i]);
            C = _mm_div_ps(A, B);
            _mm_store_ps(&c[i], C);
        }
    }
};


int main() {
    const size_t num = 7;
    float a[num] = {1, 2, 3, 4, 5, 6, 7};
    float b[num] = {1, -1, -2, 1, -3, -2, 5};
    float c[num];
    vectorManip::vectorAdd(a, b, c, num);
    for(int i = 0; i < num; ++i) {
        printf("%f ", c[i]);
    }
    printf("\n");
    vectorManip::vectorSub(a, b, c, num);
    for(int i = 0; i < num; ++i) {
        printf("%f ", c[i]);
    }
    printf("\n");
    vectorManip::vectorMultiply(a, b, c, num);
    for(int i = 0; i < num; ++i) {
        printf("%f ", c[i]);
    }
    printf("\n");
    vectorManip::vectorDiv(a, b, c, num);
    for(int i = 0; i < num; ++i) {
        printf("%f ", c[i]);
    }
    printf("\n");

    return 0;
}
