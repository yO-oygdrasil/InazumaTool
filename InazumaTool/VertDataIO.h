#pragma once
#include <fstream>
#include <maya/MGlobal.h>
#include <maya/MString.h>
static class VertDataIO
{
private:
	class VertData
	{
	public:
		VertData(int vCount, int lpv = 1);
		bool SetVertData(int vertIndex, int lineIndex, int eleIndex,float value);
		bool SetVertData(int vertIndex, int lineIndex, float* values);
		bool SetVertData(int vertIndex, int lineIndex, MString valuesStr);
		//at least one (position)
		int linePerVert;
		int vertsCount;
		//float3* pos;
		float*** datas;


	};

public:
	


	static MString ReadFromTextFile(MString filePath);
};

