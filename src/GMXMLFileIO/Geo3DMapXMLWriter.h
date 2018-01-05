#pragma once
#include "xmlwriter.h"
namespace gmml
{
	class Geo3DMap;
}

class GMXMLFILEIO_EXPORT Geo3DMapXMLWriter : public XMLWriter
{
public:
	///@brief ���캯��
	///@author zhaowei
	///@date 2014.03.17
	Geo3DMapXMLWriter(void);

	///@brief ��������
	///@author zhaowei
	///@date 2014.03.17
	~Geo3DMapXMLWriter(void);

	///@brief ���ļ���д��Map����
	///@param map ָ��Map��ָ��
	///@param xml_path Map�ļ���·��
	///@author zhaowei
	///@date 2014.03.17
	bool WriteMap(gmml::Geo3DMap* map,const std::string& xml_path,char* pEncoding = "gb2312");
};

