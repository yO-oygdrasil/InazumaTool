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
		MFnDependencyNode *dn_root, *dn_rootSide, *dn_middle, *dn_final;
		MString remapValueNodeName_root = BasicFunc::CreateRemapValueNode(-2, 3, 60, -90, dn_root);
		MString remapValueNodeName_rootSide = BasicFunc::CreateRemapValueNode(-1, 1, 30, -30, dn_rootSide);
		MString	remapValueNodeName_middle = BasicFunc::CreateRemapValueNode(-1, 3, 30, -90, dn_middle);
		MString	remapValueNodeName_final = BasicFunc::CreateRemapValueNode(-1, 3, 30, -90, dn_final);
		MString ctlName = ctlDagPath.fullPathName();
		MFnDependencyNode mdn(ctlDagPath.node());
		MPlug plug_ty = mdn.findPlug("translateY");

		/*MDagModifier *dagModifier = new MDagModifier();
		dagModifier->connect(mdn.findPlug("translateY"), dn_root->findPlug("inputValue"));*/
		MDagModifier dagModifier;
		dagModifier.connect(mdn.findPlug("translateY"), dn_root->findPlug("inputValue"));
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






bool BindHumanBody::BindRPIK(MDagPath* ikDagPath)
{
	MSelectionList selected;
	MGlobal::getActiveSelectionList(selected);
	if (selected.length() == 3)
	{
		MDagPath rootObject, endObject, ctlObject;
		selected.getDagPath(0, rootObject);
		selected.getDagPath(1, endObject);
		selected.getDagPath(2, ctlObject);
		return BindRPIK(rootObject, endObject, ctlObject, ikDagPath);
	}
	else if (selected.length() == 2)
	{
		MDagPath rootObject, endObject;
		selected.getDagPath(0, rootObject);
		selected.getDagPath(1, endObject);
		return BindRPIK(rootObject, endObject, ikDagPath);
	}
	else
	{
		return false;
	}
}

bool BindHumanBody::BindRPIK(MDagPath & rootDagPath, MDagPath & endDagPath, MDagPath* ikDagPath)
{
	MDagPath ctlDagPath = BasicFunc::AddChildCircle(endDagPath);
	BasicFunc::UnparentTransform(ctlDagPath);
	BasicFunc::FreezeTransform(MFnTransform(ctlDagPath));
	return BindRPIK(rootDagPath, endDagPath, ctlDagPath, ikDagPath);
}

bool BindHumanBody::BindRPIK(MDagPath & rootDagPath, MDagPath & endDagPath, MDagPath & ctlDagPath, MDagPath* ikDagPath)
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
	MString resultStr = MGlobal::executePythonCommandStringResult("cmds.ikHandle(sj='" + rootDagPath.fullPathName() + "',ee='" + endDagPath.fullPathName() + "',sol='ikRPsolver',n='ik_" + rootDagPath.partialPathName() + "_" + endDagPath.partialPathName() + "')");
	
	//[u'ik_joint1_joint4', u'effector1']
	MStringArray msa = BasicFunc::SplitPythonResultStr(resultStr);
	//MGlobal::displayInfo(resultStr);
	/*for (int i = 0; i < msa.length(); i++)
	{
		MGlobal::displayInfo(msa[i]);
	}*/
	/*MGlobal::displayInfo("ikName:" + msa[0]);
	ikDagPath = &(BasicFunc::GetDagPathByName(msa[0]));
	if (ikDagPath != NULL)
	{
		MGlobal::displayInfo(ikDagPath->fullPathName());
	}*/
	MDagPath middleObject = MDagPath::getAPathTo(rootDagPath.child(0));
	MDagPath locDagPath;
	if (AddRPIKPole(locDagPath, middleObject))
	{
		BasicFunc::FreezeTransform(MFnTransform(locDagPath));
		//begin to add constriant
		MString poleConstraintResult = MGlobal::executeCommandStringResult("poleVectorConstraint " + locDagPath.fullPathName() + " " + msa[0]);
		//MGlobal::displayInfo(poleConstraintResult);
		MGlobal::executeCommandStringResult("pointConstraint " + ctlDagPath.fullPathName() + " " + msa[0]);

	}
	
	return true;
}

bool BindHumanBody::AddReverseFootBone(MDagPath **reverseBones)
{
	MSelectionList selected;
	MGlobal::getActiveSelectionList(selected);
	if (selected.length() == 3)
	{
		MDagPath rootObject, endObject, ctlObject;
		selected.getDagPath(0, rootObject);
		selected.getDagPath(1, endObject);
		selected.getDagPath(2, ctlObject);
		return AddReverseFootBone(rootObject, endObject, ctlObject, reverseBones);
	}
	return false;
}


bool BindHumanBody::AddReverseFootBone(MDagPath & rootDagPath, MDagPath & middleDagPath, MDagPath & endDagPath, MDagPath **reverseBones)
{
	//啊啊
	//*reverseBones = new MDagPath[8];
	MDagPath* result = new MDagPath[8];
	*reverseBones = result;

	MFnIkJoint rootJoint;
	MVector rootPos = MFnTransform(rootDagPath).getTranslation(MSpace::kWorld);
	MVector middlePos = MFnTransform(middleDagPath).getTranslation(MSpace::kWorld);
	MVector endPos = MFnTransform(endDagPath).getTranslation(MSpace::kWorld);
	//MGlobal::displayInfo("root:" + BasicFunc::ToCMDSParamStr(rootPos) + " middle:" + BasicFunc::ToCMDSParamStr(middlePos) + " end:" + BasicFunc::ToCMDSParamStr(endPos));
	
	MObject jt_ankle_Object = rootJoint.create();
	result[0] = MDagPath::getAPathTo(jt_ankle_Object);
	MFnIkJoint jt_ankle(result[0]);
	jt_ankle.setTranslation(rootPos, MSpace::kWorld);
	
	MObject jt_heel_Object = rootJoint.create(jt_ankle_Object);
	result[1] = MDagPath::getAPathTo(jt_heel_Object);
	MFnIkJoint jt_heel(result[1]);
	jt_heel.setTranslation(MVector(rootPos.x, endPos.y, rootPos.z), MSpace::kWorld);

	MObject jt_side_Object = rootJoint.create(jt_heel_Object);
	result[2] = MDagPath::getAPathTo(jt_side_Object);
	MFnIkJoint jt_side(result[2]);
	float sideFactor = 0.6 * (middlePos - endPos).length() / abs(middlePos.z);
	jt_side.setTranslation(MVector(middlePos.x, endPos.y, middlePos.z*(1+sideFactor)), MSpace::kWorld);

	MObject jt_front_Object = rootJoint.create(jt_side_Object);
	result[3] = MDagPath::getAPathTo(jt_front_Object);
	MFnIkJoint jt_front(result[3]);
	jt_front.setTranslation(endPos, MSpace::kWorld);

	MObject jt_middleF_Object = rootJoint.create(jt_front_Object);
	result[4] = MDagPath::getAPathTo(jt_middleF_Object);
	MFnIkJoint jt_middleF(result[4]);
	jt_middleF.setTranslation(middlePos, MSpace::kWorld);

	MObject jt_middleB_Object = rootJoint.create(jt_front_Object);
	result[5] = MDagPath::getAPathTo(jt_middleB_Object);
	MFnIkJoint jt_middleB(result[5]);
	jt_middleB.setTranslation(middlePos, MSpace::kWorld);
	
	MObject jt_toe_Object = rootJoint.create(jt_middleF_Object);
	result[6] = MDagPath::getAPathTo(jt_toe_Object);
	MFnIkJoint jt_toe(result[6]);
	jt_toe.setTranslation(endPos, MSpace::kWorld);

	MObject jt_ankleIn_Object = rootJoint.create(jt_middleB_Object);
	result[7] = MDagPath::getAPathTo(jt_ankleIn_Object);
	MFnIkJoint jt_ankleIn(result[7]);
	jt_ankleIn.setTranslation(rootPos, MSpace::kWorld);

	MGlobal::displayInfo("create joints ok");
	
	return true;
}

bool BindHumanBody::BindReverseFootRPIK()
{
	MSelectionList selected;
	MGlobal::getActiveSelectionList(selected);
	if (selected.length() == 4)
	{
		MDagPath legRootDagPath, ankleDagPath, middleDagPath, endDagPath;
		selected.getDagPath(0, legRootDagPath);
		selected.getDagPath(1, ankleDagPath);
		selected.getDagPath(2, middleDagPath);
		selected.getDagPath(3, endDagPath);
		return BindReverseFootRPIK(legRootDagPath, ankleDagPath, middleDagPath, endDagPath);
	}
	return false;
}

bool BindHumanBody::BindReverseFootRPIK(MDagPath & legRootDagPath, MDagPath & ankleDagPath, MDagPath & middleDagPath, MDagPath & endDagPath)
{
	//ypa
	//create reverseBones
	MDagPath *rbs = NULL;
	if (!AddReverseFootBone(ankleDagPath, middleDagPath, endDagPath, &rbs))
	{
		return false;
	}

	MGlobal::displayInfo(rbs[7].fullPathName());
	MDagPath ikDagPath;
	//int count = sizeof(rbs) / sizeof(MDagPath);
	BindRPIK(legRootDagPath, ankleDagPath, rbs[7], &ikDagPath);
	MGlobal::executeCommandStringResult("orientConstraint -mo " + rbs[4].fullPathName() + " " + middleDagPath.fullPathName());
	MGlobal::executeCommandStringResult("orientConstraint -mo " + rbs[5].fullPathName() + " " + ankleDagPath.fullPathName());



	return true;
}


