#pragma once
#include "xmlwriter.h"
namespace gmml
{
	class GeoModel;	
}

class GMXMLFILEIO_EXPORT GeoModelXMLWriter : public XMLWriter
{
public:
	///@brief ���캯��
	///@author zhaowei
	///@date 2014.03.18
	GeoModelXMLWriter(void);

	///@brief ��������
	///@author zhaowei
	///@date 2014.03.18
	~GeoModelXMLWriter(void);

	///@brief ��Model����д���ļ�
	///@param model ָ��Model���ݵ�ָ��
	///@param xml_path Model�ļ���·��
	///@author zhaowei
	///@date 2014.03.18
	bool WriteModel(gmml::GeoModel* model, const std::string& xml_path,char* pEncoding = "gb2312");
};

