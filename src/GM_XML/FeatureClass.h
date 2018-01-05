#ifndef FeatureClass_h__
#define FeatureClass_h__

#include "AbstractFeature.h" 

namespace gmml
{
	class GeologicFeature;
	class GEOXML_EXPORT GeologicFeatureClass : public gml::AbstractGML
	{
	public:
		///@brief  ���캯��
		///@author zhaowei
		///@date   2013.11.08
		GeologicFeatureClass(void);

		///@brief  ��������
		///@author zhaowei
		///@date   2013.11.08
		~GeologicFeatureClass(void);

		///@brief  ��ȡ��������
		///@param
		///@return ���ظ�������
		///@author zhaowei
		///@date   2013.11.08
		virtual std::string GetClassName() { return "GeologicFeatureClass"; };

		///@brief  ��ȡָ����ŵ�Schema��
		///@param i ���
		///@return ����ָ����ŵ�Schema��
		///@author zhaowei
		///@date   2013.11.08
		AttributeValue& GetFeatureClassSchema(const int& i);

		///@brief ��ȡ������Schema��Ŀ
		///@return ���ذ�����Schema����
		///@author zhaowei
		///@date 2013.12.03
		int GetFeatureClassSchemaCount();

		///@brief  ��ȡָ�����Ƶ�Schema��
		///@param fieldname ����
		///@return ������Ӧ��Schema��
		///@author zhaowei
		///@date   2013.11.08
		AttributeValue GetFeatureClassSchema(const std::string& field_name);

		///@brief  ��ȡȫ����Schema
		///@param  feature_class_schemas ��Ϊ���ñ��������洫��������Schema
		///@return 
		///@author zhaowei
		///@date   2013.11.08
		void GetAllFeatureClassSchema(std::vector<AttributeValue>& feature_class_schemas);

		///@brief  ����µ�Schema��
		///@param  value ����ӵ�Schema��
		///@return 
		///@author zhaowei
		///@date   2013.11.08
		void AddFeatureClassSchema(const AttributeValue& value);

		///@brief  ��ȡָ����ŵ�GeologicFeature
		///@param  i ���
		///@return ���ص�i��GeologicFeature
		///@author zhaowei
		///@date   2013.11.08
		GeologicFeature* GetGeologicFeature(const int& i);

		///@brief ��ȡ������GeoFeature��Ŀ
		///@return ���ذ�����GeoFeature����
		///@author zhaowei
		///@date 2013.12.03
		int GetGeologicFeatureCount();

		///@brief  ��ȡȫ����GeologicFeature
		///@param  geo_features ��Ϊ���ñ���������ȡ����ȫ��GeologicFeature
		///@return 
		///@author zhaowei
		///@date   2013.11.08
		void GetAllGeologicFeature(std::vector<GeologicFeature*>& geo_features);

		///@brief  ���GeologicFeature
		///@param  value ����ӵ�GeologicFeature
		///@return
		///@author zhaowei
		///@date   2013.11.08
		void AddGeologicFeature(GeologicFeature* value);

		///@brief  �ͷŹ�����ڴ�
		///@param  
		///@return
		///@author zhaowei
		///@date   2013.11.13
		void deleteMembers();
	protected:
		std::vector<AttributeValue>  schema_;
		std::vector<GeologicFeature*>  features;
	};
}

#endif // FeatureClass_h__
