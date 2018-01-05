#pragma once
#include "xmlreader.h"
namespace gmml
{
	class Geo3DProjectMetaData;
	class Geo3DMapMetaData;
	class Geo3DMap;
	class Geo3DProject;
	class Geo3DLayer;
}

namespace se
{
	class FeatureStyleRule;
	class CoverageStyleRule;
	class GeoSymbolizer;
	class RasterSymbolizer;

}

class GMXMLFILEIO_EXPORT Geo3DStyleXMLReader :
	public XMLReader
{
public:
	///@brief  ���캯��
	Geo3DStyleXMLReader(void);

	///@brief  ��������
	~Geo3DStyleXMLReader(void);

	///@brief  ��ȡGeo3DStyle���
	gml::AbstractGML* GetGeo3DStyle();

	///@brief ��ȡGeo3DStyle�ڵ�
	///@param geo3DstyleNodeΪGeo3DStyle�Ľڵ�
	///@author yang hongjun
	///@author zhaowei
	///@date 2013.11.13
	///@date 2013.11.14
	virtual bool ReadGeo3DStyle(xmlNode* geo3DstyleNode);

protected:
	bool ReadCoverageSymbolizer(se::CoverageStyleRule* rule, xmlNode* geo3DstyleNode);
	bool ReadRasterSymbolizer(se::CoverageStyleRule* rule, xmlNode* geo3DstyleNode);
	bool ReadSymbolizer(se::FeatureStyleRule* rule, xmlNode* geo3DstyleNode);
	bool ReadFilter(se::FeatureStyleRule* rule, xmlNode* geo3DstyleNode);
	bool ReadCoverageFilter(se::CoverageStyleRule* rule, xmlNode* geo3DstyleNode);
	bool ReadMaterial(se::GeoSymbolizer*, xmlNode* geo3DstyleNode);

	bool ReadColorMap(se::RasterSymbolizer*, xmlNode* geo3DstyleNode);
	///@brief ����������
	///@param 
	///@author yang hongjun
	///@date 2014.11.27
	bool ReadGeoReferencedTexture(se::GeoSymbolizer*, xmlNode* geo3DstyleNode);


	///@brief �����µ�Geo3DStyle
	///@param 
	///@author yang hongjun
	///@date 2013.11.13
	void CreateGeo3DStyle();
 
};

