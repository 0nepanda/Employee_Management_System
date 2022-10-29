target=workManager
libs=09职工管理系统_需求分析及案例.cpp 01workerManager.cpp 02employee.cpp 03manager.cpp 04boss.cpp
$(target):$(libs)
	g++ -std=c++11 $^ -o $@