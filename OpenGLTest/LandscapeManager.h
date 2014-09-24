#ifndef LANDSCAPEMANAGER_H
#define LANDSCAPEMANAGER_H

#include "PerlinHeightmapObject.h"
#include "Viewer.h"
#include <vector>

/* A class for managing landscapes which the user can walk on. */
class LandscapeManager {
public:
    LandscapeManager();

    /* Register 'perlin_hm' as the current walkable landscape. */
    void registerLandscape(PerlinHeightmapObject* perlin_hm);

    /* Get the landscape that 'viewer' is standing on. */
    PerlinHeightmapObject* getRegisteredLandscape(Viewer& viewer);

    /* Return landscape chunks near the 'viewer.' */
    const std::vector<PerlinHeightmapObject*> getLandscapeChunks(Viewer& viewer);

private:
    PerlinHeightmapObject* landscape;

    int last_base_chunk_x, last_base_chunk_z;
    std::vector<PerlinHeightmapObject*> landscape_chunks;
};

extern LandscapeManager landscapeManager;

#endif