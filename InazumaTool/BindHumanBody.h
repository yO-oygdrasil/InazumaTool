#pragma once
#include <maya/MObject.h>
#include <maya/MFnIkJoint.h>
#include <maya/MFnTransform.h>
#include <maya/MPlug.h>
#include <maya/MFnIkHandle.h>
#include "JointProcess.h"
#include "BasicFunc.h"
static class BindHumanBody
{
public:
	static bool BindFinger(MObject& rootJoint, MString fingerTag, bool useIK = false);
	static bool BindFinger(MObject& rootJoint, MObject& middleJoint, MObject& finalJoint, MString fingerTag, bool useIK = false);
	//bool BindFinger(MFnIkJoint& rootJoint, MFnIkJoint& middleJoint, MFnIkJoint& finalJoint, MString fingerTag, bool useIK = false);

	static void AddRPIKPole();
	static void AddRPIKPole(MObject& middleObject);
	static void AddRPIKPole(MDagPath& rootDagPath, MDagPath& middleDagPath, MDagPath& endDagPath);

	static bool BindRPIK();
	static bool BindRPIK(MDagPath& rootObject, MDagPath& endObject, MDagPath& ctlObject);
};

