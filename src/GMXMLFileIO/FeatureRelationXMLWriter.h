#pragma once
#include "xmlwriter.h"

namespace gmml
{
	class FeatureRelation;
	class GeologicFeatureClass;
	class GeoModel;
}

class GMXMLFILEIO_EXPORT FeatureRelationXMLWriter : public XMLWriter
{
public:
	///@brief ���캯��
	///@author zhaowei
	///@date 2014.03.18
	FeatureRelationXMLWriter(void);

	///@brief ��������
	///@author zhaowei
	///@date 2014.03.18
	~FeatureRelationXMLWriter(void);

	///@brief ��FeatureRelationд���ļ�
	///@param feature_relation ָ��FeatureRelationָ��
	///@param xml_stream д���ļ���
	///@author zhaowei
	///@date 2014.03.18
	void WriteFeatureRelation(gmml::FeatureRelation* feature_relation, std::ofstream& xml_stream);
};

