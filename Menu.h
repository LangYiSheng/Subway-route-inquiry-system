//
// Created by LanCher on 24-6-29.
//

#ifndef MENU_H
#define MENU_H

#include "Line.h"
#include "FileIO.h"
#include <iostream>
#include <map>


class Menu {
    map<int,Line> lines;//线路信息,线路号到线路的映射，使用map是为了按序号排序
public:
    Menu() = default;


    void MainMenu();//主菜单
        void InquiryLineMenu();//线路查询菜单
            void ShowAllLines();//显示所有线路
            void InquiryLine();//显示某条线路
        void EditLineMenu();//线路数据编辑菜单
            void AddLine();//添加线路
            void RemoveLine();//删除线路
            void EditLine();//编辑线路
                void AddStation(int line_number);//编辑线路->添加站点
                void RemoveStation(int line_number);//编辑线路->删除站点
                void EditStationDistance(int line_number);//编辑线路->编辑站点间距离
                void EditStationName(int line_number);//编辑线路->编辑站点名
                void ExtendLine(int line_number);//编辑线路->延长线路
                void ShortenLine(int line_number);//编辑线路->缩短线路
        void FileMenu();//文件操作菜单
            void SaveLines();//保存线路信息
            void ReadLines();//读取线路信息
        void TestMenu();//测试菜单
};



#endif //MENU_H
