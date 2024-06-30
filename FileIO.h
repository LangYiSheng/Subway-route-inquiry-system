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

//������·�ͻ�����Ϣ�Ĵ洢���ȡ���ܡ�
class FileIO {
    static void SaveSetting(ofstream& os,const vector<bool>& settings) ;//����������Ϣ
    static void SaveLine(ofstream& os,const Line& line) ;//������·��Ϣ
    static void SaveBlockedStations(ofstream& os,const set<string>& blocked_stations) ;//�������վ����Ϣ
    static vector<bool> LoadSetting(ifstream& is) ;//��ȡ������Ϣ
    static Line LoadLine(ifstream& is) ;//��ȡ��·��Ϣ
    static set<string> LoadBlockedStations(ifstream& is) ;//��ȡ����վ����Ϣ
public:
    static bool GETSET0() ;//��ȡ�Ƿ��ڳ�������ʱ�Զ���ȡ��·��Ϣ
    static bool SaveMain(const map<int, Line>& lines,const set<string>& blocked_stations,const vector<bool>& settings) ;//������·�ͻ�����Ϣ
    static bool LoadMain(map<int, Line>& lines,set<string>& blocked_stations,vector<bool>& settings) ;//��ȡ��·�ͻ�����Ϣ

    /*void saveTransfer(const std::string& filename, const Transfer& transfer) const;//���滻����Ϣ*/
    /*Transfer loadTransfer(const std::string& filename) const;//��ȡ������Ϣ*/
};


#endif //FILEIO_H
