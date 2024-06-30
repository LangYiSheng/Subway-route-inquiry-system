//
// Created by LanCher on 24-6-25.
//

#ifndef FILEIO_H
#define FILEIO_H

#include "Line.h"

#include <set>
#include <map>
#include <vector>
#include <fstream>
#define SETTING_NUM 10

//处理线路和换乘信息的存储与读取功能。
class FileIO {
    static void SaveSetting(ofstream& os,const vector<bool>& settings) ;//保存设置信息
    static void SaveLine(ofstream& os,const Line& line) ;//保存线路信息
    static void SaveBlockedStations(ofstream& os,const set<string>& blocked_stations) ;//保存禁用站点信息
    static vector<bool> LoadSetting(ifstream& is) ;//读取设置信息
    static Line LoadLine(ifstream& is) ;//读取线路信息
    static set<string> LoadBlockedStations(ifstream& is) ;//读取禁用站点信息
public:
    static bool GETSET0() ;//获取是否在程序启动时自动读取线路信息
    static bool SaveMain(const map<int, Line>& lines,const set<string>& blocked_stations,const vector<bool>& settings) ;//保存线路和换乘信息
    static bool LoadMain(map<int, Line>& lines,set<string>& blocked_stations,vector<bool>& settings) ;//读取线路和换乘信息

    /*void saveTransfer(const std::string& filename, const Transfer& transfer) const;//保存换乘信息*/
    /*Transfer loadTransfer(const std::string& filename) const;//读取换乘信息*/
};


#endif //FILEIO_H
