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
	

	static void SetTranslateLimit(MObject & mObject, float minX, float minY, float minZ, float maxX, float maxY, float maxZ);
	static void SetTranslateLimit(MFnTransform & mfnTrans, float minX, float minY, float minZ, float maxX, float maxY, float maxZ);

	
	static MString ToCMDSParamStr(MVector vector);
	static MString ToCMDSParamStr(int *arr, size_t  count, char concatChar = ',');

	static bool CreateLocator(MDagPath& locDagPath, MVector worldPos, MString locatorName = "loc_sample");
	static MDagPath CreateCircle(MString ctlName = "circle_sample");
	static MDagPath CreateCTL_Crystal(MString ctlName = "ctl_sample");
	static MDagPath CreateCurve(MVector points[],int ptCount, MString curveName = "curve_sample");
	static MString CreateRemapValueNode(float inputMin, float inputMax, float outputMin, float outputMax, MFnDependencyNode** dependencyNode = NULL);

	static void IterateChidren(int(*func)(MDagPath&),MDagPath& rootNode);

	static MObject GetSelectedObject(int index);
	static MDagPath GetSelectedDagPath(int index);
	static MSelectionList GetSelectedDagPaths();
	//static void PrintMVector(MVector vec);
	//static void Print(MString str);

	static MSelectionList GetObjectsByName(MString name);
	static MObject GetObjectByName(MString name, int index = 0);
	static MDagPath GetDagPathByName(MString name, int index = 0);

	static MDagPath AddChildCircle(MObject& targetObject);
	static MDagPath AddChildCircle(MDagPath& targetDagPath);
	static MDagPath AddParentCircle(MObject& targetObject, bool createParallelGrp = false);
	static MDagPath AddParentCircle(MDagPath& targetDagPath, bool createParallelGrp = false);

	static MDagPath AddEmptyGroup(MFnTransform& parent);
	static MDagPath AddEmptyGroup(MString grpName, MString parentName = "");


	static void SetTransformParent(MFnTransform& c, MFnTransform& p);
	static void SetTransformParent(MString cFullName, MString pFullName);
	static void UnparentTransform(MDagPath& dagPath);
	static void UnparentTransform(MFnTransform& mfnTrans);
	static void FreezeTransform(MFnTransform& targetTransform);
	static void ClearTransform(MFnTransform& targetTransform, bool clearPos = true, bool clearPivotRot = true, bool clearPivotScale = true);

	static MString SubUShell(MString originStr);
	static MStringArray SplitPythonResultStr(MString pythonStr);

//private:
//	static std::stringstream* strStream;
//	static std::stringstream& SS();
};

