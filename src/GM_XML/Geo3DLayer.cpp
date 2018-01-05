#include "Geo3Dlayer.h"
#include "FeatureClass.h"
#include "Geo3DStyle.h"

using namespace gmml;

///@brief  ���캯��
///@author zhaowei
///@date   2013.11.07
Geo3DLayer::Geo3DLayer(void)
{
	featureClass = NULL;
	geoStyle = NULL;
}

///@brief  ��������
///@author zhaowei
///@date   2013.11.07
Geo3DLayer::~Geo3DLayer(void)
{
	deleteMembers();
}

///@brief  ��ȡGeo3DLayer��ӦҪ����
///@param 
///@return ����ָ��Ҫ�����ָ��
///@author zhaowei
///@date   2013.11.07
GeologicFeatureClass* Geo3DLayer::GetFeatureClass()
{
	return featureClass;
}

///@brief  ��ȡ���ӻ�����
///@param 
///@return ����ָ����ӻ�����GeoStyle��ָ��
///@author zhaowei
///@date   2013.11.07
Geo3DStyle* Geo3DLayer::GetStyle()
{
	return geoStyle;
}

///@brief  �ͷŹ�����ڴ�
///@param  
///@return
///@author zhaowei
///@date   2013.11.13
void Geo3DLayer::deleteMembers()
{
   if(featureClass && featureClass->getContainer() == this)
	   delete featureClass;

   if(geoStyle && geoStyle->getContainer() == this)
	   delete geoStyle;
}
///@brief  ����Geo3DLayer��Ӧ��Ҫ����
///@param  value �����õ�Ҫ����
///@return 
///@author zhaowei
///@date   2013.11.07
void Geo3DLayer::SetFeatureClass(GeologicFeatureClass* value)
{
	if(featureClass && featureClass->getContainer() == this)
		delete featureClass;

	if(value->getContainer() == NULL)
		value->setContainer(this);

	featureClass = value;

}

///@brief  ����Geo3DLayer��Ӧ����ʾ����
///@param  value �����õ���ʾ����
///@return 
///@author zhaowei
///@date   2013.11.07
void Geo3DLayer::SetStyle(Geo3DStyle* value)
{	
	if(geoStyle && geoStyle->getContainer() == this)
		delete geoStyle;	
	
	if(value)
	if(value->getContainer() == NULL)
		value->setContainer(this);

	geoStyle = value;
}

///@brief  ��ȡ������Ŀ
///@param 
///@return ����������Ŀ
///@author zhaowei
///@date   2013.11.08
int Geo3DLayer::GetAttributeValueCount()
{
	int attr_count = attributeValues.size();
	return attr_count;
}

///@brief  ��ȡ���Ϊi������
///@param  i ���
///@return ��������
///@author zhaowei
///@date   2013.11.08
AttributeValue Geo3DLayer::GetAttributeValue(const int& i)
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
///@param  fieldname ��������
///@return �����������Ϊ�գ������������ƺ�����ֵΪ�յĶ��󣻷��򷵻���Ӧ������
///@author zhaowei
///@date   2013.11.08
AttributeValue Geo3DLayer::GetAttributeValue(const std::string& fieldname)
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
void Geo3DLayer::AddAttributeValue(const AttributeValue& value)
{
	attributeValues.push_back(value);
}