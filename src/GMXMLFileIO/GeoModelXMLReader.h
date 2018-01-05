#pragma once
#include "xmlreader.h"
#include <string>
namespace gmml
{
	class Geo3DProjectMetaData;
	class Geo3DMapMetaData;
	class Geo3DMap;
	class Geo3DProject;
}
class GMXMLFILEIO_EXPORT GeoModelXMLReader :
	public XMLReader
{
public:
	GeoModelXMLReader(void);
	~GeoModelXMLReader(void);

	gml::AbstractGML* GetGeomodel();

	///@brief  ��ȡGeoModel
	///@param  DocName ��������ȡGeoModel���ļ�
	///@return �����ȡ�ɹ�������true�����򷵻�false
	///@author zhaowei
	///@date   2013.11.04
	
     bool ReadNode(xmlNodePtr curNode);

protected:

	///@brief  �����µ�Geo3DProject����
	///@param 
	///@return 
	///@author zhaowei
	///@date   2013.11.04
	void CreateGeomodel();
};


