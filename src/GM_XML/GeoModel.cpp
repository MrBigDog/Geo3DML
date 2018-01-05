#include "GeoModel.h"
#include "GeoModelMetaData.h"
#include "FeatureRelation.h"
#include "GeologicFeature.h"
#include "FeatureClass.h"
using namespace gmml;

///@brief  ���캯��
///@author zhaowei
///@date   2013.11.08
GeoModel::GeoModel(void)
{
	metaData = new GeoModelMetaData;
	metaData->setContainer(this);
}

///@brief  ��������
///@author zhaowei
///@date   2013.11.08
GeoModel::~GeoModel(void)
{
	deleteMembers();

}

///@brief  ��ȡGeoModel��Ӧ��Ԫ����
///@param
///@return ����ָ��GeoModelMetaData��ָ��
///@author zhaowei
///@date   2013.11.08
GeoModelMetaData* GeoModel::GetGeoModelMetaData()
{
	return metaData;
}

///@brief  ����GeoModel��Ӧ��Ԫ����
///@param value �����õ�Ԫ����
///@return 
///@author zhaowei
///@date   2013.11.08
void GeoModel::SetGeoModelMetaData(GeoModelMetaData* value)
{
	value->setContainer(this);
	metaData = value;
}

///@brief  ��ȡģ������
///@param
///@return ���ظ�ģ�͵�����
///@author zhaowei
///@date   2013.11.08
std::string GeoModel::GetType()
{
	return geoModelType;
}

///@brief  ����ģ������
///@param value �����õ�ģ������
///@return
///@author zhaowei
///@date   2013.11.08
void GeoModel::SetType(const std::string& value)
{
	geoModelType = value;
}

///@brief  ��ȡ������Ŀ
///@param
///@return ����������Ŀ
///@author zhaowei
///@date   2013.11.08
int GeoModel::GetAttributeValueCount()
{
	int attr_count = attributeValues.size();
	return attr_count;
}

///@brief  ��ȡ���Ϊi������
///@param i ���
///@return ��������
///@author zhaowei
///@date   2013.11.08
AttributeValue GeoModel::GetAttributeValue(const int& i)
{
	if(i < 0 || i >= attributeValues.size())
	{
		AttributeValue v;
		v.fieldName = "";
		v.fieldValue = "";
		return v;
	}
	AttributeValue attr_value = attributeValues[i];
	return attr_value;
}

///@brief  ��ȡ������Ϊfieldname������
///@param fieldname ��������
///@return ��������
///@author zhaowei
///@date   2013.11.08
AttributeValue GeoModel::GetAttributeValue(const std::string& fieldname)
{
	if(fieldname.empty())
	{
		AttributeValue v;
		v.fieldName = "";
		v.fieldValue = "";
		return v;
	}
	for(int i = 0; i < attributeValues.size(); i++)
	{
		if(attributeValues[i].fieldName == fieldname)
		{
			return attributeValues[i];
		}
	}
}

///@brief  ��AttributeValue����������µ�Ԫ��
///@param  const AttributeValue& value ����ӵ���Ԫ��
///@return 
///@author zhaowei
///@date   2013.11.08
void GeoModel::AddAttributeValue(const AttributeValue& value)
{
	attributeValues.push_back(value);
}

///@brief  ��ȡָ����ŵ�FeatureClass
///@param  i ���
///@return ����ָ��FeatureClass��ָ��
///@author zhaowei
///@date   2013.11.08
GeologicFeatureClass* GeoModel::GetGeoFeatureClass(const int& i)
{
	if(i < 0 || i >= geoFeatureClasses.size())
	{
		return NULL;
	}
	return geoFeatureClasses[i];
}

///@brief ��ȡָ��ID��FeatureClass
///@param fcID FeatureClass��ID
///@return ����FeatureClassָ��
///@author wang
///@date 2013.11.26
GeologicFeatureClass* GeoModel::GetGeoFeatureClass(const std::string& fcID)
{
	for(int i = 0;  i < geoFeatureClasses.size(); i++)
	{
		if(geoFeatureClasses[i]->getID() == fcID)
			return geoFeatureClasses[i];
	}
	return NULL;
}

///@brief  ��ȡȫ����FeatureClass
///@param  geo_feature_class ��Ϊ���ò���������ȡ����FeatureClass
///@return 
///@author zhaowei
///@date   2013.11.08
void GeoModel::GetAllFeatureClass(std::vector<GeologicFeatureClass*>& geo_feature_class)
{
	geoFeatureClasses = geo_feature_class;
}

///@brief  ����µ�FeatureClass
///@param  value ����ӵ�FeatureClass
///@return 
///@author zhaowei
///@date   2013.11.08
void GeoModel::AddFeatureClass(GeologicFeatureClass* value)
{
	geoFeatureClasses.push_back(value);
	value->setContainer(this);	
}


///@brief  ��ȡָ����ŵ�FeatureRelation
///@param i ���
///@return ����ָ��FeatureRelation��ָ��
///@author zhaowei
///@date   2013.11.08
FeatureRelation* GeoModel::GetGeoFeatureRelation(const int& i)
{
	if(i < 0 || i >=  featureRelations.size())
		return NULL;
	return featureRelations[i];
}

///@brief  ��ȡȫ����FeatureRelation
///@param  geo_feature_relation ��Ϊ���ò���������ȡ����FeatureRelation
///@return 
///@author zhaowei
///@date   2013.11.08
void GeoModel::GetAllFeatureRelation(std::vector<FeatureRelation*>& geo_feature_relation)
{
	featureRelations = geo_feature_relation;
}

///@brief  ����µ�FeatureRelation
///@param  value ����ӵ�FeatureRelation
///@return 
///@author zhaowei
///@date   2013.11.08
void GeoModel::AddFeatureRelation(FeatureRelation* value)
{
	if (value)
	{
		featureRelations.push_back(value);
		value->setContainer(this);
	}
}

///@brief  �ͷŹ�����ڴ�
///@param  
///@return
///@author zhaowei
///@date   2013.11.13
void GeoModel::deleteMembers()
{
	if(metaData)
		delete metaData;
	    metaData  = NULL;

	for(std::vector<GeologicFeatureClass*>::size_type i = 0; i < geoFeatureClasses.size(); i++)
	{
		if(geoFeatureClasses[i]->getContainer() == this);
		{
			delete geoFeatureClasses[i];
		}
	}
	geoFeatureClasses.clear();

	for(std::vector<FeatureRelation*>::size_type i = 0; i < featureRelations.size(); i++)
	{
		if(featureRelations[i]->getContainer() == this);
		{
			delete featureRelations[i];
		}
	}
	featureRelations.clear();
}

int GeoModel::GetGeoFeatureClassCount()
{
	return	geoFeatureClasses.size();
}

int GeoModel::GetGeoFeatureRelationCount()
{
	return	featureRelations.size();
}

///@brief ��ȡָ��Model��IDȷ����GeoFeature
///@param model ָ����GeoModelָ��
///@param fid ȷ����GeoFeatureID
///@return ����GeoFeature��ָ��
///@author wang
///@date 2013.11.26
GeologicFeature* GetFeature(GeoModel* model, std::string fid)
{
	for(int j = 0; j < model->GetGeoFeatureClassCount() ; j++)
	{
		GeologicFeatureClass* fc =  model->GetGeoFeatureClass(j);
		for(int i = 0; i < fc->GetGeologicFeatureCount(); i++)
		{
			GeologicFeature *f =  fc->GetGeologicFeature(i);

			if(f->getID() == fid)
			{
				return f;
			}
		}
	}
	return 0;
}

void GeoModel::UpdateRelations()
{
	for(int i = 0; i < featureRelations.size(); i++)
	{
		if( featureRelations[i]->GetClassName() != "BoundaryRelationship")
			continue;

		std::string  sid = featureRelations[i]->getSourceRole();
		int b = sid.find("#");
		sid = sid.substr(b+1,sid.length());

		GeologicFeature* sourceFeature = GetFeature(this,sid);

		if(sourceFeature)
			for(int j = 0; j < featureRelations[i]->GetTargetCount(); j++)
			{
				std::string  tid = featureRelations[i]->getTargetRole(j) ;

				int bc = tid.find("#");
				tid = tid.substr(bc+1,tid.length());

				GeologicFeature * targetFeature = GetFeature(this,tid);
				if(targetFeature)
				{
					sourceFeature->AddBoundaryFeature(targetFeature);
				}
			}
	}
}