#include "pluginMain.h"

class TempClass : public MPxCommand
{
public:
	MStatus doIt(const MArgList& args)
	{
		BasicFunc::Print("oooo");
		//cout << "Hello oMaya " << args.asString(0).asChar() << endl;
		return MS::kSuccess;
	}
	static void* creator()
	{
		//std::cout << "test ok" << endl;
		return new TempClass;
	}
};


MStatus initializePlugin(MObject obj)
{
	MFnPlugin plugin(obj, "InazumaTool", "beta", MApiVersion);

	MString totalMenuName = GetMayaWindowName();
	plugin.registerCommand("Print", TempClass::creator);

	plugin.addMenuItem("test1", totalMenuName, "Print", "fuck all");
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

