#include "SurvivantRendering/Resources/Material.h"
#include "SurvivantCore/Debug/Logger.h"

#include <fstream>

bool Material::Load(const std::string& filename) 
{
    // Opening the materials file
    std::ifstream file(filename);
    if (!file.is_open()) 
    {
        SV_LOG_ERROR("Failed to Load file");
        return false;
    }

    // Read materials datas
    file >> m_diffuseTexture;
    file >> m_specularTexture;
    file >> m_normalTexture;

    file >> m_ambientColor[0] >> m_ambientColor[1] >> m_ambientColor[2];
    file >> m_diffuseColor[0] >> m_diffuseColor[1] >> m_diffuseColor[2];
    file >> m_specularColor[0] >> m_specularColor[1] >> m_specularColor[2];

    file >> m_shininess;

    //Close file
    file.close();

    return true;
}

void Material::SetDiffuseTexture(const std::string& filename) 
{
    // Checking if the path is absolute
    if (std::filesystem::path(filename).is_absolute())
    {
        m_diffuseTexture = filename;
    }
    else 
    {
        // If the file path is relative, make it absolute using the current working directory.
        std::string absolutePath = std::filesystem::absolute(filename).string();
        m_diffuseTexture = absolutePath;
    }
}

void Material::SetSpecularTexture(const std::string& filename) 
{
    if (std::filesystem::path(filename).is_absolute()) {
        m_specularTexture = filename;
    }
    else {
        std::string absolutePath = std::filesystem::absolute(filename).string();
        m_specularTexture = absolutePath;
    }
}

void Material::SetNormalTexture(const std::string& filename) 
{
    if (std::filesystem::path(filename).is_absolute()) {
        m_normalTexture = filename;
    }
    else {
        std::string absolutePath = std::filesystem::absolute(filename).string();
        m_normalTexture = absolutePath;
    }
}

void Material::SetAmbientColor(float r, float g, float b) {
    // Définir la couleur ambiante
    m_ambientColor[0] = r;
    m_ambientColor[1] = g;
    m_ambientColor[2] = b;
}

void Material::SetDiffuseColor(float r, float g, float b) {
    // Définir la couleur de diffusion
    m_diffuseColor[0] = r;
    m_diffuseColor[1] = g;
    m_diffuseColor[2] = b;
}

void Material::SetSpecularColor(float r, float g, float b) {
    // Définir la couleur spéculaire
    m_specularColor[0] = r;
    m_specularColor[1] = g;
    m_specularColor[2] = b;
}

void Material::SetShininess(float shininess) 
{
    // Définir la brillance
    m_shininess = shininess;
}