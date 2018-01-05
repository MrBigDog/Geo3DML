#ifndef Geo3DMap_h__
#define Geo3DMap_h__

#include "AbstractGML.h"

namespace gmml
{

	class Geo3DMapMetaData;
	class Geo3DLayer;
	///@brief ����ͼ
	class GEOXML_EXPORT Geo3DMap : public gml::AbstractGML
	{
	public:
		///@brief  ���캯��
		///@author zhaowei
		///@date   2013.11.07
		Geo3DMap(void);

		///@brief ��������
		///@author zhaowei
		///@date   2013.11.07
		~Geo3DMap(void);

		///@brief  ��ȡ���������
		///@param 
		///@return ���ظ��������
		///@author zhaowei
		///@date   2013.11.07
		virtual std::string GetClassName() { return "Geo3DMap"; };

	public:


		///@brief  ��ȡGeoMap��Ӧ��Ԫ����
		///@param
		///@return ����ָ��Geo3DMapMetaData��ָ��
		///@author zhaowei
		///@date   2013.11.01
		Geo3DMapMetaData* GetGeoMapMetaData();

		///@brief  ����GeoMap��Ӧ��Ԫ����
		///@param  value �����õ�Ԫ����
		///@return
		///@author zhaowei
		///@date   2013.11.08
		void SetGeoMapMetaData(Geo3DMapMetaData* value);

		///@name ����ͼ�е�ͼ�㡣
		//@{
		///@brief  ȡ����ͼ����������ͼ�����Ŀ��
		///@return ���ص���ͼ��������ͼ�����Ŀ��
		///@author zhaowei
		///@date   2013.11.07
		int GetGeo3DLayerCount();

		///@brief  ȡ����ͼ�е�ͼ�㡣
		///@param  i ͼ���ڵ���ͼ�е������ţ���0��ʼ����
		///@return ָ����ͼ�㡣������ָ����ָ�������ڴ��ɱ�������������ָ����ͼ�㲻���ڣ��򷵻�0.
		///@author zhaowei
		///@date   2013.11.07
		Geo3DLayer* GetLayer(int i);
		//@}

		///@brief  ��ȡȫ���ĵ���ͼ��
		///@param geo_layers ��Ϊ���ò���������ȡ����ȫ������ͼ��
		///@return 
		///@author zhaowei
		///@date   2013.11.08
		void GetAllGeoLayer(std::vector<Geo3DLayer*>& geo_layers);

		///@brief  ȡ����ͼ��������Ϣ��
		///@return ���ص���ͼ�����͡�
		///@author zhaowei
		///@date   2013.11.07
		std::string GetType();

		///@brief  ���õ���ͼ����
		///@param mapType ����ͼ����ֵ
		///@return
		///@author zhaowei
		///@date   2013.11.07
		void SetType(const std::string& mapType);

		///@brief  ��ӵ���ͼ��
		///@param  value ����ӵĵ���ͼ��
		///@return
		///@author zhaowei
		///@date   2013.11.07
		void AddGeoLayer(Geo3DLayer* value);

		///@brief  ��ȡGeoMap��������Ŀ
		///@param  
		///@return ����GeoMap��������Ŀ
		///@author zhaowei
		///@date   2013.11.07
		int GetAttributeValueCount();

		///@brief  ��ȡ����ͼ�е�i������
		///@param i ���i����0��ʼ������
		///@return ������i��Ч�����ص�i�����ԣ����򷵻��������ƺ�����ֵ��Ϊ�յ�����
		///@author zhaowei
		///@date   2013.11.07
		AttributeValue GetAttributeValue(const int& i);

		///@brief  ��ȡ��������Ϊfieldname�������ֶ�
		///@param  fieldname ��������
		///@return �������������Ч���򷵻ض�Ӧ�����ԣ����򷵻��������ƺ�����ֵ��Ϊ�յ�����
		///@author zhaowei
		///@date   2013.11.07
		AttributeValue GetAttributeValue(const std::string& fieldname);

		///@brief  ��AttributeValue����������µ�Ԫ��
		///@param const AttributeValue& value ����ӵ���Ԫ��
		///@return 
		///@author zhaowei
		///@date   2013.11.05
		void AddAttributeValue(const AttributeValue& value);

		///@brief  �ͷŹ�����ڴ�
		///@param  
		///@return
		///@author zhaowei
		///@date   2013.11.13
		void deleteMembers();
	protected:
		std::vector<AttributeValue>  attributeValues;
		std::vector<Geo3DLayer*>     geo3DLayers;
		gmml::Geo3DMapMetaData*      metaData;
		std::string                  geoMapType;
	};

}
#endif // Geo3DMap_h__