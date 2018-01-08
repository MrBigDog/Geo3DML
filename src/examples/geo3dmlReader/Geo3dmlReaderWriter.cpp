#include <osgDB/Registry>
#include <osgDB/ReaderWriter>
#include <osgDB/FileUtils>
#include <osgDB/FileNameUtils>
#include <osgDB/WriteFile>

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
						de->push_back(pts[0]);
						de->push_back(pts[1]);
						de->push_back(pts[2]);
					}

					osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
					geom->setName(shapeName);
					geom->setVertexArray(va);
					geom->addPrimitiveSet(de);

					geode->addDrawable(geom);
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

		return projGroup;
	}
};

REGISTER_OSGPLUGIN(xml, Geo3dmlReaderWriter)