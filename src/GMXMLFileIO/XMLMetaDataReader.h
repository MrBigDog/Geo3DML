#ifndef XMLMetaDataReader_h__
#define XMLMetaDataReader_h__

#include "XMLReader.h"
#include <libxml/parser.h>//#include "parser.h"//  [1/5/2018 BigDog]

namespace gmml
{
	class Geo3DProjectMetaData;
	class Geo3DMapMetaData;
	class Geo3DMap;
	class Geo3DProject;
}

class XMLMetaDataReader: public XMLReader
{
public:
	///@brief ���캯��
	XMLMetaDataReader(void);

	///@brief ��������
	~XMLMetaDataReader(void);

	///@brief  ��ȡGeoProject��Ԫ����
	///@params Geo3DProject* geoproject ��Ԫ���ݶ�Ӧ��Geo3DProject
	///        xmlNode* metadataNode ��Ԫ�������ڵ�XML���
	///@return 
	///@author zhaowei
	///@date   2013.11.1
	void ReadGeoProjectMetaData(gmml::Geo3DProject* geoproject, xmlNode* metadataNode);


	///@brief  ��ȡGeoMap��Ԫ����
	///@params Geo3DMap* geomap ��Ԫ���ݶ�Ӧ��Geo3DMap
	///        xmlNode* metadataNode ��Ԫ�������ڵ�XML���
	///@return 
	///@author zhaowei
	///@date   2013.11.1
	void ReadGeoMapMetaData(gmml::Geo3DMap* geomap, xmlNode* metadataNode);
};

#endif // XMLMetaDataReader_h__