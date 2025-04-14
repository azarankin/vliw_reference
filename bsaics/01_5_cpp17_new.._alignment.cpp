#include <iostream>
#include <immintrin.h>
#include <new> // std::align_val_t

int main() {
    constexpr size_t num_elements = 8;
    constexpr size_t alignment = 32;

    // הקצאה מיושרת
    int* input  = new(std::align_val_t(alignment)) int[num_elements];
    int* output = new(std::align_val_t(alignment)) int[num_elements];

    // מילוי הנתונים
    for (int i = 0; i < num_elements; ++i)
        input[i] = i + 1;

    // טעינה, חישוב, כתיבה
    __m256i vec     = _mm256_load_si256(reinterpret_cast<__m256i*>(input));
    __m256i squared = _mm256_mullo_epi32(vec, vec);
    _mm256_store_si256(reinterpret_cast<__m256i*>(output), squared);

    // הדפסה
    std::cout << "Squared values: ";
    for (int i = 0; i < num_elements; ++i)
        std::cout << output[i] << " ";
    std::cout << std::endl;

    // שחרור
    delete[] input;
    delete[] output;

    return 0;
}
