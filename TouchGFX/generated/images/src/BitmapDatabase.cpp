// 4.15.0 0x47035510
// Generated by imageconverter. Please, do not edit!

#include <BitmapDatabase.hpp>
#include <touchgfx/Bitmap.hpp>

extern const unsigned char image_cisynth_background[]; // BITMAP_CISYNTH_BACKGROUND_ID = 0, Size: 480x272 pixels
extern const unsigned char image_dark_buttons_square_icon_button[]; // BITMAP_DARK_BUTTONS_SQUARE_ICON_BUTTON_ID = 1, Size: 60x60 pixels
extern const unsigned char image_dark_buttons_square_icon_button_pressed[]; // BITMAP_DARK_BUTTONS_SQUARE_ICON_BUTTON_PRESSED_ID = 2, Size: 60x60 pixels

const touchgfx::Bitmap::BitmapData bitmap_database[] =
{
    { image_cisynth_background, 0, 480, 272, 0, 0, 480, (uint8_t)(touchgfx::Bitmap::RGB565) >> 3, 272, (uint8_t)(touchgfx::Bitmap::RGB565) & 0x7 },
    { image_dark_buttons_square_icon_button, 0, 60, 60, 5, 4, 50, (uint8_t)(touchgfx::Bitmap::ARGB8888) >> 3, 50, (uint8_t)(touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_dark_buttons_square_icon_button_pressed, 0, 60, 60, 5, 4, 50, (uint8_t)(touchgfx::Bitmap::ARGB8888) >> 3, 50, (uint8_t)(touchgfx::Bitmap::ARGB8888) & 0x7 }
};

namespace BitmapDatabase
{
const touchgfx::Bitmap::BitmapData* getInstance()
{
    return bitmap_database;
}

uint16_t getInstanceSize()
{
    return (uint16_t)(sizeof(bitmap_database) / sizeof(touchgfx::Bitmap::BitmapData));
}
}
