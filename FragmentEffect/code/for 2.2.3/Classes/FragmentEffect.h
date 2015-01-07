/****************************************************************************
 for cocos2d-x 2.2.3

 author : LuoYu
 
 e-mail : 466474482@qq.com

 github : https://github.com/bluesky466/cocos2dxUsefulClasses
 ****************************************************************************/

#ifndef _FRAGMENT_EFFECT_H_
#define _FRAGMENT_EFFECT_H_

#include "cocos2d.h"
#include "cocoa/CCGeometry.h"
#include <vector>

const GLchar* const szEffectFragSource =
				"#ifdef GL_ES													  \n \
				precision mediump float;										  \n \
				#endif															  \n \
				uniform sampler2D u_texture;									  \n \
				varying vec2 v_texCoord;										  \n \
				varying vec4 v_fragmentColor;									  \n \
				uniform mat4 matrixEffect;										  \n \
				void main(void)													  \n \
				{																  \n \
					gl_FragColor = texture2D(u_texture, v_texCoord)*matrixEffect*v_fragmentColor; \n \
				}";

enum EffectSelect
{
	ES_NONE              = 0,  //û����Ч
	ES_BLACK_AND_WHITE   = 1,  //�ڰ׻�
	ES_OLD_PHOTOS        = 2,  //����Ƭ
	ES_INVERT            = 3,  //����
	ES_BURNS			 = 4,  //���ˣ�ƫ�죩
	ES_POISONING		 = 5,  //�ж���ƫ�̣�
	ES_COLD			     = 6,  //���䣨ƫ����

	ES_USER_DEFINED //�Զ������Ч������Ŵ����￪ʼ
};

struct Matrix44
{
	GLfloat _matrix[16];
};

struct EffectListNode
{
	cocos2d::CCNode* _pNode;
	GLint   _uniformMatrix;
	int		_effectSelect;
};

/**
 * ����ģʽ�ļ򵥵�Ƭ����ȾЧ����
 * �ȵ��� addEffectNode ������Ҫ��Ⱦ��Ч�Ľڵ�
 * Ȼ����Ե��� setEffect ������Ч�� getEffectSelect�ĵ���Чѡ��
 */
class FragmentEffect
{
public:
	static FragmentEffect* getInstance();
	static void destroy();

	/**
	 * �����Զ������Ч����
	 *@param matrix ��Ч����
	 *@return ���ؽڵ��� m_nodeList �����,ʧ���򷵻�-1
	 */
	int addEffectMatrix(const Matrix44& matrix);

	/**
	 * ���ýڵ����Ч����������Ƚϸ�Ч
	 *@param nodeIndex �ڵ���ţ���addEffectNode�����ķ���ֵ
	 *@param sel ��Ч��ѡ��
	 */
	bool setEffect(unsigned int nodeIndex,unsigned int sel);

	/**
	 * ���ýڵ����Ч������ʹ�ø��Ӹ�Ч�� bool setEffect(int nodeIndex,int sel)
	 * �����ȵ��� addEffectNode ����Ҫ��Ⱦ��Ч�Ľڵ�ӵ�������
	 *@param pNode �ڵ�ָ��
	 *@param sel ��Ч��ѡ��
	 */
	bool setEffect(cocos2d::CCNode* pNode,unsigned int sel);

	///������Ҫ��Ⱦ��Ч�Ľڵ�
	int  addEffectNode(cocos2d::CCNode* pNode);

	///�õ��ڵ����Чѡ����û�д˽ڵ��򷵻�-1����������Ƚϸ�Ч
	int  getEffectSelect(unsigned int nodeInde);

	///�õ��ڵ����Чѡ����û�д˽ڵ��򷵻�-1������ʹ�ø��Ӹ�Ч�� int getEffectSelect(int nodeInde)
	int  getEffectSelect(cocos2d::CCNode* pNode);
	
private:
	static FragmentEffect* s_instance;

	FragmentEffect();
	~FragmentEffect(){}

	std::vector<Matrix44>		m_matrices;
	std::vector<EffectListNode> m_nodeList;
};

inline int FragmentEffect::addEffectMatrix(const Matrix44& matrix) 
{
	m_matrices.push_back(matrix);
	return m_matrices.size()-1;
}

#endif
