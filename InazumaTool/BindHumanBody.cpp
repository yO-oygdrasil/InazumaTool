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
		MDagPath ctlDagPath = BasicFunc::AddChildCircle(rootJointObject);
		MString remapValueNodeName_root = BasicFunc::CreateRemapValueNode(-2, 3, 60, -90);
		MString remapValueNodeName_rootSide = BasicFunc::CreateRemapValueNode(-1, 1, 30, -30);
		MString	remapValueNodeName_middle = BasicFunc::CreateRemapValueNode(-1, 3, 30, -90);
		MString	remapValueNodeName_final = BasicFunc::CreateRemapValueNode(-1, 3, 30, -90);
		MString ctlName = ctlDagPath.fullPathName();
		MFnDependencyNode mdn(ctlDagPath.node());
		MPlug plug_ty = mdn.findPlug("translateY");

	}
	return true;
}




bool BindHumanBody::AddRPIKPole(MDagPath& locDagPath)
{
	MObject selected = BasicFunc::GetSelectedObject(0);
	return AddRPIKPole(locDagPath,selected);
}

bool BindHumanBody::AddRPIKPole(MDagPath& locDagPath, MObject & middleObject)
{
	MDagPath middleDagPath;
	if (middleObject.hasFn(MFn::kDagNode))
	{
		MDagPath::getAPathTo(middleObject, middleDagPath);
	}
	return AddRPIKPole(locDagPath, middleDagPath);
}

bool BindHumanBody::AddRPIKPole(MDagPath & locDagPath, MDagPath & middleDagPath)
{
	MDagPath rootDagPath, endDagPath;
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

			MString locName = "loc_" + rootJoint.name() + "_" + endJoint.name();
			return BasicFunc::CreateLocator(locDagPath, polePos, locName);
		}
	}
	return false;
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
		return BindRPIK(rootObject, endObject, ctlObject);
	}
	else
	{
		return false;
	}
}

bool BindHumanBody::BindRPIK(MDagPath & rootObject, MDagPath & endObject, MDagPath & ctlObject)
{
	/*MFnIkHandle* ikHandle = new MFnIkHandle;
	MStatus status;
	ikHandle->create(rootObject, endObject, &status);
	
	if (status == MStatus::kSuccess)
	{
		MGlobal::displayInfo("successsssssss" + ikHandle->name());
	}
	ikHandle->findPlug("");
	MFnIkSolver solver(ikHandle->solver());*/
	//solver

	//MString resultStr = MGlobal::executeCommandStringResult("ikHandle -sj " + rootObject.fullPathName() + " -ee " + endObject.fullPathName() + " -sol ikRPsolver -n ik_" + rootObject.partialPathName() + "_" + endObject.partialPathName(),true);
	MString resultStr = MGlobal::executePythonCommandStringResult("cmds.ikHandle(sj='" + rootObject.fullPathName() + "',ee='" + endObject.fullPathName() + "',sol='ikRPsolver',n='ik_" + rootObject.partialPathName() + "_" + endObject.partialPathName() + "')");
	
	//[u'ik_joint1_joint4', u'effector1']
	MStringArray msa = BasicFunc::SplitPythonResultStr(resultStr);
	//MGlobal::displayInfo(resultStr);
	for (int i = 0; i < msa.length(); i++)
	{
		MGlobal::displayInfo(msa[i]);
	}


	MDagPath middleObject = MDagPath::getAPathTo(rootObject.child(0));
	MDagPath locDagPath;
	if (AddRPIKPole(locDagPath, middleObject))
	{
		//begin to add constriant
		MString poleConstraintResult = MGlobal::executeCommandStringResult("poleVectorConstraint " + locDagPath.fullPathName() + " " + msa[0]);
		MGlobal::displayInfo(poleConstraintResult);
	}
	
	
	return true;
}


