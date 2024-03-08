#pragma once
#include "SurvivantCore/Resources/IResource.h"
#include <string> // Pour std::string

class Material : public SvCore::Resources::IResource 
{
public:
    Material();

    virtual bool Load(const std::string& filename) override; 
    virtual bool Init() override; 

    // Setters et getters pour les propri�t�s du mat�riau
    void SetDiffuseTexture(const std::string& filename); // D�finition de la texture de diffusion
    void SetSpecularTexture(const std::string& filename); // D�finition de la texture sp�culaire
    void SetNormalTexture(const std::string& filename); // D�finition de la texture normale
    void SetAmbientColor(float r, float g, float b); // D�finition de la couleur ambiante
    void SetDiffuseColor(float r, float g, float b); // D�finition de la couleur de diffusion
    void SetSpecularColor(float r, float g, float b); // D�finition de la couleur sp�culaire
    void SetShininess(float shininess); // D�finition de la brillance

    // Autres fonctions membres pour g�rer les param�tres du mat�riau, par exemple, activer/d�sactiver les textures, etc.

private:
    // Propri�t�s du mat�riau
    std::string m_diffuseTexture;
    std::string m_specularTexture;
    std::string m_normalTexture;
    float m_ambientColor[3];
    float m_diffuseColor[3];
    float m_specularColor[3];
    float m_shininess;
};