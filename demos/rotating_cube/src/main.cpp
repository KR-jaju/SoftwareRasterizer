#include <SDL.h>
#include <iostream>
#include <vector>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Rasterizer.h"
#include "Window.h"

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

// 연산자 오버로드 (질문 예시)
inline MyAttrib operator*(MyAttrib const& a, float f) {
    MyAttrib out;
    out.r = a.r * f;
    out.g = a.g * f;
    out.b = a.b * f;
    out.a = a.a * f;
    return out;
}

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
    MyAttrib attrib;
};

// ------------------------------
// 픽셀 셰이더 출력 구조 (PSOut)
// ------------------------------
using MyPSOut = uint32_t;

// 메인 함수
int main(int argc, char* argv[])
{
    // 1) SDL 초기화
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // 창 사이즈
    const int WIDTH = 640;
    const int HEIGHT = 480;

    // 창 및 소프트웨어 렌더링용 버퍼 준비
    Window window("Rotating Cube with GLM", WIDTH, HEIGHT);
    Rasterizer<MyVSIn, MyVSOut, MyPSOut> rasterizer;

    // 큐브를 -0.5 ~ +0.5 범위로 구성 (정점 8개)
    //  (x, y, z, w)
    MyVSIn vertex_buffer[] = {
        {-0.5f, -0.5f, -0.5f, 1.f}, // 0: 좌하앞
        { 0.5f, -0.5f, -0.5f, 1.f}, // 1: 우하앞
        { 0.5f,  0.5f, -0.5f, 1.f}, // 2: 우상앞
        {-0.5f,  0.5f, -0.5f, 1.f}, // 3: 좌상앞
        {-0.5f, -0.5f,  0.5f, 1.f}, // 4: 좌하뒤
        { 0.5f, -0.5f,  0.5f, 1.f}, // 5: 우하뒤
        { 0.5f,  0.5f,  0.5f, 1.f}, // 6: 우상뒤
        {-0.5f,  0.5f,  0.5f, 1.f}, // 7: 좌상뒤
    };

    // 큐브의 12개 삼각형(총 36 인덱스)
    // 한 면당 2개의 삼각형, 6면 * 2 = 12개의 삼각형
    uint32_t index_buffer[] = {
        // 앞면
        0, 1, 2,
        0, 2, 3,
        // 뒷면
        5, 4, 7,
        5, 7, 6,
        // 왼면
        4, 0, 3,
        4, 3, 7,
        // 오른면
        1, 5, 6,
        1, 6, 2,
        // 윗면
        3, 2, 6,
        3, 6, 7,
        // 아랫면
        4, 5, 1,
        4, 1, 0
    };

    // ----------------------------------
    // MVP 계산을 위해 glm::mat4를 사용
    // 각 프레임마다 업데이트할 수 있게 캡쳐방식으로
    // 람다(버텍스 셰이더) 밖에서 정의
    // ----------------------------------
    float angle = 0.0f; // 회전 각도
    glm::mat4 model(1.0f);
    glm::mat4 view = glm::lookAt(
        glm::vec3(0.0f, 0.0f, 3.0f),  // 카메라 위치
        glm::vec3(0.0f, 0.0f, 0.0f),  // 바라보는 지점
        glm::vec3(0.0f, 1.0f, 0.0f)   // 상단 방향
    );
    glm::mat4 projection = glm::perspective(
        glm::radians(45.0f),
        (float)WIDTH / (float)HEIGHT,
        0.1f,
        10.0f
    );

    // 2) Vertex Shader
    //    - 각 프레임마다 회전각도에 따라 모델행렬이 변하므로
    //      main 루프 안에서 model, mvp를 업데이트한 뒤
    //      람다 함수 내부에서 해당 값들을 사용
    auto vertexShader = [&](MyVSIn const& in) -> MyVSOut {
        MyVSOut out;

        // 입력 위치
        glm::vec4 pos(in.x, in.y, in.z, in.w);

        // MVP 변환
        glm::vec4 clipPos = projection * view * model * pos;

        // 결과를 VSOut에 저장
        out.x = clipPos.x;
        out.y = clipPos.y;
        out.z = clipPos.z;
        out.w = clipPos.w;

        float r = (in.x + 0.5f);
        float g = (in.y + 0.5f);
        float b = (in.z + 0.5f);
        out.attrib.r = r;
        out.attrib.g = g;
        out.attrib.b = b;
        out.attrib.a = 1.0f;

        return out;
    };

    auto pixelShader = [&](MyVSOut const& in) -> MyPSOut {
        float rf = std::fmin(std::fmax(in.attrib.r, 0.0f), 1.0f);
        float gf = std::fmin(std::fmax(in.attrib.g, 0.0f), 1.0f);
        float bf = std::fmin(std::fmax(in.attrib.b, 0.0f), 1.0f);
        float af = std::fmin(std::fmax(in.attrib.a, 0.0f), 1.0f);

        uint8_t r = static_cast<uint8_t>(rf * 255);
        uint8_t g = static_cast<uint8_t>(gf * 255);
        uint8_t b = static_cast<uint8_t>(bf * 255);
        uint8_t a = static_cast<uint8_t>(af * 255);

        return (r << 24) | (g << 16) | (b << 8) | a;
    };

    bool quit = false;
    SDL_Event e;

    while (!quit)
    {
        // 이벤트 처리
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                quit = true;
        }

        angle += 0.01f;
        model = glm::rotate(glm::mat4(1.0f), angle * 0.6f, glm::vec3(1, 0, 0));
        model = glm::rotate(model, angle, glm::vec3(0, 1, 0));
        model = glm::rotate(model, angle * 0.5f, glm::vec3(0, 0, 1));

        uint32_t* pixel_buffer = window.getPixelBuffer();
        rasterizer.setVertexBuffer(vertex_buffer);
        rasterizer.setIndexBuffer(index_buffer);
        rasterizer.setVertexShader(vertexShader);
        rasterizer.setPixelShader(pixelShader);
        rasterizer.setViewport(0, 0, WIDTH, HEIGHT);
        rasterizer.setDepthRange(0.0f, 1.0f);
        rasterizer.setRenderTarget(pixel_buffer);

        rasterizer.clear(0);
        rasterizer.draw(0, 36);
        window.update();
        SDL_Delay(16);
    }

    // 정리
    SDL_Quit();
    return 0;
}
