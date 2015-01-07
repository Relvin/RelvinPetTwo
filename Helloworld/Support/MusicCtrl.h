//
//  MusicCtrl.h
//  HelloWorld
//
//  Created by 朱 俊杰 on 13-12-3.}
//
//

#ifndef __HelloWorld__MusicCtrl__
#define __HelloWorld__MusicCtrl__

#include <string>
#include "Defines.h"
#include "ResourceMusic.h"

class CMusicCtrl {
    
public:
	static void Init();
    
	static bool GetIsMusicOn();
    
	static void SetIsMusicOn(bool bOn);
    
	static void SetIsMusicOn2(bool bOn);
    
	static bool GetIsEffectOn();
    
	static void SetIsEffectOn(bool bOn);
    
	static void PlayBackgroundMusic(const char * szMusicName);
    
	static unsigned int PlayEffect(const char * szEffectName);
    
    static void PauseEffect(unsigned int nSoundId);
    
    static void PauseAllEffect();
    
    static void ResumeEffect(unsigned int nSoundId);
    
    static void ResumeAllEffect();
    
    static void StopEffect(unsigned int nSoundId);
    
    static void StopAllEffect();
    
	static bool IsBackgroundMusicPlaying();
    
	static void StopBackgroundMusic();
    
	static unsigned int PlayEffect(uint16 wMusicEffectId);
    
	static std::string CurrentMusicName();
	
	static void PlayButtonClickEffect();
    
    //设置声音大小}
    static void SetEffectsVolume(float volume);
    static void SetBackgroundMusicVolume(float volume);
    
    //震动}
    static void PlayVibrate();
    
private:
    
	static bool m_bIsMusicOn;
	static bool m_bIsEffectOn;
	static std::string m_strCurrentMusicName;
};

#endif /* defined(__HelloWorld__MusicCtrl__) */
