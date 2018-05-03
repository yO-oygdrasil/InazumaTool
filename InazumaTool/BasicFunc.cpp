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

MString BasicFunc::ToCMDSParamStr(MVector vector)
{	
	MString temp;
	temp = vector.x;
	//MGlobal::displayInfo(temp);
	char* str = new char[50];
	sprintf_s(str, 50, "(%f,%f,%f)", vector.x, vector.y, vector.z);
	//std::stringstream ss;
	//ss << "(" << vector.x << "," << vector.y << "," << vector.z << ")";
	MString result = str;// ss.str().c_str();
	//MGlobal::displayInfo(result);
	return result;
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

int BasicFunc::GetSelectedDagPaths(MDagPath ** result)
{
	MSelectionList selected;
	MGlobal::getActiveSelectionList(selected);
	int count = selected.length();
	if (count == 0)
	{
		return 0;
	}
	result = new MDagPath*[count];
	for (int i = 0; i < count; i++)
	{
		MDagPath dagPath;
		selected.getDagPath(i, dagPath);
		result[i] = &dagPath;
	}
	return count;
}



MSelectionList BasicFunc::GetObjectsByName(MString name)
{
	MSelectionList matched;
	MGlobal::getSelectionListByName(name, matched);
	//MGlobal::displayInfo("ask if [" + name + "] exist,result count:" + matched.length());
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

MDagPath BasicFunc::GetDagPathByName(MString name, int index)
{
	MSelectionList matched = GetObjectsByName(name.asChar());
	MDagPath mDagPath;
	if (index < matched.length())
	{
		matched.getDagPath(index, mDagPath);
	}
	else
	{
		/*MString re = "aa";
		re = matched.length();
		MGlobal::displayInfo(name+" count:"+ re);*/
		mDagPath = MDagPath();
	}
	return mDagPath;
}



MDagPath BasicFunc::AddChildCircle(MObject & targetObject)
{
	if (targetObject.hasFn(MFn::kTransform))
	{
		return AddChildCircle(MDagPath::getAPathTo(targetObject));
	}
	else
	{
		return MDagPath();
	}
}

MDagPath BasicFunc::AddChildCircle(MDagPath& targetDagPath)
{
	MString ctlName = "ctl_" + targetDagPath.partialPathName();
	MDagPath ctlDagPath = BasicFunc::CreateCircle(ctlName);
	ctlName = ctlDagPath.fullPathName();
	SetTransformParent(ctlName, targetDagPath.fullPathName());
	MFnTransform circleTransform(ctlDagPath);
	circleTransform.setTranslation(MVector(0, 0, 0), MSpace::kObject);
	circleTransform.setRotation(MEulerRotation(0, 90 / ConstantValue::DPR, 0));
	FreezeTransform(circleTransform);
	return ctlDagPath;
}



MDagPath BasicFunc::AddParentCircle(MObject & targetObject, bool createParallelGrp)
{
	if (targetObject.hasFn(MFn::kTransform))
	{
		return AddParentCircle(MDagPath::getAPathTo(targetObject), createParallelGrp);
	}
	else
	{
		return MDagPath();
	}
}

MDagPath BasicFunc::AddParentCircle(MDagPath & targetDagPath, bool createParallelGrp)
{
	MString ctlName = "ctl_" + targetDagPath.partialPathName();
	MDagPath ctlDagPath = BasicFunc::CreateCircle(ctlName);
	ctlName = ctlDagPath.fullPathName();
	MFnTransform targetTrans(targetDagPath);
	if (createParallelGrp)
	{		
		MFnTransform parellelGrpTrans(AddEmptyGroup(MFnTransform(targetTrans.parent(0)))); 
		parellelGrpTrans.setTranslation(targetTrans.getTranslation(MSpace::kTransform), MSpace::kTransform);
		//MGlobal::displayInfo("finalLocalPos:"+BasicFunc::ToCMDSParamStr(parellelGrpTrans.getTranslation(MSpace::kTransform)));
		parellelGrpTrans.setRotatePivotTranslation(targetTrans.rotatePivotTranslation(MSpace::kTransform), MSpace::kTransform);
		SetTransformParent(ctlName, parellelGrpTrans.fullPathName());
	}

	MFnTransform circleTransform(ctlDagPath);
	circleTransform.setTranslation(MVector(0, 0, 0), MSpace::kTransform);
	circleTransform.setRotation(MEulerRotation(0, 90 / ConstantValue::DPR, 0));
	FreezeTransform(circleTransform);
	return ctlDagPath;
}


bool BasicFunc::CreateLocator(MDagPath& locDagPath,MVector worldPos, MString locatorName)
{
	MString cmdStr = "cmds.spaceLocator(n='" + locatorName + "')";
	//cmdStr += ToCMDSParamStr(worldPos);
	//cmdStr += (")");
	//MGlobal::displayInfo(cmdStr);
	//MGlobal::displayInfo(ToCMDSParamStr(worldPos));
	
	locatorName = SubUShell(MGlobal::executePythonCommandStringResult(cmdStr));
	locDagPath = BasicFunc::GetDagPathByName(locatorName);
	MFnTransform locatorTrans(locDagPath);
	//MGlobal::displayInfo(locatorName+"dag:"+locDagPath.fullPathName());
	locatorTrans.setTranslation(worldPos, MSpace::kWorld);
	return true;
}

MDagPath BasicFunc::CreateCircle(MString ctlName)
{
	MStatus status;
	MString resultStr = MGlobal::executePythonCommandStringResult("cmds.circle(n='" + ctlName + "')", &status);
	if (status == MStatus::kSuccess)
	{
		MStringArray msa = SplitPythonResultStr(resultStr);
		return GetDagPathByName(msa[0]);
	}
	else
	{
		return MDagPath();
	}		
}


MDagPath BasicFunc::CreateCTL_Crystal(MString ctlName)
{
	MString resultName = MGlobal::executePythonCommandStringResult("cmds.curve(n='" + ctlName + "', d=1,\
                   p=[(0, 1, 0), (0, 0, 1), (1, 0, 0), (0, -1, 0), (0, 0, -1),\
                      (1, 0, 0), (0, 1, 0), (0, 0, -1),(-1, 0, 0), (0, -1, 0), \
                      (0, 0, 1), (-1, 0, 0), (0, 1, 0)],\
                   k=[0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12])");
	//MGlobal::displayInfo("circleName_BeforeSub:" + resultName);
	//resultName = SubUShell(resultName);
	//MGlobal::displayInfo("circleName_AfterSub:" + resultName);
	return GetDagPathByName(resultName);
}

MString BasicFunc::CreateRemapValueNode(float inputMin, float inputMax, float outputMin, float outputMax, MFnDependencyNode** dependencyNode)
{
	*dependencyNode = new MFnDependencyNode();
	(*dependencyNode)->create("remapValue");
	//MGlobal::displayInfo("created node:" + (*dependencyNode).absoluteName());
	(*dependencyNode)->findPlug("inputMin").setFloat(inputMin);
	(*dependencyNode)->findPlug("inputMax").setFloat(inputMax);
	(*dependencyNode)->findPlug("outputMin").setFloat(outputMin);
	(*dependencyNode)->findPlug("outputMax").setFloat(outputMax);
	return (*dependencyNode)->absoluteName();
}

void BasicFunc::IterateChidren(int(*func)(MDagPath &), MDagPath & rootNode)
{
	/*if (rootNode != )
	{
		
	}*/

}


MDagPath BasicFunc::AddEmptyGroup(MFnTransform & parent)
{
	return AddEmptyGroup("grp_childrenOf" + parent.partialPathName(), parent.fullPathName());
}

MDagPath BasicFunc::AddEmptyGroup(MString grpName, MString parentName)
{
	MString resultGrpName = MGlobal::executeCommandStringResult("group -em -n " + grpName);
	MDagPath resultGrpDagPath = GetDagPathByName(resultGrpName);
	if (parentName.length()>0)
	{
		MFnTransform resultGrpTrans(resultGrpDagPath);
		SetTransformParent(resultGrpName, parentName);
		ClearTransform(resultGrpTrans);
		FreezeTransform(resultGrpTrans);
	}
	return resultGrpDagPath;
}



void BasicFunc::SetTransformParent(MFnTransform& c, MFnTransform& p)
{	
	SetTransformParent(c.fullPathName(), p.fullPathName());
}

void BasicFunc::SetTransformParent(MString cFullName, MString pFullName)
{	
	MGlobal::executePythonCommand("cmds.parent('" + cFullName + "','" + pFullName + "')",true);
}

void BasicFunc::UnparentTransform(MDagPath & dagPath)
{
	MGlobal::executeCommand("parent -w " + dagPath.fullPathName());
}

void BasicFunc::UnparentTransform(MFnTransform & mfnTrans)
{
	MGlobal::executeCommand("parent -w " + mfnTrans.fullPathName());
}

void BasicFunc::FreezeTransform(MFnTransform& targetTransform)
{	
	MGlobal::executePythonCommand("cmds.makeIdentity('" + targetTransform.fullPathName() + "',apply=True)", true);
}

void BasicFunc::ClearTransform(MFnTransform & targetTransform, bool clearPos, bool clearPivotRot, bool clearPivotScale)
{
	if (clearPos)
	{
		targetTransform.setTranslation(MVector::zero, MSpace::kObject);
	}
	if (clearPivotRot)
	{
		targetTransform.setRotatePivotTranslation(MVector::zero, MSpace::kObject);
	}
	if (clearPivotScale)
	{
		targetTransform.setScalePivotTranslation(MVector::one, MSpace::kObject);
	}
}

MString BasicFunc::SubUShell(MString originStr)
{
	originStr.substitute("[u'", "");
	originStr.substitute("u'", "");
	originStr.substitute("']", "");
	originStr.substitute("'", "");
	originStr.substitute(" ", "");
	originStr.asUTF8();
	return originStr;
}

MStringArray BasicFunc::SplitPythonResultStr(MString pythonStr)
{
	//MGlobal::displayInfo("origin:" + pythonStr);
	MStringArray msa;
	pythonStr.split(',', msa);
	for (int i = 0; i < msa.length(); i++)
	{
		msa[i] = SubUShell(msa[i]);
	}
	return msa;
}






