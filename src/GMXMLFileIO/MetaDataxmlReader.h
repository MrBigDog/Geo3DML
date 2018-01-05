#pragma once
#include "XMLReader.h"


namespace gmml
{
	class Geo3DProjectMetaData;
	class Geo3DMapMetaData;
	class GeoModelMetaData;
	class Geo3DMap;
	class Geo3DProject;
	class GeoModel;
}

class GMXMLFILEIO_EXPORT MetaDataXMLReader: public XMLReader
{
public:
	///@brief ���캯��
	MetaDataXMLReader(void);

	///@brief ��������
	~MetaDataXMLReader(void);

	///@brief  ��ȡGeoProject��Ԫ����
	///@param Geo3DProject* geoproject ��Ԫ���ݶ�Ӧ��Geo3DProject
	///        xmlNode* metadataNode ��Ԫ�������ڵ�XML���
	///@return 
	///@author zhaowei
	///@date   2013.11.1
	void ReadGeoProjectMetaData(gmml::Geo3DProject* geoproject, xmlNode* metadataNode);


	///@brief  ��ȡGeoMap��Ԫ����
	///@param Geo3DMap* geomap ��Ԫ���ݶ�Ӧ��Geo3DMap
	///        xmlNode* metadataNode ��Ԫ�������ڵ�XML���
	///@return 
	///@author zhaowei
	///@date   2013.11.1
	void ReadGeoMapMetaData(gmml::Geo3DMap* geomap, xmlNode* metadataNode);


	///@brief  ��ȡGeoModel��Ԫ����
	///@param GeoModel* geomodel ��Ԫ���ݶ�Ӧ��GeoModel
	///        xmlNode* metadataNode ��Ԫ�������ڵ�XML���
	///@return 
	///@author yang hongjun
	///@date   2013.11.10
	void ReadGeoModelMetaData(gmml::GeoModel* geomodel, xmlNode* metadataNode);

};