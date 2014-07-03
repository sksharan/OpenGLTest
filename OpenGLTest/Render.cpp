#include "Render.h"
#include "Window.h"
#include "ProgramState.h"
#include "RenderableObject.h"
#include <GL/glew.h>

void render() {
	glClearColor(0.8f, 0.8f, 1.0f, 1.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(programState.program);

	for (int i = 0; i < RenderableObject::getRenderableObjects().size(); i++) {
		RenderableObject* object = &*(RenderableObject::getRenderableObjects()[i]);
		if (object->isVisible()) {
			object->render();
		}
	}

	glUseProgram(0);

	SDL_GL_SwapWindow(mainWindow.window);
}