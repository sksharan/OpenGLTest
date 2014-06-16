#include "Render.h"
#include "Window.h"
#include "ProgramState.h"
#include "RenderableObject.h"
#include <GL/glew.h>

void render() {
	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(programState.program);

	for (int i = 0; i < RenderableObject::renderableObjects.size(); i++) {
		RenderableObject* object = &*(RenderableObject::renderableObjects[i]);
		object->render();
	}

	glUseProgram(0);

	SDL_GL_SwapWindow(mainWindow.window);
}