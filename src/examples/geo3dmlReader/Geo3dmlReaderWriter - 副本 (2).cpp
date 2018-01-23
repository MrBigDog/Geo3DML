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
	osg::Node* createFeatureNode(gmml::GeologicFeature* gf, osg::TransferFunction1D* tf)
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

					osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
					geom->setUseDisplayList(false);
					geom->setUseVertexBufferObjects(true);
					geom->setName(shapeName);
					geom->setVertexArray(va);
					geom->setNormalArray(na, osg::Array::BIND_PER_VERTEX);
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
				if (grid->GetGeometryType() == 10)//������;
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
				else if (grid->GetGeometryType() == 12)//������;
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
		int modelNum = project->GetGeoModelCount();
		if (modelNum < 1) return ReadResult(0L);

		osg::ref_ptr<osg::Group> projGroup = new osg::Group;
		for (int mi = 0; mi < modelNum; ++mi)
		{
			gmml::GeoModel* pModel = project->GetGeoModel(mi);
			if (!pModel) continue;

			gmml::Geo3DMap* pMap = project->GetGeo3DMap(mi);
			int layercount = pMap->GetGeo3DLayerCount();

			//osg::ref_ptr<osg::Group> mgroup = new osg::Group;
			for (int layeri = 0; layeri < layercount; ++layeri)
			{
				gmml::Geo3DLayer* layer = pMap->GetLayer(layeri);
				if (!layer) continue;

				gmml::GeologicFeatureClass* fc = layer->GetFeatureClass();

				gmml::Geo3DStyle* style = layer->GetStyle();
				int ftsNum = style->GetFeatureTypeStyleCount();
				for (int ftsi = 0; ftsi < ftsNum; ++ftsi)
				{
					se::FeatureType3DStyle* fts = style->GetFeatureTypeStyle(ftsi);
					int rulNum = fts->getRuleCount();
					for (int ruli = 0; ruli < rulNum; ++ruli)
					{
						se::FeatureStyleRule* rule = fts->getRule(ruli);
						se::GeoSymbolizer* gs = rule->GetSymbolizer();
						gs->DiffuseColor;
						osg::Vec4 color(gs->DiffuseColor[0], gs->DiffuseColor[1], gs->DiffuseColor[2], 1.0);
						std::cout << "color: " << color[0] << " " << color[1] << " " << color[2] << " " << color[3] << std::endl;
					}
				}

				//int fnum = fc->GetGeologicFeatureCount();
				//int fcsn = fc->GetFeatureClassSchemaCount();
				//for (int fi = 0; fi < fnum; ++fi)
				//{
				//	gmml::GeologicFeature* geoFeature = fc->GetGeologicFeature(fi);
				//	osg::ref_ptr<osg::Node> node = createFeatureNode(geoFeature, _transferFunction);
				//	mgroup->addChild(node);
				//}
			}
			//projGroup->addChild(mgroup);


			osg::ref_ptr<osg::Group> mgroup = new osg::Group;
			int fcNum = pModel->GetGeoFeatureClassCount();
			for (int fci = 0; fci < fcNum; ++fci)
			{
				gmml::GeologicFeatureClass* fc = pModel->GetGeoFeatureClass(fci);

				gmml::Geo3DLayer* layer = dynamic_cast<gmml::Geo3DLayer*>(fc->getContainer());
				if (layer)
				{
					std::cout << "wow" << std::endl;
				}

				int fscn = fc->GetFeatureClassSchemaCount();

				int fnum = fc->GetGeologicFeatureCount();
				for (int fi = 0; fi < fnum; ++fi)
				{
					gmml::GeologicFeature* geoFeature = fc->GetGeologicFeature(fi);
					int mfc = geoFeature->GetMappedFeatureCount();

					gmml::MappedFeature* mf = geoFeature->GetMappedFeature(0);
					osg::ref_ptr<osg::Node> node = createFeatureNode(geoFeature, _transferFunction);
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