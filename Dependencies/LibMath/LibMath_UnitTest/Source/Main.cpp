#include <catch2/catch_session.hpp>

#if defined(_DEBUG) && defined(_MSC_VER)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

/*
 * references
 * https://en.cppreference.com/w/cpp/language/operators
 *
 * https://docs.unity3d.com/ScriptReference/Vector3.html
 * https://docs.unity3d.com/ScriptReference/Mathf.html
 * https://docs.unity3d.com/ScriptReference/Matrix4x4.html
 * https://docs.unrealengine.com/4.26/en-US/API/Runtime/Core/Math/FVector/
 * https://docs.unrealengine.com/4.27/en-US/API/Runtime/Core/Math/FMath/
 * https://docs.unrealengine.com/4.27/en-US/API/Runtime/Core/Math/FMatrix/
 */

void addGroups([[maybe_unused]] std::vector<const char*>& arguments)
{
    // Uncomment lines below to enable the corresponding test groups
    // By default if no groups are specified, no tests are executed

    arguments.push_back("[all],");
    // arguments.push_back("[arithmetic],");
    // arguments.push_back("[trigonometry],");
    // arguments.push_back("[angle],");
    // arguments.push_back("[vector],");
    // arguments.push_back("[matrix],");
    // arguments.push_back("[quaternion],");
    // arguments.push_back("[transform],");
}

void addTests([[maybe_unused]] std::vector<const char*>& arguments)
{
    // Uncomment lines below to enable the corresponding test cases
    // Note: You can leave the group section fully commented out and only uncomment lines from this section

    // arguments.push_back("Degree,");
    // arguments.push_back("Radian,");
    // arguments.push_back("Vector2,");
    // arguments.push_back("Vector3,");
    // arguments.push_back("Vector4,");
    // arguments.push_back("Matrix2,");
    // arguments.push_back("Matrix3,");
    // arguments.push_back("Matrix4,");
    // arguments.push_back("Quaternion,");
    // arguments.push_back("Transform,");
}

void addSections([[maybe_unused]] std::vector<const char*>& arguments)
{
    // Uncomment lines from below to only run specific sections of the enabled test cases
    // By default if no sections are specified, all sections are executed

    // arguments.push_back("-c Accessor");
    // arguments.push_back("-c Arithmetic");
    // arguments.push_back("-c Comparator");
    // arguments.push_back("-c Constant");
    // arguments.push_back("-c Conversion");
    // arguments.push_back("-c Debug");
    // arguments.push_back("-c Extra");
    // arguments.push_back("-c Functionality");
    // arguments.push_back("-c Instantiation");
    // arguments.push_back("-c Transformation");
}

void addExtra([[maybe_unused]] std::vector<const char*>& arguments)
{
    // Add more catch command line argument here (see https://github.com/catchorg/Catch2/blob/devel/docs/command-line.md)

    // arguments.push_back("-o test_results.txt"); // Makes catch write the test results in "test_results.txt" instead of the console
}

int main(const int argc, const char* argv[])
{
#if defined(_DEBUG) && defined(_MSC_VER)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    // transfers command line argument to dynamic collection so we can add our own arguments easily
    std::vector<const char*> arguments;
    arguments.reserve(argc);

    for (int i = 0; i < argc; i++)
        arguments.push_back(argv[i]);

    addGroups(arguments);
    addTests(arguments);
    addSections(arguments);
    addExtra(arguments);

    // Running catch test with command line argument + custom argument from main
    return Catch::Session().run(static_cast<int>(arguments.size()), arguments.data());
}
