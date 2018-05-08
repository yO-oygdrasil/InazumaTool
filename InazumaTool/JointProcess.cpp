#include "JointProcess.h"



bool JointProcess::SetLimit(MFnTransform & mfnTrans, float rxMin, float ryMin, float rzMin, float rxMax, float ryMax, float rzMax, bool inRadian)
{
	if (!inRadian)
	{
		rxMin /= ConstantValue::DPR;
		ryMin /= ConstantValue::DPR;
		rzMin /= ConstantValue::DPR;
		rxMax /= ConstantValue::DPR;
		ryMax /= ConstantValue::DPR;
		rzMax /= ConstantValue::DPR;
	}
	mfnTrans.setLimit(MFnTransform::kRotateMinX, rxMin);
	mfnTrans.setLimit(MFnTransform::kRotateMinY, ryMin);
	mfnTrans.setLimit(MFnTransform::kRotateMinZ, rzMin);
	mfnTrans.setLimit(MFnTransform::kRotateMaxX, rxMax);
	mfnTrans.setLimit(MFnTransform::kRotateMaxY, ryMax);
	mfnTrans.setLimit(MFnTransform::kRotateMaxZ, rzMax);
	mfnTrans.enableLimit(MFnTransform::kRotateMinX, true);
	mfnTrans.enableLimit(MFnTransform::kRotateMinY, true);
	mfnTrans.enableLimit(MFnTransform::kRotateMinZ, true);
	mfnTrans.enableLimit(MFnTransform::kRotateMaxX, true);
	mfnTrans.enableLimit(MFnTransform::kRotateMaxY, true);
	mfnTrans.enableLimit(MFnTransform::kRotateMaxZ, true);
	return true;
}

bool JointProcess::SetJointLimit(MDagPath & mDagPath, JointType jointType)
{
	return SetJointLimit(MFnTransform(mDagPath), jointType);
}

bool JointProcess::SetJointLimit(MObject & mobject, JointType jointType)
{
	if (mobject.hasFn(MFn::kTransform))
	{
		return SetJointLimit(MFnTransform(MDagPath::getAPathTo(mobject)),jointType);
	}
	else
	{
		return false;
	}
}

bool JointProcess::SetJointLimit(MFnTransform & mfnTransform, JointType jointType)
{
	switch (jointType)
	{
	case JointType::Default:
	{
		SetLimit(mfnTransform, -360, -360, -360, 360, 360, 360, false);
		break;
	}
	case JointType::FingerMiddle:
	{
		SetLimit(mfnTransform, 0, 0, -90, 0, 0, 30, false);
		break;
	}
	case JointType::FingerRoot:
	{
		SetLimit(mfnTransform, 0, -30, -90, 0, 30, 60, false);
		break;
	}
	case JointType::Shoulder:
	{
		SetLimit(mfnTransform, -80, -90, -120, 30, 90, 120, false);
		break;	
	}
	default:
	{
		return false;
		//SetLimit(mfnTransform, -360, -360, -360, 360, 360, 360, false);

	}

	}
	return true;
}

//void JointProcess::CreateJointsCurve(MDagPath ** jointDagPaths)
//{
//	int count;
//	bool deleteMemory = false;
//	if (jointDagPaths == NULL)
//	{
//		deleteMemory = true;
//		MDagPath* dagPaths = NULL;
//		jointDagPaths = &dagPaths;
//		//MGlobal::displayInfo("start danger");
//		count = BasicFunc::GetSelectedDagPaths().length();
//		//MString message = "inside size:";
//		//message += (int)(sizeof(*jointDagPaths)/sizeof(MDagPath));
//		//MGlobal::displayInfo(message);
//	}
//	else
//	{
//		count = sizeof(*jointDagPaths) / sizeof(MDagPath);
//	}
//
//	MString msg = "selected count:";
//	msg += std::to_string(count).c_str();
//	MGlobal::displayInfo(msg);
//
//
//	if (jointDagPaths == NULL || count == 0)
//	{
//		MGlobal::displayInfo("ash to ash");
//		return;
//	}
//	/*else
//	{
//		MString message = "outside size:";
//		message += (int)(sizeof(jointDagPaths));
//		MGlobal::displayInfo(message);
//	}*/
//
//
//	MVector *vectors = new MVector[count];
//	for (int i = 0; i < count; i++)
//	{
//		MDagPath dagPath;
//
//		MFnTransform ptTrans((*jointDagPaths)[i]);
//		vectors[i] = ptTrans.getTranslation(MSpace::kWorld);
//		MGlobal::displayInfo(BasicFunc::ToCMDSParamStr(vectors[i]));
//	}
//	MDagPath curveDagPath = BasicFunc::CreateCurve(vectors, "curve_" + (*jointDagPaths)[0].partialPathName() + "_" + (*jointDagPaths)[count - 1].partialPathName());
//	MGlobal::displayInfo("create Finish");
//
//	if (deleteMemory && (*jointDagPaths))
//	{
//		delete[] (*jointDagPaths);
//		jointDagPaths = NULL;
//	}
//}


MDagPath JointProcess::CreateJointsCurve(MSelectionList jointDagPathList)
{
	int count = jointDagPathList.length();
	MString curveName = "curve_";
	MVector *vectors = new MVector[count];
	for (int i = 0; i < count; i++)
	{
		MDagPath dagPath;
		jointDagPathList.getDagPath(i, dagPath);
		if (i == 0)
		{
			curveName += dagPath.partialPathName() + "_";
		}
		else if (i == count - 1)
		{
			curveName += dagPath.partialPathName();
		}
		MFnTransform ptTrans(dagPath);
		vectors[i] = ptTrans.getTranslation(MSpace::kWorld);
		//MGlobal::displayInfo(BasicFunc::ToCMDSParamStr(vectors[i]));
	}
	MDagPath curveDagPath = BasicFunc::CreateCurve(vectors, count, curveName);
	MGlobal::displayInfo("create Finish");

	if (vectors)
	{
		delete[](vectors);
	}

	return curveDagPath;
}

void JointProcess::MakeJointsHairChain(MSelectionList jointDagPaths)
{	
	//begin convert curve to dynamic
	MDagPath curveDagPath = CreateJointsCurve(jointDagPaths);

	MString resultStr = MGlobal::executeCommandStringResult("makeCurvesDynamic 2 {\"0\",\"0\",\"0\",\"1\",\"0\"}");
	MGlobal::displayInfo("message" + resultStr);
}



