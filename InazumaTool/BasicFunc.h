#pragma once
#include <maya/MFnTransform.h>
#include <maya/MObject.h>
#include "ConstantValue.h"
#include <maya/MGlobal.h>
#include <maya/MSelectionList.h>
#include <maya/MDagPath.h>
#include <maya/MVector.h>
#include <maya/MFnNurbsCurve.h>
#include <maya/MPointArray.h>
#include <maya/MEulerRotation.h>
#include <maya/MPlug.h>
#include <maya/MStringArray.h>
#include <sstream>
static class BasicFunc
{
public:
	

	void SetTranslateLimit(MObject & mObject, float minX, float minY, float minZ, float maxX, float maxY, float maxZ);
	void SetTranslateLimit(MFnTransform & mfnTrans, float minX, float minY, float minZ, float maxX, float maxY, float maxZ);

	static MString ToCMDSParamStr(MVector vector);

	static bool CreateLocator(MDagPath& locDagPath, MVector worldPos, MString locatorName = "loc_sample");
	static MString CreateCTL_Crystal(MString ctlName = "ctl_sample");
	static MString CreateRemapValueNode(float inputMin, float inputMax, float outputMin, float outputMax);

	static void IterateChidren(int(*func)(MDagPath&),MDagPath& rootNode);

	static MObject GetSelectedObject(int index);
	static MDagPath GetSelectedDagPath(int index);

	//static void PrintMVector(MVector vec);
	//static void Print(MString str);

	static MSelectionList GetObjectsByName(MString name);
	static MObject GetObjectByName(MString name, int index = 0);
	static MDagPath GetDagPathByName(MString name, int index = 0);


	static MObject AddChildCircle(MObject& targetObject);
	static void SetTransformParent(MFnTransform& c, MFnTransform& p);
	static void SetTransformParent(MString cFullName, MString pFullName);
	static void FreezeTransform(MFnTransform& targetTransform);

	static MString SubUShell(MString originStr);
	static MStringArray SplitPythonResultStr(MString pythonStr);

//private:
//	static std::stringstream* strStream;
//	static std::stringstream& SS();
};

