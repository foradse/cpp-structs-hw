#ifndef SIMILARITY_H
#define SIMILARITY_H

#include "image.h"

// Структура для хранения метрик схожести
struct SimilarityMetrics {
    double mse;           // Mean Squared Error
    double psnr;          // Peak Signal-to-Noise Ratio
    double ssim;          // Structural Similarity Index
    double correlation;   // Корреляция
    
    SimilarityMetrics() : mse(0.0), psnr(0.0), ssim(0.0), correlation(0.0) {}
};

// Вычислить метрики схожести между двумя изображениями
SimilarityMetrics calculateSimilarity(const Image& img1, const Image& img2);

#endif // SIMILARITY_H

