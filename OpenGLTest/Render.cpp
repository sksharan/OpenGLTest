#include "Render.h"
#include "Window.h"
#include "ProgramState.h"
#include "RenderableObject.h"
#include <GL/glew.h>

void render(Scene& scene) {
	glm::vec4 clear_color = scene.getClearColor();
	float clear_depth = scene.getClearDepth();

	glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.a);
	glClearDepth(clear_depth);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//begin rendering
	for (int i = 0; i < scene.getSceneObjects().size(); i++) {
		RenderableObject* object = scene.getSceneObjects()[i];
		if (object->isVisible()) {
			object->render();
		}
	}
	if (landscapeManager.getLandscape(mainViewer) != NULL) {
		landscapeManager.getLandscape(mainViewer)->render();
	}
	//end rendering

	SDL_GL_SwapWindow(mainWindow.window);
}