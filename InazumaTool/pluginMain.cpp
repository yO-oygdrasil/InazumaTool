#include "pluginMain.h"

class TempClass : public MPxCommand
{
public:
	MStatus doIt(const MArgList& args)
	{
		cout << "Hello oMaya " << args.asString(0).asChar() << endl;
		return MS::kSuccess;
	}
	static void* creator()
	{
		std::cout << "test ok" << endl;
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
	BasicFunc::Print(menus);
	//MString* menuArr = new MString[1];
	//menuArr[0] = totalMenuName;
	//MStringArray menuArr();	
	//plugin.removeMenuItem(MStringArray(menuArr, 1));
	//MGlobal::executeCommand("print \"unload haha la da fatang\"");
	return MStatus::kSuccess;
}