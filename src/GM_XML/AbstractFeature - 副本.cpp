#include "AbstractFeature.h"
 
using namespace gml;

///@brief  ���캯��
///@author zhaowei
///@date   2013.11.13
AbstractFeature::AbstractFeature(void)
{
}

///@brief  ��������
///@author zhaowei
///@date   2013.11.13
AbstractFeature::~AbstractFeature(void)
{
}

///@brief  ��ȡ������Ŀ
///@param
///@return ����������Ŀ
///@author zhaowei
///@date   2013.11.13
int AbstractFeature::GetAttributeValueCount()
{
	int attr_count = attributeValues.size();
	return attr_count;
}

///@brief  ��ȡ���Ϊi������
///@param i ���
///@return ��������
///@author zhaowei
///@date   2013.11.13
AttributeValue AbstractFeature::GetAttributeValue(const int& i)
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
///@return �����������Ϊ�գ������������ƺ�����ֵΪ�յĶ��󣻷��򷵻���Ӧ������
///@author zhaowei
///@date   2013.11.13
AttributeValue AbstractFeature::GetAttributeValue(std::string fieldname)
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
///@param const AttributeValue& value ����ӵ���Ԫ��
///@return 
///@author zhaowei
///@date   2013.11.13
void AbstractFeature::AddAttributeValue(const AttributeValue& value)
{
	attributeValues.push_back(value);
}