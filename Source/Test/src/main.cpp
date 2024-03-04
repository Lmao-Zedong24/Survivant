#include "SurvivantTest/EventManager.h"
#include "SurvivantTest/InputManager.h"
#include "SurvivantTest/Window.h"

#include <SurvivantCore/Debug/Assertion.h>
#include <SurvivantCore/Utility/FileSystem.h>
#include <SurvivantCore/Utility/Timer.h>

#include <SurvivantRendering/Core/Camera.h>
#include <SurvivantRendering/Core/Color.h>
#include <SurvivantRendering/Resources/Model.h>
#include <SurvivantRendering/RHI/IRenderAPI.h>
#include <SurvivantRendering/RHI/IShader.h>
#include <SurvivantRendering/RHI/ITexture.h>

#include <Transform.h>

using namespace LibMath;
using namespace SvCore::Utility;
using namespace SvRendering::Core;
using namespace SvRendering::Core::Buffers;
using namespace SvRendering::Enums;
using namespace SvRendering::Geometry;
using namespace SvRendering::Resources;
using namespace SvRendering::RHI;

constexpr const char* UNLIT_SHADER_PATH  = "assets/shaders/Unlit.glsl";
constexpr float       CAM_MOVE_SPEED     = 3.f;
constexpr Radian      CAM_ROTATION_SPEED = 90_deg;

ITexture& GetTexture()
{
    static std::shared_ptr<ITexture> texture  = ITexture::Create();
    static bool                      isLoaded = false;

    if (!isLoaded)
    {
        ASSERT(texture->Load("assets/textures/grid.png"));
        ASSERT(texture->Init());

        texture->SetFilters(ETextureFilter::NEAREST, ETextureFilter::NEAREST);
        texture->SetWrapModes(ETextureWrapMode::REPEAT, ETextureWrapMode::REPEAT);

        isLoaded = true;
    }

    return *texture;
}

std::tuple<int, int> AddInputTranslate(char i)
{
    return { i, 10 };
}

std::tuple<int, int> AddMouseTranslate(float i, float j)
{
    return { (int)i, (int)j };
}

void DrawModel(const Model& p_model)
{
    for (size_t i = 0; i < p_model.GetMeshCount(); ++i)
    {
        const Mesh& mesh = p_model.GetMesh(i);

        mesh.Bind();
        IRenderAPI::GetCurrent().DrawElements(EPrimitiveType::TRIANGLES, mesh.GetIndexCount());
    }
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

    IRenderAPI& renderAPI = IRenderAPI::SetCurrent(EGraphicsAPI::OPENGL);
    renderAPI.Init(true)
             .SetCapability(ERenderingCapability::DEPTH_TEST, true)
             .SetCullFace(ECullFace::BACK);

    App::Window::SetupInputManager(window);

    Model model;

    ASSERT(model.Load("assets/models/cube.obj"), "Failed to load model");
    ASSERT(model.Init(), "Failed to initialize model");

    std::shared_ptr<IShader> unlitShader = IShader::Create();
    ASSERT(unlitShader->Load(UNLIT_SHADER_PATH), "Failed to load shader at path \"%s\"", UNLIT_SHADER_PATH);
    ASSERT(unlitShader->Init(), "Failed to initialize shader at path \"%s\"", UNLIT_SHADER_PATH);

    unlitShader->Bind();
    unlitShader->SetUniformTexture("u_diffuse", &GetTexture());

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

        unlitShader->Bind();
        unlitShader->SetUniformMat4("u_mvp", viewProjection * modelMat1);
        unlitShader->SetUniformVec4("u_tint", Color::white);
        DrawModel(model);

        unlitShader->SetUniformMat4("u_mvp", viewProjection * modelMat2);
        unlitShader->SetUniformVec4("u_tint", Color::red);
        DrawModel(model);

        if (camFrustum.Intersects(TransformBoundingBox(model.GetBoundingBox(), testModelMat)))
        {
            unlitShader->SetUniformMat4("u_mvp", viewProjection * testModelMat);
            unlitShader->SetUniformVec4("u_tint", Color::yellow);
            DrawModel(model);
        }

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
