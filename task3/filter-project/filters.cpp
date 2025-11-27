#include "filters.h"
#include <algorithm>
#include <vector>
#include <cmath>

// Фильтр скользящего среднего
// Использует буфер для хранения последних N значений
Image movingAverageFilter(const Image& img, int bufferSize) {
    if (bufferSize <= 0 || bufferSize > 256) {
        return img.copy(); // Возвращаем копию, если некорректный размер
    }

    Image result(img.width, img.height);
    
    // Для каждой строки изображения применяем фильтр скользящего среднего
    for (int y = 0; y < img.height; ++y) {
        std::vector<uint8_t> buffer;
        buffer.reserve(bufferSize);
        
        for (int x = 0; x < img.width; ++x) {
            // Добавляем текущее значение в буфер
            buffer.push_back(img.get(x, y));
            
            // Если буфер переполнен, удаляем самый старый элемент
            if (static_cast<int>(buffer.size()) > bufferSize) {
                buffer.erase(buffer.begin());
            }
            
            // Вычисляем среднее значение
            int sum = 0;
            for (uint8_t val : buffer) {
                sum += val;
            }
            
            // Используем оптимизацию для степеней двойки (деление заменяется на сдвиг)
            uint8_t avg;
            if (bufferSize == 2 || bufferSize == 4 || bufferSize == 8 || 
                bufferSize == 16 || bufferSize == 32 || bufferSize == 64 || 
                bufferSize == 128 || bufferSize == 256) {
                // Находим степень двойки
                int shift = 0;
                int temp = bufferSize;
                while (temp > 1) {
                    temp >>= 1;
                    shift++;
                }
                avg = static_cast<uint8_t>(sum >> shift);
            } else {
                avg = static_cast<uint8_t>(sum / static_cast<int>(buffer.size()));
            }
            
            result.set(x, y, avg);
        }
    }
    
    return result;
}

// Медианный фильтр
// filterSize должен быть нечетным (3, 5, 7, ...)
Image medianFilter(const Image& img, int filterSize) {
    if (filterSize <= 0 || filterSize % 2 == 0) {
        return img.copy(); // Возвращаем копию, если некорректный размер
    }

    Image result(img.width, img.height);
    int radius = filterSize / 2;
    
    for (int y = 0; y < img.height; ++y) {
        for (int x = 0; x < img.width; ++x) {
            std::vector<uint8_t> neighbors;
            neighbors.reserve(filterSize * filterSize);
            
            // Собираем значения из окрестности
            for (int dy = -radius; dy <= radius; ++dy) {
                for (int dx = -radius; dx <= radius; ++dx) {
                    int nx = x + dx;
                    int ny = y + dy;
                    
                    // Обработка границ: используем значение пикселя, если выходим за границы
                    if (nx < 0) nx = 0;
                    if (nx >= img.width) nx = img.width - 1;
                    if (ny < 0) ny = 0;
                    if (ny >= img.height) ny = img.height - 1;
                    
                    neighbors.push_back(img.get(nx, ny));
                }
            }
            
            // Сортируем и берем медиану
            std::sort(neighbors.begin(), neighbors.end());
            uint8_t median = neighbors[neighbors.size() / 2];
            
            result.set(x, y, median);
        }
    }
    
    return result;
}

