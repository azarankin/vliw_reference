#include <iostream>
#include <immintrin.h> // עבור AVX2

int main() {
    std::cout << "== Hello from WSL C++ with SIMD! ==" << std::endl;

    // הגדרת וקטור של 8 מספרים שלמים
    alignas(32) int input[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    alignas(32) int output[8];

    // טעינת הנתונים ל־__m256i
    __m256i vec = _mm256_load_si256(reinterpret_cast<__m256i*>(input));

    // חישוב ריבוע: vec * vec
    __m256i squared = _mm256_mullo_epi32(vec, vec);

    // אחסון התוצאה חזרה למערך
    _mm256_store_si256(reinterpret_cast<__m256i*>(output), squared);

    // הדפסת תוצאה
    std::cout << "Squared values: ";
    for (int i = 0; i < 8; i++) {
        std::cout << output[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
 