#include "VertDataIO.h"

MString VertDataIO::ReadFromTextFile(MString filePath)
{
	std::ifstream inFile;
	inFile.open(filePath.asChar());
	if (!inFile)
	{
		MGlobal::displayInfo("file path: " + filePath + " error");
		return MString();
	}
	int vCount,lpv;
	inFile >> vCount >> lpv;
	MGlobal::displayInfo(vCount + "," + lpv);
	VertData vdi = VertData(vCount, lpv);

	//int currentVertIndex = 0;
	std::string line;
	/*for (int i = 0; i < vCount; i++)
	{
		for (int j = 0; j < lpv; j++)
		{
			vdi.SetVertData(i,j,)
		}
	}*/



	return MString();
}

VertDataIO::VertData::VertData(int vCount, int lpv)
{
	linePerVert = lpv;
	vertsCount = vCount;
	//pos = new float3[vCount];
	datas = new float**[vCount];
	for (int i = 0; i < vCount; i++)
	{
		datas[i] = new float*[linePerVert];
	}
	
}

bool VertDataIO::VertData::SetVertData(int vertIndex, int lineIndex, int eleIndex,float value)
{
	if (vertIndex < vertsCount && lineIndex < linePerVert)
	{
		int eleCount = sizeof(datas[vertIndex][lineIndex]) / sizeof(float);
		if (eleIndex < eleCount)
		{
			datas[vertIndex][lineIndex][eleIndex] = value;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool VertDataIO::VertData::SetVertData(int vertIndex, int lineIndex, float * values)
{
	if (vertIndex < vertsCount && lineIndex < linePerVert)
	{
		datas[vertIndex][lineIndex] = values;
		return true;
	}
	else
	{
		return false;
	}
}

bool VertDataIO::VertData::SetVertData(int vertIndex, int lineIndex, MString valuesStr)
{	
	MStringArray sa;
	valuesStr.split(' ', sa);
	int count = sa.length();
	float* values = new float[count];
	for (int i = 0; i < count; i++)
	{
		values[i] = sa[i].asFloat();
	}	
	return SetVertData(vertIndex, lineIndex, values);
}
