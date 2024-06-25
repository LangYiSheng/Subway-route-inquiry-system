//
// Created by LanCher on 24-6-25.
//

#ifndef FILEIO_H
#define FILEIO_H

#include "Line.h"
#include "Transfer.h"

#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>

//处理线路和换乘信息的存储与读取功能。
class FileIO {
public:
    void saveLine(const std::string& filename, const Line& line) const;//保存线路信息
    void saveTransfer(const std::string& filename, const Transfer& transfer) const;//保存换乘信息
    Line loadLine(const std::string& filename) const;//读取线路信息
    Transfer loadTransfer(const std::string& filename) const;//读取换乘信息
};


#endif //FILEIO_H
