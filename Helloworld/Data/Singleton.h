//
//  Singleton.h
//  HelloWorld
//
//  Created by jun on 13-11-13.
//
//

#ifndef __HelloWorld__Singleton__
#define __HelloWorld__Singleton__

#include <iostream>

template <class T>

class Singleton {
public:
    //获得单体实例对象，这里不new，避免出现多个对象}
    static T* Get()
    {
        return m_pObject;
    }
    
    //创建单体实例}
    static T* Create()
    {
        if (!m_pObject) {
            m_pObject = new T;
        }
        return m_pObject;
    }
    
    //销毁单体对象}
    static void Destory()
    {
        if (m_pObject) {
            delete m_pObject;
            m_pObject = NULL;
        }
    }
public:
    static T* m_pObject;
};

template <class T>
T* Singleton<T>::m_pObject = NULL;

#endif /* defined(__HelloWorld__Singleton__) */
