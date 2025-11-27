#include "image.h"
#include <fstream>
#include <iostream>
#include <algorithm>

// BMP заголовки
#pragma pack(push, 1)
struct BMPHeader {
    uint16_t signature;      // "BM"
    uint32_t fileSize;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t dataOffset;
};

struct BMPInfoHeader {
    uint32_t headerSize;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bitsPerPixel;
    uint32_t compression;
    uint32_t imageSize;
    int32_t xPixelsPerM;
    int32_t yPixelsPerM;
    uint32_t colorsUsed;
    uint32_t colorsImportant;
};
#pragma pack(pop)

uint8_t Image::get(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return 0;
    }
    return data[y * width + x];
}

void Image::set(int x, int y, uint8_t value) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return;
    }
    data[y * width + x] = value;
}

Image Image::copy() const {
    Image result(width, height);
    result.data = data;
    return result;
}

bool Image::loadFromBMP(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return false;
    }

    BMPHeader header;
    file.read(reinterpret_cast<char*>(&header), sizeof(header));
    
    if (header.signature != 0x4D42) { // "BM"
        std::cerr << "Error: Not a valid BMP file" << std::endl;
        return false;
    }

    BMPInfoHeader infoHeader;
    file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

    if (infoHeader.bitsPerPixel != 24 && infoHeader.bitsPerPixel != 8) {
        std::cerr << "Error: Unsupported BMP format (only 8-bit and 24-bit supported)" << std::endl;
        return false;
    }

    width = infoHeader.width;
    height = std::abs(infoHeader.height); // Может быть отрицательным (top-down)
    bool topDown = infoHeader.height < 0;

    // Переход к данным изображения
    file.seekg(header.dataOffset, std::ios::beg);

    if (infoHeader.bitsPerPixel == 24) {
        // 24-bit BMP (RGB)
        data.resize(width * height);
        int rowSize = ((width * 3 + 3) / 4) * 4; // Выравнивание по 4 байта
        std::vector<uint8_t> row(rowSize);

        for (int y = 0; y < height; ++y) {
            file.read(reinterpret_cast<char*>(row.data()), rowSize);
            int actualY = topDown ? y : (height - 1 - y);
            
            for (int x = 0; x < width; ++x) {
                // BMP хранит в формате BGR, конвертируем в grayscale
                uint8_t b = row[x * 3];
                uint8_t g = row[x * 3 + 1];
                uint8_t r = row[x * 3 + 2];
                // Формула для преобразования RGB в grayscale
                uint8_t gray = static_cast<uint8_t>(0.299 * r + 0.587 * g + 0.114 * b);
                set(x, actualY, gray);
            }
        }
    } else if (infoHeader.bitsPerPixel == 8) {
        // 8-bit BMP (grayscale с палитрой)
        // Пропускаем палитру (обычно 256 цветов * 4 байта)
        file.seekg(header.dataOffset, std::ios::beg);
        
        data.resize(width * height);
        int rowSize = ((width + 3) / 4) * 4; // Выравнивание по 4 байта
        std::vector<uint8_t> row(rowSize);

        for (int y = 0; y < height; ++y) {
            file.read(reinterpret_cast<char*>(row.data()), rowSize);
            int actualY = topDown ? y : (height - 1 - y);
            
            for (int x = 0; x < width; ++x) {
                set(x, actualY, row[x]);
            }
        }
    }

    file.close();
    return true;
}

bool Image::saveToBMP(const std::string& filename) const {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot create file " << filename << std::endl;
        return false;
    }

    BMPHeader header;
    header.signature = 0x4D42; // "BM"
    header.reserved1 = 0;
    header.reserved2 = 0;
    header.dataOffset = sizeof(BMPHeader) + sizeof(BMPInfoHeader) + 256 * 4; // + палитра

    BMPInfoHeader infoHeader;
    infoHeader.headerSize = sizeof(BMPInfoHeader);
    infoHeader.width = width;
    infoHeader.height = height;
    infoHeader.planes = 1;
    infoHeader.bitsPerPixel = 8;
    infoHeader.compression = 0;
    int rowSize = ((width + 3) / 4) * 4;
    infoHeader.imageSize = rowSize * height;
    infoHeader.xPixelsPerM = 0;
    infoHeader.yPixelsPerM = 0;
    infoHeader.colorsUsed = 256;
    infoHeader.colorsImportant = 256;

    header.fileSize = header.dataOffset + infoHeader.imageSize;

    // Записываем заголовки
    file.write(reinterpret_cast<const char*>(&header), sizeof(header));
    file.write(reinterpret_cast<const char*>(&infoHeader), sizeof(infoHeader));

    // Записываем палитру (grayscale)
    for (int i = 0; i < 256; ++i) {
        uint8_t palette[4] = {static_cast<uint8_t>(i), static_cast<uint8_t>(i), static_cast<uint8_t>(i), 0};
        file.write(reinterpret_cast<const char*>(palette), 4);
    }

    // Записываем данные изображения (снизу вверх для BMP)
    std::vector<uint8_t> row(rowSize, 0);

    for (int y = height - 1; y >= 0; --y) {
        for (int x = 0; x < width; ++x) {
            row[x] = get(x, y);
        }
        file.write(reinterpret_cast<const char*>(row.data()), rowSize);
    }

    file.close();
    return true;
}

