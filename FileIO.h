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

//������·�ͻ�����Ϣ�Ĵ洢���ȡ���ܡ�
class FileIO {
public:
    void saveLine(const std::string& filename, const Line& line) const;//������·��Ϣ
    void saveTransfer(const std::string& filename, const Transfer& transfer) const;//���滻����Ϣ
    Line loadLine(const std::string& filename) const;//��ȡ��·��Ϣ
    Transfer loadTransfer(const std::string& filename) const;//��ȡ������Ϣ
};


#endif //FILEIO_H
