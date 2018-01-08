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
	bool SetJointLimit(MObject& mobject, MString jointType);
	bool SetJointLimit(MFnTransform& mfnTrans, MString jointType);


private:
	class JointLimit
	{
	public:
		MVector min, max;
		JointLimit(float rxMin, float ryMin, float rzMin, float rxMax, float ryMax, float rzMax, MString jName = "", bool inRadian = false);
		bool SetLimit(MObject& mobject);
		bool SetLimit(MFnTransform& mfnTrans);
	};
	std::list<JointLimit> limitDictionary;// = { new JointLimit(};
	

};

