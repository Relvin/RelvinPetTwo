
#ifndef _BYTE_BUFFER_H
#define _BYTE_BUFFER_H

//#include "Common.h"
//#include "Errors.h"
//#include "Log.h"
#include "cocos2d.h"
USING_NS_CC;

#include "Defines.h"
#include <list>

class ByteBuffer
{
public:
    const static size_t DEFAULT_SIZE = 0x1000;
    
    // constructor
    ByteBuffer(): _rpos(0), _wpos(0)
    {
        _storage.reserve(DEFAULT_SIZE);
    }
    // constructor
    ByteBuffer(size_t res): _rpos(0), _wpos(0)
    {
        _storage.reserve(res);
    }
    // copy constructor
    ByteBuffer(const ByteBuffer &buf): _rpos(buf._rpos), _wpos(buf._wpos), _storage(buf._storage) { }
    
    void clear()
    {
        _storage.clear();
        _rpos = _wpos = 0;
    }
    
    template <typename T> void append(T value)
    {
        append((uint8 *)&value, sizeof(value));
    }
    template <typename T> void put(size_t pos,T value)
    {
        put(pos,(uint8 *)&value,sizeof(value));
    }
    
    ByteBuffer &operator<<(bool value)
    {
        append<char>((char)value);
        return *this;
    }
    ByteBuffer &operator<<(uint8 value)
    {
        append<uint8>(value);
        return *this;
    }
    ByteBuffer &operator<<(uint16 value)
    {
        append<uint16>(value);
        return *this;
    }
    ByteBuffer &operator<<(uint32 value)
    {
        append<uint32>(value);
        return *this;
    }
    ByteBuffer &operator<<(uint64 value)
    {
        append<uint64>(value);
        return *this;
    }
    
    // signed as in 2e complement
    ByteBuffer &operator<<(int8 value)
    {
        append<int8>(value);
        return *this;
    }
    ByteBuffer &operator<<(int16 value)
    {
        append<int16>(value);
        return *this;
    }
    ByteBuffer &operator<<(int32 value)
    {
        append<int32>(value);
        return *this;
    }
    ByteBuffer &operator<<(int64 value)
    {
        append<int64>(value);
        return *this;
    }
    
    // floating points
    ByteBuffer &operator<<(float value)
    {
        append<float>(value);
        return *this;
    }
    ByteBuffer &operator<<(double value)
    {
        append<double>(value);
        return *this;
    }
    ByteBuffer &operator<<(const std::string &value)
    {
        append((uint8 const *)value.c_str(), value.length());
        append((uint8)0);
        return *this;
    }
    ByteBuffer &operator<<(const char *str)
    {
        append((uint8 const *)str, str ? strlen(str) : 0);
        append((uint8)0);
        return *this;
    }
    
    ByteBuffer &operator>>(bool &value)
    {
        value = read<char>() > 0 ? true : false;
        return *this;
    }
    ByteBuffer &operator>>(uint8 &value)
    {
        value = read<uint8>();
        return *this;
    }
    ByteBuffer &operator>>(uint16 &value)
    {
        value = read<uint16>();
        return *this;
    }
    ByteBuffer &operator>>(uint32 &value)
    {
        value = read<uint32>();
        return *this;
    }
    ByteBuffer &operator>>(uint64 &value)
    {
        value = read<uint64>();
        return *this;
    }
    
    //signed as in 2e complement
    ByteBuffer &operator>>(int8 &value)
    {
        value = read<int8>();
        return *this;
    }
    ByteBuffer &operator>>(int16 &value)
    {
        value = read<int16>();
        return *this;
    }
    ByteBuffer &operator>>(int32 &value)
    {
        value = read<int32>();
        return *this;
    }
    ByteBuffer &operator>>(int64 &value)
    {
        value = read<int64>();
        return *this;
    }
    
    ByteBuffer &operator>>(float &value)
    {
        value = read<float>();
        return *this;
    }
    ByteBuffer &operator>>(double &value)
    {
        value = read<double>();
        return *this;
    }
    ByteBuffer &operator>>(std::string& value)
    {
        value.clear();
        while (rpos() < size())                         // prevent crash at wrong string format in packet
        {
            char c=read<char>();
            if (c==0)
                break;
            value+=c;
        }
        return *this;
    }
    
    uint8 operator[](size_t pos)
    {
        return read<uint8>(pos);
    }
    
    size_t rpos()
    {
        return _rpos;
    };
    
    size_t rpos(size_t rpos_)
    {
        _rpos = rpos_;
        return _rpos;
    };
    
    size_t wpos()
    {
        return _wpos;
    }
    
    size_t wpos(size_t wpos_)
    {
        _wpos = wpos_;
        return _wpos;
    }
    
    template <typename T> T read()
    {
        T r=read<T>(_rpos);
        _rpos += sizeof(T);
        return r;
    };
    template <typename T> T read(size_t pos) const
    {
        //assert(pos + sizeof(T) <= size() || PrintPosError(false,pos,sizeof(T)));
        if (pos + sizeof(T) > size())
        {
            return T(0);
        }
//        return *((T const*)&_storage[pos]);
        T r;
        memcpy(&r, &_storage[pos], sizeof(T));
        return r;
    }
    
    void read(uint8 *dest, size_t len)
    {
        //assert(_rpos  + len  <= size() || PrintPosError(false,_rpos,len));
        if (_rpos + len > size())
        {
            memset(dest, 0, len);
            return ;
        }
        
        memcpy(dest, &_storage[_rpos], len);
        _rpos += len;
    }
    
    const uint8 *contents() const { return &_storage[0]; }
    
    size_t size() const { return _storage.size(); }
    bool empty() const { return _storage.empty(); }
    
    void resize(size_t newsize)
    {
        _storage.resize(newsize);
        _rpos = 0;
        _wpos = size();
    };
    void reserve(size_t ressize)
    {
        if (ressize > size()) _storage.reserve(ressize);
    };
    
    void append(const std::string& str)
    {
        append((uint8 const*)str.c_str(),str.size() + 1);
    }
    void append(const char *src, size_t cnt)
    {
        return append((const uint8 *)src, cnt);
    }
    void append(const uint8 *src, size_t cnt)
    {
        if (!cnt) return;
        
        assert(size() < 10000000);
        
        if (_storage.size() < _wpos + cnt)
            _storage.resize(_wpos + cnt);
        memcpy(&_storage[_wpos], src, cnt);
        _wpos += cnt;
    }
    void append(const ByteBuffer& buffer)
    {
        if(buffer.size()) append(buffer.contents(),buffer.size());
    }
    
    void appendPackGUID(uint64 guid)
    {
        size_t mask_position = wpos();
        *this << uint8(0);
        for(uint8 i = 0; i < 8; i++)
        {
            if(guid & 0xFF)
            {
                _storage[mask_position] |= (1<<i);
                *this << ((uint8)(guid & 0xFF));
            }
            
            guid >>= 8;
        }
    }
    
    void put(size_t pos, const uint8 *src, size_t cnt)
    {
        assert(pos + cnt <= size() || PrintPosError(true,pos,cnt));
        memcpy(&_storage[pos], src, cnt);
    }
    void print_storage()
    {
        //if(!sLog.IsOutDebug())                          // optimize disabled debug output
        //    return;
        
        CCLOG("STORAGE_SIZE: %lu", size() );
        for(uint32 i = 0; i < size(); i++)
            CCLOG("%u - ", read<uint8>(i) );
        CCLOG(" ");
    }
    
    void textlike()
    {
        //if(!sLog.IsOutDebug())                          // optimize disabled debug output
        //    return;
        
        CCLOG("STORAGE_SIZE: %lu", size() );
        for(uint32 i = 0; i < size(); i++)
            CCLOG("%c", read<uint8>(i) );
        CCLOG(" ");
    }
    
    void hexlike()
    {
        //if(!sLog.IsOutDebug())                          // optimize disabled debug output
        //    return;
        
        uint32 j = 1, k = 1;
        CCLOG("STORAGE_SIZE: %lu", size() );
        for(uint32 i = 0; i < size(); i++)
        {
            if ((i == (j*8)) && ((i != (k*16))))
            {
                if (read<uint8>(i) < 0x0F)
                {
                    CCLOG("| 0%X ", read<uint8>(i) );
                }
                else
                {
                    CCLOG("| %X ", read<uint8>(i) );
                }
                j++;
            }
            else if (i == (k*16))
            {
                if (read<uint8>(i) < 0x0F)
                {
                    CCLOG("\n0%X ", read<uint8>(i) );
                }
                else
                {
                    CCLOG("\n%X ", read<uint8>(i) );
                }
                
                k++;
                j++;
            }
            else
            {
                if (read<uint8>(i) < 0x0F)
                {
                    CCLOG("0%X ", read<uint8>(i) );
                }
                else
                {
                    CCLOG("%X ", read<uint8>(i) );
                }
            }
        }
        CCLOG(" ");
    }
    
protected:
    bool PrintPosError(bool add, size_t pos, size_t esize) const
    {
        CCLOG("ERROR: Attempt %s in ByteBuffer (pos: %lu size: %lu) value with size: %lu",(add ? "put" : "get"),pos, size(), esize);
        // assert must fail after function call
        return false;
    }
    
    size_t _rpos, _wpos;
    std::vector<uint8> _storage;
};

template <typename T> ByteBuffer &operator<<(ByteBuffer &b, const std::vector<T> &v)
{
    b << (uint32)v.size();
	for (typename std::vector<T>::const_iterator i = v.begin(); i != v.end(); i++)
    {
        b << *i;
    }
    return b;
}

template <typename T> ByteBuffer &operator>>(ByteBuffer &b, std::vector<T> &v)
{
    uint32 vsize;
    b >> vsize;
    v.clear();
    while(vsize--)
    {
        T t;
        b >> t;
        v.push_back(t);
    }
    return b;
}

template <typename T> ByteBuffer &operator<<(ByteBuffer &b, const std::list<T> &v)
{
    b << (uint32)v.size();
    for (typename std::list<T>::const_iterator i = v.begin(); i != v.end(); i++)
    {
        b << *i;
    }
    return b;
}

template <typename T> ByteBuffer &operator>>(ByteBuffer &b, std::list<T> &v)
{
    uint32 vsize;
    b >> vsize;
    v.clear();
    while(vsize--)
    {
        T t;
        b >> t;
        v.push_back(t);
    }
    return b;
}

template <typename K, typename V> ByteBuffer &operator<<(ByteBuffer &b, const std::map<K, V> &m)
{
    b << (uint32)m.size();
    for (typename std::map<K, V>::const_iterator i = m.begin(); i != m.end(); i++)
    {
        b << i->first << i->second;
    }
    return b;
}

template <typename K, typename V> ByteBuffer &operator>>(ByteBuffer &b, std::map<K, V> &m)
{
    uint32 msize;
    b >> msize;
    m.clear();
    while(msize--)
    {
        K k;
        V v;
        b >> k >> v;
        m.insert(std::make_pair(k, v));
    }
    return b;
}
#endif