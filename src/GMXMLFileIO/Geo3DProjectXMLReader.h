#pragma once

#include <string>
#include <vector>

#include "XMLReader.h"
class GMXMLFILEIO_EXPORT Geo3DProjectXMLReader: public XMLReader
{
public:
	///@brief  ���캯��
	///@author zhaowei
	///@date   2013.11.04
	Geo3DProjectXMLReader();

	///@brief  ��������
	///@author zhaowei
	///@date   2013.11.04
	~Geo3DProjectXMLReader();

	///@brief  ��ȡGeo3DProject
	///@param   
	///@return ����ָ��Geo3DProject�����ָ��
	///@author zhaowei
	///@date   2013.11.04
	gml::AbstractGML* GetGeoProject();

	///@brief  ��ȡGeo3DProject
	///@param projectFile ��������ȡGeo3DProject���ļ�
	///@param charSet ���ļ����ַ���
	///@return �����ȡ�ɹ�������true�����򷵻�false
	///@author zhaowei
	///@date   2013.11.04
	virtual bool ReadFile(const char *DocName, const std::string charSet,int binary=0);

private:
	///@brief  �����µ�Geo3DProject����
	///@param 
	///@return 
	///@author zhaowei
	///@date   2013.11.04
	void CreateProject();

	gml::AbstractGML* Project_;
};