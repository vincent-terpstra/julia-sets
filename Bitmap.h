#pragma once

class Bitmap {
    unsigned char * image;
    
    const char * filename;
    int idx = 0;
    public:
        const int height;
        const int width;
        Bitmap(const char * filename, const int height, const int width);

        ~Bitmap();

        void operator<<(float input);
};