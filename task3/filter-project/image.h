#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <string>
#include <cstdint>

// Структура для представления изображения в градациях серого
struct Image {
    int width;
    int height;
    std::vector<uint8_t> data; // данные изображения (0-255)
    
    Image() : width(0), height(0) {}
    Image(int w, int h) : width(w), height(h), data(w * h, 0) {}
    
    // Получить значение пикселя
    uint8_t get(int x, int y) const;
    
    // Установить значение пикселя
    void set(int x, int y, uint8_t value);
    
    // Загрузить изображение из BMP файла
    bool loadFromBMP(const std::string& filename);
    
    // Сохранить изображение в BMP файл
    bool saveToBMP(const std::string& filename) const;
    
    // Создать копию изображения
    Image copy() const;
};

#endif // IMAGE_H

