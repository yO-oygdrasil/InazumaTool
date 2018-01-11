#pragma once
#include <maya/MFnTransform.h>
#include <maya/MObject.h>
#include "ConstantValue.h"
#include <maya/MGlobal.h>
#include <maya/MSelectionList.h>
#include <maya/MDagPath.h>
#include <maya/MVector.h>
static class BasicFunc
{
public:
	void SetTranslateLimit(MObject & mObject, float minX, float minY, float minZ, float maxX, float maxY, float maxZ);
	void SetTranslateLimit(MFnTransform & mfnTrans, float minX, float minY, float minZ, float maxX, float maxY, float maxZ);

	static MObject GetSelectedObject(int index);
	static MDagPath GetSelectedDagPath(int index);

	static void PrintMVector(MVector vec);

	static MSelectionList GetObjectsByName(MString name);
	static MObject GetObjectByName(MString name, int index = 0);

};

