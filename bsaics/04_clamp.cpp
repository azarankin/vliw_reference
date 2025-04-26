
#include <iostream>
#include <immintrin.h>

// פונקציית clamp עבור וקטור __m256
__m256 clamp_ps(const __m256& value, const __m256& min_val, const __m256& max_val) {
    // מגביל את הערכים לערך המקסימלי
    __m256 clamped_upper = _mm256_min_ps(value, max_val);
    // מגביל את הערכים לערך המינימלי
    __m256 clamped = _mm256_max_ps(clamped_upper, min_val);
    return clamped;
}


int main() {
    // יצירת וקטור עם ערכים לדוגמה
    float data[8] = { -10.0f, 0.0f, 5.0f, 15.0f, 25.0f, 35.0f, 45.0f, 55.0f };
    __m256 vec = _mm256_loadu_ps(data);

    // הגדרת גבולות ה-clamp
    __m256 min_val = _mm256_set1_ps(5.0f);
    __m256 max_val = _mm256_set1_ps(30.0f);

    // ביצוע ה-clamp
    __m256 clamped_vec = clamp_ps(vec, min_val, max_val);

    // אחסון התוצאה במערך
    float result[8];
    _mm256_storeu_ps(result, clamped_vec);

    // הדפסת התוצאה
    std::cout << "תוצאה לאחר clamp: ";
    for (int i = 0; i < 8; ++i) {
        std::cout << result[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}