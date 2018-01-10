#include "BasicFunc.h"


void BasicFunc::SetTranslateLimit(MObject & mObject, float minX, float minY, float minZ, float maxX, float maxY, float maxZ)
{
	MFnTransform mfnTransform(mObject);
	SetTranslateLimit(mfnTransform, minX, minY, minZ, maxX, maxY, maxZ);
}

void BasicFunc::SetTranslateLimit(MFnTransform & mfnTrans, float minX, float minY, float minZ, float maxX, float maxY, float maxZ)
{
	mfnTrans.enableLimit(MFnTransform::LimitType::kTranslateMinX, true);
	mfnTrans.enableLimit(MFnTransform::LimitType::kTranslateMinY, true);
	mfnTrans.enableLimit(MFnTransform::LimitType::kTranslateMinZ, true);
	mfnTrans.enableLimit(MFnTransform::LimitType::kTranslateMaxX, true);
	mfnTrans.enableLimit(MFnTransform::LimitType::kTranslateMaxY, true);
	mfnTrans.enableLimit(MFnTransform::LimitType::kTranslateMaxZ, true);
	mfnTrans.setLimit(MFnTransform::LimitType::kTranslateMinX, minX);
	mfnTrans.setLimit(MFnTransform::LimitType::kTranslateMinY, minY);
	mfnTrans.setLimit(MFnTransform::LimitType::kTranslateMinZ, minZ);
	mfnTrans.setLimit(MFnTransform::LimitType::kTranslateMaxX, maxX);
	mfnTrans.setLimit(MFnTransform::LimitType::kTranslateMaxY, maxY);
	mfnTrans.setLimit(MFnTransform::LimitType::kTranslateMaxZ, maxZ);
}

MObject BasicFunc::GetSelectedObject(int index)
{
	MSelectionList selected;
	MGlobal::getActiveSelectionList(selected);



	return MObject();
}
