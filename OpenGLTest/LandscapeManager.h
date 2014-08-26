#ifndef LANDSCAPEMANAGER_H
#define LANDSCAPEMANAGER_H

#include "PerlinHeightmapObject.h"

/* A class for managing landscapes, the enviornment that the user can walk on. */
class LandscapeManager {

public:
	PerlinHeightmapObject* landscape;
};

extern LandscapeManager landscapeManager;

#endif