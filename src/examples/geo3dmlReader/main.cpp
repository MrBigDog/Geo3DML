#include <osg/Group>
#include <osgDB/ReadFile>
#include <osgGA/StateSetManipulator>

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

int main()
{
	osg::ref_ptr<osg::Node> geo3dmlNode = osgDB::readNodeFile("D:\\Geo3DGml_GIT\\Geo3DML\\data\\geo3dml_test_models\\六面体模型\\规则六面体模型.xml");

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