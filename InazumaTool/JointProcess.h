#pragma once
#include <maya/MObject.h>
#include<maya/MFnTransform.h>
#include<maya/MVector.h>
#include<maya/MFnIkJoint.h>
#include<maya/MDagPath.h>
#include "ConstantValue.h"
#include<maya/MFn.h>
#include <maya/MGlobal.h>
#include <maya/MSelectionList.h>
#include "BasicFunc.h"
#include <list>
#include <numeric>  
static class JointProcess
{
public:
	enum JointType
	{
		Shoulder,
		FingerMiddle,
		FingerRoot,
		Default
	};

	static bool SetJointLimit(MDagPath& mDagPath, JointType jointType);
	static bool SetJointLimit(MObject& mobject, JointType jointType);
	static bool SetJointLimit(MFnTransform& mfnTrans, JointType jointType);

	//static void CreateJointsCurve(MDagPath** jointDagPaths = NULL);
	static MDagPath CreateJointsCurve(MSelectionList jointDagPaths);

	static void MakeJointsHairChain(MSelectionList jointDagPaths);

	static MDagPath CreateJoint(MString jtName = "joint");
	static MDagPath CreateJoint(MVector worldPos, MString jtName = "joint");
	static MDagPath CreateJoint(MFnIkJoint targetPosJoint, MString jtName = "joint");

private:
	static bool SetLimit(MFnTransform & mfnTrans, float rxMin, float ryMin, float rzMin, float rxMax, float ryMax, float rzMax, bool inRadian);


};

