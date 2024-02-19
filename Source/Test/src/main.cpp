#include "SurvivantTest/EventManager.h"
#include "SurvivantTest/InputManager.h"

#include <SurvivantCore/Debug/Assertion.h>
#include <SurvivantCore/Utility/FileSystem.h>
#include <SurvivantCore/Utility/Timer.h>

#include <SurvivantRendering/Core/Camera.h>
#include <SurvivantRendering/Core/Color.h>
#include <SurvivantRendering/Core/Vertex.h>
#include <SurvivantRendering/Core/VertexAttributes.h>
#include <SurvivantRendering/Core/Buffers/IndexBuffer.h>
#include <SurvivantRendering/Core/Buffers/VertexBuffer.h>
#include <SurvivantRendering/Geometry/BoundingBox.h>
#include <SurvivantRendering/Resources/Shader.h>
#include "SurvivantRendering/Resources/Model.h"
#include "SurvivantRendering/Resources/Texture.h"
#include <Transform.h>

// TODO: Implement relevant parts in corresponding libs to get rid of glad dependency
#include <glad/gl.h>

#include "SurvivantTest/Window.h"

using namespace LibMath;
using namespace SvCore::Utility;
using namespace SvRendering::Core;
using namespace SvRendering::Core::Buffers;
using namespace SvRendering::Geometry;
using namespace SvRendering::Resources;

constexpr const char* UNLIT_SHADER_PATH  = "assets/shaders/Unlit.glsl";
constexpr float       CAM_MOVE_SPEED     = 3.f;
constexpr Radian      CAM_ROTATION_SPEED = 90_deg;

const Texture& GetTexture()
{
    static Texture texture;
    static bool isLoaded = false;

    if (!isLoaded)
    {
        ASSERT(texture.Load("assets/textures/grid.png"));
        ASSERT(texture.Init());

        texture.SetFiltering(ETextureFilter::Nearest, ETextureFilter::Nearest);
        texture.SetWrapping(ETextureWrapMode::Repeat, ETextureWrapMode::Repeat);

        isLoaded = true;
}

    return texture;
}

std::tuple<int, int> AddInputTranslate(char i)
{
    return { i, 10 };
}

std::tuple<int, int> AddMouseTranslate(float i, float j)
{
    return { (int)i, (int)j };
}

BoundingBox GetCubeBoundingBox(const Matrix4& transform)
{
    BoundingBox boundingBox
    {
        { -.5f, -.5f, -.5f },
        { .5f, .5f, .5f }
    };

    Vector3 corners[8]
    {
        boundingBox.m_min,
        { boundingBox.m_min.m_x, boundingBox.m_max.m_y, boundingBox.m_min.m_z },
        { boundingBox.m_min.m_x, boundingBox.m_min.m_y, boundingBox.m_max.m_z },
        { boundingBox.m_min.m_x, boundingBox.m_max.m_y, boundingBox.m_max.m_z },
        { boundingBox.m_max.m_x, boundingBox.m_min.m_y, boundingBox.m_max.m_z },
        { boundingBox.m_max.m_x, boundingBox.m_max.m_y, boundingBox.m_min.m_z },
        { boundingBox.m_max.m_x, boundingBox.m_min.m_y, boundingBox.m_min.m_z },
        boundingBox.m_max
    };

    boundingBox.m_min = Vector3(std::numeric_limits<float>::max());
    boundingBox.m_max = Vector3(std::numeric_limits<float>::lowest());

    for (Vector3& corner : corners)
    {
        corner            = (transform * Vector4(corner, 1.f)).xyz();
        boundingBox.m_min = min(boundingBox.m_min, corner);
        boundingBox.m_max = max(boundingBox.m_max, corner);
    }

    return boundingBox;
}

int main()
{
    SvCore::Debug::Logger::GetInstance().SetFile("debug.log");

    ASSERT(SetWorkingDirectory(GetApplicationDirectory()), "Failed to update working directory");
    SV_LOG("Current working directory: \"%s\"", GetWorkingDirectory().c_str());

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Test", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    ASSERT(gladLoadGL(glfwGetProcAddress), "Failed to initialize glad");

    glEnable(GL_DEPTH_TEST);
    App::Window::SetupInputManager(window);

    Model model;

    ASSERT(model.Load("assets/models/cube.obj"), "Failed to load model");
    ASSERT(model.Init(), "Failed to initialize model");

    const Texture& texture = GetTexture();
    texture.Bind();

    Shader unlitShader;
    ASSERT(unlitShader.Load(UNLIT_SHADER_PATH), "Failed to load shader at path \"%s\"", UNLIT_SHADER_PATH);
    ASSERT(unlitShader.Init(), "Failed to initialize shader at path \"%s\"", UNLIT_SHADER_PATH);

    unlitShader.Use();
    unlitShader.SetUniformInt("u_diffuse", 0);

    const Matrix4 projMat = perspectiveProjection(90_deg, 4.f / 3.f, .01f, 14.f);

    Vector3   camPos(0.f, 1.8f, 2.f);
    Transform camTransform(camPos, Quaternion::identity(), Vector3::one());

    const Vector3 testPos      = camPos + Vector3::front();
    const Matrix4 testModelMat = translation(testPos) * scaling(1.5f, .5f, .1f);

    Camera cam(projMat);

    Degree angle;

    cam.SetClearColor(Color::gray);

    Timer timer;

    //event and inputs
    using namespace Core;
    using namespace App;
    using AddEvent = Event<int, int>;

    EventManager& em = EventManager::GetInstance();
    InputManager& im = InputManager::GetInstance();

    AddEvent::EventDelegate printAdd = [](int i, int j)
    {
        std::cout << "Add = " << i + j << std::endl;
    };

    std::shared_ptr<AddEvent> ligEvent = std::make_shared<AddEvent>();
    ligEvent->AddListener(printAdd);
    em.AddEvent<AddEvent>(ligEvent);

    InputManager::KeyboardKeyType a(EKey::A, EKeyState::RELEASED, EInputModifier::ALT);
    InputManager::KeyboardKeyType b(EKey::B, EKeyState::PRESSED, EInputModifier());
    InputManager::MouseKeyType    mouse(EMouseButton::MOUSE_1, EMouseButtonState::PRESSED, EInputModifier());

    im.AddInputEventBinding<AddEvent>(a, &AddInputTranslate);
    im.AddInputEventBinding<AddEvent>(b, &AddInputTranslate);
    //mouse, &AddMouseTranslate
    im.AddInputEventBinding<AddEvent>(mouse, &AddMouseTranslate);
    //im.CallInput(b, 'b');

    Vector2 moveInput, rotateInput;

    im.AddInputBinding({ EKey::W, EKeyState::PRESSED, EInputModifier() }, [&moveInput](const char)
    {
        ++moveInput.m_y;
    });

    im.AddInputBinding({ EKey::W, EKeyState::RELEASED, EInputModifier() }, [&moveInput](const char)
    {
        --moveInput.m_y;
    });

    im.AddInputBinding({ EKey::S, EKeyState::PRESSED, EInputModifier() }, [&moveInput](const char)
    {
        --moveInput.m_y;
    });

    im.AddInputBinding({ EKey::S, EKeyState::RELEASED, EInputModifier() }, [&moveInput](const char)
    {
        ++moveInput.m_y;
    });

    im.AddInputBinding({ EKey::A, EKeyState::PRESSED, EInputModifier() }, [&moveInput](const char)
    {
        --moveInput.m_x;
    });

    im.AddInputBinding({ EKey::A, EKeyState::RELEASED, EInputModifier() }, [&moveInput](const char)
    {
        ++moveInput.m_x;
    });

    im.AddInputBinding({ EKey::D, EKeyState::PRESSED, EInputModifier() }, [&moveInput](const char)
    {
        ++moveInput.m_x;
    });

    im.AddInputBinding({ EKey::D, EKeyState::RELEASED, EInputModifier() }, [&moveInput](const char)
    {
        --moveInput.m_x;
    });

    im.AddInputBinding({ EKey::UP, EKeyState::PRESSED, EInputModifier() }, [&rotateInput](const char)
    {
        ++rotateInput.m_y;
    });

    im.AddInputBinding({ EKey::UP, EKeyState::RELEASED, EInputModifier() }, [&rotateInput](const char)
    {
        --rotateInput.m_y;
    });

    im.AddInputBinding({ EKey::DOWN, EKeyState::PRESSED, EInputModifier() }, [&rotateInput](const char)
    {
        --rotateInput.m_y;
    });

    im.AddInputBinding({ EKey::DOWN, EKeyState::RELEASED, EInputModifier() }, [&rotateInput](const char)
    {
        ++rotateInput.m_y;
    });

    im.AddInputBinding({ EKey::LEFT, EKeyState::PRESSED, EInputModifier() }, [&rotateInput](const char)
    {
        --rotateInput.m_x;
    });

    im.AddInputBinding({ EKey::LEFT, EKeyState::RELEASED, EInputModifier() }, [&rotateInput](const char)
    {
        ++rotateInput.m_x;
    });

    im.AddInputBinding({ EKey::RIGHT, EKeyState::PRESSED, EInputModifier() }, [&rotateInput](const char)
    {
        ++rotateInput.m_x;
    });

    im.AddInputBinding({ EKey::RIGHT, EKeyState::RELEASED, EInputModifier() }, [&rotateInput](const char)
    {
        --rotateInput.m_x;
    });

    im.AddInputBinding({ EKey::R, EKeyState::RELEASED, {} }, [&camTransform, &camPos](const char)
    {
        camTransform.setAll(camPos, Quaternion::identity(), Vector3::one());
    });

    im.AddInputBinding({ EKey::ESCAPE, EKeyState::RELEASED, {} }, [&window](const char)
    {
        glfwSetWindowShouldClose(window, true);
    });

    while (!glfwWindowShouldClose(window))
    {
        timer.tick();
        glfwPollEvents();

        angle += 20_deg * timer.getDeltaTime();

        const Matrix4 modelRot  = rotation(angle, Vector3::up());
        const Matrix4 modelMat1 = translation(-1.f, .5f, 0.f);
        const Matrix4 modelMat2 = translation(1.f, .5f, 0.f) * modelRot;

        Vector3    newPos = camTransform.getPosition();
        Quaternion newRot = camTransform.getRotation();

        if (moveInput.magnitudeSquared() > 0.f)
        {
            const Vector3 moveDir = moveInput.m_x * camTransform.worldRight() + moveInput.m_y * camTransform.worldBack();
            newPos += moveDir.normalized() * (CAM_MOVE_SPEED * timer.getDeltaTime());
        }

        if (rotateInput.magnitudeSquared() > 0.f)
        {
            TVector3<Radian> angles = newRot.toEuler(ERotationOrder::YXZ);

            angles.m_y -= CAM_ROTATION_SPEED * rotateInput.m_x * timer.getDeltaTime();
            angles.m_x += CAM_ROTATION_SPEED * rotateInput.m_y * timer.getDeltaTime();
            angles.m_x = Degree(clamp(angles.m_x.degree(true), -85.f, 85.f));

            newRot = Quaternion::fromEuler(angles, ERotationOrder::YXZ);
        }

        camTransform.setAll(newPos, newRot, Vector3::one());

        cam.SetView(camTransform.getWorldMatrix().inverse());
        cam.Clear();

        const Frustum camFrustum     = cam.GetFrustum();
        const Matrix4 viewProjection = cam.GetViewProjection();

        unlitShader.Use();
        unlitShader.SetUniformMat4("u_mvp", viewProjection * modelMat1);
        unlitShader.SetUniformVec4("u_tint", Color::white);
        model.Bind();
        glDrawElements(GL_TRIANGLES, model.GetIndexCount(), GL_UNSIGNED_INT, nullptr);

        unlitShader.SetUniformMat4("u_mvp", viewProjection * modelMat2);
        unlitShader.SetUniformVec4("u_tint", Color::red);
        glDrawElements(GL_TRIANGLES, model.GetIndexCount(), GL_UNSIGNED_INT, nullptr);

        if (camFrustum.Intersects(GetCubeBoundingBox(testModelMat)))
        {
            unlitShader.SetUniformMat4("u_mvp", viewProjection * testModelMat);
            unlitShader.SetUniformVec4("u_tint", Color::yellow);
            glDrawElements(GL_TRIANGLES, model.GetIndexCount(), GL_UNSIGNED_INT, nullptr);
        }

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
