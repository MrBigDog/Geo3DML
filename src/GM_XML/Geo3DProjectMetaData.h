#ifndef Geo3DProjectMetaData_h__
#define Geo3DProjectMetaData_h__

#include "AbstractGML.h"

namespace gmml
{
	class GEOXML_EXPORT Geo3DProjectMetaData : public gml::AbstractGML
	{
	public:
		///@brief  ���캯��
		///@author zhaowei
		///@date   2013.11.08
		Geo3DProjectMetaData(void);

		///@brief  ��������
		///@author zhaowei
		///@date   2013.11.08
		~Geo3DProjectMetaData(void);

		///@brief  ��ȡ������Ŀ
		///@param
		///@return ������������
		///@author zhaowei
		///@date   2013.11.08
		int GetAttributeValueCount();

		///@brief  ��ȡָ����ŵ�����
		///@param i ���
		///@return ����ָ������
		///@author zhaowei
		///@date   2013.11.08
		AttributeValue GetAttributeValue(const int& i);

		///@brief  ��ȡָ��������������
		///@param  fieldname ������
		///@return ����ָ������
		///@author zhaowei
		///@date   2013.11.08
		AttributeValue GetAttributeValue(const std::string& fieldname);

		///@brief  ��AttributeValue����������µ�Ԫ��
		///@param  const AttributeValue& value ����ӵ���Ԫ��
		///@return 
		///@author zhaowei
		///@date   2013.11.08
		void AddAttributeValue(const AttributeValue& value);

		///@brief  �ͷŹ�����ڴ�
		///@param  
		///@return
		///@author zhaowei
		///@date   2013.11.13
		void deleteMembers() { ; };
	protected:
		std::vector<AttributeValue>  attributeValues;
	};

}

#endif // Geo3DProjectMetaData_h__
