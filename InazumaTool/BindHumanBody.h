#pragma once
#include <maya/MObject.h>
#include <maya/MFnIkJoint.h>
#include <maya/MFnTransform.h>
#include <maya/MPlug.h>
#include <maya/MFnIkHandle.h>
#include <maya/MFnIkSolver.h>
#include <maya/MDGModifier.h>
//#include <maya/MDagModifier.h>
#include "JointProcess.h"
#include "BasicFunc.h"
static class BindHumanBody
{
public:
	static bool BindFinger(MDagPath& rootJoint, MString fingerTag, bool useIK = false);
	static bool BindFinger(MDagPath& rootJoint, MDagPath& middleJoint, MDagPath& finalJoint, MString fingerTag, bool useIK = false);
	//bool BindFinger(MFnIkJoint& rootJoint, MFnIkJoint& middleJoint, MFnIkJoint& finalJoint, MString fingerTag, bool useIK = false);

	static bool AddRPIKPole(MDagPath& locDagPath);
	static bool AddRPIKPole(MDagPath& locDagPath, MObject& middleObject);
	static bool AddRPIKPole(MDagPath& locDagPath, MDagPath& middleDagPath);

	static bool BindRPIK(MDagPath* ikDagPath = NULL);
	static bool BindRPIK(MDagPath& rootDagPath, MDagPath& endDagPath, MDagPath* ikDagPath = NULL);
	static bool BindRPIK(MDagPath& rootDagPath, MDagPath& endDagPath, MDagPath& ctlDagPath, MDagPath* ikDagPath = NULL);

	static bool AddReverseFootBone(MDagPath **reverseBones = NULL);
	static bool AddReverseFootBone(MDagPath& rootDagPath, MDagPath& middleDagPath, MDagPath& endDagPath, MDagPath **reverseBones = NULL);

	static bool BindReverseFootRPIK();
	static bool BindReverseFootRPIK(MDagPath& legRootDagPath, MDagPath& ankleDagPath, MDagPath& middleDagPath, MDagPath& endDagPath);
	
};

