#pragma once
#include "xmlwriter.h"
#include <string>
#include "vtkPointData.h"
#include "../vtkExtending/GMPolyData.h"
#include "../vtkExtending/GMUnstructuredGrid.h"
#include "../vtkExtending/GMStructuredPoints.h"
#include "vtkCellArray.h"
#include "vtkMath.h"
#include "vtkPoints.h"
#include "vtkPointData.h"
#include "vtkCellData.h"
#include "vtkDoubleArray.h"
#include "vtkFloatArray.h"

#include "vtkCharArray.h"
#include "vtkLongArray.h"
#include "vtkIntArray.h"
//#include "vtkPolyDataNormals.h"

namespace gmml
{
	class GeologicFeature;
	class MappedFeature;
}
class GMXMLFILEIO_EXPORT GeoFeatureXMLWriter :	public XMLWriter
{
public:
	///@brief ���캯��
	///@author zhaowei
	///@date 2014.03.19
	GeoFeatureXMLWriter(void);

	///@brief ��������
	///@author zhaowei
	///@date 2014.04.19
	~GeoFeatureXMLWriter(void);

	///@brief ��GeoFeatureд���ļ�
	///@param feature ָ��Feature��ָ��
	///@param xml_stream д���ļ���
	///@author zhaowei
	///@date 2014.03.19	
	void WriteFeature(gmml::GeologicFeature* feature, std::ostream& xml_stream);

	///@brief ��MappedFeatureд���ļ�
	///@param mapped_feature ָ��MappedFeature��ָ��
	///@param xml_stream д���ļ���
	///@author zhaowei
	///@date 2014.03.19
	void WriteMappedFeature(gmml::MappedFeature* mapped_feature, std::ostream& xml_stream);

	///@brief ��MappedProperyд���ļ�
	///@param feature ָ��MappedFeature��ָ��	
	///@param xml_stream д���ļ���
	///@author zhaowei
	///@date 2014.03.19
	void WriteMappedProperty(gmml::MappedFeature* mapped_feature, std::ostream& xml_stream);

	///@brief ��DiscreteCoverageд���ļ�
	///@param position_type ���Գ���λ��
	///@param shape_property ������Ϣ
	///@param xml_stream д���ļ���
	///@param geoid ���Գ����
	///@author zhaowei
	///@date 2014.03.19
	void WriteDiscreteCoverage(int position_type, vtkObject* shape_property, std::ostream& xml_stream, std::string geoid);
};

