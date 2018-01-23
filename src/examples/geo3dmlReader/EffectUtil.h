#ifndef STATESETUTIL_H
#define STATESETUTIL_H 1

#include <osg/Program>
#include <osg/Material>
#include <osg/StateSet>
#include <osg/BlendFunc>
#include <osg/BlendColor>
#include <osgAnimation/EaseMotion>

//Ч�ʸߣ�Ч����(��Ϊshader��û�ӹ���);
void setBloomEffect1(osg::Node* node);

//�޸�Color Array�ķ�ʽ��Ч�ʵ�, Ч����;
void setBloomEffect2(osg::Node* node, const osg::Vec4& color1 = osg::Vec4(1, 0, 0, 1), const osg::Vec4& color2 = osg::Vec4(1, 1, 0, 1));

//�޸�Material�ķ�ʽ��Ч�ʱ�2�ߣ���1�Եͣ�Ч��ͬ2;
void setBloomEffect3(osg::Node* node, const osg::Vec4& color1 = osg::Vec4(1, 0, 0, 1), const osg::Vec4& color2 = osg::Vec4(1, 1, 0, 1));

//����͸��;
void setTransparentEffect(osg::Node* state, float alf);

void renderNodeAsPoint(osg::Node* node);
void renderNodeAsLine(osg::Node* node);

//nodeҪ��parent;
void setOutlineEffect(osg::Node* node, const osg::Vec4& color = osg::Vec4(1, 1, 0, 1), float width = 5.0f);

#endif // StateUtil_h__
