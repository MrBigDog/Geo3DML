#include "Geo3DMapMetaData.h"

using namespace  gmml;

///@brief  ���캯��
///@author zhaowei
///@date   2013.11.08
Geo3DMapMetaData::Geo3DMapMetaData(void)
{

}

///@brief  ��������
///@author zhaowei
///@date   2013.11.08
Geo3DMapMetaData::~Geo3DMapMetaData(void)
{
}

///@brief  ��ȡ������Ŀ
///@param 
///@return ������������
///@author zhaowei
///@date   2013.11.08
int Geo3DMapMetaData::GetAttributeValueCount()
{
	int attr_count = attributeValues.size();
	return attr_count;
}

///@brief  ��ȡָ����ŵ�����
///@param  i ���
///@return ����ָ������
///@author zhaowei
///@date   2013.11.08
AttributeValue Geo3DMapMetaData::GetAttributeValue(const int& i)
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
AttributeValue Geo3DMapMetaData::GetAttributeValue(const std::string& fieldname)
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
void Geo3DMapMetaData::AddAttributeValue(const AttributeValue& value)
{
	attributeValues.push_back(value);
}


void Geo3DMapMetaData::deleteMembers()
{

}