#pragma once
#include "xmlreader.h"
namespace gmml
{
	class Geo3DModel;
	class GeologicFeatureClass;
	class Geo3DMap;
	class Geo3DProject;
}
class GMXMLFILEIO_EXPORT GeoFeatureXMLReader :
	public XMLReader
{
public:
	GeoFeatureXMLReader(void);
	~GeoFeatureXMLReader(void);
	gml::AbstractGML* GetGeoFeature();

	///@brief ��ȡGeologicFeature
	///@param curNodeΪ��ǰGeologicFeature�ڵ�
	///@return ����ɹ�����true ���򷵻�false
	///@author yang hongjun
	///@date 2013.11.12
	virtual bool ReadNode(xmlNode* geoFeatureNode);
protected:
	// Read geometry Object
	bool ReadMappedFeature(xmlNode* geoNode);

	///@brief  �����µ�GeologicFeature����
	///@param 
	///@return 
	///@author yang hongjun
	///@date   2013.11.12
	void CreateGeoFeature();	
};
