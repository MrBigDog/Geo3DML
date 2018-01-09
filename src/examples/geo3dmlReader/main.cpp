#include <osg/Group>
#include <osg/Material>
#include <osg/BlendFunc>
#include <osg/BlendColor>
#include <osgDB/ReadFile>
#include <osgDB/WriteFile>
#include <osgGA/StateSetManipulator>

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

void setTransparent(osg::StateSet* state, float alf)
{
	state->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED);
	state->setMode(GL_BLEND, osg::StateAttribute::ON);
	state->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);
	state->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
	osg::ref_ptr<osg::BlendColor> bc = new osg::BlendColor(osg::Vec4(1.0, 1.0, 1.0, 0.0));
	osg::ref_ptr<osg::BlendFunc>bf = new osg::BlendFunc();
	state->setAttributeAndModes(bf, osg::StateAttribute::ON);
	state->setAttributeAndModes(bc, osg::StateAttribute::ON);
	bf->setSource(osg::BlendFunc::CONSTANT_ALPHA);
	bf->setDestination(osg::BlendFunc::ONE_MINUS_CONSTANT_ALPHA);
	bc->setConstantColor(osg::Vec4(1, 1, 1, 0.5));
}

void writeToLocal(osg::Node* node, const std::string& name = "geo3dml.osg")
{
	osgDB::writeNodeFile(*node, name);
}

int main()
{
	osg::ref_ptr<osg::Node> geo3dmlNode = osgDB::readNodeFile("D:\\Geo3DGml_GIT\\Geo3DML\\data\\geo3dml_test_models\\cubeMode\\aa.xml");

	osg::ref_ptr<osg::Group> root = new osg::Group;
	root->addChild(geo3dmlNode);

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