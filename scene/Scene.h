#ifndef __hSCENE_H__
#define __hSCENE_H__

namespace Hound {
	class Application;

	class Scene {
	protected:
		friend class Application;
	public:
		struct Scene_Info {
			char title[128];
			int width;
			int height;
		} mSceneInfo;

	public:
		Scene() = default;
		virtual ~Scene() = default;

		virtual void Init() = 0;
		virtual void LoadScene() = 0;
		virtual void UnloadScene() = 0;

		virtual void Update(float deltaTime) = 0;
		virtual void Draw() = 0;
	};
}

#endif