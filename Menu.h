//
// Created by LanCher on 24-6-29.
//

#ifndef MENU_H
#define MENU_H

#include "Line.h"
#include "FileIO.h"
#include "Transfer.h"
#include <iostream>
#include <map>
#include <set>

class Menu {
    map<int,Line> lines;//线路信息,线路号到线路的映射，使用map是为了按序号排序
    set<string> blockedStations;//禁用站点
    Transfer TS;//换乘信息
    vector<bool> settings;//设置信息,存有10个bool值用于设置
    //第一个bool值表示是否在程序启动时自动读取线路信息
    //第二个bool值表示是否在程序退出时自动保存线路信息
    //第三个bool值表示是否在显示路线时显示站点间距离
    //第四个bool值表示是否在显示路线时显示站点是否被禁用
public:
    Menu():settings(SETTING_NUM,true) {}//初始化设置信息;



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
            void BlockStationMenu();//禁用站点菜单
                void ShowBlockedStations();//禁用站点菜单->显示禁用站点
                void BlockStation();//禁用站点菜单->禁用指定站点
                void BlockStationInterval();//禁用站点菜单->禁用指定站点
                void UnblockStation();//禁用站点菜单->解禁站点
                void UnblockStationInterval();//禁用站点菜单->解禁站点
            void TransferMenu();//换乘信息菜单
                void ShowAllTransfers();//换乘信息菜单->显示所有换乘信息
                void ShowStationTransfers();//换乘信息菜单->显示某线路的换乘信息
                void AddTransfer();//换乘信息菜单->添加换乘信息
                void RemoveTransfer();//换乘信息菜单->删除换乘信息
        void FileMenu();//文件操作菜单
            void SaveLines();//保存线路信息
            void ReadLines();//读取线路信息
        void SettingMenu();//设置菜单
        void TestMenu();//测试菜单
            void EnterTransferInformationInBatches();//批量输入换乘信息
};



#endif //MENU_H
