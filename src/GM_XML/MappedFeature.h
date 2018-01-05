#ifndef MappedFeature_h__
#define MappedFeature_h__

#include "AbstractFeature.h" 

class vtkObject;

namespace gmml
{
	// MappedFeature == Geo3DML::Geometry
	class GEOXML_EXPORT MappedFeature : public gml::AbstractFeature
	{
	public:
		///@brief  ���캯��
		///@author zhaowei
		///@date   2013.11.13
		MappedFeature(void);

		///@brief  ��������
		///@author zhaowei
		///@date   2013.11.13
		~MappedFeature(void);

		///@brief  ��ȡ���������
		///@param
		///@return �����������
		///@author zhaowei
		///@date   2013.11.13
		virtual std::string GetClassName() { return "MappedFeature"; };

		///@brief  �ͷŹ�����ڴ�
		///@param  
		///@return
		///@author zhaowei
		///@date   2013.11.13
		void deleteMembers();

		///@brief  ��ȡ��������
		///@param
		///@return ָ�򼸺����ݵ�ָ��
		///@author zhaowei
		///@date   2013.11.13
		vtkObject* GetShape();

		///@brief  ���ü�������
		///@param  value �����õļ�������
		///@return 
		///@author zhaowei
		///@date   2013.11.13
		void SetShape(vtkObject* value);

		///@brief �жϼ��������Ƿ����
		///@author zhaowei
		///@date 2014.03.20
		bool isShaped();


	protected:
		vtkObject* shape;
	};

}

#endif // MappedFeature_h__
