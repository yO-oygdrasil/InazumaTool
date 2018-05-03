#pragma once
#include "BasicFunc.h"
//#include <maya/MSimple.h>
#include <maya/MGlobal.h>
#include <maya/MFnPlugin.h>
#include <maya/MIOStream.h>
#include <maya/MArgList.h>
#include <maya/MStringArray.h>
#include <sstream>
#include "MPxCommandMap.h"

MString GetMayaWindowName();

MString AddSubMenu(MString parentMenuName, MString labelStr, bool tearOff = false);




//DeclareSimpleCommand(Print, "yO_oygdrasil", "beta")