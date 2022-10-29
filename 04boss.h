#pragma once
#include <iostream>
#include <string>
#include "02worker.h"
using namespace std;

// 老板类
class Boss : public Worker
{
public:
    // 构造函数
    Boss(int id, string name, int dId);

    // 显示个人信息
    virtual void showInfo();

    // 获取岗位名称
    virtual string getDeptName(); 
};