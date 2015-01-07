//
//  MainShowPet.cpp
//  HelloWorld
//
//  Created by 朱 俊杰 on 14-1-8.}
//
//

#include "MainShowPet.h"
#include "FlccMovieClip.h"
#include "SpccMovieClip.h"
#include "FlccMovieAction.h"
#include "FlccMovieFPSAction.h"
#include "SpccMovieAction.h"
#include "SpccMovieFPSAction.h"
#include "ConfigGet.h"
#include "SequenceAction.h"
#include "PetCtrl.h"
#include "UISupport.h"

#define FlccFPS     45

MainShowPet::MainShowPet() {
    pMc = NULL;
    bPlayIng = false;
}

MainShowPet::~MainShowPet()
{

}

MainShowPet* MainShowPet::create(uint16 wPetIndex)
{
    MainShowPet* pRet = new MainShowPet();
    if (pRet && pRet->init(wPetIndex)) {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool MainShowPet::init(uint16 wPetIndex)
{
    if (!CCLayer::init()) {
        return false;
    }
    setTouchEnabled(true);
    
    m_wPetIndex = wPetIndex;

    pMc = SequencePet::create(wPetIndex);
    pMc->setAnchorPoint(ccp(0.5, 0));
    //转换flcc的位置（flcc的锚点一点要设为（0.5，0）才能站的准）}
    CCPoint pos = CPetCtrl::Get()->ConvertFlccPos(wPetIndex, getWidth(pMc), CCPointZero);
    pMc->setPosition(pos);
    
    pMc->setFPS(seq_fps);

    addChild(pMc);

    return true;
}

void MainShowPet::onEnter()
{
    CCLayer::onEnter();
    if (pMc) {
        pMc->runAction(CCRepeatForever::create(SequenceAction::create(pMc, SEQ_ACT_STAND)));
    }
}

void MainShowPet::onExit()
{
    CCLayer::onExit();
    // 暂停所有动作}
    pMc->stopAllActions();
}

#pragma mark Public Method
void MainShowPet::playAttackAction()
{
    if (pMc)
    {
        pMc->stopAllActions();
        onAttack();
    }
}
void MainShowPet::onAttack()
{
    if (bPlayIng) {
        return;
    }
    bPlayIng = true;
    int cnt = rand() % 5 + 1;
    pMc->runAction(CCRepeatForever::create(CCSequence::create(SequenceAction::create(pMc, SEQ_ACT_ATTACK),
                                                              CCRepeat::create(SequenceAction::create(pMc, SEQ_ACT_STAND), cnt),
                                                              NULL)));
}
void MainShowPet::setOpacity(GLubyte opacity)
{
    if (m_pChildren && m_pChildren->count() > 0)
	{
		CCObject* pObject = NULL;
		CCARRAY_FOREACH(m_pChildren, pObject)
		{
			CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>( pObject );
			if (pRGBAProtocol)
			{
				pRGBAProtocol->setOpacity(opacity);
			}
		}
	}
}

#pragma mark Private Method

void MainShowPet::playStandAction()
{
    pMc->stopAllActions();
    stopAttackAction();
}

void MainShowPet::stopAttackAction()
{
    bPlayIng = false;
    pMc->runAction(CCRepeatForever::create(SequenceAction::create(pMc, SEQ_ACT_STAND)));
}


#pragma mark Touch Delegate



