#include <osgDB/Registry>
#include <osgDB/ReaderWriter>
#include <osgDB/FileUtils>
#include <osgDB/FileNameUtils>
#include <osgDB/WriteFile>

#include <GMLFeature/gmlFeatureCollection.h>
#include <GM_XML/Geo3DProject.h>
#include <GM_XML/FeatureClass.h>
#include <GM_XML/GeologicFeature.h>
#include <GM_XML/MappedFeature.h>
#include <GM_XML/GeoModel.h>
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
	osg::Node* createFeatureNode(gmml::GeologicFeature* gf)
	{
		osg::ref_ptr<osg::Geode> geode = new osg::Geode;

		for (int i = 0; i < gf->GetMappedFeatureCount(); ++i)
		{
			gmml::MappedFeature* mf = gf->GetMappedFeature(i);
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

					for (int i = 0; i < cellNum * 4; i += 4)
					{
						vtkIdType counta;
						vtkIdType *pts;
						cellAry->GetCell(i, counta, pts);
						if (counta != 3) continue;

						de->push_back(pts[0]);
						de->push_back(pts[1]);
						de->push_back(pts[2]);
					}

					osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
					geom->setUseDisplayList(false);
					geom->setUseVertexBufferObjects(true);
					geom->setName(shapeName);
					geom->setVertexArray(va);
					geom->addPrimitiveSet(de);

					geode->addDrawable(geom);
				}
			}
			else if (shapeName == "GMUnstructuredGrid")//VoxelModel
			{
				GMUnstructuredGrid* grid = (GMUnstructuredGrid*)shape;
				vtkPoints* points = grid->GetPoints();
				int pointNum = points->GetNumberOfPoints();
				osg::ref_ptr<osg::Vec3Array> va = new osg::Vec3Array;
				va->reserve(pointNum);
				for (int i = 0; i < pointNum; i++)
				{
					osg::Vec3d p;
					points->GetPoint(i, p.ptr());
					va->push_back(p);
				}

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
					//osg::ref_ptr<osg::DrawElementsUInt> de = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
					for (int i = 0; i < grid->GetNumberOfCells() * 9; i = i + 9)
					{
						vtkIdType counta;
						vtkIdType *pts;
						cellAry->GetCell(i, counta, pts);

						if (counta != 8) continue;

						osg::ref_ptr<osg::Vec3Array> cubeVa = new osg::Vec3Array;
						osg::ref_ptr<osg::Vec3Array> cubeNa = new osg::Vec3Array;

						cubeVa->push_back(va->at(pts[0]));
						cubeVa->push_back(va->at(pts[1]));
						cubeVa->push_back(va->at(pts[2]));
						cubeVa->push_back(va->at(pts[3]));
						cubeNa->push_back(osg::Vec3(0, 0, -1));
						cubeNa->push_back(osg::Vec3(0, 0, -1));
						cubeNa->push_back(osg::Vec3(0, 0, -1));
						cubeNa->push_back(osg::Vec3(0, 0, -1));

						cubeVa->push_back(va->at(pts[4]));
						cubeVa->push_back(va->at(pts[5]));
						cubeVa->push_back(va->at(pts[6]));
						cubeVa->push_back(va->at(pts[7]));
						cubeNa->push_back(osg::Vec3(0, 0, 1));
						cubeNa->push_back(osg::Vec3(0, 0, 1));
						cubeNa->push_back(osg::Vec3(0, 0, 1));
						cubeNa->push_back(osg::Vec3(0, 0, 1));

						cubeVa->push_back(va->at(pts[1]));
						cubeVa->push_back(va->at(pts[5]));
						cubeVa->push_back(va->at(pts[4]));
						cubeVa->push_back(va->at(pts[0]));
						cubeNa->push_back(osg::Vec3(0, -1, 0));
						cubeNa->push_back(osg::Vec3(0, -1, 0));
						cubeNa->push_back(osg::Vec3(0, -1, 0));
						cubeNa->push_back(osg::Vec3(0, -1, 0));

						cubeVa->push_back(va->at(pts[1]));
						cubeVa->push_back(va->at(pts[2]));
						cubeVa->push_back(va->at(pts[6]));
						cubeVa->push_back(va->at(pts[5]));
						cubeNa->push_back(osg::Vec3(1, 0, 0));
						cubeNa->push_back(osg::Vec3(1, 0, 0));
						cubeNa->push_back(osg::Vec3(1, 0, 0));
						cubeNa->push_back(osg::Vec3(1, 0, 0));

						cubeVa->push_back(va->at(pts[2]));
						cubeVa->push_back(va->at(pts[6]));
						cubeVa->push_back(va->at(pts[7]));
						cubeVa->push_back(va->at(pts[3]));
						cubeNa->push_back(osg::Vec3(0, 1, 0));
						cubeNa->push_back(osg::Vec3(0, 1, 0));
						cubeNa->push_back(osg::Vec3(0, 1, 0));
						cubeNa->push_back(osg::Vec3(0, 1, 0));

						cubeVa->push_back(va->at(pts[3]));
						cubeVa->push_back(va->at(pts[7]));
						cubeVa->push_back(va->at(pts[4]));
						cubeVa->push_back(va->at(pts[0]));
						cubeNa->push_back(osg::Vec3(-1, 0, 0));
						cubeNa->push_back(osg::Vec3(-1, 0, 0));
						cubeNa->push_back(osg::Vec3(-1, 0, 0));
						cubeNa->push_back(osg::Vec3(-1, 0, 0));

						osg::ref_ptr<osg::Vec4Array> ca = new osg::Vec4Array;
						ca->push_back(osg::Vec4(1, 1, 1, 1));

						osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
						geom->setUseDisplayList(false);
						geom->setUseVertexBufferObjects(true);
						geom->setVertexArray(cubeVa);
						geom->setNormalArray(cubeNa, osg::Array::BIND_PER_VERTEX);
						geom->setColorArray(ca, osg::Array::BIND_OVERALL);
						geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, cubeVa->size()));
						geode->addDrawable(geom);
					}

					////vertex_offset += 3 * sizeof(float);
					int num1 = grid->GetPointData()->GetNumberOfArrays();
					if (num1 > 0)
					{
						vtkDataArray * vPointData = grid->GetPointData()->GetArray(0);
						if (0 == strcmp(vPointData->GetClassName(), "vtkDoubleArray"))
						{
							double dMin = 1E10, dMax = -1E10;
							vtkDoubleArray* dataA = (vtkDoubleArray*)vPointData;
							for (unsigned long i = 0; i < dataA->GetNumberOfTuples()*dataA->GetNumberOfComponents(); ++i)
							{
								double fValue = dataA->GetValue(i);
								dMin = (fValue < dMin) ? fValue : dMin;
								dMax = (fValue > dMax) ? fValue : dMax;
							}
							int nAllColorCount = 0x000000FF - 0;
							double dStep = (dMax - dMin) / nAllColorCount;
							for (unsigned long i = 0; i < dataA->GetNumberOfTuples()*dataA->GetNumberOfComponents(); ++i)
							{
								double fValue = dataA->GetValue(i);
								//in_hardware_mesh->set_ulong(vertex_offset, i, ulong((fValue - dMin)*dStep));
							}
						}
					}
				}
			}
		}

		//osgDB::writeNodeFile(*geode, "geo3dmltest.osgb");
		return geode.release();
	}

}

//  [1/5/2018 BigDog]
class Geo3dmlReaderWriter :public osgDB::ReaderWriter
{
public:
	Geo3dmlReaderWriter()
	{
		supportsExtension("xml", "geo3dml reader");
		supportsExtension("geo3dxml", "geo3dml reader");
	}

	const char* className() const
	{
		return "Geo3dmlReaderWriter";
	}

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

#if 0
		gmml::Geo3DProject* project;
		int rs = ReadGeo3DProject(project, file.c_str());
#else
		Geo3DProjectXMLReader xmlreader;
		if (!xmlreader.ReadFile(file.c_str(), ""))
		{
			return ReadResult::FILE_NOT_HANDLED;
		}
#endif
		gmml::Geo3DProject* project = dynamic_cast<gmml::Geo3DProject*>(xmlreader.GetGeoProject());

		if (!project) return ReadResult(0L);
		int modelNum = project->GetGeoModelCount();
		if (modelNum < 1) return ReadResult(0L);

		osg::ref_ptr<osg::Group> projGroup = new osg::Group;
		for (int mi = 0; mi < modelNum; ++mi)
		{
			gmml::GeoModel* pModel = project->GetGeoModel(mi);
			if (!pModel) continue;

			osg::ref_ptr<osg::Group> mgroup = new osg::Group;

			int fcNum = pModel->GetGeoFeatureClassCount();
			for (int fci = 0; fci < fcNum; ++fci)
			{
				gmml::GeologicFeatureClass* fc = pModel->GetGeoFeatureClass(fci);
				for (int fi = 0; fi < fc->GetGeologicFeatureCount(); ++fi)
				{
					gmml::GeologicFeature* geoFeature = fc->GetGeologicFeature(fi);
					osg::ref_ptr<osg::Node> node = createFeatureNode(geoFeature);
					mgroup->addChild(node);
				}
			}
			projGroup->addChild(mgroup);
		}

		delete project;
		return projGroup;
	}
};

REGISTER_OSGPLUGIN(xml, Geo3dmlReaderWriter)