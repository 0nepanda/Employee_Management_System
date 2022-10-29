#include "01workerManager.h"
#include "02employee.h"
#include "03manager.h"
#include "04boss.h"

WorkerManager::WorkerManager()    //在.cpp中空实现
{
    // 初始化属性    // 如果已经有文件了， 那么不能对数量和数组指针初始化
    ifstream ifs;
    ifs.open( FILENAME, ios::in);   //读文件

    // 1. 文件不存在
    if ( !ifs.is_open() )
    {
        /* 没打开 */
        // cout << "文件不存在" << endl;
        // 初始化属性
        this->m_EmpNum = 0;
        this->m_EmpArray = nullptr;
        this->m_FileisEmpty = true;
        ifs.close();
        return;
    }
    
    // 2.文件存在， 但数据为空
    char ch;
    ifs >> ch;
    if ( ifs.eof() )    // eof为true 时，说明读到的是文件尾为空
    {
        /* 文件为空 */
        cout << "文件为空！" << endl;
        // 初始化属性
        this->m_EmpNum = 0;
        this->m_EmpArray = nullptr;
        this->m_FileisEmpty = true;
        ifs.close();
        return;
    }
    // else
    // {
    //     cout << "文件不为空" << endl;
    //     cout << ch << endl;          // 为什么能读到1  删除.txt内容后也要保存
    // }
    
    // 3. 文件存在， 并且记录数据
    this->m_FileisEmpty = false;   //(自己加的)
    int num = this->get_EmpNum();
    // cout << "当前公司人员数为： " << num << endl;
    this->m_EmpNum = num;

    // 开辟空间
    this->m_EmpArray = new Worker*[this->m_EmpNum];
    // 将温江中的数据， 存到数组中
    this->init_Emp();

    // // 测试代码
    // for (int i = 0; i < this->m_EmpNum; i++)
    // {
    //     /* 输出测试 */
    //     cout << "职工编号： " << this->m_EmpArray[i]->m_Id
    //          << "    职工姓名： " << this->m_EmpArray[i]->m_Name
    //          << "    职工职责： " << this->m_EmpArray[i]->m_DeptId << endl;
    // }
    
}

// 展示菜单
void WorkerManager::Show_Menu()
{
    cout << "**********************************************" << endl;
    cout << "************ 欢迎使用职工管理系统! *************" << endl;
    cout << "*************    0.退出管理程序   **************" << endl;
    cout << "*************    1.增加职工信息   **************" << endl;
    cout << "*************    2.显示职工信息   **************" << endl;
    cout << "*************    3.删除职工信息   **************" << endl;
    cout << "*************    4.修改职工信息   **************" << endl;
    cout << "*************    5.查找职工信息   **************" << endl;
    cout << "*************    6.按照编号排序   **************" << endl;
    cout << "*************    7.清空所有文档   **************" << endl;
    cout << "**********************************************" << endl;
    cout << endl;
}

// 0.退出系统
void WorkerManager::ExitSystem()
{
    cout << "欢迎下次使用" << endl;
    exit(0);    //退出程序
}

// 1.添加职工
void WorkerManager::Add_Emp()
{
    cout << "请输入添加人数： " << endl;

    int addNum = 0;  //用来保存用户的数量
    cin >> addNum;

    if (addNum > 0)
    {
        /* 添加 */
        // 计算添加新空间大小
        int newSize = this->m_EmpNum + addNum;   //新空间人数

        // 开辟新空间
        Worker ** newSpace = new Worker*[newSize];   //原来就是要你的地址（work*）,为 这nieSize个地址开辟new Worker*[newSize]这般的新内存

        // 将原来空间下数据， 拷贝到新空间下
        if (this->m_EmpArray != NULL)  //原来有数据 且不为空
        {
            for (int i = 0; i < this->m_EmpNum; i++)
            {
                /* 拷贝原有的 */
                newSpace[i] = this->m_EmpArray[i];
            }
            
        }

        // then添加新数据
        for (int i = 0; i < addNum; i++)
        {
            /* 添加新存的 */
            int id;
            string name;
            int dSelect;  //部门选择

            cout << "请输入第 " << i+1 << "位新职工编号： " << endl;
            cin >> id;
            cout << "请输入第 " << i+1 << "位新职工姓名： " << endl;
            cin >> name;
            cout << "请输入第 " << i+1 << "位新职工所在岗位： " << endl;
            cout << "1---普通职工" << endl;
            cout << "2---经理" << endl;
            cout << "3---老板" << endl;
            cin >> dSelect;

            Worker * worker = NULL;
            switch (dSelect)     //通过多态的方式将 工种 创造出来
            {
            case 1:
                /* 普通职工 */
                worker = new Employee(id, name, dSelect);
                break;
            case 2:
                /* 普通职工 */
                worker = new Manager(id, name, dSelect);
                break;
            case 3:
                worker = new Boss(id, name, dSelect);
                /* 普通职工 */
                
                break;                            
            default:
                cout << "输入有误" << endl;
                break;
            }
            // 将所创建的职工职责， 保存到数组中
            newSpace[this->m_EmpNum + i] = worker;
        }

        // 释放原有空间
        delete[] this->m_EmpArray;

        // 更改指针指向
        this->m_EmpArray = newSpace;

        // 更新新的职工人数
        this->m_EmpNum = newSize;

        // 既然写进去了数据， 便更新文件为空状态为假
        this->m_FileisEmpty = false;

        // 成功添加后， 保存数据到文件
        this->save();

        // 提示添加成功
        cout << "成功添加 " << addNum << " 位职工。" << endl; 

    }
    else
    {
        cout << "输入有误" << endl;
    }
    
    // 按任意键后清屏，回到上级目录
    // system("pause");
    // system("cls");
    // cin.get();    //任意键继续 但是好像没用
    // printf ("\033c");   // 清屏

}

// 1.保存文件
void  WorkerManager::save()
{
    ofstream ofs;
    ofs.open(FILENAME, ios::out);     // 用输出的方式打开文件---写文件

    for (int i = 0; i < this->m_EmpNum; i++)
    {
        /* 将每个人的数据写入到文件夹 */
        ofs << this->m_EmpArray[i]->m_Id << " "
            << this->m_EmpArray[i]->m_Name << " "
            << this->m_EmpArray[i]->m_DeptId << " " << endl;
    }
    // 关闭文件
    ofs.close();
    
}

// 2. 读文件---统计人数
int WorkerManager::get_EmpNum()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    int id;
    string name;
    int dId;

    int num = 0;
    while (ifs >> id && ifs >> name && ifs >> dId)
    {
        /* 同时读到一个人的三条信息，算作加1 */
        num++;
    }
    return num;
    
}

// 2. 读文件---在（编译器）初始化员工
void WorkerManager::init_Emp()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    
    int id;
    string name;
    int dId;

    int index = 0;
    while (ifs >> id && ifs >> name && ifs >> dId)
    {
        /* code */
        Worker * worker = NULL;    // 创建一个具体职工类

        if (dId == 1)  // 普通职工
        {
            /* code */
            worker = new Employee(id, name, dId);
        }
        else if (dId == 2)
        {
            /* 经理 */
            worker = new Manager(id, name, dId);
        }
        else              // 老板
        { 
            worker = new Boss(id, name, dId);
        }
        this->m_EmpArray[index] = worker;
        index++;
        
    }
    ifs.close();

}

// 2. 显示成员职工（多态接口调用show_Emp）
void WorkerManager::Show_Emp()
{
    // 判断文件是否为空
    if(this->m_FileisEmpty)
    {
        cout << "文件不存在， 或者文件为空" << endl;
    }
    else      // 显示每个职工
    {
        for (int i = 0; i < this->m_EmpNum; i++)
        {
            /* 利用多态抵用程序接口 */
            this->m_EmpArray[i]->showInfo();
        }
    }
    // 按任意键后清屏，回到上级目录
    // system("pause");
    // system("cls");
    // cin.get();    //任意键继续 但是好像没用
    // printf ("\033c");   // 清屏

}

// 3. 删除职工--是否存在
int WorkerManager::IsExist(int id)
{
    int index = -1;
    for (int i = 0; i < this->m_EmpNum; i++)
    {
        /* 遍历寻找职工编号 */
        if (this->m_EmpArray[i]->m_Id == id)
        {
            /* 有编号可以等于 */
            index = i;
            break;
        }
        
    }
    return index;
}

// 3. 删除职工
void WorkerManager::Del_Emp()
{
    if (this->m_FileisEmpty)  //先判断文档存在与否
    {
        /* true不存在 */
        cout << "当前文件不存在或记录为空" << endl;
    }
    else
    {
        cout << "请输入要删除人员的编号：" << endl;
        // 按照职工编号删除
        int id = 0;
        cin >> id;    
        int index = this->IsExist(id);  //-1不能在， 其他返回值i为存在  ||index: 0~num-1

        if (index != -1)
        {
            /* 存在，即将删除 */
            // 数据前移
            for (int i = index; i < this->m_EmpNum-1; i++)
            {
                /* 依次前移 类地址 */
                this->m_EmpArray[i] = this->m_EmpArray[i+1];
            }
            this->m_EmpNum--; //更新数组中记录人员个数
            // 数据同步更新到文件夹中
            this->save();

            cout << "删除成功！" << endl;
        }
        else      // index = -1,即检测到没有这个人，无法删除
        {
            cout << "删除失败，未找到该员工" << endl;
        }
        
    }
// 按任意键后清屏，回到上级目录
// system("pause");
// system("cls");
// cin.get();    //任意键继续 但是好像没用
// printf ("\033c");   // 清屏    
}

// 4. 修改职工
void WorkerManager::Mod_Emp()
{
    if (this->m_FileisEmpty)
    {
        /* 文件不存在|空文件 */
        cout << "文件不存在或当前记录为空" << endl;
    }
    else
    {
        cout << "请输入需要修改职工的编号：" << endl;
        int id;
        cin >> id;

        int ret = this->IsExist(id);
        if ( ret != -1)   // 找到了
        {
            /* ret = i ~(0,num-1) */
            
            delete this->m_EmpArray[ret];

            int newId = 0;
            string name = "";
            int dSelect = 0;

            cout << "已查到： " << id << "号职工， 请输入新职工号:" << endl;
            cin >> newId;

            cout << "请继续输入新职工姓名： " << endl;
            cin >> name;

            cout << "请继续输入新职工岗位： " << endl;
            cout << "1---普通职工" << endl;
            cout << "2---经理" << endl;
            cout << "3---老板" << endl;
            cin >> dSelect;

            Worker * worker = NULL;
            switch (dSelect)
            {
            case 1:
                /* 普通职工 */
                worker = new Employee(id, name, dSelect);  // 父类指针或引用指向子类对象
                break;
            case 2:
                /* 普通职工 */
                worker = new Manager(id, name, dSelect);
                break;            
            case 3:
                /* 普通职工 */
                worker = new Boss(id, name, dSelect);
                break;
            default:
                break;
            }

            // 更新数据 到数组中
            this->m_EmpArray[ret] = worker;
            cout << "修改成功！" << endl;

            // 保存到文件
            this->save();
        }
        else
        {
            cout << "修改失败，查无此人" << endl;
        }
        
    }
// 按任意键后清屏，回到上级目录
// system("pause");
// system("cls");
// cin.get();    //任意键继续 但是好像没用
// printf ("\033c");   // 清屏     
}

// 5. 查找职工
void WorkerManager::Find_Emp()
{
    if (this->m_FileisEmpty)
    {
        /* 文件空或不存在 */
        cout << "文件不存在或当前记录为空" << endl;
    }
    else
    {
        cout << "请输入查找方法：" << endl;
        cout << "1、按照职工编号查找" << endl;
        cout << "2、按照职工姓名查找" << endl;

        int select;
        cin >> select;

        if (select == 1)
        {
            /* 编号查找 */
            cout << "请输入要查找员工的编号： " << endl;
            int id;
            cin >> id;

            int ret = IsExist(id);
            if (ret != -1)
            {
                /* 找到，返回数组索引 */
                this->m_EmpArray[ret]->showInfo();
            }
            else  //-1
            {
                cout << " 查无此人" << endl;
            }
            

        }
        else if (select == 2)
        {
            /* 姓名查找 */      
            cout << "请输入要查找员工的姓名： " << endl;    

            string name;
            cin >> name;

            //加入判断是否查到的标志。 用以循环中更改，否则不利于应对 “ 循环--失败 ”情况
            bool flag = false;
            for (int i = 0; i < this->m_EmpNum; i++)
            {
                /* 遍历匹配 */
                if (this->m_EmpArray[i]->m_Name == name)
                {
                    /* 匹配 */
                    cout << "查找成功。 职工编号为： " << this->m_EmpArray[i]->m_Id << "    职工信息如下: " << endl;
                    flag = true;
                    this->m_EmpArray[i]->showInfo();
                }

            }
            if (flag == false)
            {
                /* 查找失败 */
                cout << "查无此人" << endl;
            }      
        }
        else
        {
            cout << "选择的查找方式有误！" << endl;
        }
        // printf("\033c");
        
    }
    
}

// 6. 编号排序
void WorkerManager::Sort_Emp()
{
    if (this->m_FileisEmpty)
    {
        /* 空、不存在 */
        cout << "当前文件不存在或记录为空" << endl;
        // 按任意键后清屏，回到上级目录
        // system("pause");
        // system("cls");
        // cin.get();    //任意键继续 但是好像没用
        // printf ("\033c");   // 清屏

    }
    else
    {
        cout << "请选择排序方式： " << endl;
        cout << "1、升序排列" << endl;
        cout << "2、降序排列" << endl;

        int select;
        cin >> select;

        for (int i = 0; i < this->m_EmpNum; i++)   //选择循环
        {
            /* 外循环遍历数组 */
            int minormax = i;    // 假定的最小值或最大值下标
            for (int j = i+1; j < this->m_EmpNum; j++)
            {
                /* 寻找一个最小的，等待交换 */
                if (select == 1)
                {
                    /* 选择升序 */
                    if (this->m_EmpArray[minormax]->m_Id > this->m_EmpArray[j]->m_Id )
                    {
                        /* 假定的比排在我后面的大 */
                        minormax = j;
                    }
                    
                }
                else
                {
                    /* 选择降序 */
                    if (this->m_EmpArray[minormax]->m_Id < this->m_EmpArray[j]->m_Id )
                    {
                        /* 假定的比排在我后面的大 */
                        minormax = j;
                    }
                }
            }

            // 判断循环开始假定的 最小值或最大值 ，是不是计算的最小值或最大值， 如果不是，交换数据
            if (minormax != i)
            {
                /* 索引不是假设的那个 */
                Worker* temp = this->m_EmpArray[i];
                this->m_EmpArray[i] = this->m_EmpArray[minormax];  //下次循环开始所在i+1前面的数都是升序的，每次把最小或最大的放到i索引处
                this->m_EmpArray[minormax] = temp;
            }
            
        }

        cout << " 排序成功！ 排序结果为： " << endl;
        this->save();
        this->Show_Emp();   // 展示所有职工 ||这里面有清屏
        
    }
    
}

// 7. 清空文件
void WorkerManager::Clean_File()
{
    // 确认
    cout << "是否确认清空？" << endl;
    cout << "1、确认" << endl;
    cout << "2、取消" << endl;

    int select = 0;
    cin >> select;

    if (select == 1)
    {
        /* 确认清空 */
        // 1、文件
        ofstream ofs;
        ofs.open(FILENAME, ios::trunc);  //删除文件后重新创建
        ofs.close();

        // 2、内存数组地址
        if (this->m_EmpArray != NULL)
        {
            /* 删除堆区的每个worker对象 */
            for (int i = 0; i < this->m_EmpNum; i++)
            {
                delete this->m_EmpArray[i];
                this->m_EmpArray[i] = NULL;
            }

            // 删除堆区数组指针
            delete[] this->m_EmpArray;
            this->m_EmpArray = NULL;
            this->m_EmpNum = 0;
            this->m_FileisEmpty = true;
      
        }
        cout << "清空成功" << endl;
        printf("/33c");
    }
    else
    {
        return;
    }
    
}

WorkerManager::~WorkerManager()
{
    if ( this->m_EmpArray != NULL)
    {
        /* WM类内由Add_Emp将数组指针m_EmpArray指向newspace，现在需要手动释放 */
        delete[] this->m_EmpArray;
        this->m_EmpArray = NULL;
    }
    
}