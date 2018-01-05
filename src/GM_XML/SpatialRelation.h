#ifndef SpatialRelation_h__
#define SpatialRelation_h__

#include "FeatureRelation.h"

namespace gmml
{
	class GEOXML_EXPORT SpatialRelation : public FeatureRelation
	{
	public:
		///@brief  ���캯��
		///@author zhaowei
		///@date   2013.11.13
		SpatialRelation(void);

		///@brief  ��������
		///@author zhaowei
		///@date   2013.11.13
		~SpatialRelation(void);

		///@brief  ��ȡ���������
		///@param
		///@return �����������
		///@author zhaowei
		///@date   2013.11.13
		virtual std::string GetClassName() { return "SpatialRelation"; };

	private:

	};
}

#endif // SpatialRelation_h__
