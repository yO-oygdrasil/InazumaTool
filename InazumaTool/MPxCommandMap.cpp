#include "MPxCommandMap.h"

MStatus TempClass::doIt(const MArgList& args)
{
	MGlobal::displayInfo("oooo");
	return MS::kSuccess;
}
void* TempClass::creator() { return new TempClass; }

MStatus MPCMap::doIt(const MArgList & args)
{
	MGlobal::displayInfo("at least it enters");
	if (args.length() == 0)
	{
		MGlobal::displayInfo("no param!");
		return MStatus::kFailure;
	}
	int type = args.asInt(0);
	//MString param = (std::to_string(type)).c_str();
	//BasicFunc::Print("value:" + param);
	if (args.get(0, type) == MStatus::kSuccess)
	{
		MPCType mpcType = (MPCType)type;

		switch (mpcType)
		{
		case MPCType::Test:
		{
			MGlobal::displayInfo("oh my god it works");
			break;
		}
		case MPCType::BindFinger_CTL_L:
		{
			MGlobal::displayInfo("oh my god it works222");
			break;
		}
		case MPCType::BindFinger_CTL_R:
		{
			MGlobal::displayInfo("oh my god it works333");
			break;
		}
		case MPCType::AddRPIK:
		{
			MGlobal::displayInfo("oh my god it works444");
			break;
		}
		case MPCType::AddRPIKPole:
		{
			MGlobal::displayInfo("oh my god it works555");
			break;
		}

		}
	}
	else
	{
		MGlobal::displayInfo("sad story");
		return MStatus::kFailure;
	}
	return MStatus::kSuccess;
}

void * MPCMap::creator()
{
	return new MPCMap;
}
