#ifndef Geo3DLayer_h__
#define Geo3DLayer_h__

#include "AbstractGML.h"

namespace gmml
{
	class GeologicFeatureClass;
	class Geo3DStyle;
	class GEOXML_EXPORT Geo3DLayer : public gml::AbstractGML
	{
	public:
		///@brief  ���캯��
		///@author zhaowei
		///@date   2013.11.07
		Geo3DLayer(void);

		///@brief  ��������
		///@author zhaowei
		///@date   2013.11.07
		~Geo3DLayer(void);

		///@brief  ��ȡ���������
		///@param  
		///@return ���ظ��������
		///@author zhaowei
		///@date   2013.11.07
		virtual std::string GetClassName() { return "Geo3DLayer"; };

	public:
		///@brief  ��ȡGeo3DLayer��ӦҪ����
		///@param  
		///@return ����ָ��Ҫ�����ָ��
		///@author zhaowei
		///@date   2013.11.07
		GeologicFeatureClass* GetFeatureClass();

		///@brief  ��ȡ���ӻ�����
		///@param  
		///@return ����ָ����ӻ�����GeoStyle��ָ��
		///@author zhaowei
		///@date   2013.11.07
		Geo3DStyle* GetStyle();

		///@brief  ����Geo3DLayer��Ӧ��Ҫ����
		///@param  value �����õ�Ҫ����
		///@return 
		///@author zhaowei
		///@date   2013.11.07
		void SetFeatureClass(GeologicFeatureClass* value);

		///@brief  ����Geo3DLayer��Ӧ����ʾ����
		///@param  value �����õ���ʾ����
		///@return 
		///@author zhaowei
		///@date   2013.11.07
		void SetStyle(Geo3DStyle* value);

		///@brief  ��ȡ������Ŀ
		///@param 
		///@return ����������Ŀ
		///@author zhaowei
		///@date   2013.11.08
		int GetAttributeValueCount();

		///@brief  ��ȡ���Ϊi������
		///@param  i ���
		///@return ��������
		///@author zhaowei
		///@date   2013.11.08
		AttributeValue GetAttributeValue(const int& i);

		///@brief  ��ȡ������Ϊfieldname������
		///@param  fieldname ��������
		///@return �����������Ϊ�գ������������ƺ�����ֵΪ�յĶ��󣻷��򷵻���Ӧ������
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
		void deleteMembers();
	protected:
		GeologicFeatureClass*		featureClass;
		Geo3DStyle*					geoStyle;
		std::vector<AttributeValue> attributeValues;
	};

}

#endif // Geo3DLayer_h__
