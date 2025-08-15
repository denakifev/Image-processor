#include "image.h"
#include "../utils/utils.h"

#include <algorithm>
#include <cstdint>
#include <fstream>
#include <stdexcept>
#include <tuple>
#include <vector>

namespace image_processor {

Pixel::Pixel(uint8_t blue, uint8_t green, uint8_t red) {
    constexpr float ColorNormalization = 255.0f;
    this->blue = static_cast<float>(blue) / ColorNormalization;
    this->green = static_cast<float>(green) / ColorNormalization;
    this->red = static_cast<float>(red) / ColorNormalization;
}

uint8_t Pixel::ToByte(float value) {
    constexpr int ColorNormalization = 255;
    return static_cast<uint8_t>(std::clamp(value, 0.0f, 1.0f) * ColorNormalization);
}

std::tuple<uint8_t, uint8_t, uint8_t> Pixel::ToBytes() const {
    uint8_t blue = ToByte(this->blue);
    uint8_t green = ToByte(this->green);
    uint8_t red = ToByte(this->red);
    return std::make_tuple(blue, green, red);
}

Image::Image(const std::string& file) {
    LoadImage(file);
}

int32_t Image::GetWidth() const {
    return dib_header_.bi_width;
}

int32_t Image::GetHeight() const {
    return dib_header_.bi_height;
}

void Image::SetWidth(int32_t width) {
    width = std::min(width, width_);
    for (int i = 0; i < height_; ++i) {
        pixels_[i].erase(pixels_[i].begin() + width, pixels_[i].end());
    }
    dib_header_.bi_width = width;
    width_ = width;
}

void Image::SetHeight(int32_t height) {
    height = std::min(height, height_);
    pixels_.erase(pixels_.begin() + height, pixels_.end());
    dib_header_.bi_height = height;
    height_ = height;
}

Pixel Image::GetPixel(int32_t x, int32_t y) const {
    return pixels_[x][y];
}

Pixel Image::GetPixel(int32_t x, int32_t y) {
    return pixels_[x][y];
}

Pixel Image::At(int32_t x, int32_t y) {
    x = std::clamp(x, 0, height_ - 1);
    y = std::clamp(y, 0, width_ - 1);
    return pixels_[x][y];
}

Pixel Image::At(int32_t x, int32_t y) const {
    x = std::clamp(x, 0, height_ - 1);
    y = std::clamp(y, 0, width_ - 1);
    return pixels_[x][y];
}

void Image::SetPixel(int32_t x, int32_t y, const Pixel& pixel) {
    pixels_[x][y] = pixel;
}

void Image::SetPixels(std::vector<std::vector<Pixel>>&& pixels) {
    pixels_ = std::move(pixels);
    SetHeight(static_cast<int32_t>(pixels_.size()));
    SetWidth(static_cast<int32_t>(pixels_[0].size()));
}

void Image::LoadImage(const std::string& file) {
    std::ifstream file_stream(file, std::ios::binary);
    file_stream.read(reinterpret_cast<char*>(&header_), sizeof(BMPHeader));
    file_stream.read(reinterpret_cast<char*>(&dib_header_), sizeof(DIBHeader));

    // It is considered that if the image does not own the resource then it is an exception situation
    if (header_.bf_type != SupportedBfType || dib_header_.bi_bit_count != SupportedBiBitCount) {
        throw std::runtime_error("Unsupported image format! Only 24-bit BMP images are supported.\n");
    }

    height_ = dib_header_.bi_height;
    width_ = dib_header_.bi_width;

    file_stream.seekg(header_.bf_off_bits, std::ios::beg);

    pixels_.resize(height_, std::vector<Pixel>(width_));

    int32_t padding = utils::CalculatePadding(width_);

    for (int i = height_ - 1; i >= 0; --i) {
        for (int j = 0; j < width_; ++j) {
            uint8_t blue = 0;
            uint8_t green = 0;
            uint8_t red = 0;
            file_stream.read(reinterpret_cast<char*>(&blue), BYTE);
            file_stream.read(reinterpret_cast<char*>(&green), BYTE);
            file_stream.read(reinterpret_cast<char*>(&red), BYTE);
            pixels_[i][j] = Pixel(blue, green, red);
        }
        file_stream.ignore(padding);
    }

    file_stream.close();
}

void Image::Save(const std::string& file) const {
    std::ofstream file_stream(file, std::ios::binary);

    file_stream.write(reinterpret_cast<const char*>(&header_), sizeof(BMPHeader));
    file_stream.write(reinterpret_cast<const char*>(&dib_header_), sizeof(DIBHeader));

    file_stream.seekp(header_.bf_off_bits, std::ios::beg);

    int32_t padding = utils::CalculatePadding(width_);

    for (int i = height_ - 1; i >= 0; --i) {
        for (int j = 0; j < width_; ++j) {
            const auto& [blue, green, red] = pixels_[i][j].ToBytes();
            file_stream.write(reinterpret_cast<const char*>(&blue), BYTE);
            file_stream.write(reinterpret_cast<const char*>(&green), BYTE);
            file_stream.write(reinterpret_cast<const char*>(&red), BYTE);
        }
        file_stream.write(PaddingPixel, padding);
    }

    file_stream.close();
}

}  // namespace image_processor
