#pragma once
#include <maya/MString.h>
#include <maya/MGlobal.h>
#include <maya/MTypeId.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MPlug.h>
static class Incubater
{
public:
	static MString CreateCTL_Crystal(MString ctlName = "ctl_sample");
	static MString CreateRemapValueNode(float inputMin, float inputMax, float outputMin, float outputMax);
};

