#include <osg/Group>
#include <osg/Material>
#include <osg/BlendFunc>
#include <osg/BlendColor>
#include <osgDB/ReadFile>
#include <osgDB/WriteFile>
#include <osgGA/StateSetManipulator>

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

int main()
{
	osg::ref_ptr<osg::Node> geo3dmlNode = osgDB::readNodeFile("D:\\Geo3DGml_GIT\\Geo3DML\\data\\geo3dml_test_models\\cubeMode\\aa.xml");
	//osg::ref_ptr<osg::Node> geo3dmlNode = osgDB::readNodeFile("geo3dmltest.osgb");

	osg::ref_ptr<osg::Group> root = new osg::Group;
	root->addChild(geo3dmlNode);

	osgDB::writeNodeFile(*geo3dmlNode, "geoModel.osg");

	//osg::ref_ptr<osg::CullFace> cullface = new osg::CullFace(osg::CullFace::BACK);
	//root->getOrCreateStateSet()->setAttribute(cullface.get());
	//root->getOrCreateStateSet()->setMode(GL_CULL_FACE, osg::StateAttribute::ON);
	//state->setAttributeAndModes(bf, osg::StateAttribute::ON);
	//state->setAttributeAndModes(bc, osg::StateAttribute::ON);
	//bf->setSource(osg::BlendFunc::CONSTANT_ALPHA);
	//bf->setDestination(osg::BlendFunc::ONE_MINUS_CONSTANT_ALPHA);
	//bc->setConstantColor(osg::Vec4(1, 1, 1, 0.5));

	osgViewer::Viewer viewer;
	viewer.setSceneData(root);
	viewer.addEventHandler(new osgGA::StateSetManipulator(viewer.getCamera()->getOrCreateStateSet()));
	viewer.addEventHandler(new osgViewer::StatsHandler());
	viewer.addEventHandler(new osgViewer::WindowSizeHandler());
	viewer.addEventHandler(new osgViewer::ThreadingHandler());
	viewer.addEventHandler(new osgViewer::LODScaleHandler());
	viewer.realize();
	viewer.run();

	return 0;
}