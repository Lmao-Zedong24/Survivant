#pragma once
#include "SurvivantCore/Resources/IResource.h"
#include <string> // Pour std::string

class Material : public SvCore::Resources::IResource 
{
public:
    Material();

    virtual bool Load(const std::string& filename) override; 
    virtual bool Init() override; 

    // Setters et getters pour les propriétés du matériau
    void SetDiffuseTexture(const std::string& filename); // Définition de la texture de diffusion
    void SetSpecularTexture(const std::string& filename); // Définition de la texture spéculaire
    void SetNormalTexture(const std::string& filename); // Définition de la texture normale
    void SetAmbientColor(float r, float g, float b); // Définition de la couleur ambiante
    void SetDiffuseColor(float r, float g, float b); // Définition de la couleur de diffusion
    void SetSpecularColor(float r, float g, float b); // Définition de la couleur spéculaire
    void SetShininess(float shininess); // Définition de la brillance

    // Autres fonctions membres pour gérer les paramètres du matériau, par exemple, activer/désactiver les textures, etc.

private:
    // Propriétés du matériau
    std::string m_diffuseTexture;
    std::string m_specularTexture;
    std::string m_normalTexture;
    float m_ambientColor[3];
    float m_diffuseColor[3];
    float m_specularColor[3];
    float m_shininess;
};