/**
* @file: TestDispatchCallback.cpp
* @author: Ofir Nahshoni
* @brief: This is a test file for Dispatcher Design-Pattern.
*/

#include <string>
#include <iostream>

#include "DispatchCallback.hpp"

namespace observers
{

class ViewWindow
{
public:
    ViewWindow(size_t width = 10, size_t height = 10, 
                const std::string& name = "");
    void PrintMembers();
    void Foo(int num);
    void SetName(const std::string& name);

private:
    size_t m_width;
    size_t m_height;
    std::string m_name;
};  // class ViewWindow

class DataModel
{
public:
    DataModel(int data1 = 0, int data2 = 0, const std::string& name = "");
    void PrintMembers();
    void Foo(int num);
    void SetName(const std::string& name);

private:
    int m_data1;
    int m_data2;
    std::string m_name;
};  // class DataModel

class ControlWindow
{
public:
    ControlWindow(const std::string& name = "");
    void PrintMembers();
    void Foo(int num);
    void SetName(const std::string& name);

private:
    std::string m_name;
};  // class ControlWindow

ViewWindow::ViewWindow(size_t width, size_t height, const std::string& name): 
                        m_width(width), m_height(height), m_name(name)
{ }

void ViewWindow::Foo(int num)
{
    std::cout << "num = " << num << std::endl;
}

void ViewWindow::SetName(const std::string& name)
{
    m_name = name;
}

DataModel::DataModel(int data1, int data2, const std::string& name): 
                    m_data1(data1), m_data2(data2), m_name(name)
{ }

void DataModel::Foo(int num)
{
    std::cout << "num = " << num << std::endl;
}

void DataModel::SetName(const std::string& name)
{
    m_name = name;
}

ControlWindow::ControlWindow(const std::string& name): m_name(name)
{ }

void ControlWindow::Foo(int num)
{
    std::cout << "num = " << num << std::endl;
}

void ControlWindow::SetName(const std::string& name)
{
    m_name = name;
}

}   // namespace observers

void TestsOneDispatcherAndObserver();
void TestsOneDispatcherMultipleObservers();

int main()
{
    TestsOneDispatcherAndObserver();
    TestsOneDispatcherMultipleObservers();

    return 0;
}

void TestsOneDispatcherAndObserver()
{
    observers::ViewWindow vw;
    ilrd::Callback<int, observers::ViewWindow> callback1(vw, 
                    &observers::ViewWindow::Foo);
    ilrd::Dispatcher<int> d;
    
    d.Register(&callback1);
    d.Notify(31);
}

void TestsOneDispatcherMultipleObservers()
{
    observers::DataModel dt;
    observers::ControlWindow cw;
    ilrd::Dispatcher<int> d;
    
    ilrd::Callback<int, observers::DataModel> callback1(dt, 
        &observers::DataModel::Foo);
    ilrd::Callback<int, observers::ControlWindow> callback2(cw, 
        &observers::ControlWindow::Foo);
    

    d.Register(&callback1);
    d.Register(&callback2);
    d.Notify(10);

    d.Unregister(&callback2);
    d.Notify(5);
    d.Unregister(&callback1);
}