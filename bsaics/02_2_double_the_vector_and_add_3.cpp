#include <iostream>
#include <immintrin.h> // כולל גם SSE

int main() {
    alignas(16) uint32_t input[100];
    alignas(16) uint32_t output[100];

    // מילוי הקלט: לדוגמה, 1 עד 100
    for (int i = 0; i < 100; ++i)
        input[i] = i + 1;

    __m128i* in_vec  = reinterpret_cast<__m128i*>(input);
    __m128i* out_vec = reinterpret_cast<__m128i*>(output);

    __m128i xmm0;
    __m128i add3 = _mm_set1_epi32(3); // כל איבר = 3

    for (int i = 0; i < 25; ++i) {
        xmm0 = _mm_load_si128(&in_vec[i]);         // טוען 4 איברים
        xmm0 = _mm_mullo_epi32(xmm0, xmm0);        // ריבוע
        xmm0 = _mm_add_epi32(xmm0, add3);          // מוסיף 3
        _mm_store_si128(&out_vec[i], xmm0);        // כותב פלט
    }

    // הדפסת כמה תוצאות לבדיקה
    for (int i = 0; i < 12; ++i)
        std::cout << output[i] << " ";
    std::cout << std::endl;

    return 0;
}
