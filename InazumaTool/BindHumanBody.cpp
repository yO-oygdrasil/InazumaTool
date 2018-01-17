#include "BindHumanBody.h"




bool BindHumanBody::BindFinger(MObject& rootJointObject, MString fingerTag, bool useIK = false)
{
	MFnIkJoint rootJoint(rootJointObject);
	
	if (rootJoint.childCount() > 0)
	{
		MObject middleJointObject = rootJoint.child(0);
		MFnIkJoint middleJoint(middleJointObject);
		if (middleJoint.childCount() > 0)
		{
			MObject finalJointObject = middleJoint.child(0);
			MFnIkJoint finalJoint(finalJointObject);
			//enough, start control
			BindFinger(rootJointObject, middleJointObject, finalJointObject, fingerTag, useIK);
		}
	}
	return false;
}

bool BindHumanBody::BindFinger(MObject& rootJoint, MObject& middleJoint, MObject& finalJoint, MString fingerTag, bool useIK = false)
{
	JointProcess::SetJointLimit(rootJoint, JointProcess::JointType::FingerRoot);
	JointProcess::SetJointLimit(middleJoint, JointProcess::JointType::FingerMiddle);
	JointProcess::SetJointLimit(finalJoint, JointProcess::JointType::FingerMiddle);

	if (useIK)
	{

	}
	else
	{

	}




	return true;
}
