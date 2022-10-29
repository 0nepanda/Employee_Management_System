#pragma once
#include <iostream>
#include <string>
using namespace std;

// 职工抽象基类
class Worker
{
public:
    // 显示个人信息
    virtual void showInfo() = 0;

    // 获取岗位名称
    virtual string getDeptName() = 0;

    string m_Name;
    int m_Id;
    int m_DeptId;
};


// 不需要任何实现，  那么.cpp文件也不要创建。  去写子类