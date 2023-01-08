//#pragma once
//
//#define UR_OPENGL
//#include "Engine.h"
//
//#include "Uranium/Utils/Maths/vec3.h"
//#include "Uranium/Utils/Maths/vec4.h"
//
//#include "Shader/ShaderProgram.h"
//#include "Uranium/Utils/Buffers/ShaderStorageBuffer.h"
//using namespace Uranium;
//
//class ComputeShader : public ShaderProgram {
//private:
//
//public:
//	ComputeShader() 
//		: ShaderProgram("src/testComp.glsl")
//	{
//
//	}
//
//	void load() const {
//		vec4 colors[] = {
//			vec4(1.0, 0.0, 0.0, 1.0),
//			vec4(0.0, 1.0, 0.0, 1.0),
//			vec4(0.0, 0.0, 1.0, 1.0),
//			vec4(1.0, 1.0, 1.0, 1.0),
//		};
//
//		ShaderStorageBuffer* ssbo = new ShaderStorageBuffer(GL_DYNAMIC_DRAW, 0, sizeof(colors), colors);
//
//		bind();
//
//		dispatchCompute(1, 1, 1, GL_SHADER_STORAGE_BARRIER_BIT);
//
//		unbind();
//
//		ssbo->getData(0, sizeof(colors), colors);
//
//		for (int i = 0; i < 4; i++) {
//			//cout << colors[i].x << ", " << colors[i].y << ", " << colors[i].z << ", " << colors[i].w << endl;
//		}
//
//		delete ssbo;
//	}
//
//	void update() const {
//
//	}
//
//	void unload() const {
//
//	}
//
//};