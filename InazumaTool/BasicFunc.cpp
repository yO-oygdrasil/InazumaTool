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
	MObject mObject;
	if (index < selected.length())
	{
		selected.getDependNode(index, mObject);
	}
	else
	{
		mObject = MObject();
	}
	return mObject;
}

MDagPath BasicFunc::GetSelectedDagPath(int index)
{
	MSelectionList selected;
	MGlobal::getActiveSelectionList(selected);
	MDagPath dagPath;
	if (index < selected.length())
	{
		selected.getDagPath(index, dagPath);
	}
	else
	{
		dagPath = MDagPath();
	}
	return dagPath;
}



//void BasicFunc::PrintMVector(MVector vec)
//{
//	//may be not useful, mo le
//
//}

//void BasicFunc::Print(MString str)
//{
//	MGlobal::displayInfo(str);
//	//cout << str << endl;
//	//MGlobal::executePythonCommand("print '" + str + "'");
//}



MSelectionList BasicFunc::GetObjectsByName(MString name)
{
	MSelectionList matched;
	MGlobal::getSelectionListByName(name, matched);
	return matched;
}

MObject BasicFunc::GetObjectByName(MString name, int index)
{
	MSelectionList matched = GetObjectsByName(name);
	MObject mObject;
	if (index < matched.length())
	{
		matched.getDependNode(index, mObject);
	}
	else
	{
		mObject = MObject();
	}
	return mObject;
}

MObject BasicFunc::AddChildCircle(MObject& targetObject)
{
	MFnTransform targetTransform(targetObject);
	MString ctlName = "ctl_" + targetTransform.name();
	ctlName = BasicFunc::CreateCTL_Crystal(ctlName);
	SetTransformParent(ctlName, targetTransform.fullPathName());
	MObject circleObject = BasicFunc::GetObjectByName(ctlName);
	MFnTransform circleTransform(circleObject);
	circleTransform.setTranslation(MVector(0, 0, 0), MSpace::kObject);
	circleTransform.setRotation(MEulerRotation(0, 90 / ConstantValue::DPR, 0));
	FreezeTransform(circleTransform);
	return circleObject;
}

MString BasicFunc::CreateCTL_Crystal(MString ctlName)
{
	return MGlobal::executePythonCommandStringResult("cmds.curve(n='" + ctlName + "', d=1,\
                   p=[(0, 1, 0), (0, 0, 1), (1, 0, 0), (0, -1, 0), (0, 0, -1),\
                      (1, 0, 0), (0, 1, 0), (0, 0, -1),(-1, 0, 0), (0, -1, 0), \
                      (0, 0, 1), (-1, 0, 0), (0, 1, 0)],\
                   k=[0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12])");

}

MString BasicFunc::CreateRemapValueNode(float inputMin, float inputMax, float outputMin, float outputMax)
{
	MFnDependencyNode dependencyNode;
	dependencyNode.create("remapValue");
	dependencyNode.findPlug("inputMin").setFloat(inputMin);
	dependencyNode.findPlug("inputMax").setFloat(inputMax);
	dependencyNode.findPlug("outputMin").setFloat(outputMin);
	dependencyNode.findPlug("outputMax").setFloat(outputMax);
	return dependencyNode.absoluteName();
}


void BasicFunc::SetTransformParent(MFnTransform& c, MFnTransform& p)
{	
	SetTransformParent(c.fullPathName(), p.fullPathName());
}

void BasicFunc::SetTransformParent(MString cFullName, MString pFullName)
{
	MGlobal::executePythonCommand("cmds.parent(" + cFullName + "," + pFullName + "))");
}

void BasicFunc::FreezeTransform(MFnTransform& targetTransform)
{
	MGlobal::executePythonCommand("cmds.makeIdentity(" + targetTransform.fullPathName() + ",apply=True");
}





