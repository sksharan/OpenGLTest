#include "LandscapeManager.h"
#include "ObjectGenerator.h"
#include <iostream>

LandscapeManager landscapeManager;

LandscapeManager::LandscapeManager() {
    last_base_chunk_x = -1;
    last_base_chunk_z = -1;
}

void LandscapeManager::registerLandscape(PerlinHeightmapObject* perlin_hm) {
    landscape = perlin_hm;
}

PerlinHeightmapObject* LandscapeManager::getRegisteredLandscape(Viewer& viewer) {
    //viewer is not used right now, but can be used later if we want infinite chunked landscapes
    return landscape;
}

/* Round m down to the closest multiple of n. Some rounding algorithms (including this one)
can be seen at  https://gist.github.com/aslakhellesoy/1134482 */
int roundDown(int n, int m) {
    if (m >= 0) {
        return n * (m / n);
    }
    return n * ((m - n + 1) / n);
}

const std::vector<PerlinHeightmapObject*> LandscapeManager::getLandscapeChunks(Viewer& viewer) {
    const int off = 128;
    int base_chunk_x = roundDown(off, viewer.getPosition().x);
    int base_chunk_z = roundDown(off, viewer.getPosition().z) + off;

    if (last_base_chunk_x == -1 && last_base_chunk_z == -1) {
        //for the comments below, consider the -z direction to be "north" and the +x direction to be "east"
        landscape_chunks.push_back(genPerlinHeightmapObject(glm::vec3(base_chunk_x, 0, base_chunk_z), off + 1)); //current chunk 0
        landscape_chunks.push_back(genPerlinHeightmapObject(glm::vec3(base_chunk_x, 0, base_chunk_z - off), off + 1)); //north chunk 1
        landscape_chunks.push_back(genPerlinHeightmapObject(glm::vec3(base_chunk_x + off, 0, base_chunk_z - off), off + 1)); //ne chunk 2
        landscape_chunks.push_back(genPerlinHeightmapObject(glm::vec3(base_chunk_x + off, 0, base_chunk_z), off + 1)); //east chunk 3
        landscape_chunks.push_back(genPerlinHeightmapObject(glm::vec3(base_chunk_x + off, 0, base_chunk_z + off), off + 1)); //se chunk 4
        landscape_chunks.push_back(genPerlinHeightmapObject(glm::vec3(base_chunk_x, 0, base_chunk_z + off), off + 1)); //south chunk 5
        landscape_chunks.push_back(genPerlinHeightmapObject(glm::vec3(base_chunk_x - off, 0, base_chunk_z + off), off + 1)); //sw chunk 6
        landscape_chunks.push_back(genPerlinHeightmapObject(glm::vec3(base_chunk_x - off, 0, base_chunk_z), off + 1)); //west chunk 7
        landscape_chunks.push_back(genPerlinHeightmapObject(glm::vec3(base_chunk_x - off, 0, base_chunk_z - off), off + 1)); //nw chunk 8
        last_base_chunk_x = base_chunk_x;
        last_base_chunk_z = base_chunk_z;
        return landscape_chunks;
    }

    //if we don't need to generate new chunks yet, just return old vector of chunks that were used
    if (base_chunk_x == last_base_chunk_x && base_chunk_z == last_base_chunk_z) {
        return landscape_chunks;
    }

    //otherwise, we need to create new chunks and delete the unneccessary ones
    std::vector<PerlinHeightmapObject*> new_landscape_chunks(9);

    //moved to the west
    if (base_chunk_x < last_base_chunk_x) {
        delete landscape_chunks[2], landscape_chunks[3], landscape_chunks[4];
        new_landscape_chunks[0] = landscape_chunks[7];
        new_landscape_chunks[1] = landscape_chunks[8];
        new_landscape_chunks[2] = landscape_chunks[1];
        new_landscape_chunks[3] = landscape_chunks[0];
        new_landscape_chunks[4] = landscape_chunks[5];
        new_landscape_chunks[5] = landscape_chunks[6];
        new_landscape_chunks[6] = genPerlinHeightmapObject(glm::vec3(base_chunk_x - off, 0, base_chunk_z + off), off + 1);
        new_landscape_chunks[7] = genPerlinHeightmapObject(glm::vec3(base_chunk_x - off, 0, base_chunk_z), off + 1);
        new_landscape_chunks[8] = genPerlinHeightmapObject(glm::vec3(base_chunk_x - off, 0, base_chunk_z - off), off + 1);
    }
    //moved to the north
    else if (base_chunk_z < last_base_chunk_z) {
        delete landscape_chunks[4], landscape_chunks[5], landscape_chunks[6];
        new_landscape_chunks[0] = landscape_chunks[1];
        new_landscape_chunks[1] = genPerlinHeightmapObject(glm::vec3(base_chunk_x, 0, base_chunk_z - off), off + 1);
        new_landscape_chunks[2] = genPerlinHeightmapObject(glm::vec3(base_chunk_x + off, 0, base_chunk_z - off), off + 1);
        new_landscape_chunks[3] = landscape_chunks[2];
        new_landscape_chunks[4] = landscape_chunks[3];
        new_landscape_chunks[5] = landscape_chunks[0];
        new_landscape_chunks[6] = landscape_chunks[7];
        new_landscape_chunks[7] = landscape_chunks[8];
        new_landscape_chunks[8] = genPerlinHeightmapObject(glm::vec3(base_chunk_x - off, 0, base_chunk_z - off), off + 1);
    }
    //moved to the east
    if (base_chunk_x > last_base_chunk_x) {
        delete landscape_chunks[6], landscape_chunks[7], landscape_chunks[8];
        new_landscape_chunks[0] = landscape_chunks[3];
        new_landscape_chunks[1] = landscape_chunks[2];
        new_landscape_chunks[2] = genPerlinHeightmapObject(glm::vec3(base_chunk_x + off, 0, base_chunk_z - off), off + 1);
        new_landscape_chunks[3] = genPerlinHeightmapObject(glm::vec3(base_chunk_x + off, 0, base_chunk_z), off + 1);
        new_landscape_chunks[4] = genPerlinHeightmapObject(glm::vec3(base_chunk_x + off, 0, base_chunk_z + off), off + 1);
        new_landscape_chunks[5] = landscape_chunks[4];
        new_landscape_chunks[6] = landscape_chunks[5];
        new_landscape_chunks[7] = landscape_chunks[0];
        new_landscape_chunks[8] = landscape_chunks[1];
    }
    //moved to the south
    else if (base_chunk_z > last_base_chunk_z) {
        delete landscape_chunks[1], landscape_chunks[2], landscape_chunks[8];
        new_landscape_chunks[0] = landscape_chunks[5];
        new_landscape_chunks[1] = landscape_chunks[0];
        new_landscape_chunks[2] = landscape_chunks[3];
        new_landscape_chunks[3] = landscape_chunks[4];
        new_landscape_chunks[4] = genPerlinHeightmapObject(glm::vec3(base_chunk_x + off, 0, base_chunk_z + off), off + 1);
        new_landscape_chunks[5] = genPerlinHeightmapObject(glm::vec3(base_chunk_x, 0, base_chunk_z + off), off + 1);
        new_landscape_chunks[6] = genPerlinHeightmapObject(glm::vec3(base_chunk_x - off, 0, base_chunk_z + off), off + 1);
        new_landscape_chunks[7] = landscape_chunks[6];
        new_landscape_chunks[8] = landscape_chunks[7];
    }

    landscape_chunks = new_landscape_chunks;
    last_base_chunk_x = base_chunk_x;
    last_base_chunk_z = base_chunk_z;
    return landscape_chunks;
}