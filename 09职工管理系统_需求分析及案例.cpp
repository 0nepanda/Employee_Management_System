#include <iostream>
#include <string>
#include <cstdlib>  
#include <fstream>
#include "01workerManager.h"
#include "02worker.h"
#include "02employee.h"
#include "03manager.h"
#include "04boss.h"
using namespace std;

/*
职工管理系统
    1、管理系统需求
    职工管理系统可以用来管理公司内所有员工的信息

    公司中职工分为三类： 普通员工、经理、老板， 显示信息时， 需要显示职工编号、职工姓名、职工岗位、以及职责
        普通员工职责：      完成经理交给的任务
        经理职责：          完成老板交给的任务，并下发任务给员工
        老板职责：          管理公司所有事物

    管理系统中需要实现的功能如下：
        1.退出管理程序：      退出当前管理系统
        2.增加职工信息：      实现批量添加职工职能， 将信息录入到文件中， 职工信息为: 职工编号、姓名、部门编号
        3.显示职工信息：      显示公司内部所有职工的信息
        4.删除离职职工：      按照编号删除指定的职工
        5.修改职工信息：      按照编号修改职工个人信息
        6.查找职工信息：      按照职工的比那好或者职工的姓名进行查找星官的人员信息
        7.按照编号排序：      按照职工编号， 进行排序， 排序规则由用户指定
        8.清空所有文档：      清空文件中记录的所偶职工信息   （清空前需要再次确认，防止误删）
*/

int main() {
    // // 测试多态代码
    // Worker * worker = NULL;  //创建空指针
    // worker = new Employee(1, "张三", 1);             // 父类指针指或地址向子类对象
    // worker->showInfo();
    // delete worker;

    // worker = new Manager(2, "李四", 2);
    // worker->showInfo();
    // delete worker;

    // worker = new Boss(3, "王五", 3);
    // worker->showInfo();
    // delete worker;    

    // 实例化管理者对象
    WorkerManager wm;

    int choice = 0;      //用来记录用户的选项

    while (true)
    {
        /* code */
        // 调用展示菜单成员函数
        wm.Show_Menu();

        cout << "请输入您的选择： " << endl;
        cin >> choice;

        switch (choice)
        {
        case 0:
            /* 0.退出管理程序 */
            wm.ExitSystem();
            break;
        case 1:
            /* 1.增加职工信息 */
            wm.Add_Emp();
            break;
        case 2:
            /* 2.显示职工信息 */
            wm.Show_Emp();
            break;
        case 3:
        {//当switch-case下case的语句过长时， case用{}封装代码段
            /* 3.删除离职职工 */
            // 检测是否存在
            // int ret = wm.IsExist(3);
            // if (ret != -1)
            // {
            //     /* 不存在 */
            //     cout << "存在该职工！" << endl;
            // }
            // else
            // {
            //     cout << "不存在该职工！" << endl;
            // }
            wm.Del_Emp();
            break;
        }
        case 4:
            /* 4.修改职工信息 */
            wm.Mod_Emp();
            break;
        case 5:
            /* 5.查找职工信息 */
            wm.Find_Emp();
            break;
        case 6:
            wm.Sort_Emp();
            /* 6.按照编号排序 */
            break;
        case 7:
            /* 7.清空所有文档 */
            wm.Clean_File();
            break;
        default:
            break;
        }
    }
    



    return 0;
}