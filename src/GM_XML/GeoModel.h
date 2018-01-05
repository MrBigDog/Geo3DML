#ifndef GeoModel_h__
#define GeoModel_h__

#include "AbstractGML.h"

namespace gmml
{
	class GeoModelMetaData;
	class FeatureRelation;
	class GeologicFeatureClass;
	class GEOXML_EXPORT GeoModel : public gml::AbstractGML
	{
	public:
		///@brief  ���캯��
		///@author zhaowei
		///@date   2013.11.06
		GeoModel(void);

		///@brief ��������
		///@author zhaowei
		///@date   2013.11.06
		~GeoModel(void);

		///@brief  ��ȡ���������
		///@param 
		///@return ���ظ��������
		///@author zhaowei
		///@date   2013.11.06
		std::string GetClassName() { return "GeoModel"; };

		///@brief  ��ȡGeoModel��Ӧ��Ԫ����
		///@param 
		///@return ����ָ��GeoModelMetaData��ָ��
		///@author zhaowei
		///@date   2013.11.08
		GeoModelMetaData* GetGeoModelMetaData();

		///@brief  ����GeoModel��Ӧ��Ԫ����
		///@param value �����õ�Ԫ����
		///@return 
		///@author zhaowei
		///@date   2013.11.08
		void SetGeoModelMetaData(GeoModelMetaData* value);

		///@brief  ��ȡģ������
		///@param 
		///@return ���ظ�ģ�͵�����
		///@author zhaowei
		///@date   2013.11.07
		std::string GetType();

		///@brief  ����ģ������
		///@param  value �����õ�ģ������
		///@return
		///@author zhaowei
		///@date   2013.11.08
		void SetType(const std::string& value);

		///@brief  ��ȡ������Ŀ
		///@param 
		///@return ����������Ŀ
		///@author zhaowei
		///@date   2013.11.06
		int GetAttributeValueCount();

		///@brief  ��ȡ���Ϊi������
		///@param  i ���
		///@return ��������
		///@author zhaowei
		///@date   2013.11.06
		AttributeValue GetAttributeValue(const int& i);

		///@brief  ��ȡ������Ϊfieldname������
		///@param  fieldname ��������
		///@return ��������
		///@author zhaowei
		///@date   2013.11.06
		AttributeValue GetAttributeValue(const std::string& fieldname);

		///@brief  ��AttributeValue����������µ�Ԫ��
		///@param  const AttributeValue& value ����ӵ���Ԫ��
		///@return 
		///@author zhaowei
		///@date   2013.11.05
		void AddAttributeValue(const AttributeValue& value);

		///@brief ��ȡModel������FeatureClass��Ŀ
		///@return ����FeatureClass��Ŀ
		///@author wang
		///@date 2013.11.26
		int GetGeoFeatureClassCount();

		///@brief  ��ȡָ����ŵ�FeatureClass
		///@param  i ���
		///@return ����ָ��FeatureClass��ָ�� 
		///@author zhaowei
		///@date   2013.11.08
		GeologicFeatureClass* GetGeoFeatureClass(const int& i);

		///@brief ��ȡָ��ID��FeatureClass
		///@param fcID FeatureClass��ID
		///@return ����FeatureClassָ��
		///@author wang
		///@date 2013.11.26
		GeologicFeatureClass* GetGeoFeatureClass(const std::string& fcID);

		///@brief  ��ȡȫ����FeatureClass
		///@param  geo_feature_class ��Ϊ���ò���������ȡ����FeatureClass
		///@return 
		///@author zhaowei
		///@date   2013.11.08
		void GetAllFeatureClass(std::vector<GeologicFeatureClass*>& geo_feature_class);

		///@brief  ����µ�FeatureClass
		///@param  value ����ӵ�FeatureClass
		///@return 
		///@author zhaowei
		///@date   2013.11.08
		void AddFeatureClass(GeologicFeatureClass* value);

		///@brief  ��ȡָ����ŵ�FeatureRelation
		///@param  i ���
		///@return ����ָ��FeatureRelation��ָ��
		///@author zhaowei
		///@date   2013.11.08
		FeatureRelation* GetGeoFeatureRelation(const int& i);

		///@brief ��ȡModel�е�FeatureRelation��Ŀ
		///@return ����FeatureRelation��Ŀ
		///@author wang
		///@date 2013.11.26
		int GetGeoFeatureRelationCount();

		///@brief  ��ȡȫ����FeatureRelation
		///@param  geo_feature_relation ��Ϊ���ò���������ȡ����FeatureRelation
		///@return 
		///@author zhaowei
		///@date   2013.11.08
		void GetAllFeatureRelation(std::vector<FeatureRelation*>& geo_feature_relation);

		///@brief  ����µ�FeatureRelation
		///@param  value ����ӵ�FeatureRelation
		///@return 
		///@author zhaowei
		///@date   2013.11.08
		void AddFeatureRelation(FeatureRelation* value);

		///@brief  �ͷŹ�����ڴ�
		///@param  
		///@return
		///@author zhaowei
		///@date   2013.11.13
		void deleteMembers();

		///@brief ���Model������Feature�����FeatureRelation
		///@author wang
		///@date 2013.11.26
		void UpdateRelations();
	protected:
		/// Model���Զ�����������
		std::vector<AttributeValue>          attributeValues;
		/// Model������FeatureClass����
		std::vector<GeologicFeatureClass*>   geoFeatureClasses;
		/// Model������FeatureRelation����
		std::vector<FeatureRelation*>        featureRelations;
		/// Model��Ӧ��Ԫ����
		GeoModelMetaData*					 metaData;
		/// Model������
		std::string							 geoModelType;
	};

}


#endif // GeoModel_h__
