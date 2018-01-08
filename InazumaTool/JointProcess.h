#pragma once
#include <maya/MObject.h>
#include<maya/MFnTransform.h>
#include<maya/MVector.h>
#include<maya/MFnIkJoint.h>
#include "ConstantValue.h"
#include<maya/MFn.h>

static class JointProcess
{
public:
	bool SetJointLimit(MObject& mobject, MString jointType);
	bool SetJointLimit(MFnTransform& mfnTrans, MString jointType);


private:
	class JointLimit
	{
	public:
		MVector min, max;
		bool SetLimit(MObject& mobject);
		bool SetLimit(MFnTransform& mfnTrans);
	};


};

