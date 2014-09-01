#ifndef LANDSCAPEMANAGER_H
#define LANDSCAPEMANAGER_H

#include "PerlinHeightmapObject.h"
#include "Viewer.h"

/* A class for managing landscapes which the user can walk on. */
class LandscapeManager {
public:
	/* Register 'perlin_hm' as the current walkable landscape. */
	void registerLandscape(PerlinHeightmapObject* perlin_hm);

	/* Get the landscape that 'viewer' is standing on. */
	PerlinHeightmapObject* getLandscape(Viewer& viewer);

private:
	PerlinHeightmapObject* landscape;
};

extern LandscapeManager landscapeManager;

#endif