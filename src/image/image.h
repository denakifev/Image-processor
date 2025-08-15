#pragma once

#include <cstdint>
#include <string>
#include <tuple>
#include <vector>

namespace image_processor {

#pragma pack(push, 1)
struct BMPHeader {
    uint16_t bf_type;
    uint32_t bf_size;
    uint16_t bf_reserved1;
    uint16_t bf_reserved2;
    uint32_t bf_off_bits;
};

struct DIBHeader {
    uint32_t bi_size;
    int32_t bi_width;
    int32_t bi_height;
    uint16_t bi_planes;
    uint16_t bi_bit_count;
    uint32_t bi_compression;
    uint32_t bi_size_image;
    int32_t bi_x_pels_per_meter;
    int32_t bi_y_pels_per_meter;
    uint32_t bi_clr_used;
    uint32_t bi_clr_important;
};
#pragma pack(pop)

struct Pixel {
    float blue;
    float green;
    float red;

    explicit Pixel(uint8_t blue = 0, uint8_t green = 0, uint8_t red = 0);
    std::tuple<uint8_t, uint8_t, uint8_t> ToBytes() const;
    static uint8_t ToByte(float value);
};

class Image {
protected:
    constexpr static int32_t SupportedBfType = 0x4D42;
    constexpr static int32_t SupportedBiBitCount = 24;
    constexpr static char BYTE = 1;
    constexpr static char PaddingPixel[3] = {'\0', '\0', '\0'};
    BMPHeader header_;
    DIBHeader dib_header_;
    int32_t height_;
    int32_t width_;
    std::vector<std::vector<Pixel>> pixels_;
    void LoadImage(const std::string& file);

public:
    explicit Image(const std::string& file);
    int32_t GetWidth() const;
    int32_t GetHeight() const;
    void SetWidth(int32_t width);
    void SetHeight(int32_t height);
    Pixel GetPixel(int32_t x, int32_t y) const;
    Pixel GetPixel(int32_t x, int32_t y);
    Pixel At(int32_t x, int32_t y);
    Pixel At(int32_t x, int32_t y) const;
    void SetPixel(int32_t x, int32_t y, const Pixel& pixel);
    void Save(const std::string& file) const;
    void SetPixels(std::vector<std::vector<Pixel>>&& pixels);
};

}  // namespace image_processor