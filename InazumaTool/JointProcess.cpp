#include "JointProcess.h"



bool JointProcess::JointLimit::SetLimit(MObject & mobject)
{
	if (mobject.hasFn(MFn::kTransform))
	{
		return SetLimit(MFnTransform(mobject));
	}
	else
	{
		return false;
	}
}

bool JointProcess::JointLimit::SetLimit(MFnTransform & mfnTrans)
{
	mfnTrans.setLimit(MFnTransform::kRotateMinX, min.x);
	mfnTrans.setLimit(MFnTransform::kRotateMinY, min.y);
	mfnTrans.setLimit(MFnTransform::kRotateMinZ, min.z);
	mfnTrans.setLimit(MFnTransform::kRotateMaxX, max.x);
	mfnTrans.setLimit(MFnTransform::kRotateMaxY, max.y);
	mfnTrans.setLimit(MFnTransform::kRotateMaxZ, max.z);
	mfnTrans.enableLimit(MFnTransform::kRotateMinX, true);
	mfnTrans.enableLimit(MFnTransform::kRotateMinY, true);
	mfnTrans.enableLimit(MFnTransform::kRotateMinZ, true);
	mfnTrans.enableLimit(MFnTransform::kRotateMaxX, true);
	mfnTrans.enableLimit(MFnTransform::kRotateMaxY, true);
	mfnTrans.enableLimit(MFnTransform::kRotateMaxZ, true);
	return true;
}

bool JointProcess::SetJointLimit(MObject & mobject, MString jointType)
{
	return false;
}

bool JointProcess::SetJointLimit(MFnTransform & mfnTransform, MString jointType)
{
	return false;
}
