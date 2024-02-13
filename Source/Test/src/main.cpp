#include "SurvivantRendering/Core/Vertex.h"
#include "SurvivantRendering/Core/VertexAttributes.h"
#include "SurvivantRendering/Core/Buffers/IndexBuffer.h"
#include "SurvivantRendering/Core/Buffers/VertexBuffer.h"
#include "SurvivantRendering/Resources/Shader.h"

// TODO: Implement relevant parts in rendering lib to get rid of glad/glfw dependencies
#include "SurvivantCore/Debug/Assertion.h"
#include "SurvivantCore/Utility/FileSystem.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

using namespace LibMath;
using namespace SvCore::Utility;
using namespace SvRendering::Core;
using namespace SvRendering::Core::Buffers;
using namespace SvRendering::Resources;

constexpr const char* UNLIT_SHADER_PATH = "assets/shaders/Unlit.glsl";

std::pair<const Vertex*, const uint32_t*> MakeCube()
{
    constexpr float normalLength = 0.57735027f;	// normal length = 1 / sqrt(3) ~= 0.57735027f

    static const Vertex vertices[]
    {
        { { -.5f, -.5f, .5f }, { -normalLength, -normalLength, normalLength }, { 0, 0 } },   // (0) Front-bottom-left
        { { -.5f, .5f, .5f }, { -normalLength, normalLength, normalLength }, { 0, 1 } },     // (1) Front-top-left
        { { -.5f, -.5f, -.5f }, { -normalLength, -normalLength, -normalLength }, { 1, 0 } }, // (2) Back-bottom-left
        { { -.5f, .5f, -.5f }, { -normalLength, normalLength, -normalLength }, { 1, 1 } },   // (3) Back-top-left
        { { .5f, -.5f, .5f }, { normalLength, -normalLength, normalLength }, { 0, 0 } },     // (4) Front-bottom-right
        { { .5f, .5f, .5f }, { normalLength, normalLength, normalLength }, { 0, 1 } },       // (5) Front-top-right
        { { .5f, -.5f, -.5f }, { normalLength, -normalLength, -normalLength }, { 1, 0 } },   // (6) Back-bottom-right
        { { .5f, .5f, -.5f }, { normalLength, normalLength, -normalLength }, { 1, 1 } }      // (7) Back-top-right
    };

    static constexpr uint32_t indices[]
    {
        // Left
        0, 1, 3,
        0, 3, 2,

        // Back
        2, 3, 7,
        2, 7, 6,

        // Right
        6, 7, 5,
        6, 5, 4,

        // Front
        4, 5, 1,
        4, 1, 0,

        // Bottom
        2, 6, 4,
        2, 4, 0,

        // Top
        7, 3, 1,
        7, 1, 5
    };

    return { vertices, indices };
}

GLuint GetDefaultTexture()
{
    static GLuint textureId;

    if (textureId == 0)
    {
        constexpr GLsizei width  = 1;
        constexpr GLsizei height = 1;

        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);

        Vector4 color(1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, color.getArray());

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }

    return textureId;
}

#include "SurvivantTest/EventManager.h"
#include "SurvivantTest/InputManager.h"
#include "SurvivantTest/Window.h"


std::tuple<int, int> AddInputTranslate(char i)
{
	return { i, 10 };
}

std::tuple<int, int> AddMouseTranslate(float i, float j)
{
    return { (int)i, (int)j };
}


int main()
{
    ASSERT(SetWorkingDirectory(GetApplicationDirectory()), "Failed to update working directory");
    SV_LOG("Current working directory: \"%s\"", GetWorkingDirectory().c_str());

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Test", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    // TODO : including glad/gl.h brings up error in Window constructor
    ASSERT(gladLoadGL(glfwGetProcAddress), "Failed to initialize glad");

    App::Window::SetupInputManager(window);

    Shader shader;
    ASSERT(shader.Load(UNLIT_SHADER_PATH), "Failed to load shader at path \"%s\"", UNLIT_SHADER_PATH);
    ASSERT(shader.Init(), "Failed to initialize shader at path \"%s\"", UNLIT_SHADER_PATH);

    const auto [vertices, indices] = MakeCube();

    const VertexBuffer     vbo(vertices, 8);
    const IndexBuffer      ebo(indices, 36); // 6 indices * 6 faces
    const VertexAttributes vao(vbo, ebo);

    shader.Use();

    vao.Bind();
    vbo.Bind();
    ebo.Bind();

    const GLuint textureId = GetDefaultTexture();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);

    const Matrix4 projMat     = perspectiveProjection(90_deg, 4.f / 3.f, .01f, 14.f);
    const Matrix4 viewMat     = lookAt({ 0.f, 1.8f, 1.f }, Vector3::zero(), Vector3::up());
    const Matrix4 viewProjMat = projMat * viewMat;
    shader.SetUniformInt("u_diffuse", 0);

    Degree angle;

    glClearColor(0, 0, 0, 1);

    //event and inputs
    using namespace Core;
    using namespace App;
    using AddEvent = Event<int, int>;

    EventManager& em = EventManager::GetInstance();
    InputManager& im = InputManager::GetInstance();

    AddEvent::EventDelegate printAdd = [](int i, int j) { std::cout << "Add = " << i + j << std::endl; };
    std::shared_ptr<AddEvent> ligEvent = std::make_shared<AddEvent>();
    ligEvent->AddListener(printAdd);
    em.AddEvent<AddEvent>(ligEvent);

    InputManager::KeyboardKeyType   a(EKey::A, EKeyState::RELEASED, EInputModifier::ALT);
    InputManager::KeyboardKeyType   b(EKey::B, EKeyState::PRESSED, EInputModifier());
    InputManager::MouseKeyType      mouse(EMouseButton::MOUSE_1, EMouseButtonState::PRESSED, EInputModifier());
    im.AddInputEventBinding<AddEvent>(a, &AddInputTranslate);
    im.AddInputEventBinding<AddEvent>(b, &AddInputTranslate);
    //mouse, &AddMouseTranslate
    im.AddInputEventBinding<AddEvent>(mouse, &AddMouseTranslate);
    //im.CallInput(b, 'b');

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        angle += .01_deg; // TODO: use delta time

        const Matrix4 modelMat = translation(0.f, .5f, 0.f) * rotation(angle, Vector3::up());
        shader.SetUniformMat4("u_mvp", viewProjMat * modelMat);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();


    //test events and inputs



	//em.AddEvent<HelloWorldEvent>(hwEvent);
	//em.Invoke<HelloWorldEvent>();

	//ligEvent->Invoke(8, 9);
	//em.Invoke<AddEvent>(9, 10);

	//InputManager::KeyboardKeyType a(EKey::A, EKeyState::PRESSED, EInputModifier());
	//InputManager::KeyCallback aF = [](int i) { std::cout << "Test A: " << i << std::endl; };

	//im.AddInputBinding(a, aF);
	//im.CallInput(a, 'a');



    return 0;
}

