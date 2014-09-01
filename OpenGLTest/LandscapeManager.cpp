#include "LandscapeManager.h"

LandscapeManager landscapeManager;

void LandscapeManager::registerLandscape(PerlinHeightmapObject* perlin_hm) {
	landscape = perlin_hm;
}

PerlinHeightmapObject* LandscapeManager::getLandscape(Viewer& viewer) {
	//viewer is used right now, but can be used later if we want infinite chunked landscapes
	return landscape;
}