#pragma once

#include <maya/MGlobal.h>
#include <maya/MPxCommand.h>
#include "BasicFunc.h"
#include <maya/MArgList.h>
#include <sstream>




class TempClass : public MPxCommand { public:MStatus doIt(const MArgList& args); static void* creator(); };

class MPCMap : public MPxCommand 
{ 
public:
	enum MPCType
	{
		Test = 0,
		BindFinger_CTL_L = 1,
		BindFinger_CTL_R = 2,
		AddRPIK = 3,
		AddRPIKPole = 4
	};
	MStatus doIt(const MArgList& args); 
	static void* creator(); 

};
