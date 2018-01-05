#ifndef Geo3DStyle_h__
#define Geo3DStyle_h__



#include "AbstractGML.h"
#include "Featurestyle.h"

namespace se
{
	class FeatureType3DStyle;
	class CoverageType3DStyle;
}

namespace gmml
{
	class GEOXML_EXPORT Geo3DStyle : public gml::AbstractGML
	{
	public:
		///@brief  ���캯��
		///@author zhaowei
		///@date   2013.11.14
		Geo3DStyle(void);

		///@brief  ��������
		///@author zhaowei
		///@date   2013.11.14
		~Geo3DStyle(void);

		///@brief  ��ȡ������
		///@param
		///@return �������
		///@author zhaowei
		///@date   2013.11.14
		virtual std::string GetClassName() { return "Geo3DStyle"; };

		///@brief  ��ȡFeatureTypeStyle
		///@param  i FeatureTypeStyle�����
		///@return ����FeatureTypeStyle
		///@author zhaowei
		///@date   2013.11.14
		se::FeatureType3DStyle* GetFeatureTypeStyle(int i);

		///@brief ��ȡFeatureTypeStyle����Ŀ
		///@return ����FeatureTypeStyle����Ŀ
		///@author wang
		///@date 2013.11
		int GetFeatureTypeStyleCount();

		///@brief  ����FeatureTypeStyle
		///@param  value �����õ�FeatureTypeStyle
		///@return
		///@author zhaowei
		///@date   2013.11.14
		void SetFeatureTypeStyle(se::FeatureType3DStyle* value);


		///@brief  ��ȡ������

	///@brief  ��ȡCoverageTypeStyle
	///@param  i CoverageTypeStyle�����
	///@return ����CoverageTypeStyle
	///@author zhaowei
	///@date   2013.11.14
		se::CoverageType3DStyle* GetCoverageTypeStyle(int i);

		///@brief ��ȡCoverageTypeStyle����Ŀ
		///@return ����CoverageTypeStyle����Ŀ
		///@author wang
		///@date 2013.11
		int GetCoverageTypeStyleCount();

		///@brief  ����CoverageTypeStyle
		///@param  value �����õ�CoverageTypeStyle
		///@return
		///@author zhaowei
		///@date   2013.11.14
		void SetCoverageTypeStyle(se::CoverageType3DStyle* value);

		///@brief  �ͷŹ�����ڴ�
		///@param  
		///@return
		///@author zhaowei
		///@date   2013.11.13
		void deleteMembers();
	private:
		std::vector<se::FeatureType3DStyle*> featureStyles_;
		std::vector<se::CoverageType3DStyle*> coverageStyles_;
	};

}

#endif // Geo3DStyle_h__
