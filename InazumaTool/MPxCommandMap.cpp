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
			MFnTransform selected(BasicFunc::GetSelectedDagPath(0));
			MStatus success = MStatus();
			MVector worldPos = selected.getTranslation(MSpace::kWorld, &success);
			if (success == MStatus::kSuccess)
			{
				MGlobal::displayInfo("success");
			}
			else
			{
				MGlobal::displayInfo("failure");
			}
			//selected.setTranslation(worldPos, MSpace::kWorld);
			MGlobal::displayInfo("selected object worldPos:" + BasicFunc::ToCMDSParamStr(worldPos));
			MGlobal::displayInfo("hahaha");
			break;
		}
		case MPCType::BindFinger_CTL_L:
		{
			BindHumanBody::AddRPIKPole();
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
			MGlobal::displayInfo("the holy one has fallen");
			BindHumanBody::BindRPIK();
			break;
		}
		case MPCType::AddRPIKPole:
		{
			BindHumanBody::AddRPIKPole();
			MGlobal::displayInfo("add rpik pole loc");
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
