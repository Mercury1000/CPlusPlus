#define _CRT_SECURE_NO_WARNINGS
#include"Smart_ptr.h"

double Divide(int a , int b)
{
    // 当b == 0时抛出异常
    if (b == 0)
    {
           throw "Divide by zero condition !";
    }
    else
    {
         return (double)a / (double)b;
    }
}
void Func()
{
    //这里可以看到如果发生除0错误抛出异常，另外下面的array和array2没有得到释放。
    //所以这里捕获异常后并不处理异常，异常还是交给外面处理，这里捕获了再重新抛出去。
    //但是如果array2new的时候抛异常呢，就还需要套一层捕获释放逻辑，这里更好解决方法是智能指针
    int* array1 = new int[10];
    int* array2 = new int[10];   
    try
    {
           int len,time;
           cin >> len >> time;
           cout << Divide(len , time) << endl;
    }
    catch (...)
    {
           cout << "delete []" << array1 << endl;
           cout << "delete []" << array2 << endl;
           delete[] array1;
           delete[] array2;

           throw; // 异常重新抛出，捕获到什么抛出什么
    }

    // ...
    cout << "delete []" << array1 << endl;
    delete[] array1;

    cout << "delete []" << array2 << endl;
    delete[] array2;
}
//int main()
//{
//    try
//    {
//           Func();
//    }
//    catch (const char* errmsg)
//    {
//           cout << errmsg << endl;
//    }
//    catch (const exception& e)
//    {
//           cout << e .what() << endl;
//    }
//    catch (...)
//    {
//           cout << "未知异常" << endl;
//    }
//    return 0;
//}
struct Date
{
    int _year;
    int _month;
    int _day;

    Date(int year = 1 , int month = 1 , int day = 1)
            :_year(year)
            ,_month(month)
             ,_day(day)
     {}

     ~Date()
     {
            cout << "~Date()" << endl;
     }
};

//C++标准库智能指针的使用(C++11)  *//C++98设计的auto_ptr不要使用，拷贝时会把被拷贝对象置空，访问会报错
void test1()
{
    unique_ptr<Date> up1(new Date);
    //unique_ptr<Date> up2(up1);不支持拷贝
    unique_ptr<Date> up3(move(up1));//但move之后支持移动，但是移动后up1也悬空，所以使用移动要谨慎

    shared_ptr<Date> sp1(new Date);
    shared_ptr<Date> sp2(sp1);
    shared_ptr<Date> sp3(sp2);
    cout << sp1.use_count() << endl;//引用计数

    sp1->_year++;
    cout << sp1->_year << endl;
    cout << sp2->_year << endl;
    cout << sp3->_year << endl;
}


template<class T>
void DeleteArrayFunc(T* ptr) 
{
    delete[] ptr;
}
template<class T>
class DeleteArray
{
public :
     void operator()(T* ptr)
     {
            delete[] ptr;
     }
};
class Fclose
{
public :
    void operator()(FILE* ptr)
    {
           cout << "fclose :" << ptr << endl;
           fclose(ptr);
    }
};

void test2()
{
    // 这样实现程序会崩溃
    // unique_ptr<Date> up1(new Date [10]);
    // shared_ptr<Date> sp1(new Date [10]);

    // 解决方案1
    // 因为new[]经常使用，所以unique_ptr和shared_ptr
    // 实现了一个特化版本，这个特化版本析构时用的delete[]
    unique_ptr<Date[]> up1(new Date[5]);
    shared_ptr<Date[]> sp1(new Date[5]);

    // 解决方案2

    // 仿函数对象做删除器
    //unique_ptr<Date, DeleteArray<Date>> up2(new Date [5], DeleteArray<Date>

    // unique_ptr和shared_ptr支持删除器的方式有所不同
    // unique_ptr是在类模板参数支持的，shared_ptr是构造函数参数支持的
    // 这里没有使用相同的方式还是挺坑的

    //使用仿函数unique_ptr可以不在构造函数传递，因为仿函数类型构造的对象直接就可以调用,但是下面的函数指针和lambda的类型就不可以
    //仿函数删除器
    unique_ptr<Date, DeleteArray<Date>> up2(new Date[5]);
    shared_ptr<Date> sp2(new Date[5], DeleteArray<Date>());

    //函数指针删除器
    unique_ptr<Date, void(*)(Date*)> up3(new Date[5], DeleteArrayFunc<Date>);
    shared_ptr<Date> sp3(new Date[5], DeleteArrayFunc<Date>);

    //lambda表达式删除器
    auto delArrOBJ = [](Date* ptr) {delete[] ptr; };
    unique_ptr<Date, decltype(delArrOBJ)> up4(new Date[5], delArrOBJ); //decltype()推导类型
    shared_ptr<Date> sp4(new Date[5], delArrOBJ);

    // 实现其他资源管理的删除器
    shared_ptr<FILE> sp5(fopen("Test .cpp", "r"), Fclose());
    shared_ptr<FILE> sp6(fopen("Test .cpp", "r"), [](FILE* ptr) {
        cout << "fclose :" << ptr << endl;
        fclose(ptr);
    });
}


int main()
{
    shared_ptr<Date> sp1(new Date);
    shared_ptr<Date> sp2 = make_shared<Date>(2026,5,1);
    //make_shared 的优势在于：它通过一次内存分配，同时为引用计数控制块和管理的对象申请一块连续的内存空间（通常控制块位于对象之前）。
    //这种“单次分配、内存连续”的设计不仅提升了分配效率，还增强了访问时的缓存局部性，并显著减少了内存碎片。
    //有点类似new[],不过会提升效率

    shared_ptr<Date> sp4;
    
    // if (sp1.operator bool())
    if (sp1)
        cout << "sp1 is not nullptr" << endl;
    
    if (!sp4)
        cout << "sp1 is nullptr" << endl;

    //报错,不支持普通指针构造成智能指针
    //shared_ptr<Date> sp5 = new Date(2024 , 9 , 11);
    //unique_ptr<Date> sp6 = new Date(2024 , 9 , 11);

    return 0;
}
