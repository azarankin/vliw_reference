#include <iostream>
#include <immintrin.h> // AVX2
#include <new>         // ::operator new עם יישור
#include <cstdlib>     // free (אם בוחר ב-aligned_alloc במקום)

int main() {
    std::cout << "== Hello from SIMD with aligned new ==" << std::endl;

    constexpr size_t num_elements = 8;
    constexpr size_t alignment = 32;

    // הקצאה עם יישור (C++17 ומעלה)
    int* input  = static_cast<int*>(::operator new[](num_elements * sizeof(int), std::align_val_t(alignment)));
    int* output = static_cast<int*>(::operator new[](num_elements * sizeof(int), std::align_val_t(alignment)));

    // מילוי הנתונים
    for (int i = 0; i < num_elements; ++i)
        input[i] = i + 1;

    // SIMD: טעינה, חישוב ריבוע, כתיבה
    __m256i vec     = _mm256_load_si256(reinterpret_cast<__m256i*>(input));
    __m256i squared = _mm256_mullo_epi32(vec, vec);
    _mm256_store_si256(reinterpret_cast<__m256i*>(output), squared);

    // הדפסה
    std::cout << "Squared values: ";
    for (int i = 0; i < num_elements; ++i)
        std::cout << output[i] << " ";
    std::cout << std::endl;

    // ניקוי זיכרון
    ::operator delete[](input, std::align_val_t(alignment));
    ::operator delete[](output, std::align_val_t(alignment));

    return 0;
}
