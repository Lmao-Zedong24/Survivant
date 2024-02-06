#include <vector>
#include <string>
#include "SurvivantRendering/Resources/texture.h"

class Model
{
public:
	Model();

	~Model();

	bool								LoadModel(const std::string& p_filename);

	void								RenderModel();

	void								SetTransformation(float p_x, float p_y, float p_z, float p_rotationX, float p_rotationY,
														  float p_rotationZ, float p_scaleX,float p_scaleY, float p_scaleZ);

	void								PlayAnimation(const std::string& p_animationName);

	void								StopAnimation();
	
	void								SetMaterial();

	bool								CheckCollision();

	void								Update(float p_deltaTime);

	void								CleanUp();
private:

	std::vector<float>					m_vertices;
	std::vector<float>					m_normals;
	std::vector<float>					m_UVs;
};