#pragma once
#include "xmlreader.h"
namespace gmml
{
	class Geo3DProjectMetaData;
	class Geo3DMapMetaData;
	class Geo3DMap;
	class Geo3DProject;
}
class GMXMLFILEIO_EXPORT Geo3DMapXMLReader :
	public XMLReader
{
public:
	Geo3DMapXMLReader(void);
	~Geo3DMapXMLReader(void);

	gml::AbstractGML* GetGeomap();

	///@brief  ��ȡGeo3DMap
	///@param MapFile ��������ȡGeo3DMap���ļ�
	///@return �����ȡ�ɹ�������true�����򷵻�false
	///@author zhaowei
	///@date   2013.11.04
	
	 bool ReadNode(xmlNodePtr curNode);
protected:
	//virtual bool ReadGeo3DMap(const char *DocName);
	///@brief  �����µ�Geo3DProject����
	///@param  
	///@return 
	///@author zhaowei
	///@date   2013.11.04
	void CreateGeomap();
};
	
 

