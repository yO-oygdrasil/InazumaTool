#include "pluginMain.h"


MStatus initializePlugin(MObject obj)
{
	MFnPlugin plugin(obj, "InazumaTool", "beta", MApiVersion);

	MString totalMenuName = GetMayaWindowName();
	//MGlobal::displayInfo("Total Menu Name:" + totalMenuName);
	plugin.registerCommand("InazumaCommand", MPCMap::creator);


	MString paramStr;//never do [MString str = (int)], must be two line
					 //std::to_string((int)MPCMap::MPCType::BindFinger_CTL_L).c_str();
					 //int intValue = (int)MPCMap::MPCType::Test;
	paramStr = MPCMap::MPCType::Test;
	plugin.addMenuItem("Test", totalMenuName, "InazumaCommand", paramStr);

	MString subMenuName_bodyBind = AddSubMenu(totalMenuName, "Body Bind",true);
	MString subMenuName_create= AddSubMenu(totalMenuName, "Create",true);




	paramStr = MPCMap::MPCType::AddRPIK;
	plugin.addMenuItem("add rpik", subMenuName_bodyBind, "InazumaCommand", paramStr);

	paramStr = (int)MPCMap::MPCType::AddRPIKPole;
	plugin.addMenuItem("add rpik pole", subMenuName_create, "InazumaCommand", paramStr);

	paramStr = MPCMap::MPCType::CreateCTL_CrysTal;
	plugin.addMenuItem("create cystal ctl", subMenuName_create, "InazumaCommand", paramStr);

	paramStr = MPCMap::MPCType::AddChildCtl;
	plugin.addMenuItem("add child ctl", subMenuName_create, "InazumaCommand", paramStr);

	paramStr = MPCMap::MPCType::AddParentCtl;
	plugin.addMenuItem("add parent ctl", subMenuName_create, "InazumaCommand", paramStr);

	paramStr = MPCMap::MPCType::AddReverseFootBones;
	plugin.addMenuItem("add reverse foot bones", subMenuName_create, "InazumaCommand", paramStr);

	paramStr = MPCMap::MPCType::BindReverseFootRPIK;
	plugin.addMenuItem("Bind Reverse Foot RPIK", subMenuName_bodyBind, "InazumaCommand", paramStr);

	paramStr = MPCMap::MPCType::BindFinger_CTL_L;
	plugin.addMenuItem("Bind Finger using CTL L", subMenuName_bodyBind, "InazumaCommand", paramStr);
	

	return MStatus::kSuccess;
}

MString totalMenuName;
MString GetMayaWindowName()
{
	MGlobal::executePythonCommand("import maya.cmds as cmds");
	totalMenuName = MGlobal::executePythonCommandStringResult("cmds.menu(parent=mel.eval('$temp1=$gMainWindow'), label='InazumaTool',tearOff = True)");
	return totalMenuName;
}

MString AddSubMenu(MString parentMenuName,MString labelStr,bool tearOff)
{
	MGlobal::executePythonCommand("import maya.cmds as cmds");
	MString subMenuName = MGlobal::executePythonCommandStringResult((tearOff?"cmds.menuItem(tearOff = True, parent='":"cmds.menuItem(parent='") + parentMenuName + "',subMenu = True, label='" + labelStr + "')");
	return subMenuName;
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

