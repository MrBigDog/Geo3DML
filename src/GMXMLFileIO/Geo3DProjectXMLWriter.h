#pragma once

#include <string>
#include <vector>

#include "xmlwriter.h"


namespace gmml
{
	class Geo3DProject;
	class Geo3DProjectMetaData;
	class Geo3DMap;
	class Geo3DMapMetaData;
	class GeoModel;
	class GeoModelMetaData;
}


class GMXMLFILEIO_EXPORT Geo3DProjectXMLWriter : public XMLWriter
{
public:
	///@brief ���캯��
	///@author zhaowei
	///@date 2014.03.17
	Geo3DProjectXMLWriter(void);

	///@brief ��������
	///@author zhaowei
	///@date 2014.03.17
	~Geo3DProjectXMLWriter(void);

	///@brief ���ļ���д��Project����
	///@param project ָ���д��Project��ָ��
	///@param xml_path д���ļ���·��
	bool WriteProject(gmml::Geo3DProject* project, const char* xml_path,char* pEncoding="gb2312",int binary=0) const;
};

