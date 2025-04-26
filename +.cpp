#include <immintrin.h>
#include <iostream>

void add_arrays(const float* a, const float* b, float* result, size_t size) {
    size_t i = 0;

    // שלב 1: עיבוד וקטורי ל-8 איברים בכל פעם
    for (; i + 7 < size; i += 8) {
        __m256 va = _mm256_loadu_ps(&a[i]);
        __m256 vb = _mm256_loadu_ps(&b[i]);
        __m256 vsum = _mm256_add_ps(va, vb);
        _mm256_storeu_ps(&result[i], vsum);
    }

    // שלב 2: עיבוד סקאלרי לשארית (אם יש)
    for (; i < size; ++i) {
        result[i] = a[i] + b[i];
    }
}