#include <osg/Group>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

int main()
{
	osg::ref_ptr<osg::Node> geo3dmlNode = osgDB::readNodeFile("D:/Geo3DGml/0gwGeo3DML/data/geo3dml_test_models/Geo3dml/Geo3dml.xml");

	osg::ref_ptr<osg::Group> root = new osg::Group;
	root->addChild(geo3dmlNode);

	osgViewer::Viewer viewer;
	viewer.realize();
	viewer.run();

	return 0;
}