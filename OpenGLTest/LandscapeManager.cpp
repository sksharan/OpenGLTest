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
	const int off = 64;
	int base_chunk_x = roundDown(off, viewer.getPosition().x);
	int base_chunk_z = roundDown(off, viewer.getPosition().z) + off;

	//if we don't need to generate new chunks yet, just return old vector of chunks that were used
	if (base_chunk_x == last_base_chunk_x && base_chunk_z == last_base_chunk_z) {
		return landscape_chunks;
	}

	//otherwise, we need to create new chunks and delete the unneccessary ones
	landscape_chunks.clear();

	landscape_chunks.push_back(genPerlinHeightmapObject(glm::vec3(base_chunk_x, 0, base_chunk_z), off + 1));
	landscape_chunks.push_back(genPerlinHeightmapObject(glm::vec3(base_chunk_x + off, 0, base_chunk_z), off + 1));
	landscape_chunks.push_back(genPerlinHeightmapObject(glm::vec3(base_chunk_x - off, 0, base_chunk_z), off + 1));
	landscape_chunks.push_back(genPerlinHeightmapObject(glm::vec3(base_chunk_x, 0, base_chunk_z + off), off + 1));
	landscape_chunks.push_back(genPerlinHeightmapObject(glm::vec3(base_chunk_x, 0, base_chunk_z - off), off + 1));
	landscape_chunks.push_back(genPerlinHeightmapObject(glm::vec3(base_chunk_x + off, 0, base_chunk_z + off), off+1));
	landscape_chunks.push_back(genPerlinHeightmapObject(glm::vec3(base_chunk_x + off, 0, base_chunk_z - off), off+1));
	landscape_chunks.push_back(genPerlinHeightmapObject(glm::vec3(base_chunk_x - off, 0, base_chunk_z + off), off+1));
	landscape_chunks.push_back(genPerlinHeightmapObject(glm::vec3(base_chunk_x - off, 0, base_chunk_z - off), off+1));

	last_base_chunk_x = base_chunk_x;
	last_base_chunk_z = base_chunk_z;
}