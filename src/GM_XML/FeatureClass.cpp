#include "FeatureClass.h"
#include "GeologicFeature.h"

using namespace gmml;

///@brief  ���캯��
///@author zhaowei
///@2013.11.08
GeologicFeatureClass::GeologicFeatureClass(void)
{

}

///@brief  ��������
///@author zhaowei
///@2013.11.08
GeologicFeatureClass::~GeologicFeatureClass(void)
{

}
int GeologicFeatureClass:: GetFeatureClassSchemaCount()
{
	return schema_.size();
}
 
int GeologicFeatureClass:: GetGeologicFeatureCount()
{
	return features.size();
}
///@brief  ��ȡָ����ŵ�Schema��
///@param  i ���
///@return ����ָ����ŵ�Schema��
///@author zhaowei
///@date   2013.11.08
AttributeValue& GeologicFeatureClass::GetFeatureClassSchema(const int& i)
{
	if(i < 0 || i >= schema_.size())
	{
		AttributeValue v;
		v.fieldName = "";
		v.fieldValue = "";
		v.fieldType = "";
		return v;
	}
	return schema_[i];
}

///@brief  ��ȡָ�����Ƶ�Schema��
///@param fieldname ����
///@return ������Ӧ��Schema��
///@author zhaowei
///@date   2013.11.08
AttributeValue GeologicFeatureClass::GetFeatureClassSchema(const std::string& field_name)
{
	if(field_name.empty())
	{
		AttributeValue v;
		v.fieldName = "";
		v.fieldValue = "";
		v.fieldType = "";
		return v;
	}
	for(int i = 0; i < schema_.size(); i++)
	{
		if(schema_[i].fieldName == field_name)
			return schema_[i];
	}
}

///@brief  ��ȡȫ����Schema
///@param  feature_class_schemas ��Ϊ���ñ��������洫��������Schema
///@return 
///@author zhaowei
///@date   2013.11.08
void GeologicFeatureClass::GetAllFeatureClassSchema(std::vector<AttributeValue>& feature_class_schemas)
{
	feature_class_schemas = schema_;
}

///@brief  ����µ�Schema��
///@param  value ����ӵ�Schema��
///@return 
///@author zhaowei
///@date   2013.11.08
void GeologicFeatureClass::AddFeatureClassSchema(const AttributeValue& value)
{
	schema_.push_back(value);
}

///@brief  ��ȡָ����ŵ�GeologicFeature
///@param i ���
///@return ���ص�i��GeologicFeature
///@author zhaowei
///@date   2013.11.08
GeologicFeature* GeologicFeatureClass::GetGeologicFeature(const int& i)
{
	if(i < 0 || i >= features.size())
		return NULL;
	return features[i];
}

///@brief  ��ȡȫ����GeologicFeature
///@param  geo_features ��Ϊ���ñ���������ȡ����ȫ��GeologicFeature
///@return 
///@author zhaowei
///@date   2013.11.08
void GeologicFeatureClass::GetAllGeologicFeature(std::vector<GeologicFeature*>& geo_features)
{
	geo_features = features;
}

///@brief  ���GeologicFeature
///@param  value ����ӵ�GeologicFeature
///@return
///@author zhaowei
///@date   2013.11.08
void GeologicFeatureClass::AddGeologicFeature(GeologicFeature* value)
{
	value->setContainer(this);
	features.push_back(value);
}

///@brief  �ͷŹ�����ڴ�
///@param  
///@return
///@author zhaowei
///@date   2013.11.13
void GeologicFeatureClass::deleteMembers()
{
	for(std::vector<GeologicFeature*>::size_type i = 0; i < features.size(); i++)
	{
		if(features[i]->getContainer() == this)
		{
			delete features[i];
		}
	}
	features.clear();
}