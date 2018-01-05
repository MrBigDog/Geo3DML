#ifndef FeatureRelation_h__
#define FeatureRelation_h__

#include "AbstractGML.h"

namespace gmml
{
	static std::string BoundaryRelationshipTerm;
	static std::string BoundaryRelationshipSourceRoleTerm;
	static std::string BoundaryRelationshipTargetRoleTerm;
	static std::string SpatialTopologicalAggregationRelationshipTerm;
	static std::string SpatialTopologicalAggregationRelationshipSourceRole;
	static std::string SpatialTopologicalAggregationRelationshipTargetRole;

	class GEOXML_EXPORT FeatureRelation : public gml::AbstractGML
	{
	public:
		///@brief  ���캯��
		///@author zhaowei
		///@date   2013.11.13
		FeatureRelation(void);

		///@brief  ��������
		///@author zhaowei
		///@date   2013.11.13
		~FeatureRelation(void);

		///@brief  ��ȡ���������
		///@param
		///@return �����������
		///@author zhaowei
		///@date   2013.11.13
		virtual std::string GetClassName() { return "FeatureRelation"; };

		///@brief  ��������Feature֮��Ĺ�ϵ
		///@param  term �����õĹ�ϵ
		///@return
		///@author zhaowei
		///@date   2013.11.13
		void setRelationship(const std::string& term);

		///@brief  ��ȡ��ϵ
		///@param
		///@return ���ع�ϵ
		///@author zhaowei
		///@date   2013.11.13
		std::string getRelationship() const;

		///@brief  ����Դ��ɫ
		///@param  Դ��ɫ�ַ���
		///@return
		///@author zhaowei
		///@date   2013.11.13
		void setSourceRole(const std::string& term);

		///@brief  ��ȡԴ��ɫ
		///@param  
		///@return ����Դ��ɫ�ַ���
		///@author zhaowei
		///@date   2013.11.13
		std::string getSourceRole() const;

		///@brief  ����Ŀ���ɫ
		///@param  Ŀ���ɫ�ַ���
		///@return
		///@author zhaowei
		///@date   2013.11.13
		void addTargetRole(const std::string& term);

		///@brief  ��ȡĿ���ɫ
		///@param  
		///@return ����Ŀ���ɫ�ַ���
		///@author zhaowei
		///@date   2013.11.13	
		std::string getTargetRole(int) const;

		///@brief ��ȡĿ���ɫ��Ŀ
		///@return ����Ŀ���ɫ��Ŀ
		///@author wang
		///@date 2013.11.26
		int GetTargetCount();
		//@}

		///@brief  ����ڴ���������
		///@param
		///@return
		///@author zhaowei
		///@date   2013.11.13
		void deleteMembers();
	private:
		/// Ҫ��֮��Ĺ�ϵ����
		std::string relationshipTerm;
		/// ԴҪ��
		std::string source;
		/// Ŀ��Ҫ������
		std::vector<std::string> targets;

	};

}

#endif // FeatureRelation_h__
