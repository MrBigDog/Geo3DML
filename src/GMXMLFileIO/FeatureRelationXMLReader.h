#pragma once
#include "xmlreader.h"
class GMXMLFILEIO_EXPORT FeatureRelationXMLReader :
	public XMLReader
{
public:
	FeatureRelationXMLReader(void);
	~FeatureRelationXMLReader(void);

 
	///@brief ��ȡFeatureRelation
	///@featurerelationNodeΪ��ǰFeatureRelation�ڵ�
	///@return ����ɹ�����true ���򷵻�false
	///@author yang hongjun
	///@date 2013.11.13
	virtual bool ReadNode(xmlNode* relationshipNode);

protected:
	bool ReadRelation(xmlNode* relationshipNode);
	///@brief  �����µ�FeatureRelation����
	///@param  
	///@return 
	///@author yang hongjun
	///@date   2013.11.13
	void CreateRelationship(std::string relationType);
	 
};

