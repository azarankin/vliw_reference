#include <iostream>
#include <immintrin.h> // AVX2
#include <cstdlib>     // aligned_alloc, free

int main() {
    std::cout << "== Hello from WSL C++ with SIMD on heap ==" << std::endl;

    // נניח שנעבוד על 8 איברים (256 ביט / 32 בתים)
    constexpr size_t num_elements = 8;
    constexpr size_t alignment = 32;

    // הקצאת זיכרון מיושר ב-heap עבור קלט ופלט
    int* input  = static_cast<int*>(aligned_alloc(alignment, num_elements * sizeof(int)));
    int* output = static_cast<int*>(aligned_alloc(alignment, num_elements * sizeof(int)));

    // בדיקת הצלחה
    if (!input || !output) {
        std::cerr << "Memory allocation failed!" << std::endl;
        return 1;
    }

    // מילוי נתונים
    for (int i = 0; i < num_elements; ++i)
        input[i] = i + 1;  // 1 עד 8

    // טעינת הנתונים ל־SIMD vector
    __m256i vec = _mm256_load_si256(reinterpret_cast<__m256i*>(input));

    // חישוב ריבוע לכל איבר
    __m256i squared = _mm256_mullo_epi32(vec, vec);

    // אחסון תוצאה חזרה לזיכרון
    _mm256_store_si256(reinterpret_cast<__m256i*>(output), squared);

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
