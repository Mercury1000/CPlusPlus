#pragma once
#include<iostream>
#include<memory>
#include<functional>

using namespace std;
//RAII是一种管理资源的类的设计思想,本质是利用对象生命周期来管理获取到的动态资源，避免资源泄漏
template<class T>
class SmartPtr
{
public:
    // RAII
    SmartPtr(T* ptr)
        :_ptr(ptr)
    {
    }
    ~SmartPtr()
    {
        cout << "delete[] " << _ptr << endl;
        delete[] _ptr;
    }
    // 重载运算符，模拟指针的行为，方便访问资源
    T& operator*()
    {
        return *_ptr;
    }
    T* operator->()
    {
        return _ptr;
    }
    T& operator[](size_t i)
    {
        return _ptr[i];
    }
private:
    T* _ptr;
};

namespace mercury
{
    template<class T>
    struct default_delete
    {
        void operator()(T* ptr)
        {
            delete ptr;
        }
    };
    template<class T>
    struct default_delete<T[]> 
    {
        void operator()(T* ptr) const { delete[] ptr; }
    };

    template<class T,class D = default_delete<T>>
    class unique_ptr
    {
    public:
        unique_ptr(T* ptr = nullptr, D del = D()) noexcept
            : _ptr(ptr)
            , _del(std::move(del)) //移动构造
        {}

        //禁止拷贝
        unique_ptr(const unique_ptr&) = delete;
        unique_ptr& operator=(const unique_ptr&) = delete;

        // 移动语义
        unique_ptr(unique_ptr&& up) noexcept
            : _ptr(up.release())
            , _del(std::move(up._del)) 
        {}
        ~unique_ptr()
        {
            if (_ptr)
                _del(_ptr);
        }
        T& operator*()
        {
            return *_ptr;
        }
        T* operator->()
        {
            return _ptr;
        }
        T& operator[](size_t i)
        {
            return _ptr[i];
        }
        T* get() const { return _ptr; }
        T* release() {
            T* tmp = _ptr;
            _ptr = nullptr;
            return tmp;
        }
        explicit operator bool() const { return _ptr != nullptr; }
    private:
        T* _ptr;
        D _del;
    };
    //数组特化
    template <class T, class D> 
    class unique_ptr<T[], D>
    {
    public:
        unique_ptr(T* ptr = nullptr, D del = D()) noexcept
            : _ptr(ptr)
            , _del(std::move(del)) //移动构造
        {}

        unique_ptr(const unique_ptr&) = delete;
        unique_ptr& operator=(const unique_ptr&) = delete;
        ~unique_ptr()
        {
            if(_ptr)
                _del(_ptr);
        }
        T& operator[](size_t i)
        {
            return _ptr[i];
        }
        explicit operator bool() const { return _ptr != nullptr; }
    private:
        T* _ptr;
        D _del;
    };

    template<class T>
    class shared_ptr
    {
    public:
        shared_ptr(T* ptr)
            :_ptr(ptr)
            ,_pcount(new atomic<int>(1))
        {}
        template<class D>
        shared_ptr(T* ptr,D del)
            :_ptr(ptr)
            ,_pcount(new atomic<int>(1))
            ,_del(del)
        {}
        shared_ptr(const shared_ptr<T>& sp)
            :_ptr(sp._ptr)
            ,_pcount(sp._pcount)
            , _del(sp._del)
        {
            (*_pcount)++;
        }
        shared_ptr& operator=(const shared_ptr<T>& sp)
        {
            if (_ptr != sp._ptr)
            {
                if (--(*_pcount) == 0)
                {
                    _del(_ptr);
                    delete _pcount;
                }
                _ptr = sp._ptr;
                _pcount = sp._pcount;
                _del = sp._del;
                (*_pcount)++;
            }
            return *this;
        }
        ~shared_ptr()
        {
            if (--(*_pcount) == 0)
            {
                _del(_ptr);
                delete _pcount;
            }
        }
        T& operator*()
        {
            return *_ptr;
        }
        T* operator->()
        {
            return _ptr;
        }
        T& operator[](size_t i)
        {
            return _ptr[i];
        }
        int use_count()
        {
            return *_pcount;
        }
        T* get() const { return _ptr; }
        explicit operator bool() const { return _ptr != nullptr; }

    private:
        T* _ptr;
        atomic<int>* _pcount;  // 原子操作 _pcount;
        std::function<void(T*)> _del = [](T* ptr) {delete ptr;};
    };
    template<class T>
    class shared_ptr<T[]>
    {
    public:
        shared_ptr(T* ptr)
            :_ptr(ptr)
            , _pcount(new atomic<int>(1))
        {}
        template<class D>
        shared_ptr(T* ptr, D del)
            : _ptr(ptr)
            , _pcount(new atomic<int>(1))
            , _del(del)
        {}
        shared_ptr(const shared_ptr<T[]>& sp)
            :_ptr(sp._ptr)
            , _pcount(sp._pcount)
            , _del(sp._del)
        {
            (*_pcount)++;
        }
        shared_ptr& operator=(const shared_ptr<T[]>& sp)
        {
            if (_ptr != sp._ptr)
            {
                if (--(*_pcount) == 0)
                {
                    _del(_ptr);
                    delete _pcount;
                }
                _ptr = sp._ptr;
                _pcount = sp._pcount;
                _del = sp._del;
                (*_pcount)++;
            }
            return *this;
        }
        ~shared_ptr()
        {
            if (--(*_pcount) == 0)
            {
                _del(_ptr);
                delete _pcount;
            }
        }
        T& operator[](size_t i)
        {
            return _ptr[i];
        }
        int use_count()
        {
            return *_pcount;
        }
        T* get() const { return _ptr; }
        explicit operator bool() const { return _ptr != nullptr; }

    private:
        T* _ptr;
        atomic<int>* _pcount;  // 原子操作 _pcount;
        std::function<void(T*)> _del = [](T* ptr) {delete[] ptr; };
    };
}