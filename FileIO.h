//
// Created by LanCher on 24-6-25.
//

#ifndef FILEIO_H
#define FILEIO_H

#include "Line.h"

#include <string>
#include <map>
#include <fstream>

//������·�ͻ�����Ϣ�Ĵ洢���ȡ���ܡ�
class FileIO {
    static void SaveLine(ofstream& os,const Line& line) ;//������·��Ϣ
    static Line LoadLine(ifstream& is) ;//��ȡ��·��Ϣ
public:
    static bool SaveMain(const map<int,Line>& lines) ;//������·�ͻ�����Ϣ
    static bool LoadMain(map<int,Line>& lines) ;//��ȡ��·�ͻ�����Ϣ

    /*void saveTransfer(const std::string& filename, const Transfer& transfer) const;//���滻����Ϣ*/
    /*Transfer loadTransfer(const std::string& filename) const;//��ȡ������Ϣ*/
};


#endif //FILEIO_H
