#include "pluginMain.h"


MStatus initializePlugin(MObject obj)
{
	MFnPlugin plugin(obj, "InazumaTool", "beta", MApiVersion);

	MString totalMenuName = GetMayaWindowName();
	plugin.registerCommand("InazumaCommand", MPCMap::creator);
	MString paramStr;//never do [MString str = (int)], must be two line
	//std::to_string((int)MPCMap::MPCType::BindFinger_CTL_L).c_str();
	//int intValue = (int)MPCMap::MPCType::Test;
	paramStr = MPCMap::MPCType::AddRPIK;
	plugin.addMenuItem("add rpik", totalMenuName, "InazumaCommand", paramStr);
	paramStr = (int)MPCMap::MPCType::AddRPIKPole;
	plugin.addMenuItem("add rpik pole", totalMenuName, "InazumaCommand", paramStr);
	paramStr = MPCMap::MPCType::CreateCTL_CrysTal;
	plugin.addMenuItem("create cystal ctl", totalMenuName, "InazumaCommand", paramStr);
	paramStr = MPCMap::MPCType::AddChildCtl;
	plugin.addMenuItem("add child ctl", totalMenuName, "InazumaCommand", paramStr);
	paramStr = MPCMap::MPCType::AddReverseFootBones;
	plugin.addMenuItem("add reverse foot bones", totalMenuName, "InazumaCommand", paramStr);
	return MStatus::kSuccess;
}

MString totalMenuName;
MString GetMayaWindowName()
{
	MGlobal::executePythonCommand("import maya.cmds as cmds");
	totalMenuName = MGlobal::executePythonCommandStringResult("cmds.menu(parent=mel.eval('$temp1=$gMainWindow'), label='InazumaTool')");
	return totalMenuName;
}

MStatus uninitializePlugin(MObject obj)
{
	//MString totalMenuName = GetMayaWindowName();
	MFnPlugin plugin(obj);
	plugin.deregisterCommand("Print");
	
	MString menus = MGlobal::executePythonCommandStringResult("cmds.window(mel.eval('$temp1=$gMainWindow'), q=True, menuArray=True)");
	//BasicFunc::Print(menus);
	menus.substituteFirst("[", "");
	menus.substitute("]", "");
	MStringArray menuNames;
	menus.split(',', menuNames);
	for (int i = 0; i < menuNames.length(); i++)
	{
		//BasicFunc::Print(menuNames[i]); 
		MString labelName = MGlobal::executePythonCommandStringResult("cmds.menu(" + menuNames[i] + ",q=True,label=True)");
		if (labelName == "InazumaTool")
		{
			MGlobal::executePythonCommand("cmds.deleteUI(" + menuNames[i] + ",m=True)");
		}
	}

	return MStatus::kSuccess;
}

