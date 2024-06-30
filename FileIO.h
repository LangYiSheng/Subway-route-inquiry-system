//
// Created by LanCher on 24-6-25.
//

#ifndef FILEIO_H
#define FILEIO_H

#include "Line.h"

#include <string>
#include <map>
#include <fstream>

//处理线路和换乘信息的存储与读取功能。
class FileIO {
    static void SaveLine(ofstream& os,const Line& line) ;//保存线路信息
    static Line LoadLine(ifstream& is) ;//读取线路信息
public:
    static bool SaveMain(const map<int,Line>& lines) ;//保存线路和换乘信息
    static bool LoadMain(map<int,Line>& lines) ;//读取线路和换乘信息

    /*void saveTransfer(const std::string& filename, const Transfer& transfer) const;//保存换乘信息*/
    /*Transfer loadTransfer(const std::string& filename) const;//读取换乘信息*/
};


#endif //FILEIO_H
