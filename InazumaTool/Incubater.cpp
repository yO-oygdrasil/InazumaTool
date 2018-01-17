#include "Incubater.h"



MString Incubater::CreateCTL_Crystal(MString ctlName = "ctl_sample")
{
	return MGlobal::executePythonCommandStringResult("cmds.curve(n='" + ctlName + "', d=1,\
                   p=[(0, 1, 0), (0, 0, 1), (1, 0, 0), (0, -1, 0), (0, 0, -1),\
                      (1, 0, 0), (0, 1, 0), (0, 0, -1),(-1, 0, 0), (0, -1, 0), \
                      (0, 0, 1), (-1, 0, 0), (0, 1, 0)],\
                   k=[0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12])");

}

MString Incubater::CreateRemapValueNode(float inputMin, float inputMax, float outputMin, float outputMax)
{
	MFnDependencyNode dependencyNode;
	dependencyNode.create("remapValue");
	dependencyNode.findPlug("inputMin").setFloat(inputMin);
	dependencyNode.findPlug("inputMax").setFloat(inputMax);
	dependencyNode.findPlug("outputMin").setFloat(outputMin);
	dependencyNode.findPlug("outputMax").setFloat(outputMax);
	return dependencyNode.absoluteName;
}


