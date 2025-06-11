#include <iostream>
#include <immintrin.h> // AVX2
#include <cstdlib>     // aligned_alloc, free

int main() {
    std::cout << "== SIMD with aligned_alloc: 24 elements ==" << std::endl;

    constexpr size_t num_elements = 24;
    constexpr size_t alignment = 32;

    // הקצאה מיושרת ל-24 שלמים
    int* input  = (int*)(aligned_alloc(alignment, num_elements * sizeof(int)));
    int* output = (int*)(aligned_alloc(alignment, num_elements * sizeof(int)));

    if (!input || !output) {
        std::cerr << "Memory allocation failed!" << std::endl;
        return 1;
    }

    // מילוי קלט: 1 עד 24
    for (int i = 0; i < num_elements; ++i)
        input[i] = i + 1;

    // חישוב SIMD: כל פעם 8 איברים
    for (int i = 0; i < num_elements; i += 8) {
        __m256i vec     = _mm256_load_si256(reinterpret_cast<__m256i*>(&input[i]));
        __m256i squared = _mm256_mullo_epi32(vec, vec);
        _mm256_store_si256(reinterpret_cast<__m256i*>(&output[i]), squared);
    }

    // הדפסת התוצאה
    std::cout << "Squared values: ";
    for (int i = 0; i < num_elements; ++i)
        std::cout << output[i] << " ";
    std::cout << std::endl;

    // ניקוי זיכרון
    free(input);
    free(output);

    return 0;
}
