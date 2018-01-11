#pragma once
#include <maya/MObject.h>
#include<maya/MFnTransform.h>
#include<maya/MVector.h>
#include<maya/MFnIkJoint.h>
#include "ConstantValue.h"
#include<maya/MFn.h>
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

	bool SetJointLimit(MObject& mobject, JointType jointType);
	bool SetJointLimit(MFnTransform& mfnTrans, JointType jointType);
private:
	bool SetLimit(MFnTransform & mfnTrans, float rxMin, float ryMin, float rzMin, float rxMax, float ryMax, float rzMax, bool inRadian);


};

