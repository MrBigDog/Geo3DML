#pragma once
#include "XMLReader.h"
class GMXMLFILEIO_EXPORT SpatialRelationXMLReader :
	public XMLReader
{
public:
	SpatialRelationXMLReader(void);
	~SpatialRelationXMLReader(void);

	gml::AbstractGML* GetSpatialRelation();

	///@brief ��ȡSpatialRelation,featurerelationNodeΪ��ǰSpatialRelation�ڵ�
	///@return ����ɹ�����true ���򷵻�false
	///@author yang hongjun
	///@date 2013.11.13
	virtual bool ReadSpatialRelation(xmlNode* spatialrelationNode);
protected:
	///@brief  �����µ�SpatialRelation����
	///@author yang hongjun
	///@date   2013.11.13
	void CreateSpatialRelation();
	gml::AbstractGML *SpatialRelation_;
};
