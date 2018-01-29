#pragma once
#include <maya/MObject.h>
#include <maya/MFnIkJoint.h>
#include <maya/MFnTransform.h>
#include <maya/MPlug.h>
#include "JointProcess.h"
#include "BasicFunc.h"
static class BindHumanBody
{
public:
	bool BindFinger(MObject& rootJoint, MString fingerTag, bool useIK = false);
	bool BindFinger(MObject& rootJoint, MObject& middleJoint, MObject& finalJoint, MString fingerTag, bool useIK = false);
	//bool BindFinger(MFnIkJoint& rootJoint, MFnIkJoint& middleJoint, MFnIkJoint& finalJoint, MString fingerTag, bool useIK = false);

	void 

	bool BindRPIK();
	bool BindRPIK(MObject& rootObject, MObject& endObject, MObject& ctlObject);
};

