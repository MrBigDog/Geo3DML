#pragma once
#include "xmlreader.h"
namespace gmml
{
	class Geo3DModel;
	class GeologicFeatureClass;
	class Geo3DMap;
	class Geo3DProject;
}
class GeologicFeatureXMLReader :
	public XMLReader
{
public:
	GeologicFeatureXMLReader(void);
	~GeologicFeatureXMLReader(void);
	gml::AbstractGML* GetGeologicFeature();

	///@brief ��ȡGeologicFeature
	///@curNodeΪ��ǰGeologicFeature�ڵ�
	///@return ����ɹ�����true ���򷵻�false
	///@author yang hongjun
	///@date 2013.11.12
	virtual bool ReadGeologicFeature(xmlNode* geologicFeatureNode);
protected:
	///@brief  �����µ�GeologicFeature����	
	///@param 
	///@return 
	///@author yang hongjun
	///@date   2013.11.12
	void CreateGeologicFeature();
	gml::AbstractGML *GeologicFeature_;
};
