#ifndef STATESETUTIL_H
#define STATESETUTIL_H 1

#include <osg/Program>
#include <osg/Material>
#include <osg/StateSet>
#include <osg/BlendFunc>
#include <osg/BlendColor>
#include <osgAnimation/EaseMotion>

//效率高，效果差(因为shader中没加光照);
void setBloomEffect1(osg::Node* node);

//修改Color Array的方式，效率低, 效果好;
void setBloomEffect2(osg::Node* node, const osg::Vec4& color1 = osg::Vec4(1, 0, 0, 1), const osg::Vec4& color2 = osg::Vec4(1, 1, 0, 1));

//修改Material的方式，效率比2高，比1稍低，效果同2;
void setBloomEffect3(osg::Node* node, const osg::Vec4& color1 = osg::Vec4(1, 0, 0, 1), const osg::Vec4& color2 = osg::Vec4(1, 1, 0, 1));

//设置透明;
void setTransparentEffect(osg::Node* state, float alf);

void renderNodeAsPoint(osg::Node* node);
void renderNodeAsLine(osg::Node* node);

//node要有parent;
void setOutlineEffect(osg::Node* node, const osg::Vec4& color = osg::Vec4(1, 1, 0, 1), float width = 5.0f);

#endif // StateUtil_h__
