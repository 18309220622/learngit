#pragma once

#include <iostream>
#include <stack>
#include<assert.h>
using namespace std;

template<class T>  
class DoubleStack_Queue  
{  
public:  
    void Push(const T& d);  
    void Pop();  
    bool Empty();  
    size_t Size();  
    T& Front();  
    T& Back();  
  
private:  
    stack<T> s1;  
    stack<T> s2;  
};  
  
template<class T>  
void DoubleStack_Queue<T>::Push(const T& d)  
{  
    s1.push(d);  
}  
  
template<class T>  
void DoubleStack_Queue<T>::Pop()  
{  
    assert(!s1.empty() || !s2.empty());  
    /*if (!s2.empty()) 
    { 
    cout<<s2.top()<<" "; 
    s2.pop(); 
    }*/  
    if (s2.empty())  
    {  
        while(!s1.empty())  
        {  
            s2.push(s1.top());  
            s1.pop();  
        }  
    }  
    s2.pop();  
}  
  
template<class T>  
bool DoubleStack_Queue<T>::Empty()  
{  
    return s1.empty()&&s2.empty();  
}  
  
template<class T>  
size_t DoubleStack_Queue<T>::Size()  
{  
    return s1.size();  
}  
template<class T>  
T& DoubleStack_Queue<T>::Front()  
{  
    assert(!s1.empty()||!s2.empty());   
    /*if (!s2.empty()) 
    { 
        return s2.top(); 
    }*/  
    if (s2.empty())  
    {  
        while(!s1.empty())  
        {  
            s2.push(s1.top());  
            s1.pop();  
        }  
    }  
    return s2.top();  
}  
  
template<class T>  
T& DoubleStack_Queue<T>::Back()  
{  
    assert(!s1.empty()||!s2.empty());  
    /*if (!s1.empty()) 
    { 
        return s1.top(); 
    }*/  
    if (s1.empty())  
    {  
        while(!s2.empty())  
        {  
            s1.push(s2.top());  
            s2.pop();  
        }  
    }  
    return s1.top();  
}  