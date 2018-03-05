#pragma once
#include <maya/MMaterial.h>
#include <maya/MGlobal.h>
#include <maya/MDagPath.h>

class UVManager
{
public:
	UVManager();
	~UVManager();

	static void RePlanUV(float targetMinX, float targetMinY, float targetMaxX, float targetMaxY, float originMinX = 0, float originMinY = 0, float originMaxX = 0, float originMaxY = 0);



};

