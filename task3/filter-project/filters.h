#ifndef FILTERS_H
#define FILTERS_H

#include "image.h"

// Фильтр скользящего среднего
// bufferSize - размер буфера (рекомендуется степень двойки: 2, 4, 8, 16, 32...)
Image movingAverageFilter(const Image& img, int bufferSize);

// Медианный фильтр
// filterSize - размер фильтра (должен быть нечетным: 3, 5, 7...)
Image medianFilter(const Image& img, int filterSize);

#endif // FILTERS_H

