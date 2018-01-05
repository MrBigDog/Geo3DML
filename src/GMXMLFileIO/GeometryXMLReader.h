#pragma once
#include "xmlreader.h"
#include <vector>
#include "MappedFeature.h"

class vtkObject;
class GMPolyData;
class GMUnstructuredGrid;
class vtkPointSet;
class GMStructuredPoints;
class vtkDataArray;
class GMCornerPointGrid;

class GMXMLFILEIO_EXPORT GeometryXMLReader :
	public XMLReader
{
public:
	GeometryXMLReader(void);
	~GeometryXMLReader(void);
	//gml::AbstractGML* GetShape();
	static int BinaryExport;	//�Ƿ���Ϊ�����ƶ��ı�ʶ��
	vtkObject* GetReadShape();


	bool ReadNode(xmlNodePtr geometryNode, gmml::MappedFeature* mappedFeature);
	virtual vtkObject* ReadShape(xmlNode* geometryNode);
	vtkObject* ReadPolyDataTIN(xmlNode* geometryNode);
	vtkObject* ReadPolyDataTEN(xmlNode* geometryNode);
	vtkDataArray*  GeometryXMLReader::ReadDiscreteCoverageGMML(xmlNode* geometryNode);
	vtkDataArray*  GeometryXMLReader::ReadDataArray(xmlNode* arrayNode);
	///@brief  ��ȡ<LineString>��ǩ
	///@param  geometryNode <LineString>��ǩ��xml���ָ��
	///@return ��LineString����ΪvtkObject����
	///@author zhaowei
	///@date   2013.11.19
	vtkObject* ReadPolyDataLine(xmlNode* geometryNode);
	vtkObject* ReadPolyDataPoints(xmlNode* geometryNode);
	vtkObject* ReadGeoVolume(xmlNode* geometryNode);
	vtkObject* ReadGeoGrid(xmlNode* geometryNode);
	vtkObject* ReadGeoCornerPointGrid(xmlNode* geometryNode);

	vtkDataArray* ReadValueArray(xmlNode* arrayNode);

	///@brief  ��ȡ<DiscreteCoverage>��ǩ�µ�����
	///@param  dataarrays ����<ValueArray>��ǩ�µ�����
	///@param  dataarraytypes ����ValueArray�����ͱ��
	///@param  dataarraysname ����ValueArray��Ӧ����������
	///@return ���RangeSet�е�ValueArrayֵ��RangeType�й涨�������ֶ�һ�£�����true�����򷵻�false
	///@author zhaowei
	///@date   2013.11.18
	bool ReadDiscreteCoverage(xmlNode* geometryNode,std::vector<vtkDataArray*> &dataarrays,std::vector<int> &dataarraytypes, std::vector<std::string>& dataarraysname);

	///@brief  ��ȡ<ShapeProperty>��ǩ
	///@param  arrayNode ָ��<ShapeProperty>��ǩ��xmlָ��
	///@author zhaowei
	///@date   2013.11.18
	void ReadProperty(xmlNode* arrayNode);
		 
protected:
	bool ReadRectifiedGrid(GMStructuredPoints*,xmlNode* geometryNode);
	bool ReadPillars(GMCornerPointGrid*,xmlNode* geometryNode);
	bool ReadCCells(GMCornerPointGrid*,xmlNode* geometryNode);
	bool ReadVertices(vtkPointSet*,xmlNode*);
	bool ReadTriangles(GMPolyData*,xmlNode*);
	bool ReadCells(GMUnstructuredGrid*,xmlNode*);

	 
		vtkObject* ShapeObject;
	 

};

