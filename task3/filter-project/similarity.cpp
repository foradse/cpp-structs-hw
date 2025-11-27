#include "similarity.h"
#include <cmath>
#include <algorithm>
#include <limits>

// Вычисление среднего значения
static double mean(const Image& img) {
    double sum = 0.0;
    int count = 0;
    for (int y = 0; y < img.height; ++y) {
        for (int x = 0; x < img.width; ++x) {
            sum += img.get(x, y);
            count++;
        }
    }
    return count > 0 ? sum / count : 0.0;
}

// Вычисление дисперсии
static double variance(const Image& img, double meanVal) {
    double sum = 0.0;
    int count = 0;
    for (int y = 0; y < img.height; ++y) {
        for (int x = 0; x < img.width; ++x) {
            double diff = img.get(x, y) - meanVal;
            sum += diff * diff;
            count++;
        }
    }
    return count > 0 ? sum / count : 0.0;
}

// Вычисление ковариации
static double covariance(const Image& img1, const Image& img2, double mean1, double mean2) {
    double sum = 0.0;
    int count = 0;
    int minWidth = std::min(img1.width, img2.width);
    int minHeight = std::min(img1.height, img2.height);
    
    for (int y = 0; y < minHeight; ++y) {
        for (int x = 0; x < minWidth; ++x) {
            double diff1 = img1.get(x, y) - mean1;
            double diff2 = img2.get(x, y) - mean2;
            sum += diff1 * diff2;
            count++;
        }
    }
    return count > 0 ? sum / count : 0.0;
}

SimilarityMetrics calculateSimilarity(const Image& img1, const Image& img2) {
    SimilarityMetrics metrics;
    
    // Проверка размеров
    if (img1.width != img2.width || img1.height != img2.height) {
        // Если размеры не совпадают, возвращаем нулевые метрики
        return metrics;
    }
    
    int pixelCount = img1.width * img1.height;
    if (pixelCount == 0) {
        return metrics;
    }
    
    // 1. MSE (Mean Squared Error)
    double mseSum = 0.0;
    for (int y = 0; y < img1.height; ++y) {
        for (int x = 0; x < img1.width; ++x) {
            double diff = static_cast<double>(img1.get(x, y)) - static_cast<double>(img2.get(x, y));
            mseSum += diff * diff;
        }
    }
    metrics.mse = mseSum / pixelCount;
    
    // 2. PSNR (Peak Signal-to-Noise Ratio)
    if (metrics.mse > 0.0) {
        const double MAX_PIXEL_VALUE = 255.0;
        metrics.psnr = 20.0 * log10(MAX_PIXEL_VALUE / sqrt(metrics.mse));
    } else {
        metrics.psnr = std::numeric_limits<double>::infinity(); // Идеальное совпадение
    }
    
    // 3. Корреляция (Pearson correlation coefficient)
    double mean1 = mean(img1);
    double mean2 = mean(img2);
    double var1 = variance(img1, mean1);
    double var2 = variance(img2, mean2);
    double cov = covariance(img1, img2, mean1, mean2);
    
    if (var1 > 0.0 && var2 > 0.0) {
        metrics.correlation = cov / sqrt(var1 * var2);
    } else {
        metrics.correlation = 0.0;
    }
    
    // 4. SSIM (Structural Similarity Index)
    // SSIM = [l(img1, img2)]^α * [c(img1, img2)]^β * [s(img1, img2)]^γ
    // Упрощенная версия: SSIM = (2*mean1*mean2 + C1) * (2*cov + C2) / ((mean1^2 + mean2^2 + C1) * (var1 + var2 + C2))
    const double C1 = 0.01 * 255.0 * 0.01 * 255.0; // (0.01 * L)^2, где L = 255
    const double C2 = 0.03 * 255.0 * 0.03 * 255.0; // (0.03 * L)^2
    
    double numerator = (2.0 * mean1 * mean2 + C1) * (2.0 * cov + C2);
    double denominator = (mean1 * mean1 + mean2 * mean2 + C1) * (var1 + var2 + C2);
    
    if (denominator > 0.0) {
        metrics.ssim = numerator / denominator;
    } else {
        metrics.ssim = 0.0;
    }
    
    return metrics;
}

