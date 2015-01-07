//
//  MusicCtrl.cpp
//  HelloWorld
//
//  Created by 朱 俊杰 on 13-12-3.}
//
//

#include "MusicCtrl.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "sound_system_fmod.h"
#include "Defines.h"
#include "Support.h"

USING_NS_CC;
using namespace CocosDenshion;
using namespace SoundSystem;

bool CMusicCtrl::m_bIsMusicOn = true;
bool CMusicCtrl::m_bIsEffectOn = true;
std::string CMusicCtrl::m_strCurrentMusicName;

void CMusicCtrl::Init()
{
	if (!CCUserDefault::sharedUserDefault()->getBoolForKey(D9_FIRST_LOGIN))
	{

		CCUserDefault::sharedUserDefault()->setBoolForKey(D9_FIRST_LOGIN,true);
        
		CCUserDefault::sharedUserDefault()->setBoolForKey(D9_MUSIC_ON, true);
		CCUserDefault::sharedUserDefault()->setBoolForKey(D9_EFFECT_ON, true);
	}
	else
	{
		m_bIsMusicOn = CCUserDefault::sharedUserDefault()->getBoolForKey(D9_MUSIC_ON);
		m_bIsEffectOn = CCUserDefault::sharedUserDefault()->getBoolForKey(D9_EFFECT_ON);
	}
	
	m_strCurrentMusicName = "";
    
    if (strcmp(Support::sharedInstance()->systemVersion(), "5.1.1") == 0) {
        SimpleAudioEngine::sharedEngine()->setEffectsVolume(1);
        SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.3);
    } else {
        SoundSystemFmod::getInstance()->setEffectsVolume(1);
        SoundSystemFmod::getInstance()->setBackgroundMusicVolume(0.7);
    }
}

std::string CMusicCtrl::CurrentMusicName()
{
	return m_strCurrentMusicName;
}
bool CMusicCtrl::GetIsMusicOn()
{
	return m_bIsMusicOn;
}

void CMusicCtrl::SetIsMusicOn(bool bOn)
{
	if (m_bIsMusicOn == bOn)
		return ;
	if (bOn)
	{
        if (strcmp(Support::sharedInstance()->systemVersion(), "5.1.1") == 0) {
            SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
        } else {
		SoundSystemFmod::getInstance()->resumeBackgroundMusic();
        }
	}
	else
	{
        if (strcmp(Support::sharedInstance()->systemVersion(), "5.1.1") == 0) {
            SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
        } else {
		SoundSystemFmod::getInstance()->pauseBackgroundMusic();
        }
	}
	m_bIsMusicOn = bOn;

	CCUserDefault::sharedUserDefault()->setBoolForKey(D9_MUSIC_ON, m_bIsMusicOn);
}

void CMusicCtrl::SetIsMusicOn2(bool bOn)
{
	if (bOn)
	{
        if (strcmp(Support::sharedInstance()->systemVersion(), "5.1.1") == 0) {
            SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
        } else {
		SoundSystemFmod::getInstance()->resumeBackgroundMusic();
        }
	}
	else
	{
        if (strcmp(Support::sharedInstance()->systemVersion(), "5.1.1") == 0) {
            SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
        } else {
		SoundSystemFmod::getInstance()->pauseBackgroundMusic();
        }
	}
}

bool CMusicCtrl::GetIsEffectOn()
{
	return m_bIsEffectOn;
}

void CMusicCtrl::SetIsEffectOn(bool bOn)
{
	m_bIsEffectOn = bOn;
	CCUserDefault::sharedUserDefault()->setBoolForKey(D9_EFFECT_ON, m_bIsEffectOn);
}

void CMusicCtrl::PlayBackgroundMusic(const char * szMusicName)
{
	std::string strMusicName = szMusicName;
	if (strMusicName == m_strCurrentMusicName)
	{
		return ;
	}
	m_strCurrentMusicName = strMusicName;
    
    if (strcmp(Support::sharedInstance()->systemVersion(), "5.1.1") == 0) {
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic(szMusicName,true);
    } else {
	SoundSystemFmod::getInstance()->playBackgroundMusic(szMusicName,true);
    }
	if (!GetIsMusicOn())
	{
        if (strcmp(Support::sharedInstance()->systemVersion(), "5.1.1") == 0) {
            SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
        } else {
		SoundSystemFmod::getInstance()->pauseBackgroundMusic();
        }
	}
    
    
}

unsigned int CMusicCtrl::PlayEffect(const char * szEffectName)
{
    if (GetIsEffectOn()) {
        if (strcmp(Support::sharedInstance()->systemVersion(), "5.1.1") == 0) {
            return SimpleAudioEngine::sharedEngine()->playEffect(szEffectName);
        } else {
		return SoundSystemFmod::getInstance()->playEffect(szEffectName);
        }
    }
    return 0;
}


void CMusicCtrl::PauseEffect(unsigned int nSoundId)
{
    if (strcmp(Support::sharedInstance()->systemVersion(), "5.1.1") == 0) {
        SimpleAudioEngine::sharedEngine()->pauseEffect(nSoundId);
    } else {
    SoundSystemFmod::getInstance()->pauseEffect(nSoundId);
    }
}

void CMusicCtrl::PauseAllEffect()
{
    if (strcmp(Support::sharedInstance()->systemVersion(), "5.1.1") == 0) {
        SimpleAudioEngine::sharedEngine()->pauseAllEffects();
    } else {
    SoundSystemFmod::getInstance()->pauseAllEffects();
    }
}

void CMusicCtrl::ResumeEffect(unsigned int nSoundId)
{
    if (strcmp(Support::sharedInstance()->systemVersion(), "5.1.1") == 0) {
        SimpleAudioEngine::sharedEngine()->resumeEffect(nSoundId);
    } else {
    SoundSystemFmod::getInstance()->resumeEffect(nSoundId);
    }
}

void CMusicCtrl::ResumeAllEffect()
{
    if (strcmp(Support::sharedInstance()->systemVersion(), "5.1.1") == 0) {
        SimpleAudioEngine::sharedEngine()->resumeAllEffects();
    } else {
    SoundSystemFmod::getInstance()->resumeAllEffects();
    }
}

void CMusicCtrl::StopEffect(unsigned int nSoundId)
{
    if (strcmp(Support::sharedInstance()->systemVersion(), "5.1.1") == 0) {
        SimpleAudioEngine::sharedEngine()->stopEffect(nSoundId);
    } else {
    SoundSystemFmod::getInstance()->stopEffect(nSoundId);
    }
}

void CMusicCtrl::StopAllEffect()
{
    if (strcmp(Support::sharedInstance()->systemVersion(), "5.1.1") == 0) {
        SimpleAudioEngine::sharedEngine()->stopAllEffects();
    } else {
    SoundSystemFmod::getInstance()->stopAllEffects();
    }
}

bool CMusicCtrl::IsBackgroundMusicPlaying()
{
    if (strcmp(Support::sharedInstance()->systemVersion(), "5.1.1") == 0) {
        return SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying();
    } else {
	return SoundSystemFmod::getInstance()->isBackgroundMusicPlaying();
    }
}

void CMusicCtrl::StopBackgroundMusic()
{
	m_strCurrentMusicName = "";
    if (strcmp(Support::sharedInstance()->systemVersion(), "5.1.1") == 0) {
        SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    } else {
	SoundSystemFmod::getInstance()->stopBackgroundMusic();
    }
}

unsigned int CMusicCtrl::PlayEffect(uint16 wMusicEffectId)
{
    char szName[32];
    snprintf(szName, 32, "music/se_%d.mp3", wMusicEffectId);
    return PlayEffect(szName);
}
void CMusicCtrl::PlayButtonClickEffect()
{
 
}

void CMusicCtrl::PlayVibrate()
{
//    SoundSystemFmod::getInstance()->vibrate();
}

//设置声音大小}
void CMusicCtrl::SetEffectsVolume(float volume)
{
    if (volume > 1) {
        volume = 1;
    }
    else if (volume < 0)
    {
        volume = 0;
    }
    if (strcmp(Support::sharedInstance()->systemVersion(), "5.1.1") == 0) {
        SimpleAudioEngine::sharedEngine()->setEffectsVolume(volume);
    } else {
    SoundSystemFmod::getInstance()->setEffectsVolume(volume);
    }
}

void CMusicCtrl::SetBackgroundMusicVolume(float volume)
{
    if (volume > 1) {
        volume = 1;
    }
    else if (volume < 0)
    {
        volume = 0;
    }

    if (strcmp(Support::sharedInstance()->systemVersion(), "5.1.1") == 0) {
        SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(volume);
    } else {
    SoundSystemFmod::getInstance()->setBackgroundMusicVolume(volume);
    }
}


