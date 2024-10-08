#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <raylib.h>
#include <time.h>
#include <math.h>

const int screenWidth = 800;
const int screenHeight = 800;

typedef struct complexs {
    double r;
    double i;
}complex;

float mod(complex z){
    float mod = sqrt(z.r*z.r+z.i*z.i);
    return mod ;
}

complex add(complex x, complex y){
    complex sum ;
    sum.r = x.r + y.r ;
    sum.i = x.i + y.i ;
    return sum ;
}   

complex sub(complex x, complex y){
    complex diff ;
    diff.r = x.r - y.r ;
    diff.i = x.i - y.i ;
    return diff ;
}

complex prod(complex x, complex y){
    complex prod ;
    prod.r = x.r*y.r - x.i*y.i ;
    prod.i = x.r*y.i + x.i*y.r ;
    return prod ;
}

complex sqr(complex z){
    return prod(z,z) ;
}

complex scale_pixel_to_mandelbrot_radius(int x, int y){
    complex z ;
    z.r = ((0.47+2.00)/(screenWidth))*x - 2.0 ;
    z.i = ((1.12+1.12)/(screenHeight))*y - 1.12 ;
    return z ;
}

Color does_dvg(int x, int y){
    Color dvg = WHITE;
    complex z;
    z.i = 0;
    z.r = 0;
    complex c = scale_pixel_to_mandelbrot_radius(x,y);
    for(int i = 0; i<=2000; i++){
        z = add(sqr(z),c);
        if(mod(z)>2){
            dvg = BLACK;
            break;
        }
    }
    return dvg;
}

void draw_mandelbrot_set(){
    for(int x = 0; x <= screenWidth; x++){
        for(int y = 0; y <= screenHeight; y++){
            Color c = does_dvg(x,y);
            DrawPixel(x,y,c);
        }
    }
}

Color getRandomColor(){
    int n = rand() % 3;
    if (n==1){return BLUE;}
    else if(n==2){return RED;}
    else {return GREEN;}
};

void redGradient(){
    for (int i = 0; i <= screenWidth; i += 20) {
        Color c = {(200.0 / screenWidth)* i, 100, 73, 255};
        for (int j = 0; j < 20; j++) {
            DrawLine(i + j, 0, i + j, screenHeight, c);
        }
    }
}

void drawImaginaryAxis(){
    DrawLine(screenWidth/2, 0, screenWidth/2,screenHeight,GRAY);
}

void drawRealAxis(){
    DrawLine(0, screenHeight/2, screenWidth, screenHeight/2, GRAY);
}

int main()
{

    InitWindow(screenWidth, screenHeight, "raylib");
    while(!WindowShouldClose()){
        BeginDrawing();
        draw_mandelbrot_set();
        drawImaginaryAxis();
        drawRealAxis();
        EndDrawing(); 
    }
    CloseWindow();
}