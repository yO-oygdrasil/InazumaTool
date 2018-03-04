#pragma once
#include <maya/MVector.h>
#include <maya/MItMeshVertex.h>
#include <maya/MItMeshFaceVertex.h>


class Cubater
{
public:
	float cubeSize = 1;
	float minX = -1, minY = -1, minZ = -1, maxX = 1, maxY = 1, maxZ = 1;
	
	Cubater(float minX, float minY, float minZ, float maxX, float maxY, float maxZ);
	
	Cubater(float minCubeSize);
	~Cubater();




};

