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

void JointProcess::CreateJointsCurve(MDagPath ** jointDagPaths)
{
	int count;
	if (jointDagPaths == NULL)
	{
		count = BasicFunc::GetSelectedDagPaths(jointDagPaths);
	}
	else
	{
		count = sizeof(jointDagPaths) / sizeof(MDagPath);
	}

	MGlobal::displayInfo("selected count:" + count);
	for (int i = 0; i <count; i++)
	{
		MGlobal::displayInfo((*(jointDagPaths[i])).fullPathName());
	}

}
