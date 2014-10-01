#ifndef LANDSCAPEMANAGER_H
#define LANDSCAPEMANAGER_H

#include "PerlinHeightmapObject.h"
#include "Viewer.h"
#include <vector>

/* A class that manages the landscape that the user walks on and which landscape chunks
should be visible. */
class LandscapeManager {
public:
    LandscapeManager();

    /* Register 'perlin_hm' as the current walkable landscape. */
    void registerLandscape(PerlinHeightmapObject* perlin_hm);

    /* Get the landscape that was registered as the walkable landscape. */
    PerlinHeightmapObject* getRegisteredLandscape(Viewer& viewer);

    /* Return landscape chunks near the 'viewer.' */
    const std::vector<PerlinHeightmapObject*> getLandscapeChunks(Viewer& viewer);

private:
    /* Registered walkable landscape. */
    PerlinHeightmapObject* landscape;

    /* Values used to determine which chunks were previously created. */
    int last_base_chunk_x, last_base_chunk_z;
    
    /* The landscape chunks that should be rendered. */
    std::vector<PerlinHeightmapObject*> landscape_chunks;
};

extern LandscapeManager landscapeManager;

#endif