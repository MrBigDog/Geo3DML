#ifndef GeologicFeature_h__
#define GeologicFeature_h__

#include "AbstractFeature.h" 

namespace gmml
{
	class MappedFeature;
	class GEOXML_EXPORT GeologicFeature : public gml::AbstractFeature
	{
	public:
		///@brief  ���캯��
		///@author zhaowei
		///@date   2013.11.13
		GeologicFeature(void);

		///@brief  ��������
		///@author zhaowei
		///@date   2013.11.13
		~GeologicFeature(void);

		///@brief  ��ȡ���������
		///@param 
		///@return ����������
		///@author zhaowei
		///@date   2013.11.13
		std::string GetClassName() { return "GeologicFeature"; };

		///@brief  ȡҪ�ص���������
		///@param  
		///@return Ҫ�ص���������
		///@author zhaowei
		///@date   2013.11.13
		std::string GetFeatureType();

		///@brief  ����Ҫ�ص�������
		///@param  value �����õ�Ҫ������
		///@return 
		///@author zhaowei
		///@date   2013.11.13
		void SetFeatureType(const std::string& value);

		///@brief  ��ȡGeologicFeature������MappedFeature��Ŀ
		///@param  
		///@return ����MappedFeature��Ŀ
		///@author zhaowei
		///@date   2013.11.13
		int GetMappedFeatureCount();

		///@brief  ��ȡָ����ŵ�MappedFeature
		///@param  i ���
		///@return ָ��MappedFeature��ָ��
		///@author zhaowei
		///@date   2013.11.13
		MappedFeature* GetMappedFeature(const int& i);

		///@brief  ��ȡȫ����MappedFeature
		///@param  mapped_features ��Ϊ���ò��������ڱ���ȫ����mappedFeature
		///@return 
		///@author zhaowei
		///@date   2013.11.13
		void GetAllMappedFeature(std::vector<MappedFeature*>& mapped_features);

		///@brief  ����µ�MappedFeature
		///@param  value ����ӵ�MappedFeature
		///@return 
		///@author zhaowei
		///@date   2013.11.08
		void AddMappedFeature(MappedFeature* value);

		///@brief  �ͷŹ�����ڴ�
		///@param  
		///@return
		///@author zhaowei
		///@date   2013.11.13
		void deleteMembers();

		///@brief ����뱾����Ҫ���б߽��ϵ������Ҫ��
		///@param f �б߽��������������Ҫ��
		///@author wang
		///@date 2013.11.26
		void AddBoundaryFeature(GeologicFeature* f);

		///@brief ��ȡ�б߽��ϵ��Ҫ���������Ŀ
		///@return �����б߽��ϵ��Ҫ����Ŀ
		///@author wang
		///@date 2013.11.26
		int  GetBoundaryFeatureCount();

		///@brief ��ȡָ����ŵ��б߽���ϵ������Ҫ��
		///@param i ���
		///@return ����ָ����ŵĵ���Ҫ�ص�ָ��
		///@author wang
		///@date 2013.11.26
		GeologicFeature* GetBoundaryFeature(int i);
	protected:
		/// Ҫ������
		std::string featureType;
		/// Ҫ�ض�Ӧ�ļ���������
		std::vector<MappedFeature*>  mappedFeatures; // Geometry
		/// �뱾Ҫ���б߽��ϵ������Ҫ������
		std::vector<GeologicFeature*>  boundaryFeatures;
	};

}

#endif // GeologicFeature_h__
