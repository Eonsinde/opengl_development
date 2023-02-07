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

			struct {
				int width;
				int height;
			} mResolution, mViewport;

			// saving myself the trouble of refactoring
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