#pragma once             //防止头文件出现重复包含
#include <iostream>      //包含输入输出流头文件
using namespace std;     //使用标准命名空间
#include "02worker.h"

#include "02employee.h"
#include "03manager.h"   //为什么6~8行，不导入也没事
#include "04boss.h"          

#include <fstream>
#define FILENAME "05empFile.txt"   //宏常量


class WorkerManager
{
public:

    //构造函数
    WorkerManager();   //.h中只做声明 不做实现

    // 展示菜单
    void Show_Menu();

    // 0.退出系统
    void ExitSystem();

    // 1.添加职工
    void Add_Emp();

    // 1.保存文件
    void save();

    // 读取文件---统计人数
    int get_EmpNum();

    // 2. 读文件---在（编译器）初始化员工
    void init_Emp();
    
    // 2. 显示成员职工（多态接口调用show_Emp）
    void Show_Emp();

    // 3. 删除职工
    // 3. 删除职工--是否存在
    int IsExist(int id);

    // 3. 删除职工
    void Del_Emp();

    // 4. 修改职工
    void Mod_Emp();

    // 5. 查找职工
    void Find_Emp();

    // 6. 编号排序
    void Sort_Emp();

    // 7. 清空文件
    void Clean_File();

    //析构函数
    ~WorkerManager();
public:
    // 1.记录职工人数
    int m_EmpNum;

    // 1.职工数组指针
    Worker ** m_EmpArray;

    // 读文件
    // 判断问价是否为空 标志
    bool m_FileisEmpty;
};