#include "GeoModelMetaData.h"

using namespace gmml;

///@brief  ���캯��
///@author zhaowei
///@date   2013.11.08
GeoModelMetaData::GeoModelMetaData(void)
{
}

///@brief  ��������
///@author zhaowei
///@date   2013.11.08
GeoModelMetaData::~GeoModelMetaData(void)
{
}

///@brief  ��ȡ������Ŀ
///@param
///@return ������������
///@author zhaowei
///@date   2013.11.08
int GeoModelMetaData::GetAttributeValueCount()
{
	int attr_count = attributeValues.size();
	return attr_count;
}

///@brief  ��ȡָ����ŵ�����
///@param i ���
///@return ����ָ������
///@author zhaowei
///@date   2013.11.08
 
AttributeValue GeoModelMetaData::GetAttributeValue(const int& i)
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

///@brief  ��ȡָ��������������
///@param  fieldname ������
///@return ����ָ������
///@author zhaowei
///@date   2013.11.08
AttributeValue GeoModelMetaData::GetAttributeValue(const std::string& fieldname)
{
	for(int i = 0; i < attributeValues.size(); i++)
	{
		if(attributeValues[i].fieldName == fieldname)
		{
			return attributeValues[i];
		}
	}
	AttributeValue v;
	v.fieldName = fieldname;
	v.fieldValue = "";
	return v;
}

///@brief  ��AttributeValue����������µ�Ԫ��
///@param const AttributeValue& value ����ӵ���Ԫ��
///@return 
///@author zhaowei
///@date   2013.11.08
void GeoModelMetaData::AddAttributeValue(const AttributeValue& value)
{
	attributeValues.push_back(value);
}

void GeoModelMetaData::deleteMembers()
{

}