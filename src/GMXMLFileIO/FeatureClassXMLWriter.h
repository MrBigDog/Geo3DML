#pragma once
#include "xmlwriter.h"

namespace gmml
{
	class GeologicFeatureClass;
	class GeologicFeature;
}

class GMXMLFILEIO_EXPORT FeatureClassXMLWriter : public XMLWriter
{
public:
	///@brief ���캯��
	///@author zhaowei
	///@date 2014.03.18
	FeatureClassXMLWriter(void);

	///@brief ��������
	///@author zhaowei
	///@date 2014.03.18
	~FeatureClassXMLWriter(void);

	///@brief ��FeatureClassд���ļ�
	///@param feature_class ָ��FeatureClass��ָ��
	///@param xml_stream д���ļ���
	///@author zhaowei
	///@date 2014.03.18
	void WriteFeatureClass(gmml::GeologicFeatureClass* feature_class, std::ofstream& xml_stream);

	///@brief ��FeatureClass�е�Schemaд���ļ�
	///@param feature_class ָ��FeatureClass��ָ��
	///@param xml_stream д���ļ���
	///@author zhaowei
	///@date 2014.03.19
	void WriteSchema(gmml::GeologicFeatureClass* feature_class, std::ofstream& xml_stream);

	///@brief ��FeatureClass�е�Featureд���ļ�
	///@param feature_class ָ��FeatureClass��ָ��
	///@param xml_stream д���ļ���
	///@author zhaowei
	///@date 2014.03.19
	void WriteMember(gmml::GeologicFeatureClass* feature_class, std::ofstream& xml_stream);
};

