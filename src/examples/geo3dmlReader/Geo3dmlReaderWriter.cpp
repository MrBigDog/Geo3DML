#include <osg/TransferFunction>
#include <osgDB/Registry>
#include <osgDB/ReaderWriter>
#include <osgDB/FileUtils>
#include <osgDB/FileNameUtils>
#include <osgDB/WriteFile>

#include <GM_XML/Geo3DProject.h>
#include <GM_XML/FeatureClass.h>
#include <GM_XML/GeologicFeature.h>
#include <GM_XML/MappedFeature.h>
#include <GM_XML/GeoModel.h>
#include <GM_XML/Geo3DMap.h>
#include <GM_XML/Geo3DLayer.h>
#include <GM_XML/Geo3DStyle.h>
#include <GM_XML/FeatureStyle.h>
#include <GM_XML/GeoSymbolizer.h>
#include <GM_XML/FeatureRelation.h>
#include <GMLFeature/gmlFeatureCollection.h>
#include <GMXMLFileIO/Geo3DProjectXMLReader.h>
#include <vtkExtending/vtkObject.h>
#include <vtkExtending/GMPolyData.h>
#include <vtkExtending/vtkCellArray.h>
#include <vtkExtending/GMUnstructuredGrid.h>
#include <vtkExtending/vtkFieldData.h>
#include <vtkExtending/vtkPointData.h>
#include <vtkExtending/vtkDataArray.h>
#include <vtkExtending/vtkDoubleArray.h>

namespace
{
	//template <typename Iterator> size_t get_length(Iterator p)
	//{
	//	unsigned char c = static_cast<unsigned char> (*p);
	//	if (c < 0x80) return 1;
	//	else if (!(c & 0x20)) return 2;
	//	else if (!(c & 0x10)) return 3;
	//	else if (!(c & 0x08)) return 4;
	//	else if (!(c & 0x04)) return 5;
	//	else return 6;
	//}

	//typedef unsigned int value_type;
	//template <typename Iterator>
	//value_type get_value(Iterator p)
	//{
	//	size_t len = get_length(p);
	//	if (len == 1) return *p;
	//	value_type res = static_cast<unsigned char> (*p & (0xff >> (len + 1))) << ((len - 1) * 6);
	//	for (--len; len; --len) {
	//		value_type next_byte = static_cast<unsigned char> (*(++p)) - 0x80;
	//		if (next_byte & 0xC0) return 0x00ffffff; // invalid UTF-8
	//		res |= next_byte << ((len - 1) * 6);
	//	}
	//	return res;
	//}

	//string utf8ToLatin1(string& s_utf8)
	//{
	//	string s_latin1;
	//	for (string::iterator p = s_utf8.begin(); p != s_utf8.end(); ++p)
	//	{
	//		value_type value = get_value<string::iterator&>(p);
	//		if (value > 0x10ffff)
	//		{
	//			return s_utf8; // invalid UTF-8: guess that the input was already Latin-1
	//		}
	//		if (value > 0xff)
	//		{
	//			//GW_LOG(GW_IO, GW_WARN, "utf8ToLatin1: wrong char value: " << value);
	//		}
	//		s_latin1 += static_cast<char>(value);
	//	}
	//	return s_latin1;
	//}

	osg::Node* createFeatureNode(gmml::GeologicFeature* gf, osg::TransferFunction1D* tf, const osg::Vec4& color)
	{
		osg::ref_ptr<osg::Geode> geode = new osg::Geode;
		for (int i = 0; i < gf->GetMappedFeatureCount(); ++i)
		{
			gmml::MappedFeature* mf = gf->GetMappedFeature(i);
			std::string name = mf->getName();
			vtkObject* shape = mf->GetShape();

			std::string shapeName = shape->GetClassName();

			//TrangleMeshModel
			if (shapeName == "GMPolyData")
			{
				GMPolyData* poly_data = (GMPolyData*)shape;
				if (poly_data && poly_data->GetGeometryType() == 5)
				{
					vtkPoints* points = poly_data->GetPoints();
					int pointNum = points->GetNumberOfPoints();
					osg::ref_ptr<osg::Vec3Array> va = new osg::Vec3Array;
					va->reserve(pointNum);
					for (int i = 0; i < pointNum; i++)
					{
						osg::Vec3d p;
						points->GetPoint(i, p.ptr());
						va->push_back(p);
					}

					osg::ref_ptr<osg::DrawElementsUInt> de = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);

					vtkCellArray* cellAry = poly_data->GetPolys();
					int cellNum = cellAry->GetNumberOfCells();

					osg::ref_ptr<osg::Vec3Array> na = new osg::Vec3Array; na->resize(va->size());
					for (int i = 0; i < cellNum * 4; i += 4)
					{
						vtkIdType counta;
						vtkIdType *pts;
						cellAry->GetCell(i, counta, pts);
						if (counta != 3) continue;

						de->push_back(pts[0]);
						de->push_back(pts[1]);
						de->push_back(pts[2]);

						osg::Vec3 v1 = va->at(pts[0]);
						osg::Vec3 v2 = va->at(pts[1]);
						osg::Vec3 v3 = va->at(pts[2]);

						osg::Plane plane(v1, v2, v3);
						osg::Vec3 nn = plane.getNormal();

						(*na)[pts[0]] = nn;
						(*na)[pts[1]] = nn;
						(*na)[pts[2]] = nn;
					}

					osg::ref_ptr<osg::Vec4Array> ca = new osg::Vec4Array;
					ca->push_back(color);

					osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
					geom->setUseDisplayList(false);
					geom->setUseVertexBufferObjects(true);
					geom->setName(shapeName);
					geom->setVertexArray(va);
					geom->setNormalArray(na, osg::Array::BIND_PER_VERTEX);
					geom->setColorArray(ca, osg::Array::BIND_OVERALL);
					geom->addPrimitiveSet(de);
					geode->addDrawable(geom);
				}
			}
			else if (shapeName == "GMUnstructuredGrid")//VoxelModel
			{
				GMUnstructuredGrid* grid = (GMUnstructuredGrid*)shape;
				vtkPoints* points = grid->GetPoints();
				int pointNum = points->GetNumberOfPoints();

				//Vertex
				osg::ref_ptr<osg::Vec3Array> va = new osg::Vec3Array;
				//va->setVertexBufferObject(vbo);
				va->reserve(pointNum);
				for (int i = 0; i < pointNum; i++)
				{
					osg::Vec3d p;
					points->GetPoint(i, p.ptr());
					va->push_back(p);
				}

				//Attribuate;
				osg::ref_ptr<osg::Vec4Array> ca = 0L;
				int num1 = grid->GetPointData()->GetNumberOfArrays();
				if (num1 > 0)
				{
					ca = new osg::Vec4Array;
					//ca->setVertexBufferObject(vbo);
					ca->reserve(pointNum);
					vtkDataArray * vPointData = grid->GetPointData()->GetArray(0);
					if (0 == strcmp(vPointData->GetClassName(), "vtkDoubleArray"))
					{
						vtkDoubleArray* dataA = (vtkDoubleArray*)vPointData;
						unsigned long tnum = dataA->GetNumberOfTuples()*dataA->GetNumberOfComponents();
						for (unsigned long i = 0; i < tnum; ++i)
						{
							double fValue = dataA->GetValue(i);
							osg::Vec4 color = tf->getColor(fValue);
							ca->push_back(color);
						}
					}
				}

				//Shape
				vtkCellArray* cellAry = grid->GetCells();
				if (grid->GetGeometryType() == 10)//四面体;
				{
					int tCount = grid->GetNumberOfCells();
					for (int i = 0; i < tCount * 5; i = i + 5)
					{
						vtkIdType counta;
						vtkIdType *pts;
						cellAry->GetCell(i, counta, pts);

						if (counta != 4) continue;
					}
				}
				else if (grid->GetGeometryType() == 12)//六面体;
				{
					int tnum = grid->GetNumberOfCells() * 9;
					for (int i = 0; i < tnum; i = i + 9)
					{
						vtkIdType counta;
						vtkIdType *pts;
						cellAry->GetCell(i, counta, pts);

						if (counta != 8) continue;

						osg::ref_ptr<osg::Vec3Array> cubeVa = new osg::Vec3Array; cubeVa->reserve(24);
						osg::ref_ptr<osg::Vec4Array> cubeCa = new osg::Vec4Array; cubeCa->reserve(24);
						osg::ref_ptr<osg::Vec3Array> cubeNa = new osg::Vec3Array; cubeNa->reserve(24);

						cubeVa->push_back(va->at(pts[0]));
						cubeVa->push_back(va->at(pts[1]));
						cubeVa->push_back(va->at(pts[2]));
						cubeVa->push_back(va->at(pts[3]));
						if (ca&&ca->size() == va->size())
						{
							cubeCa->push_back(ca->at(pts[0]));
							cubeCa->push_back(ca->at(pts[1]));
							cubeCa->push_back(ca->at(pts[2]));
							cubeCa->push_back(ca->at(pts[3]));
						}
						cubeNa->push_back(osg::Vec3(0, 0, -1));
						cubeNa->push_back(osg::Vec3(0, 0, -1));
						cubeNa->push_back(osg::Vec3(0, 0, -1));
						cubeNa->push_back(osg::Vec3(0, 0, -1));

						cubeVa->push_back(va->at(pts[4]));
						cubeVa->push_back(va->at(pts[5]));
						cubeVa->push_back(va->at(pts[6]));
						cubeVa->push_back(va->at(pts[7]));
						if (ca&&ca->size() == va->size())
						{
							cubeCa->push_back(ca->at(pts[4]));
							cubeCa->push_back(ca->at(pts[5]));
							cubeCa->push_back(ca->at(pts[6]));
							cubeCa->push_back(ca->at(pts[7]));
						}
						cubeNa->push_back(osg::Vec3(0, 0, 1));
						cubeNa->push_back(osg::Vec3(0, 0, 1));
						cubeNa->push_back(osg::Vec3(0, 0, 1));
						cubeNa->push_back(osg::Vec3(0, 0, 1));

						cubeVa->push_back(va->at(pts[1]));
						cubeVa->push_back(va->at(pts[5]));
						cubeVa->push_back(va->at(pts[4]));
						cubeVa->push_back(va->at(pts[0]));
						if (ca&&ca->size() == va->size())
						{
							cubeCa->push_back(ca->at(pts[1]));
							cubeCa->push_back(ca->at(pts[5]));
							cubeCa->push_back(ca->at(pts[4]));
							cubeCa->push_back(ca->at(pts[0]));
						}
						cubeNa->push_back(osg::Vec3(0, -1, 0));
						cubeNa->push_back(osg::Vec3(0, -1, 0));
						cubeNa->push_back(osg::Vec3(0, -1, 0));
						cubeNa->push_back(osg::Vec3(0, -1, 0));

						cubeVa->push_back(va->at(pts[1]));
						cubeVa->push_back(va->at(pts[2]));
						cubeVa->push_back(va->at(pts[6]));
						cubeVa->push_back(va->at(pts[5]));
						if (ca&&ca->size() == va->size())
						{
							cubeCa->push_back(ca->at(pts[1]));
							cubeCa->push_back(ca->at(pts[2]));
							cubeCa->push_back(ca->at(pts[6]));
							cubeCa->push_back(ca->at(pts[5]));
						}
						cubeNa->push_back(osg::Vec3(1, 0, 0));
						cubeNa->push_back(osg::Vec3(1, 0, 0));
						cubeNa->push_back(osg::Vec3(1, 0, 0));
						cubeNa->push_back(osg::Vec3(1, 0, 0));

						cubeVa->push_back(va->at(pts[2]));
						cubeVa->push_back(va->at(pts[6]));
						cubeVa->push_back(va->at(pts[7]));
						cubeVa->push_back(va->at(pts[3]));
						if (ca&&ca->size() == va->size())
						{
							cubeCa->push_back(ca->at(pts[2]));
							cubeCa->push_back(ca->at(pts[6]));
							cubeCa->push_back(ca->at(pts[7]));
							cubeCa->push_back(ca->at(pts[3]));
						}
						cubeNa->push_back(osg::Vec3(0, 1, 0));
						cubeNa->push_back(osg::Vec3(0, 1, 0));
						cubeNa->push_back(osg::Vec3(0, 1, 0));
						cubeNa->push_back(osg::Vec3(0, 1, 0));

						cubeVa->push_back(va->at(pts[3]));
						cubeVa->push_back(va->at(pts[7]));
						cubeVa->push_back(va->at(pts[4]));
						cubeVa->push_back(va->at(pts[0]));
						if (ca&&ca->size() == va->size())
						{
							cubeCa->push_back(ca->at(pts[3]));
							cubeCa->push_back(ca->at(pts[7]));
							cubeCa->push_back(ca->at(pts[4]));
							cubeCa->push_back(ca->at(pts[0]));
						}
						cubeNa->push_back(osg::Vec3(-1, 0, 0));
						cubeNa->push_back(osg::Vec3(-1, 0, 0));
						cubeNa->push_back(osg::Vec3(-1, 0, 0));
						cubeNa->push_back(osg::Vec3(-1, 0, 0));

						osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
						geom->setUseDisplayList(false);
						geom->setUseVertexBufferObjects(true);
						geom->setVertexArray(cubeVa);
						geom->setNormalArray(cubeNa, osg::Array::BIND_PER_VERTEX);
						geom->setColorArray(cubeCa, osg::Array::BIND_PER_VERTEX);
						geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, cubeVa->size()));

						geode->addDrawable(geom);
					}
				}
			}
		}
		return geode.release();
	}

	typedef std::map<std::string, gmml::GeologicFeature*> GeoFeatureMap;
	typedef std::map<std::string, GeoFeatureMap> GeoDataMap;

	void readModelGeoData(gmml::GeoModel* pModel, GeoDataMap& geoData)
	{
		int fc_count = pModel->GetGeoFeatureClassCount();
		for (int i = 0; i < fc_count; ++i)
		{
			gmml::GeologicFeatureClass* pFCls = pModel->GetGeoFeatureClass(i);
			int f_count = pFCls->GetGeologicFeatureCount();
			GeoFeatureMap& lstNames = geoData.insert(std::make_pair(pFCls->getID(), GeoFeatureMap())).first->second;
			for (int j = 0; j < f_count; ++j)
			{
				gmml::GeologicFeature* pFC = pFCls->GetGeologicFeature(j);
				lstNames.insert(std::make_pair(pFC->getName(), pFC));
			}
		}
	}
}

//  [1/5/2018 BigDog]
class Geo3dmlReaderWriter :public osgDB::ReaderWriter
{
private:
	osg::ref_ptr< osg::TransferFunction1D> _transferFunction;

public:
	Geo3dmlReaderWriter()
	{
		supportsExtension("xml", "geo3dml reader");
		supportsExtension("geo3dxml", "geo3dml reader");
		_transferFunction = new osg::TransferFunction1D();
		_transferFunction->setColor(0, osg::Vec4(46.0f / 255.0f, 154.0f / 255.0f, 88.0f / 255.0f, 1.0f));
		_transferFunction->setColor(18000 * 2, osg::Vec4(251.0f / 255.0f, 255.0f / 255.0f, 128.0f / 255.0f, 1.0f));
		_transferFunction->setColor(28000 * 2, osg::Vec4(224.0f / 255.0f, 108.0f / 255.0f, 31.0f / 255.0f, 1.0f));
		_transferFunction->setColor(35000 * 2, osg::Vec4(200.0f / 255.0f, 55.0f / 255.0f, 55.0f / 255.0f, 1.0f));
		_transferFunction->setColor(40000 * 2, osg::Vec4(215.0f / 255.0f, 244.0f / 255.0f, 244.0f / 255.0f, 1.0f));
	}

	const char* className() const { return "Geo3dmlReaderWriter"; }

	bool acceptsExtension(const std::string& extension) const
	{
		return
			osgDB::equalCaseInsensitive(extension, "xml") ||
			osgDB::equalCaseInsensitive(extension, "geo3dxml");
	}

	ReadResult readObject(const std::string& filename, const osgDB::Options* options) const
	{
		return readNode(filename, options);
	}

	virtual ReadResult readObject(std::istream& fin, const Options* options) const
	{
		return ReadResult::FILE_NOT_HANDLED;
	}

	virtual ReadResult readImage(const std::string& file, const Options* options) const
	{
		return ReadResult::FILE_NOT_HANDLED;
	}

	virtual ReadResult readImage(std::istream& fin, const Options* options) const
	{
		return ReadResult::FILE_NOT_HANDLED;
	}

	ReadResult readNode(const std::string& file, const osgDB::Options* options) const
	{
		if (!acceptsExtension(osgDB::getLowerCaseFileExtension(file)))
			return ReadResult::FILE_NOT_HANDLED;

		if (!osgDB::fileExists(file))
		{
			return ReadResult::FILE_NOT_HANDLED;
		}

		Geo3DProjectXMLReader xmlreader;
		if (!xmlreader.ReadFile(file.c_str(), ""))
		{
			return ReadResult::FILE_NOT_HANDLED;
		}

		gmml::Geo3DProject* project = dynamic_cast<gmml::Geo3DProject*>(xmlreader.GetGeoProject());

		if (!project) return ReadResult(0L);

		GeoDataMap geoData;
		std::map<std::string, gmml::FeatureRelation*> relData;

		for (int mi = 0; mi < project->GetGeoModelCount(); ++mi)
		{
			gmml::GeoModel* pModel = project->GetGeoModel(mi);
			if (!pModel) continue;
			readModelGeoData(pModel, geoData);


			// 读取关系 [1/26/2018 mahc]
			int nCount = pModel->GetGeoFeatureRelationCount();
			for (int i = 0; i < nCount; ++i)
			{
				gmml::FeatureRelation* pRel = pModel->GetGeoFeatureRelation(i);
				relData.insert(std::make_pair(pRel->getSourceRole(), pRel));
			}

		}

		if (geoData.empty())
		{
			return ReadResult(0L);
		}

		osg::ref_ptr<osg::Group> projGroup = new osg::Group;

		for (int i = 0; i < project->GetGeo3DMapCount(); ++i)
		{
			gmml::Geo3DMap* pMap = project->GetGeo3DMap(i);
			int layercount = pMap->GetGeo3DLayerCount();
			for (int j = 0; j < layercount; ++j)
			{
				//if (j != 0)
				//{
				//	continue;
				//}
				gmml::Geo3DLayer* layer = pMap->GetLayer(j);
				if (!layer) continue;

				gmml::GeologicFeatureClass* fc = layer->GetFeatureClass();
				//与Model中的数据对应
				auto itFeatureClass = geoData.find(fc->getID());
				if (itFeatureClass == geoData.end())
				{
					continue;
				}

				osg::ref_ptr<osg::Group> layerGroup = new osg::Group;

				gmml::Geo3DStyle* style = layer->GetStyle();
				int ftsNum = style->GetFeatureTypeStyleCount();
				for (int ftsi = 0; ftsi < ftsNum; ++ftsi)
				{
					se::FeatureType3DStyle* fts = style->GetFeatureTypeStyle(ftsi);
					std::string name = fts->getFeatureTypeName();

					int rulNum = fts->getRuleCount();
					for (int ruli = 0; ruli < rulNum; ++ruli)
					{
						se::FeatureStyleRule* rule = fts->getRule(ruli);
						if (!rule) continue;

						auto itFeature = itFeatureClass->second.find(rule->Literal);
						if (itFeature == itFeatureClass->second.end())
						{
							auto itRel = relData.find(rule->Literal);
							if (itRel == relData.end())
							{
								continue;
							}
							osg::ref_ptr<osg::Group> featureGroup = new osg::Group;
							for (int iRel = 0; iRel < itRel->second->GetTargetCount(); ++iRel)
							{
								std::string str = itRel->second->getTargetRole(iRel);
								auto itFeature = itFeatureClass->second.find(str);
								gmml::GeologicFeature* pFC = NULL;
								if (itFeature == itFeatureClass->second.end())
								{
									for (auto it = geoData.begin(); it != geoData.end(); ++it)
									{
										itFeature = it->second.find(str);
										if (itFeature != it->second.end())
										{
											pFC = itFeature->second;
											break;
										}
									}
								}
								else
								{
									pFC = itFeature->second;
								}


								if (NULL != pFC)
								{

									se::GeoSymbolizer* gs = rule->GetSymbolizer();
									osg::Vec4 color(1, 1, 1, 1);
									if (gs)
									{
										color = osg::Vec4(gs->DiffuseColor[0], gs->DiffuseColor[1], gs->DiffuseColor[2], 1.0);
									}
									osg::ref_ptr<osg::Node> node = createFeatureNode(pFC, _transferFunction, color);
									if (node.valid())
									{
										featureGroup->addChild(node);
									}
								}
							}
							layerGroup->addChild(featureGroup);
							continue;
						}

						gmml::GeologicFeature* geoFeature = itFeature->second;
						if (!geoFeature) continue;

						//std::string gfname = geoFeature->getName();
						//string::size_type idx = gfname.find("ault");
						//if (idx != string::npos)
						//{
						//	cout << gfname << std::endl;
						//	continue;
						//}

						osg::Vec4 color(1, 1, 1, 1);
						se::GeoSymbolizer* gs = rule->GetSymbolizer();
						if (gs)
						{
							color = osg::Vec4(gs->DiffuseColor[0], gs->DiffuseColor[1], gs->DiffuseColor[2], 1.0);
						}

						osg::ref_ptr<osg::Node> node = createFeatureNode(geoFeature, _transferFunction, color);
						if (node.valid())
						{
							//osgDB::writeNodeFile(*node, "mytest.ive");
							layerGroup->addChild(node);
						}
					}
				}
				if (layerGroup->getNumChildren() > 0)
				{
					projGroup->addChild(layerGroup);
				}
			}
		}

		delete project;
		return projGroup;
	}
};

REGISTER_OSGPLUGIN(xml, Geo3dmlReaderWriter)