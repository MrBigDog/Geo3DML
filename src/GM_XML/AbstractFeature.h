#pragma once

#include "AbstractGML.h"

namespace gml
{

class GEOXML_EXPORT AbstractFeature : public AbstractGML
{
public:
	///@brief  ���캯��
	///@author zhaowei
	///@date   2013.11.13
	AbstractFeature(void);

	///@brief  ��������
	///@author zhaowei
	///@date   2013.11.13
	~AbstractFeature(void);

	///@brief  ��ȡ������
	///@param 
	///@return ����������
	///@author zhaowei
	///@date   2013.11.13
	virtual std::string GetClassName(){return "AbstractFeature";};

	///@brief  ��ȡ������Ŀ
	///@param 
	///@return ����������Ŀ
	///@author zhaowei
	///@date   2013.11.13
	int GetAttributeValueCount();

	///@brief  ��ȡ���Ϊi������
	///@param  i ���
	///@return ��������
	///@author zhaowei
	///@date   2013.11.13
	AttributeValue GetAttributeValue(const int& i);

	bool GetAttributeValue(const int& i, AttributeValue*& pOut);

	///@brief  ��ȡ������Ϊfieldname������
	///@param  fieldname ��������
	///@return �����������Ϊ�գ������������ƺ�����ֵΪ�յĶ��󣻷��򷵻���Ӧ������
	///@author zhaowei
	///@date   2013.11.13
	AttributeValue GetAttributeValue(std::string fieldname);

	///@brief  ��AttributeValue����������µ�Ԫ��
	///@param  const AttributeValue& value ����ӵ���Ԫ��
	///@return 
	///@author zhaowei
	///@date   2013.11.13
	void AddAttributeValue(const AttributeValue& value);

protected:
	std::vector<AttributeValue>  attributeValues;//feilds
};

}