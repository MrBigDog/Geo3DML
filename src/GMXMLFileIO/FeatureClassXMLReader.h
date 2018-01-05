#pragma once
#include "xmlreader.h"

class GMXMLFILEIO_EXPORT FeatureClassXMLReader :
	public XMLReader
{
public:
	FeatureClassXMLReader(void);
	~FeatureClassXMLReader(void);

 gml::AbstractGML* GetFeatureClass();
 ///@brief ��ȡFeatureClass
 ///@featureclassNodeΪ��ǰFeatureClass�ڵ�
 ///@return ����ɹ�����true ���򷵻�false
 ///@author yang hongjun
 ///@date 2013.11.10
virtual bool ReadFeatureClass(xmlNode* featureclassNode);

protected:
	bool ReadField(xmlNode* featureclassNode);
 
	///@brief  �����µ�FeatureClass����
	///@param  
	///@return 
	///@author yang hongjun
	///@date   2013.11.10
	 void CreateFeatureClass();
	 gml::AbstractGML* FeatureClass_;
};

