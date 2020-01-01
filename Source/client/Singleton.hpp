#pragma once
template<class T>
#define HUNGER
class Singleton
{
public:
#ifdef HUNGER
    static T &GetInstance()
    {
        return smInstance;
    }
#else
    static T &GetInstance()
    {
        //TODO not multi-threading support
        if(smInstance!=nullptr)
        {
            smInstance = new T;
        }
        return *smInstance;
    }
#endif
private:
    Singleton(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton& operator=(Singleton&&) = delete;
protected:
    Singleton(){};
    virtual ~Singleton() { }
#ifdef HUNGER
    static T smInstance;
#else
    static T *smInstance;
    //class Garbo
    //{
    //public:
    //    ~Garbo()
    //    {
    //        if(smInstance!=nullptr)
    //        {
    //            delete smInstance;
    //        }
    //    }
    //};
    //static Garbo smGarbo;
#endif
};

#ifdef HUNGER
template<class T>
T Singleton<T>::smInstance;
#else
template<class T>
T *Singleton<T>::smInstance=nullptr;
//template<class T>
//Singleton<T>::Garbo Singleton<T>::smGarbo;
#endif
