#include <vector>
#include <immintrin.h>
#include <iostream>
#include <random>
#include <chrono>

// הגדרת מבנה וקטור תלת-ממדי
struct Vec3 {
    float x, y, z;
    Vec3(float x = 0.0f, float y = 0.0f, float z = 0.0f)
        : x(x), y(y), z(z) {}
};

// פונקציה ליצירת וקטור אקראי
std::vector<Vec3> generateRandomVectors(size_t count) {
    std::vector<Vec3> vectors;
    vectors.reserve(count);
    std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
    for (size_t i = 0; i < count; ++i) {
        vectors.emplace_back(dist(gen), dist(gen), dist(gen));
    }
    return vectors;
}

// פונקציה לחישוב המכפלה הסקלרית באמצעות SIMD
float dotProductSIMD(const std::vector<Vec3>& a, const std::vector<Vec3>& b) {
    size_t size = a.size();
    size_t simdSize = size - size % 8;
    __m256 sum = _mm256_setzero_ps();

    for (size_t i = 0; i < simdSize; i += 8) {
        float ax[8], ay[8], az[8];
        float bx[8], by[8], bz[8];
        for (int j = 0; j < 8; ++j) {
            ax[j] = a[i + j].x;
            ay[j] = a[i + j].y;
            az[j] = a[i + j].z;
            bx[j] = b[i + j].x;
            by[j] = b[i + j].y;
            bz[j] = b[i + j].z;
        }

        __m256 va_x = _mm256_loadu_ps(ax);
        __m256 va_y = _mm256_loadu_ps(ay);
        __m256 va_z = _mm256_loadu_ps(az);
        __m256 vb_x = _mm256_loadu_ps(bx);
        __m256 vb_y = _mm256_loadu_ps(by);
        __m256 vb_z = _mm256_loadu_ps(bz);

        //__m256 mul_x = _mm256_mul_ps(va_x, vb_x);
        //__m256 mul_y = _mm256_mul_ps(va_y, vb_y);
        //__m256 mul_z = _mm256_mul_ps(va_z, vb_z);
        //__m256 dot = _mm256_add_ps(_mm256_add_ps(mul_x, mul_y), mul_z);

        __m256 dot = _mm256_mul_ps(va_x, vb_x);                  // x1*x2
        dot = _mm256_fmadd_ps(va_y, vb_y, dot);               // x1*x2 + y1*y2
        dot = _mm256_fmadd_ps(va_z, vb_z, dot);               // x1*x2 + y1*y2 + z1*z2

        sum = _mm256_add_ps(sum, dot);
    }

    float result[8];
    _mm256_storeu_ps(result, sum);
    float total = result[0] + result[1] + result[2] + result[3] +
                  result[4] + result[5] + result[6] + result[7];

    // עיבוד שאר הווקטורים שלא נכללו בלולאת ה־SIMD
    for (size_t i = simdSize; i < size; ++i) {
        total += a[i].x * b[i].x + a[i].y * b[i].y + a[i].z * b[i].z;
    }

    return total;
}

int main() {
    const size_t numVectors = 1024;
    auto vecA = generateRandomVectors(numVectors);
    auto vecB = generateRandomVectors(numVectors);

    auto start = std::chrono::high_resolution_clock::now();
    float result = dotProductSIMD(vecA, vecB);
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Dot product result: " << result << std::endl;
    std::cout << "Computation time: "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
              << " microseconds" << std::endl;

    return 0;
}
