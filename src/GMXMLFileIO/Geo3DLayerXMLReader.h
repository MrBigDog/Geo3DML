#pragma once
#include "xmlreader.h"
namespace gmml
{
	class Geo3DProjectMetaData;
	class Geo3DMapMetaData;
	class Geo3DMap;
	class Geo3DProject;
}
class GMXMLFILEIO_EXPORT Geo3DLayerXMLReader :
	public XMLReader
{
public:
	Geo3DLayerXMLReader(void);
	~Geo3DLayerXMLReader(void);

	gml::AbstractGML* GetGeoLayer();

	///@brief ��ȡGeoLayer
	///@curNodeΪ��ǰGeoLayer�ڵ�
	///@return ����ɹ�����true ���򷵻�false
	///@author yang hongjun
	///@date 2013.11.07
	virtual bool ReadGeoLayer(xmlNode* geolayerNode);
protected:
	///@brief  �����µ�Geo3DLayer����
	///@param  
	///@return 
	///@author yang hongjun
	///@date   2013.11.07
	void CreateGeoLayer();
	gml::AbstractGML *GeoLayer_;
};