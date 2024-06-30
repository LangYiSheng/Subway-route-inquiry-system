//
// Created by LanCher on 24-6-29.
//

#include "Menu.h"

void Menu::MainMenu() {
    while(true) {
        system("cls");
        cout<<"��ӭʹ���Ϻ�������·��ѯϵͳ"<<endl;
        cout<<"�����ڴ洢��·����Ϊ��"<<lines.size()<<endl;
        cout<<"��ͨ������������ѡ���ܣ�"<<endl;
        cout<<"1.��·��ѯ-��ȡ������·����Ϣ"<<endl;
        cout<<"2.��·�༭-�༭������·����Ϣ"<<endl;
        cout<<"3.·�߲�ѯ-��ѯվ���ĳ�����·  "<<endl;
        cout<<"4.����/��ȡ-������ȡ������·��Ϣ"<<endl;
        /*cout<<"9.��������-���ó����һЩ����"<<endl;*/
        cout<<"99.�����߲��Բ˵�"<<endl;
        cout<<"0.�˳�"<<endl;
        cout<<"����������ѡ��";
        string input;
        while(cin>>input) {
            if(input=="1") {
                InquiryLineMenu();
            }
            else if(input=="2") {
                EditLineMenu();
            }
            else if(input=="3") {
                /*InquiryRouteMenu();*/
                cout<<"��δ����"<<endl;
                system("pause");
            }
            else if(input=="4") {
                FileMenu();
            }
            /*else if(input=="9") {
                /*SettingMenu();#1#
                cout<<"��δ����"<<endl;
                system("pause");
            }*/
            else if(input=="99") {
                TestMenu();
            }
            else if(input=="0") {
                cout<<"��лʹ��"<<endl;
                system("pause");
            }
            else {
                cout<<"����������������룺"<<endl;
                continue;
            }
            break;
        }
        if(input=="0") {
            break;
        }
    }
}

void Menu::InquiryLineMenu() {
    while(true) {
        system("cls");
        cout<<"��ǰλ�ڣ���ҳ��->��·��ѯ�˵�"<<endl;
        cout<<"��ͨ������������ѡ���ܣ�"<<endl;
        cout<<"1.��ʾĿǰ������·"<<endl;
        cout<<"2.��ѯĳ����·"<<endl;
        cout<<"0.������һ���˵�"<<endl;
        cout<<"����������ѡ��";
        string input;
        while(cin>>input) {
            if(input=="1") {
                ShowAllLines();
            }
            else if(input=="2") {
                /*InquiryLine();*/
                cout<<"��δ����"<<endl;
                system("pause");
            }
            else if(input=="0") {
                break;
            }
            else {
                cout<<"����������������룺"<<endl;
                continue;
            }
            break;
        }
        if(input=="0") {
            break;
        }
    }
}

void Menu::ShowAllLines() {
    system("cls");
    cout<<"��ǰλ�ڣ���ҳ��->��·��ѯ�˵�->��ʾ������·"<<endl;
    if(lines.empty())
        cout<<"������·��Ϣ"<<endl;
    else
        for(const auto & line : lines) {
            cout<<line.first<<"����"<<": "<<endl;
            for(const auto & station : line.second.getStations()) {
                if(station == line.second.getStations().back())
                    cout<<station<<' ';
                else
                    cout<<' '<<station<<' '<<"->";
            }
            cout<<endl;
        }
    system("pause");
}

void Menu::EditLineMenu() {
    while(true) {
        system("cls");
        cout<<"��ǰλ�ڣ���ҳ��->��·�༭�˵�"<<endl;
        cout<<"��ͨ������������ѡ���ܣ�"<<endl;
        cout<<"1.�����·"<<endl;
        cout<<"2.ɾ����·"<<endl;
        cout<<"3.�༭��·"<<endl;
        cout<<"0.������һ���˵�"<<endl;
        cout<<"����������ѡ��";
        string input;
        while(cin>>input) {
            if(input=="1") {
                AddLine();
            }
            else if(input=="2") {
                /*RemoveLine();*/
                cout<<"��δ����"<<endl;
                system("pause");
            }
            else if(input=="3") {
                /*EditLine();*/
                cout<<"��δ����"<<endl;
                system("pause");
            }
            else if(input=="0") {
                break;
            }
            else {
                cout<<"����������������룺"<<endl;
                continue;
            }
            break;
        }
        if(input=="0") {
            break;
        }
    }
}

void Menu::AddLine() {
    system("cls");
    cout<<"��ǰλ�ڣ���ҳ��->��·�༭�˵�->�����·"<<endl;
    vector<pair<string,Length>> stations;
    int lineNumber=0;
    cout<<"��������·��ţ�";
    string input;
    while(cin>>input) {
        try {
            lineNumber = stoi(input);
            break;
        }
        catch(...) {
            cout<<"����������������룺"<<endl;
            continue;
        }
    }
    cout<<"�Ƿ��������վ�����룿(����Ĭ�Ͼ���Ϊ1)(y/n)";
    string extra;
    while(cin>>extra) {
        if(extra=="y") {
            cout<<"������վ�����룬�����ʽΪ��վ����1 ����1 վ����2 ����2 վ����3 ����3 ..."<<endl;
            cout<<"վ����֮���ÿո������վ�������ܰ����ո񣬾���Ϊ������"<<endl;
            cout<<"����Ϊ��վ�㵽��һ��վ��ľ��룬���һ����������0����"<<endl;
            cout<<"����0��������"<<endl;
            cout<<"�����룺";
            string station;
            while(cin>>station) {
                if(station=="0") {
                    break;
                }
                string length;
                while(cin>>length) {
                    if(length=="0") {
                        stations.emplace_back(station,0);
                        break;
                    }
                    try {
                        Length len = stoi(length);
                        stations.emplace_back(station,len);
                        break;
                    }
                    catch(...) {
                        cout<<"����������������룺"<<endl;
                        continue;
                    }
                }
                if(length == "0")
                    break;
            }
            break;
        }
        else if(extra=="n") {
            cout<<"������վ����Ϣ�������ʽΪ��վ����1 վ����2 վ����3 ..."<<endl;
            cout<<"վ����֮���ÿո������վ�������ܰ����ո�"<<endl;
            cout<<"����0��������"<<endl;
            cout<<"�����룺";
            string station;
            while(cin>>station) {
                if(station=="0") {
                    stations[stations.size()-1].second = 0;
                    break;
                }
                stations.emplace_back(station,1);
            }
            break;
        }
        else {
            cout<<"����������������룺"<<endl;
            continue;
        }
    }
    Line line(lineNumber,stations);
    lines[lineNumber] = line;
    cout<<"��ӳɹ�"<<endl;
    system("pause");
}

void Menu::FileMenu() {
    while(true) {
        system("cls");
        cout<<"��ǰλ�ڣ���ҳ��->�ļ������˵�"<<endl;
        cout<<"��ͨ������������ѡ���ܣ�"<<endl;
        cout<<"����λ�ڳ���Ŀ¼�µ�data�ļ�����"<<endl;
        cout<<"1.���浱ǰ����"<<endl;
        cout<<"2.��ȡ�浵����"<<endl;
        cout<<"0.������һ���˵�"<<endl;
        cout<<"����������ѡ��";
        string input;
        while(cin>>input) {
            if(input=="1") {
                SaveLines();
            }
            else if(input=="2") {
                ReadLines();
            }
            else if(input=="0") {
                break;
            }
            else {
                cout<<"����������������룺"<<endl;
                continue;
            }
            break;
        }
        if(input=="0") {
            break;
        }
    }
}

void Menu::SaveLines() {
    if(!FileIO::SaveMain(lines)) {
        cout<<"����ʧ��"<<endl;
        cout<<"����ԭ�򣺴���/���ļ�ʧ��"<<endl;
    }
    else cout<<"����ɱ���"<<endl;
    system("pause");
}

void Menu::ReadLines() {
    if(!FileIO::LoadMain(lines)) {
        cout<<"��ȡʧ��"<<endl;
        cout<<"����ԭ���ļ������ڻ��ļ���ʽ����"<<endl;
    }
    else cout<<"����ɶ�ȡ"<<endl;
    system("pause");
}

void Menu::TestMenu() {
    while(true) {
        system("cls");
        cout<<"��ǰλ�ڣ���ҳ��->�����߲��Բ˵�"<<endl;
        cout<<"��ͨ������������ѡ���ܣ�"<<endl;
        cout<<"0.������һ���˵�"<<endl;
        cout<<"����������ѡ��";
        string input;
        while(cin>>input) {
            if(input=="0") {
                break;
            }
            else {
                cout<<"����������������룺"<<endl;
                continue;
            }
            break;
        }
        if(input=="0") {
            break;
        }
    }
}
