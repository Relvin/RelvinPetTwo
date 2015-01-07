/****************************************************************************
 for cocos2d-x 3.2

 author : LuoYu
 
 e-mail : 466474482@qq.com

 github : https://github.com/bluesky466/cocos2dxUsefulClasses
 ****************************************************************************/

#ifndef _FRAGMENT_EFFECT_H_
#define _FRAGMENT_EFFECT_H_

#include "cocos2d.h"
#include "cocos2d\cocos\editor-support\cocostudio\CocoStudio.h"
#include "cocos2d\cocos\ui\CocosGUI.h"
#include <vector>

#define EFFECT_MATRIX_NAME "matrixEffect"

const GLchar* const szEffectFragSource =
	"#ifdef GL_ES													  \n \
	precision mediump float;										  \n \
	#endif															  \n \
	varying vec2 v_texCoord;										  \n \
	varying vec4 v_fragmentColor;									  \n \
	uniform mat4 matrixEffect;										  \n \
	void main(void)													  \n \
	{																  \n \
		gl_FragColor = texture2D(CC_Texture0, v_texCoord)*matrixEffect*v_fragmentColor; \n \
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

/**
 * ����ģʽ�ļ򵥵�Ƭ����ȾЧ����
 * �ȵ��� addEffectNode ������Ҫ��Ⱦ��Ч�Ľڵ�
 * Ȼ����Ե��� setEffect ������Ч�� getEffectSelect�ĵ���Чѡ��
 */
class FragmentEffect
{
private:
	enum NodeType
	{
		NT_SPRITE,
		NT_ARMATURE
	};

	struct EffectListNode
	{
		cocos2d::Node* _pNode;
		NodeType _type;
		int		 _effectSelect;
	};

public:
	static FragmentEffect* getInstance();
	static void destroy();

	/**
	 * �����Զ������Ч����
	 *@param matrix ��Ч����
	 *@return ���ؽڵ��� m_nodeList �����,ʧ���򷵻�-1
	 */
	int addEffectMatrix(const cocos2d::Mat4& matrix);

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
	bool setEffect(cocos2d::Node* pNode,unsigned int sel);

	///������Ҫ��Ⱦ��Ч�ľ���ڵ�
	int  addEffectNode(cocos2d::Sprite* sprite);

	///������Ҫ��Ⱦ��Ч�Ĺ��������ڵ�
	int  addEffectNode(cocostudio::Armature* armature);

	///�õ��ڵ����Чѡ����û�д˽ڵ��򷵻�-1����������Ƚϸ�Ч
	int  getEffectSelect(unsigned int nodeInde);

	///�õ��ڵ����Чѡ����û�д˽ڵ��򷵻�-1������ʹ�ø��Ӹ�Ч�� int getEffectSelect(int nodeInde)
	int  getEffectSelect(cocos2d::Node* pNode);
	
private:
	static FragmentEffect* s_instance;

	FragmentEffect();
	~FragmentEffect(){}

	std::vector<cocos2d::Mat4>  m_matrices;
	std::vector<EffectListNode> m_nodeList;

	///˽�з���,Ϊ���ݽڵ�����,�ö�Ӧ�ķ�������Ч��
	void selectEffect(cocos2d::Node* pNode, NodeType type, unsigned int sel);
};

inline int FragmentEffect::addEffectMatrix(const cocos2d::Mat4& matrix) 
{
	m_matrices.push_back(matrix);
	return m_matrices.size()-1;
}

#endif
