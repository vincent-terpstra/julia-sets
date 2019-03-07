/**
 * Julia.cpp
 * Vincent Terpstra
 * Feb 18 / 2019
 * Functions to display a Mandlebrot set
 */

#include <iostream>
#include <math.h>
#include "Bitmap.h"

#define MAXCYCLES 1000
#define ITER 1
#define PI 3.14159

void calcJulia(int* array, int width, int height, float jR, float jI);
void createBMP(int* array, int width, int height);

int main(int size, const char ** args) {
    int height = (size > 1) ? atoi(args[1]) : 1000;
    int width = height / 2 * 3;

    int * array = new int[height * width];
    float jI = -0.4f;
    float jR =  0.6f;
    float angle = 2.0f / ITER * PI;
    float cosA = cos(angle);
    float sinA = sin(angle);
    for(int i = 0; i < ITER; i++){
        calcJulia(array, width, height, jI, jR);
        createBMP(array, width, height);

        //rotate the Julia point
        float tmp = jI;
        jI = cosA * jI - sinA * jR;
        jR = cosA * jR + sinA * tmp;
    }

    delete[] array;
    return 0;
}
/**
 * calcDepth
 *      finds the escape value of the Julia set
 *      inputs sR, sI: starting position on the map
 *          jR, jI: values of the julia set
 *      exits when |s| > 2 or reached MAXCYCLES
 *      return the 
 */
int calcDepth(float sR, float sI, const float jR, const float jI){
    int cycle = 0;
    while(sR * sR + sI * sI <= 4 && ++cycle < MAXCYCLES){
        // s(next) = s * s + j
        float tmp = sR;
        sR = sR * sR - sI * sI + jR;
        sI = 2 * tmp * sI + jI;
    }
    return cycle;
}

/**
 * calcJulia
 *  Function to calculate the values from (-1.5, 1.5),(-1, 1) in the Julia set
 *      saves the values onto the array
 */
void calcJulia(int * array, int width, int height, const float jR, const float jI){
    float delta = 2 / (float)height;
    float x, y = -1;
    for(int i = 0; i < height; i++){
        x = -1.5f;
        for(int j = 0; j < width; j++){
            *array++ = calcDepth(x, y, jR, jI);
            x+=delta;
        }
        y += delta;
    }
}

struct Pix {
    float val;
    int r, g, b;
    Pix(float val, int r, int g, int b) : 
        val(val), r(r), g(g), b(b) {}
};

bool lerp(float clr, Pix& first, Pix& second, Bitmap & map);

/**
 * createBMP
 *  maps the values in the array to a .bmp file
 *  linear interpolates between color values
 */
void createBMP(int * array, int width, int height){
    static int idx = 0;
    char name[] = "julia000.bmp";
        name[5] = (idx / 100) + '0';
        name[6] = ((idx / 10) % 10) + '0';
        name[7] = (idx % 10) + '0';
    Bitmap map (name, width, height);
    idx++;
    const int pix = width * height;
    struct Pix 
        clr0(0, 20, 20, 30),
        clr1(10, 20, 10, 100),
        clr2(180, 20, 170, 205), 
        clr3(MAXCYCLES, 0, 0, 0);
    const int * pMax = array + width * height;
    while(array < pMax){
        float clr = *array++;
        bool draw = 
            lerp(clr, clr0, clr1, map) || 
            lerp(clr, clr1, clr2, map) || 
            lerp(clr, clr2, clr3, map);
    }
}

/**
 * Function to linearly interpolate color values and draw to the Bitmap
 */
bool lerp(float clr, Pix& first, Pix& second, Bitmap & map){
    if(clr <= second.val){
        float diff = (clr - first.val) / (second.val - first.val);
        map << first.b + diff * (second.b - first.b);
        map << first.g + diff * (second.g - first.g);
        map << first.r + diff * (second.r - first.r);
        return true;
    }
    return false;
}
