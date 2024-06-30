//
// Created by LanCher on 24-6-29.
//

#ifndef MENU_H
#define MENU_H

#include "Line.h"
#include<iostream>
#include <map>


class Menu {
    map<int,Line> lines;//线路信息,线路号到线路的映射，使用map是为了按序号排序
public:
    Menu() = default;
    void MainMenu();//主菜单


    void InquiryLineMenu();//线路查询菜单
    void ShowAllLines();//显示所有线路

    void EditLineMenu();//线路数据编辑菜单
    void AddLine();//添加线路

    void TestMenu();//测试菜单
};



#endif //MENU_H
