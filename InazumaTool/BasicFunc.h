#pragma once
#include <maya/MFnTransform.h>
#include <maya/MObject.h>


static class BasicFunc
{
public:
	void SetTranslateLimit(MObject & mObject, float minX, float minY, float minZ, float maxX, float maxY, float maxZ);
	void SetTranslateLimit(MFnTransform & mfnTrans, float minX, float minY, float minZ, float maxX, float maxY, float maxZ);

	MObject GetSelectedObject(int index)

};

