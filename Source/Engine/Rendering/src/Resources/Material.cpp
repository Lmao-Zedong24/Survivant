#include "SurvivantRendering/Resources/Material.h"

#include "SurvivantCore/Debug/Assertion.h"

#include "SurvivantRendering/RHI/ITexture.h"

using namespace LibMath;
using namespace SvCore::Resources;
using namespace SvRendering::Enums;
using namespace SvRendering::RHI;

namespace SvRendering::Resources
{
    Material::Material(const std::shared_ptr<IShader>& p_shader)
    {
        SetShader(p_shader);
    }

    bool Material::Load(const std::string&)
    {
        // TODO: Support material files
        return false;
    }

    IShader& Material::GetShader() const
    {
        ASSERT(m_shader, "Missing material shader");
        return *m_shader;
    }

    void Material::SetShader(const std::shared_ptr<IShader>& p_shader)
    {
        m_shader = p_shader;
        m_properties.clear();

        for (auto [name, uniform] : m_shader->GetUniforms())
        {
            if (name.starts_with(ENGINE_UNIFORM_PREFIX))
                continue;

            m_properties[name] =
            {
                uniform.m_type,
                GetDefaultValue(uniform.m_type)
            };
        }
    }

    const Material::Property& Material::GetProperty(const std::string& p_name) const
    {
        const auto it = m_properties.find(p_name);
        ASSERT(it != m_properties.end(), "Unable to find material property \"%s\"", p_name.c_str());
        return it->second;
    }

    Material::Property& Material::GetProperty(const std::string& p_name)
    {
        const auto it = m_properties.find(p_name);
        ASSERT(it != m_properties.end(), "Unable to find material property \"%s\"", p_name.c_str());
        return it->second;
    }

    const std::unordered_map<std::string, Material::Property>& Material::GetProperties() const
    {
        return m_properties;
    }

    std::unordered_map<std::string, Material::Property>& Material::GetProperties()
    {
        return m_properties;
    }

    void Material::Bind() const
    {
        ASSERT(m_shader, "Failed to bind material - Missing shader");
        m_shader->Bind();

        for (const auto& [name, property] : m_properties)
            BindProperty(name, property);
    }

    std::any Material::GetDefaultValue(const EShaderDataType p_dataType)
    {
        switch (p_dataType)
        {
        case EShaderDataType::BOOL:
            return false;
        case EShaderDataType::INT:
            return 0;
        case EShaderDataType::UNSIGNED_INT:
            return 0u;
        case EShaderDataType::FLOAT:
            return 0.f;
        case EShaderDataType::VEC2:
            return Vector2();
        case EShaderDataType::VEC3:
            return Vector3();
        case EShaderDataType::VEC4:
            return Vector4();
        case EShaderDataType::MAT3:
            return Matrix3();
        case EShaderDataType::MAT4:
            return Matrix4();
        case EShaderDataType::TEXTURE:
            return std::shared_ptr<ITexture>();
        case EShaderDataType::UNKNOWN:
        default:
            ASSERT(false, "Failed to get default value - Unkown data type");
            return {};
        }
    }

    void Material::BindProperty(const std::string& p_name, const Property& p_property) const
    {
        ASSERT(m_shader, "Unable to bind material property - No shader");

        switch (p_property.m_type)
        {
        case EShaderDataType::BOOL:
            m_shader->SetUniformInt(p_name, std::any_cast<bool>(p_property.m_value));
            break;
        case EShaderDataType::INT:
            m_shader->SetUniformInt(p_name, std::any_cast<int>(p_property.m_value));
            break;
        case EShaderDataType::UNSIGNED_INT:
            m_shader->SetUniformUInt(p_name, std::any_cast<uint32_t>(p_property.m_value));
            break;
        case EShaderDataType::FLOAT:
            m_shader->SetUniformFloat(p_name, std::any_cast<float>(p_property.m_value));
            break;
        case EShaderDataType::VEC2:
            m_shader->SetUniformVec2(p_name, std::any_cast<const Vector2&>(p_property.m_value));
            break;
        case EShaderDataType::VEC3:
            m_shader->SetUniformVec3(p_name, std::any_cast<const Vector3&>(p_property.m_value));
            break;
        case EShaderDataType::VEC4:
            m_shader->SetUniformVec4(p_name, std::any_cast<const Vector4&>(p_property.m_value));
            break;
        case EShaderDataType::MAT3:
            m_shader->SetUniformMat3(p_name, std::any_cast<const Matrix3&>(p_property.m_value));
            break;
        case EShaderDataType::MAT4:
            m_shader->SetUniformMat4(p_name, std::any_cast<const Matrix4&>(p_property.m_value));
            break;
        case EShaderDataType::TEXTURE:
        {
            m_shader->SetUniformTexture(p_name, std::any_cast<const std::shared_ptr<ITexture>&>(p_property.m_value).get());
            break;
        }
        case EShaderDataType::UNKNOWN:
        default:
            ASSERT(false, "Unknown uniform type");
            return;
        }
    }
}
