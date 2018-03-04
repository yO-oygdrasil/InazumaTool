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




void BindHumanBody::AddRPIKPole()
{
	MObject selected = BasicFunc::GetSelectedObject(0);
	AddRPIKPole(selected);
}

void BindHumanBody::AddRPIKPole(MObject & middleObject)
{
	MDagPath rootDagPath, middleDagPath, endDagPath;
	if (middleObject.hasFn(MFn::kDagNode))
	{
		MDagPath::getAPathTo(middleObject, middleDagPath);
	}
	
	MFnIkJoint middleJoint(middleDagPath);
	if (middleJoint.parentCount() > 0)
	{
		MDagPath::getAPathTo(middleJoint.parent(0), rootDagPath);
		MFnIkJoint rootJoint(rootDagPath);		
		if (middleJoint.childCount() > 0)
		{
			MDagPath::getAPathTo(middleJoint.child(0), endDagPath);
			MFnIkJoint endJoint(endDagPath);
			MVector rootPos = rootJoint.getTranslation(MSpace::kWorld);
			MVector middlePos = middleJoint.getTranslation(MSpace::kWorld);
			MVector endPos = endJoint.getTranslation(MSpace::kWorld);

			float len0 = (middlePos - rootPos).length();
			float len1 = (endPos - middlePos).length();
			MVector nmPos = (len0*rootPos + len1 * endPos) / (len0 + len1);
			float factor = 2;
			MVector polePos = factor * middlePos - nmPos;

			//MGlobal::displayInfo("gogogo ");
			MString locName = "loc_" + rootJoint.name() + "_" + endJoint.name();
			//MGlobal::displayInfo(locName);
			locName = BasicFunc::CreateLocator(polePos, locName);
			//MFnTransform locTrans(BasicFunc::GetObjectByName(locName));
			//BasicFunc::FreezeTransform(locTrans);
		}
	}

}

void BindHumanBody::AddRPIKPole(MDagPath & rootDagPath, MDagPath & middleDagPath, MDagPath & endDagPath)
{
	MFnTransform rootTrans(rootDagPath), middleTrans(middleDagPath), endTrans(endDagPath);
	MVector rootPos = rootTrans.getTranslation(MSpace::kWorld);
	MVector middlePos = middleTrans.getTranslation(MSpace::kWorld);
	MVector endPos = endTrans.getTranslation(MSpace::kWorld);
	float len0 = (middlePos - rootPos).length();
	float len1 = (endPos - middlePos).length();
	MVector polePos = (len0*rootPos + len1 * endPos) / (len0 + len1);
	//MGlobal::displayInfo("gogogo ");
	MString locName = "loc_" + rootTrans.name() + "_" + endTrans.name();
	locName = BasicFunc::CreateLocator(polePos, locName);
	MFnTransform locTrans(BasicFunc::GetObjectByName(locName));
	BasicFunc::FreezeTransform(locTrans);

}



bool BindHumanBody::BindRPIK()
{
	MSelectionList selected;
	MGlobal::getActiveSelectionList(selected);
	if (selected.length() == 3)
	{
		MDagPath rootObject, endObject, ctlObject;
		selected.getDagPath(0, rootObject);
		selected.getDagPath(1, endObject);
		selected.getDagPath(2, ctlObject);
		BindRPIK(rootObject, endObject, ctlObject);
	}



	return false;
}

bool BindHumanBody::BindRPIK(MDagPath & rootObject, MDagPath & endObject, MDagPath & ctlObject)
{







	return false;
}
