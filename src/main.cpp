#include <SDL.h>
#include <iostream>
#include <vector>
#include <cmath>
#include "window/Window.h"       // 사용자의 Window 클래스 헤더
#include "rasterizer/Rasterizer.h"         // 질문에서 주어진 템플릿 Rasterizer

// ------------------------------
// 1) 정점 입력 구조체 (VSIn)
// ------------------------------
struct MyVSIn
{
    float x, y, z, w;
};

// ------------------------------
// 속성(Attribute) 구조체
// ------------------------------
struct MyAttrib {
    float r, g, b, a;
    MyAttrib() : r(0), g(0), b(0), a(1) {}
};

// operator* : MyAttrib * float
inline MyAttrib operator*(MyAttrib const& a, float f) {
    MyAttrib out;
    out.r = a.r * f;
    out.g = a.g * f;
    out.b = a.b * f;
    out.a = a.a * f;
    return out;
}

// operator+ : MyAttrib + MyAttrib
inline MyAttrib operator+(MyAttrib const& a, MyAttrib const& b) {
    MyAttrib out;
    out.r = a.r + b.r;
    out.g = a.g + b.g;
    out.b = a.b + b.b;
    out.a = a.a + b.a;
    return out;
}

// ------------------------------
// 정점 셰이더 출력 구조체 (VSOut)
// ------------------------------
struct MyVSOut {
    float x, y, z, w;
    MyAttrib attrib; // 분리된 속성 구조체
};


// ------------------------------
// 3) 픽셀 셰이더 출력 구조 (PSOut)
//    여기서는 최종 픽셀 색상을
//    uint32_t로 표현한다고 가정
// ------------------------------
using MyPSOut = uint32_t;

// ------------------------------
// 4) 메인 함수
// ------------------------------
int main(int argc, char* argv[])
{
    // 4-1) SDL 초기화
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    const int WIDTH = 640;
    const int HEIGHT = 480;

    Window window("SDL Test", WIDTH, HEIGHT);
    Rasterizer<MyVSIn, MyVSOut, MyPSOut> rasterizer;
    MyVSIn vertex_buffer[] = {
        { -0.5f, -0.5f, 0.f, 1.f },  // 왼쪽 아래
        {  0.5f, -0.5f, 0.f, 1.f },  // 오른쪽 아래
        {  0.0f,  0.5f, 0.f, 1.f },  // 위쪽
    };
    uint32_t index_buffer[] = { 0, 2, 1 };

    auto vertexShader = [&](MyVSIn const& in) -> MyVSOut {
        MyVSOut out;
        out.x = in.x;
        out.y = in.y;
        out.z = in.z;
        out.w = in.w;
        out.attrib.r = (in.x + 0.5f);
        out.attrib.g = (in.y + 0.5f);
        out.attrib.b = 1.0f;
        out.attrib.a = 1.0f;
        return out;
    };

    auto pixelShader = [&](MyVSOut const& in) -> MyPSOut {
        uint8_t r = static_cast<uint8_t>(std::fmin(std::fmax(in.attrib.r, 0.0f), 1.0f) * 255);
        uint8_t g = static_cast<uint8_t>(std::fmin(std::fmax(in.attrib.g, 0.0f), 1.0f) * 255);
        uint8_t b = static_cast<uint8_t>(std::fmin(std::fmax(in.attrib.b, 0.0f), 1.0f) * 255);
        uint8_t a = static_cast<uint8_t>(std::fmin(std::fmax(in.attrib.a, 0.0f), 1.0f) * 255);
        return (r << 24) | (g << 16) | (b << 8) | a;
    };
    bool quit = false;
    SDL_Event e;

    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                quit = true;
        }
        uint32_t* pixel_buffer = window.getPixelBuffer();

        rasterizer.setVertexBuffer(vertex_buffer);
        rasterizer.setIndexBuffer(index_buffer);
        rasterizer.setVertexShader(vertexShader);
        rasterizer.setPixelShader(pixelShader);
        rasterizer.setViewport(0, 0, WIDTH, HEIGHT);
        rasterizer.setDepthRange(0.0f, 1.0f);
        rasterizer.setRenderTarget(pixel_buffer);

        rasterizer.clear(0);
        rasterizer.draw(0, 3);
        window.update();
        SDL_Delay(16);
    }
    SDL_Quit();
    return 0;
}
