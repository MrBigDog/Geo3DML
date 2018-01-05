#include <osgDB/Registry>
#include <osgDB/ReaderWriter>
#include <osgDB/FileNameUtils>

#include <GMLFeature/gmlFeatureCollection.h>
#include <SaxReader/Geo3DProjectReader.h>
#include <GM_XML/Geo3DProject.h>
#include <GM_XML/FeatureClass.h>
#include <GM_XML/GeologicFeature.h>
#include <GM_XML/MappedFeature.h>
#include <GM_XML/GeoModel.h>
#include <GMXMLFileIO/Geo3DProjectXMLReader.h>
#include <vtkExtending/vtkObject.h>
#include <vtkExtending/GMPolyData.h>
#include <vtkExtending/vtkCellArray.h>

namespace
{
	//osg::Geometry* createGeom(gmml::GeologicFeature* gf)
	//{
	//	osg::ref_ptr<osg::Vec3Array> va = new osg::Vec3Array;
	//	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
	//	geom->setName(gf->getName());
	//	geom->setVertexArray(va);

	//	return geom.release();
	//}

	osg::Node* createFeatureNode(gmml::GeologicFeature* gf)
	{
		osg::ref_ptr<osg::Geode> geode = new osg::Geode;

		for (int i = 0; i < gf->GetMappedFeatureCount(); ++i)
		{
			gmml::MappedFeature* mf = gf->GetMappedFeature(i);
			vtkObject* shape = mf->GetShape();

			std::string shapeName = shape->GetClassName();
			if (shapeName == "GMPolyData")
			{
				GMPolyData* poly_data = (GMPolyData*)shape;
				if (poly_data && poly_data->GetGeometryType() == 5)
				{
					vtkPoints* points = poly_data->GetPoints();
					int pointNum = points->GetNumberOfPoints();
					osg::ref_ptr<osg::Vec3Array> va = new osg::Vec3Array;
					for (int i = 0; i < pointNum; i++)
					{
						osg::Vec3d p;
						points->GetPoint(i, p.ptr());
						va->push_back(p);
					}

					osg::ref_ptr<osg::DrawElementsUInt> de = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);

					vtkCellArray* line = poly_data->GetPolys();
					int cellNum = line->GetNumberOfCells();
					for (int i = 0; i < cellNum * 4; i = i + 4)
					{
						vtkIdType counta;
						vtkIdType *pts;
						line->GetCell(i, counta, pts);
					}




					osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
					geom->setName(shapeName);
					geom->setVertexArray(va);
					geom->addPrimitiveSet(de);

					geode->addDrawable(geom);
				}
			}
		}

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

		gmml::Geo3DProject* project = new gmml::Geo3DProject;

#if 0
		int rs = ReadGeo3DProject(project, file.c_str());
#else
		Geo3DProjectXMLReader xmlreader;
		if (!xmlreader.ReadFile(file.c_str(), ""))
		{
			return ReadResult::FILE_NOT_HANDLED;
		}
#endif
		if (!project)
		{
			return ReadResult::FILE_NOT_HANDLED;
		}

		int model_count = project->GetGeoModelCount();
		if (model_count < 1)
		{
			return ReadResult::FILE_NOT_HANDLED;
		}

		gmml::GeoModel* pModel = project->GetGeoModel(0);
		if (!pModel)
		{
			return ReadResult::FILE_NOT_HANDLED;
		}

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
		return ReadResult(mgroup);
	}
};

REGISTER_OSGPLUGIN(xml, Geo3dmlReaderWriter)