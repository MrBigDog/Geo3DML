#ifndef GeoModelMetaData_h__
#define GeoModelMetaData_h__

#include "AbstractGML.h"
#include "AbstractSpatialReferenceSystem.h"

namespace gmml
{
	class GEOXML_EXPORT GeoModelMetaData : public gml::AbstractGML
	{
	public:
		///@brief  ���캯��
		///@author zhaowei
		///@date   2013.11.08
		GeoModelMetaData(void);

		///@brief  ��������
		///@author zhaowei
		///@date   2013.11.08
		~GeoModelMetaData(void);

		///@brief  ��ȡ������
		///@author zhaowei
		///@date   2013.11.08
		virtual std::string GetClassName() { return "GeoModelMetaData"; };

		///@brief  ��ȡ������Ŀ
		///@param 
		///@return ������������
		///@author zhaowei
		///@date   2013.11.08
		int GetAttributeValueCount();

		///@brief  ��ȡָ����ŵ�����
		///@param  i ���
		///@return ����ָ������
		///@author zhaowei
		///@date   2013.11.08
		AttributeValue GetAttributeValue(const int& i);

		std::vector<AttributeValue> * GetAttributes();
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
		void deleteMembers();


		void SetSpatialReferenceSystem(AbstractSpatialReferenceSystem*);
		AbstractSpatialReferenceSystem* GetSpatialReferenceSystem();
	protected:
		std::vector<AttributeValue>  attributeValues;

		//SpatialReferenceSystem
		AbstractSpatialReferenceSystem*  spatialReferenceSystem;
	};

}

#endif // GeoModelMetaData_h__
