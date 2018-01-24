#include "BindHumanBody.h"




bool BindHumanBody::BindFinger(MObject& rootJointObject, MString fingerTag, bool useIK)
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
			return BindFinger(rootJointObject, middleJointObject, finalJointObject, fingerTag, useIK);
		}
	}
	return true;
}

bool BindHumanBody::BindFinger(MObject& rootJointObject, MObject& middleJointObject, MObject& finalJointObject, MString fingerTag, bool useIK)
{
	JointProcess::SetJointLimit(rootJointObject, JointProcess::JointType::FingerRoot);
	JointProcess::SetJointLimit(middleJointObject, JointProcess::JointType::FingerMiddle);
	JointProcess::SetJointLimit(finalJointObject, JointProcess::JointType::FingerMiddle);

	if (useIK)
	{

	}
	else
	{
		MObject ctlObject = BasicFunc::AddChildCircle(rootJointObject);
		MString remapValueNodeName_root = BasicFunc::CreateRemapValueNode(-2, 3, 60, -90);
		MString remapValueNodeName_rootSide = BasicFunc::CreateRemapValueNode(-1, 1, 30, -30);
		MString	remapValueNodeName_middle = BasicFunc::CreateRemapValueNode(-1, 3, 30, -90);
		MString	remapValueNodeName_final = BasicFunc::CreateRemapValueNode(-1, 3, 30, -90);
		MString ctlName = MFnTransform(ctlObject).fullPathName();
		MFnDependencyNode mdn(ctlObject);
		MPlug plug_ty = mdn.findPlug("translateY");
		

	}




	return true;
}
