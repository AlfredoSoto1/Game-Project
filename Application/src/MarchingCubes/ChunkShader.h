//#pragma once
//
//#include "Scene/Camera.h"
//#include "Renderer/ShaderProgram.h"
//#include "Renderer/Shader.h"
//
//using namespace Uranium;
//
//class ChunkShader : public ShaderProgram {
//private:
//
//public:
//	ChunkShader() 
//		: ShaderProgram("src/testV.glsl", "src/testF.glsl")
//	{
//		//color = getUniform("u_Color");
//		//viewMatrix = getUniform("viewMatrix");
//		//projectionMatrix = getUniform("projectionMatrix");
//		//transformationMatrix = getUniform("transformationMatrix");
//
//		//sampler = getSampler2D("grass");
//
//
//		//transform(&transformMat, vec3(0.0, 0.0, 0.0), vec3(0.0), vec3(1.0));
//	}
//	
//	~ChunkShader() {
//
//	}
//
//	void initStaticUniforms() {
//		//bindSampler2D(sampler, 0);
//	}
//
//	void updateUniforms() {
//		//setVec4(color, { 1.0, 0.0, 0.0, 1.0 });
//		//setMat4(viewMatrix, _camera->getViewMatrix());
//		//setMat4(projectionMatrix, _camera->getProjectionMatrix());
//		//setMat4(transformationMatrix, transformMat);
//	}
//
//};