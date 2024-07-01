//
// Created by LanCher on 24-6-25.
//

#ifndef FILEIO_H
#define FILEIO_H

#include "Line.h"
#include "Transfer.h"

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
    static void SaveTransfer(ofstream& os,const Transfer & TS) ;//���滻����Ϣ
    static vector<bool> LoadSetting(ifstream& is) ;//��ȡ������Ϣ
    static Line LoadLine(ifstream& is) ;//��ȡ��·��Ϣ
    static set<string> LoadBlockedStations(ifstream& is) ;//��ȡ����վ����Ϣ
    static Transfer LoadTransfer(ifstream& is) ;//��ȡ������Ϣ
public:
    static bool GETSET0() ;//��ȡ�Ƿ��ڳ�������ʱ�Զ���ȡ��·��Ϣ
    static bool SaveMain(const map<int, Line>& lines,const set<string>& blocked_stations,const vector<bool>& settings,const Transfer&TS) ;//������·�ͻ�����Ϣ
    static bool LoadMain(map<int, Line>& lines,set<string>& blocked_stations,vector<bool>& settings,Transfer&TS) ;//��ȡ��·�ͻ�����Ϣ

    /*void saveTransfer(const std::string& filename, const Transfer& transfer) const;//���滻����Ϣ*/
    /*Transfer loadTransfer(const std::string& filename) const;//��ȡ������Ϣ*/
};


#endif //FILEIO_H
