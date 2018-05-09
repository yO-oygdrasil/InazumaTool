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
			JointProcess::MakeJointsHairChain(BasicFunc::GetSelectedDagPaths());
			break;
		}
		case MPCType::BindFinger_CTL_L:
		{
			BindHumanBody::BindFinger(BasicFunc::GetSelectedDagPath(0), "test", false);
			break;
		}
		case MPCType::BindFinger_CTL_R:
		{
			MGlobal::displayInfo("oh my god it works333");
			break;
		}
		case MPCType::AddRPIK:
		{
			BindHumanBody::BindRPIK();
			break;
		}
		case MPCType::AddRPIKPole:
		{
			MDagPath locDagPath;
			BindHumanBody::AddRPIKPole(locDagPath);
			MGlobal::displayInfo("add rpik pole loc");
			break;
		}
		case MPCType::AddChildCtl:
		{
			BasicFunc::AddChildCircle(BasicFunc::GetSelectedDagPath(0));
			break;
		}
		case MPCType::AddParentCtl:
		{
			BasicFunc::AddParentCircle(BasicFunc::GetSelectedDagPath(0), true);
			break;
		}
		case MPCType::CreateCTL_CrysTal:
		{
			BasicFunc::CreateCTL_Crystal("ctl_sample");
			break;
		}
		case MPCType::AddReverseFootBones:
		{
			BindHumanBody::AddReverseFootBone();
			break;
		}
		case MPCType::BindReverseFootRPIK:
		{
			BindHumanBody::BindReverseFootRPIK();
			break;
		}
		case MPCType::CreateJointsCurve:
		{
			JointProcess::CreateJointsCurve(BasicFunc::GetSelectedDagPaths());
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
