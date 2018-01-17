#pragma once
#include <maya/MObject.h>
#include <maya/MFnTransform.h>
#include <maya/MFnIkJoint.h>
#include "JointProcess.h"
#include "Incubater.h"
static class BindHumanBody
{
public:
	bool BindFinger(MObject rootJoint, MString fingerTag, bool useIK = false);
	bool BindFinger(MObject& rootJoint, MObject& middleJoint, MObject& finalJoint, MString fingerTag, bool useIK = false);
	//bool BindFinger(MFnIkJoint& rootJoint, MFnIkJoint& middleJoint, MFnIkJoint& finalJoint, MString fingerTag, bool useIK = false);
};

