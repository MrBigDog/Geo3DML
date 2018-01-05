#ifndef Geo3DProject_h__
#define Geo3DProject_h__

#include "AbstractGML.h"

namespace gmml
{
	class Geo3DProjectMetaData;
	class Geo3DMap;
	class GeoModel;
	class GeoSceneStyle;
	/// ���ʹ���
	class GEOXML_EXPORT Geo3DProject : public gml::AbstractGML
	{
	public:
		///@brief  ���캯��
		///@author zhaowei
		///@date   2013.11.06
		Geo3DProject(void);

		///@brief  ��������
		///@author zhaowei
		///@date   2013.11.06
		~Geo3DProject(void);

		///@brief  ��ȡ���������
		///@param
		///@return ���ظ��������
		///@author zhaowei
		///@date   2013.11.06
		std::string GetClassName() { return "Geo3DProject"; };

	public:
		/// @name   �����а����ĵ���ͼ��
		//@{
		/// @brief  ȡ����������������ͼ����Ŀ��
		/// @return ���س����е���ͼ����Ŀ��
		/// @author zhaowei
		/// @date   2013.11.07
		int GetGeo3DMapCount();
		/// @brief  ȡ�����еĵ���ͼ��
		/// @param  i ��0��ʼ�ĵ���ͼ�������š�
		/// @return ���س����е�i������ͼ����ָ����ŵĵ���ͼ�������򷵻�0�����ص�ָ����ָ�������ڴ��ɱ��������
		/// @author zhaowei
		/// @date   2013.11.07
		Geo3DMap* GetGeo3DMap(const int& i);
		//@}

		  ///@brief  ��ӵ���ͼ
		  ///@param  Geo3DMap* geoMap ����ӵĵ���ͼ
		  ///@return 
		  ///@author zhaowei
		  ///@date   2013.11.06
		void AddGeoMap(Geo3DMap* geoMap);

		///@brief  ��ȡ���е���ͼ
		///@param  maps ��ŵ���ͼ������
		///        mapType ��ȡ�ĵ���ͼ����
		///@return 
		///@author zhaowei
		///@date   2013.11.06
		void GetAllGeoMaps(std::vector<Geo3DMap*> &maps, const std::string& mapType);

		///@brief  ���ù����߽�����
		///@param  projectBoundary �����߽�ĵ�����
		///        count           �����߽�ĵ���
		///@return
		///@author zhaowei
		///@date   2013.11.06
		void SetProjectBoundary(double* projectBoundary, const int& count);

		///@brief  ��ȡ�����߽�����
		///@param  
		///@return ��ʾ�����߽�����������ָ��
		///@author zhaowei
		///@date   2013.11.06
		double* GetProjectBoundary();

		///@brief  ��ȡ�����߽����
		///@param  
		///@return �����߽����
		///@author zhaowei
		///@date   2013.11.06
		int GetProjectBoundaryPointCount();

		///@brief ��ȡGeoProject��Ӧ��Ԫ����
		///@param 
		///@return ����ָ��Geo3DProjectMetaData��ָ��
		///@author zhaowei
		///@date	 2013.11.01
		Geo3DProjectMetaData* GetGeoProjectMetaData();

		///@brief  ����GeoProject��Ӧ��Ԫ����
		///@param  value �����õ�Geo3DProjectMetaDataָ��
		///@return 
		///@author zhaowei
		///@date   2013.11.08
		void SetGeoProjectMetaData(Geo3DProjectMetaData* value);

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
		///@return �����������Ϊ�գ������������ƺ�����ֵΪ�յĶ��󣻷��򷵻���Ӧ������
		///@author zhaowei
		///@date   2013.11.06
		AttributeValue GetAttributeValue(const std::string& fieldname);

		///@brief  ��AttributeValue����������µ�Ԫ��
		///@param  const AttributeValue& value ����ӵ���Ԫ��
		///@return 
		///@author zhaowei
		///@date   2013.11.05
		void AddAttributeValue(const AttributeValue& value);

		///@brief  ȡ����������������ģ�͵���Ŀ��
		///@return ���س����е���ģ�͵���Ŀ��
		///@author zhaowei
		///@date   2013.11.06
		int GetGeoModelCount();

		///@brief  ȡ�����еĵ���ģ�͡�
		///@param  i ��0��ʼ�ĵ���ģ�͵������š�
		///@return ���س����е�i������ģ�͡���ָ����ŵĵ���ģ�Ͳ������򷵻�0�����ص�ָ����ָ�������ڴ��ɱ��������
		///@author zhaowei
		///@date   2013.11.07
		GeoModel* GetGeoModel(const int& i);

		///@brief  ��ӵ���ģ��
		///@param  geoModel ����ӵĵ���ģ��
		///@return 
		///@author zhaowei
		///@date   2013.11.06
		void AddGeoModel(GeoModel* geoModel);

		///@brief  ��ȡ���е���ģ��
		///@param  models ��ŵ���ģ�͵�����
		///        modelType ��ȡ�ĵ���ģ������
		///@return 
		///@author zhaowei
		///@date   2013.11.06
		void GetAllGeoModels(std::vector<GeoModel*> &models, std::string modelType);

		///@brief  �ͷŹ�����ڴ�
		///@param  
		///@return
		///@author zhaowei
		///@date   2013.11.13
		void deleteMembers();

		///@brief ����Layer���ӦFeatureClass�Ĺ����������Model�е�����Feature��FeatureRelation
		///@author wang
		///@date 2013.11.26
		void UpdateRefences();
		///@brief  ɾ��ȫ��AttributeValue����������µ�Ԫ��
		///@return 
		///@author xiehaifeng
		///@date   2013.12.26
		void DeleteAllAttributeValue();

		void setDescription(std::string);
		std::string getDescription();

		GeoSceneStyle*           GetSceneStyle();
	protected:
		std::vector<AttributeValue>  attributeValues;
		Geo3DProjectMetaData*    metaData;
		std::vector<Geo3DMap*>   geo3DMaps;
		std::vector<GeoModel*>   geoModels;
		double*                  projectBoundary;
		int                      pointCount;
		GeoSceneStyle*           sceneStyle;
		std::string              projDescription;

	};

}
#endif // Geo3DProject_h__