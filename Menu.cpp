//
// Created by LanCher on 24-6-29.
//

#include "Menu.h"


void Menu::PrintTextWithColor(const string& text, int color,bool if_endl = true) {
    if(settings[5]) {
        //���������ɫ���
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, color);//������ɫ
        cout<<text;
        SetConsoleTextAttribute(hConsole, 7);//�ָ�Ĭ����ɫ
    }
    else {
        cout<<text;
    }
    if(if_endl)
        cout<<endl;
}

void Menu::MainMenu() {
    if(FileIO::GETSET0()) {
        if(!FileIO::LoadMain("lines.txt",lines,blockedStations,settings,TS)) {
            PrintTextWithColor("�Զ���ȡ�浵ʧ��",4);
            system("pause");
        }
    }
    //���Ĵ��ڱ���Ϊ
    SetConsoleTitle("�Ϻ�������·��ѯϵͳ");
    while(true) {
        system("cls");
        PrintTextWithColor("��ӭʹ���Ϻ�������·��ѯϵͳ",2);
        PrintTextWithColor("   ��ǰ�汾��2024.7.2",1);
        cout<<"�����ڴ洢��·����Ϊ��"<<lines.size()<<endl;
        cout<<"��ͨ������������ѡ���ܣ�"<<endl;
        cout<<"1.��·��ѯ\t- ��ȡ������·����Ϣ"<<endl;
        cout<<"2.��·�༭\t- �༭������·����Ϣ"<<endl;
        cout<<"3.·�߲�ѯ\t- ��ѯվ���ĳ�����·  "<<endl;
        cout<<"4.����/��ȡ\t- ������ȡ������·��Ϣ"<<endl;
        cout<<"5.����\t\t- ���ó����һЩ����"<<endl;
        /*cout<<"99.�����߲��Բ˵�"<<endl;*/
        PrintTextWithColor("0.�˳�",4);
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
                InquiryRouteMenu();
            }
            else if(input=="4") {
                FileMenu();
            }
            else if(input=="5") {
                SettingMenu();
            }
            else if(input=="99") {
                TestMenu();
            }
            else if(input=="0") {
                PrintTextWithColor("ȷ��Ҫ�˳���(y/n)",4);
                string confirm;
                while(cin>>confirm) {
                    if(confirm=="y") {
                        cout<<"��лʹ��"<<endl;
                        if(settings[1]) {
                            if(!FileIO::SaveMain(lines,blockedStations,settings,TS)) {
                                PrintTextWithColor("�Զ�����浵ʧ�ܣ�",4);
                                PrintTextWithColor("���ڷ������˵�",4);
                                system("pause");
                                input="1";//���½������˵�
                                break;
                            }
                            cout<<"���Զ�����浵"<<endl;
                        }
                        Sleep(2000);
                        return;
                    }
                    if(confirm=="n") {
                        input = "1";
                        break;
                    }
                    PrintTextWithColor("����������������룺",4);
                }
            }
            else {
                PrintTextWithColor("����������������룺",4);
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
        PrintTextWithColor("��ǰλ�ڣ���ҳ��->��·��ѯ�˵�",2);
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
                InquiryLine();
            }
            else if(input=="0") {
                break;
            }
            else {
                PrintTextWithColor("����������������룺",4);
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
    PrintTextWithColor("��ǰλ�ڣ���ҳ��->��·��ѯ�˵�->��ʾ������·",2);
    if(lines.empty())
        cout<<"������·��Ϣ"<<endl;
    else
        for(const auto & line : lines) {
            PrintTextWithColor(to_string(line.first)+"����",6);
            for(const auto & station : line.second.getStationsWithLength()) {
                cout<<station.first;
                if(settings[3]&&blockedStations.find(station.first)!=blockedStations.end())
                    PrintTextWithColor("(�ѷ�գ�",4,false);
                if(settings[4]&&TS.hasTransfer({line.first,station.first})) {
                    PrintTextWithColor("( �ɻ�������" , 9 , false);
                    for(const auto & transfer : TS.getTransfers({line.first,station.first})) {
                        cout<<transfer.first.first<<"����"<<transfer.first.second<<" ";
                    }
                    PrintTextWithColor(")" , 9 , false);
                }
                if(station!=line.second.getStationsWithLength().back())
                    if(settings[2])
                        PrintTextWithColor("->"+to_string(station.second)+"->",3,false);
                    else
                        PrintTextWithColor("->",3,false);
            }
            cout<<endl;
        }
    system("pause");
}

void Menu::InquiryLine() {
    system("cls");
    PrintTextWithColor("��ǰλ�ڣ���ҳ��->��·��ѯ�˵�->��ѯĳ����·",2);
    while(true) {
        cout<<"������Ҫ��ѯ����·���(����0��������һ��)��";
        string input;
        while(cin>>input) {
            int lineNumber;
            try {
                lineNumber = stoi(input);
            }
            catch(...) {
                PrintTextWithColor("����������������룺",4);
                continue;
            }
            if(lineNumber==0)
                break;
            if(lines.find(lineNumber) == lines.end()) {
                PrintTextWithColor("δ�ҵ�����·�����������룺",4);
                continue;
            }
            PrintTextWithColor(to_string(lineNumber)+"����",6);
            for(const auto & station : lines[lineNumber].getStationsWithLength()) {
                cout<<station.first;
                if(settings[3]&&blockedStations.find(station.first)!=blockedStations.end())
                    PrintTextWithColor("(�ѷ�գ�",4,false);
                if(settings[4]&&TS.hasTransfer({lineNumber,station.first})) {
                    PrintTextWithColor("( �ɻ�������" , 9 , false);
                    for(const auto & transfer : TS.getTransfers({lineNumber,station.first})) {
                        cout<<transfer.first.first<<"����"<<transfer.first.second<<" ";
                    }
                    PrintTextWithColor(")" , 9 , false);
                }
                if(station!=lines[lineNumber].getStationsWithLength().back())
                    if(settings[2])
                        PrintTextWithColor("->"+to_string(station.second)+"->",3,false);
                    else
                        PrintTextWithColor("->",3,false);
            }
            cout<<endl;
            break;
        }
        if(input=="0")
            break;
    }
}

void Menu::EditLineMenu() {
    while(true) {
        system("cls");
        PrintTextWithColor("��ǰλ�ڣ���ҳ��->��·�༭�˵�",2);
        cout<<"��ͨ������������ѡ���ܣ�"<<endl;
        cout<<"1.�����·"<<endl;
        cout<<"2.ɾ����·"<<endl;
        cout<<"3.�༭��·"<<endl;
        cout<<"4.����վ��˵�"<<endl;
        cout<<"5.������Ϣ�˵�"<<endl;
        cout<<"0.������һ���˵�"<<endl;
        cout<<"����������ѡ��";
        string input;
        while(cin>>input) {
            if(input=="1") {
                AddLine();
            }
            else if(input=="2") {
                RemoveLine();
            }
            else if(input=="3") {
                EditLine();
            }
            else if(input=="4") {
                BlockStationMenu();
            }
            else if(input=="5") {
                TransferMenu();
            }
            else if(input=="0") {
                break;
            }
            else {
                PrintTextWithColor("����������������룺",4);
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
    PrintTextWithColor("��ǰλ�ڣ���ҳ��->��·�༭�˵�->�����·",2);
    vector<pair<string,Length>> stations;
    int lineNumber=0;
    cout<<"��������·���(����0ȡ��������·)��";
    string input;
    while(cin>>input) {
        try {
            lineNumber = stoi(input);
            if(lines.find(lineNumber)!=lines.end()) {
                cout<<"����·�Ѵ��ڣ����������룺"<<endl;
                continue;
            }
            break;
        }
        catch(...) {
            PrintTextWithColor("����������������룺",4);
            continue;
        }
    }
    if(lineNumber==0) {
        return;
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
                        PrintTextWithColor("����������������룺",4);
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
                    if(stations.empty()) {
                        cout<<"���ʧ��"<<endl;
                        cout<<"����������һ��վ��"<<endl;
                        system("pause");
                        return;
                    }
                    stations[stations.size()-1].second = 0;
                    break;
                }
                stations.emplace_back(station,1);
            }
            break;
        }
        else {
            PrintTextWithColor("����������������룺",4);
            continue;
        }
    }
    Line line(lineNumber,stations);
    lines[lineNumber] = line;
    cout<<"��ӳɹ�"<<endl;
    system("pause");
}

void Menu::RemoveLine() {
    system("cls");
    PrintTextWithColor("��ǰλ�ڣ���ҳ��->��·�༭�˵�->ɾ����·",2);
    while(true) {
        cout<<"������Ҫɾ������·���(����0��������һ��)��";
        string input;
        while(cin>>input) {
            int lineNumber;
            try {
                lineNumber = stoi(input);
            }
            catch(...) {
                PrintTextWithColor("����������������룺",4);
                continue;
            }
            if(lineNumber==0)
                break;
            if(lines.find(lineNumber) == lines.end()) {
                PrintTextWithColor("δ�ҵ�����·�����������룺",4);
                continue;
            }
            cout<<"����ɾ��"<<lineNumber<<"���ߵ���Ϣ"<<endl;
            cout<<"�Ƿ�ȷ��ɾ������·��(y/n)";
            string confirm;
            while(cin>>confirm) {
                if(confirm=="y") {
                    lines.erase(lineNumber);
                    cout<<"ɾ���ɹ�"<<endl;
                    break;
                }
                if(confirm=="n")
                    break;
                PrintTextWithColor("����������������룺",4);
            }
            break;
        }
        if(input=="0")
            break;
    }
}

void Menu::EditLine() {
    while(true) {
        system("cls");
        PrintTextWithColor("��ǰλ�ڣ���ҳ��->��·�༭�˵�->�༭��·",2);
        cout<<"������Ҫ�༭����·���(����0��������һ��)��";
        string input;
        while(cin>>input) {
            int lineNumber;
            try {
                lineNumber = stoi(input);
            }
            catch(...) {
                PrintTextWithColor("����������������룺",4);
                continue;
            }
            if(lineNumber==0)
                break;
            if(lines.find(lineNumber) == lines.end()) {
                PrintTextWithColor("δ�ҵ�����·�����������룺",4);
                continue;
            }
            cout<<"�����༭"<<lineNumber<<"���ߵ���Ϣ"<<endl;
            cout<<"��ͨ������������ѡ���ܣ�"<<endl;
            cout<<"1.���վ��"<<endl;
            cout<<"2.ɾ��վ��"<<endl;
            cout<<"3.�޸�վ�����"<<endl;
            cout<<"4.�޸�վ������"<<endl;
            cout<<"5.������·����"<<endl;
            cout<<"6.������·����"<<endl;
            cout<<"0.������һ���˵�"<<endl;
            cout<<"����������ѡ��";
            string input2;
            while(cin>>input2) {
                if(input2=="1") {
                    AddStation(lineNumber);
                }
                else if(input2=="2") {
                    RemoveStation(lineNumber);
                }
                else if(input2=="3") {
                    EditStationDistance(lineNumber);
                }
                else if(input2=="4") {
                    EditStationName(lineNumber);
                }
                else if(input2=="5") {
                    ExtendLine(lineNumber);
                }
                else if(input2=="6") {
                    ShortenLine(lineNumber);
                }
                else if(input2=="0") {
                    break;
                }
                else {
                    PrintTextWithColor("����������������룺",4);
                    continue;
                }
                break;
            }
            system("pause");
            break;
        }
        if(input=="0")
            break;
    }
}

void Menu::AddStation(int line_number) {
    cout<<"������Ҫ��ӵ�վ������ԭվ�������(����0��������һ��������-1��ӵ���β)"<<endl;
    cout<<"���磺��Aվ��Bվ֮�����Cվ������B"<<endl;
    string pos;
    while(cin>>pos) {
        if(pos=="0")
            break;
        if(pos!="-1"&&!lines[line_number].hasStation(pos)) {
            cout<<"δ�ҵ���վ�㣬���������룺"<<endl;
            continue;
        }
        cout<<"������Ҫ��ӵ�վ�����ƣ�";
        string station;
        while(cin>>station) {
            if(lines[line_number].hasStation(station)) {
                cout<<"��վ���Ѵ��ڣ����������룺"<<endl;
                continue;
            }
            break;
        }
        if(pos=="-1") {
            Length frontLength = 1;
            cout<<"��������վ����ǰһ��վ��ľ��룺";
            string input;
            while(cin>>input) {
                try {
                    frontLength = stoi(input);
                    break;
                }
                catch(...) {
                    PrintTextWithColor("����������������룺",4);
                    continue;
                }
            }
            if(!lines[line_number].addStation_back(station,frontLength)) {
                cout<<"���ʧ��"<<endl;
            }
            else cout<<"��ӳɹ�"<<endl;
        }
        else {
            Length frontLength = 1;
            Length backLength = 1;
            if(pos!=lines[line_number].getFirstStation()->first) {
                cout<<"��������վ����ǰһ��վ��ľ��룺";
                string input;
                while(cin>>input) {
                    try {
                        frontLength = stoi(input);
                        break;
                    }
                    catch(...) {
                        PrintTextWithColor("����������������룺",4);
                        continue;
                    }
                }
            }
            cout<<"��������վ�����һ��վ��ľ��룺";
            string input;
            while(cin>>input) {
                try {
                    backLength = stoi(input);
                    break;
                }
                catch(...) {
                    PrintTextWithColor("����������������룺",4);
                    continue;
                }
            }
            if(!lines[line_number].addStation(station,pos,frontLength,backLength)) {
                cout<<"���ʧ��"<<endl;
            }
            else cout<<"��ӳɹ�"<<endl;
        }
        break;
    }
}

void Menu::RemoveStation(int line_number) {
    cout<<"������Ҫɾ����վ������(����0��������һ��)��";
    string station;
    while(cin>>station) {
        if(station=="0")
            break;
        if(!lines[line_number].hasStation(station)) {
            cout<<"δ�ҵ���վ�㣬���������룺"<<endl;
            continue;
        }
        cout<<"����ɾ��"<<station<<"վ�����Ϣ"<<endl;
        cout<<"�Ƿ�ȷ��ɾ����վ�㣿(y/n)";
        string confirm;
        while(cin>>confirm) {
            if(confirm=="y") {
                if(!lines[line_number].removeStation(station)) {
                    cout<<"ɾ��ʧ��"<<endl;
                }
                else cout<<"ɾ���ɹ�"<<endl;
                break;
            }
            if(confirm=="n")
                break;
            PrintTextWithColor("����������������룺",4);
        }
        break;
    }
}

void Menu::EditStationDistance(int line_number) {
    cout<<"������Ҫ�༭��վ������(����0��������һ�����༭�ľ���Ϊ��վ�������һ��վ��ľ���)��";
    string station;
    while(cin>>station) {
        if(station=="0")
            break;
        if(!lines[line_number].hasStation(station)) {
            cout<<"δ�ҵ���վ�㣬���������룺"<<endl;
            continue;
        }
        if(lines[line_number].isLastStation(lines[line_number].getStationIndex(station))) {
            cout<<"��վ��Ϊ���һ��վ�㣬�޷��༭����"<<endl;
            break;
        }
        cout<<"�������µ�վ�����룺";
        string input;
        while(cin>>input) {
            try {
                Length len = stoi(input);
                lines[line_number].getStationIndex(station)->second = len;
                break;
            }
            catch(...) {
                PrintTextWithColor("����������������룺",4);
                continue;
            }
        }
        cout<<"�޸ĳɹ�"<<endl;
        break;
    }
}

void Menu::EditStationName(int line_number) {
    cout<<"������Ҫ�༭��վ������(����0��������һ��)��";
    string station;
    while(cin>>station) {
        if(station=="0")
            break;
        if(!lines[line_number].hasStation(station)) {
            cout<<"δ�ҵ���վ�㣬���������룺"<<endl;
            continue;
        }
        cout<<"�������µ�վ�����ƣ�";
        string newStation;
        while(cin>>newStation) {
            if(lines[line_number].hasStation(newStation)) {
                cout<<"��վ���Ѵ��ڣ����������룺"<<endl;
                continue;
            }
            break;
        }
        cout<<"������"<<station<<"վ���޸�Ϊ"<<newStation<<"վ��"<<endl;
        cout<<"�Ƿ�ȷ���޸ģ�(y/n)";
        string confirm;
        while(cin>>confirm) {
            if(confirm=="y") {
                if(lines[line_number].changeStationName(station,newStation))
                    cout<<"�޸ĳɹ�"<<endl;
                else
                    cout<<"�޸�ʧ��"<<endl;
                break;
            }
            if(confirm=="n")
                break;
            PrintTextWithColor("����������������룺",4);
        }
        break;
    }
}

void Menu::ExtendLine(int line_number) {
    vector<pair<string,Length>> stations;
    Length frontlength = 1;
    cout<<"�������ӳ���·��ԭ��·���һ��վ��ľ��룺";
    string input;
    while(cin>>input) {
        try {
            frontlength = stoi(input);
            break;
        }
        catch(...) {
            PrintTextWithColor("����������������룺",4);
            continue;
        }
    }
    cout<<"�Ƿ�����վ�����룿(����Ĭ�Ͼ���Ϊ1)(y/n)";
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
                if(lines[line_number].hasStation(station)) {
                    cout<<"��վ���Ѵ���"<<endl;
                    continue;
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
                        PrintTextWithColor("����������������룺",4);
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
                    if(stations.empty()) {
                        cout<<"���ʧ��"<<endl;
                        cout<<"����������һ��վ��"<<endl;
                        system("pause");
                        return;
                    }
                    stations[stations.size()-1].second = 0;
                    break;
                }
                if(lines[line_number].hasStation(station)) {
                    cout<<"��վ���Ѵ���"<<endl;
                    continue;
                }
                stations.emplace_back(station,1);
            }
            break;
        }
        else {
            PrintTextWithColor("����������������룺",4);
            continue;
        }
    }
    lines[line_number].extendLine(stations,frontlength);
    cout<<"�ӳ����"<<endl;
}

void Menu::ShortenLine(int line_number) {
    cout<<"������Ҫ��β�����̵�վ������:";
    string input;
    while(cin>>input) {
        int num;
        try {
            num = stoi(input);
        }
        catch(...) {
            PrintTextWithColor("����������������룺",4);
            continue;
        }
        if(num<=0) {
            PrintTextWithColor("����������������룺",4);
            continue;
        }
        if(num>lines[line_number].getStations().size()) {
            cout<<"�������վ�㳬������վ����������������룺"<<endl;
            continue;
        }
        cout<<"����ɾ��"<<num<<"��վ��"<<endl;
        cout<<"�Ƿ�ȷ��ɾ����(y/n)";
        string confirm;
        while(cin>>confirm) {
            if(confirm=="y") {
                lines[line_number].shortenLine(num);
                cout<<"�������"<<endl;
                break;
            }
            if(confirm=="n")
                break;
            PrintTextWithColor("����������������룺",4);
        }
        break;
    }
}

void Menu::BlockStationMenu() {
    while(true) {
        system("cls");
        PrintTextWithColor("��ǰλ�ڣ���ҳ��->��·�༭�˵�->����վ��",2);
        cout<<"��ͨ������������ѡ���ܣ�"<<endl;
        cout<<"1.��ʾĿǰ���б���յ�վ��"<<endl;
        cout<<"2.����ָ��վ��"<<endl;
        cout<<"3.����ָ�����������վ��"<<endl;
        cout<<"4.���վ��"<<endl;
        cout<<"5.������������վ��"<<endl;
        cout<<"0.������һ���˵�"<<endl;
        cout<<"����������ѡ��";
        string input;
        while(cin>>input) {
            if(input=="1") {
                ShowBlockedStations();
            }
            else if(input=="2") {
                BlockStation();
            }
            else if(input=="3") {
                BlockStationInterval();
            }
            else if(input=="4") {
                UnblockStation();
            }
            else if(input=="5") {
                UnblockStationInterval();
            }
            else if(input=="0") {
                break;
            }
            else {
                PrintTextWithColor("����������������룺",4);
                continue;
            }
            break;
        }
        if(input=="0") {
            break;
        }
        system("pause");
    }
}

void Menu::ShowBlockedStations() {
    if(blockedStations.empty()) {
        cout<<"���ޱ���յ�վ��"<<endl;
    }
    else {
        cout<<"Ŀǰ�ѱ���յ�վ���У�"<<endl;
        for(const auto & station : blockedStations) {
            PrintTextWithColor(station,4);
        }
    };
}

void Menu::BlockStation() {
    cout<<"������Ҫ��յ�վ������(����0��������һ��)��";
    string station;
    while(cin>>station) {
        if(station=="0")
            break;
        if(blockedStations.find(station)!=blockedStations.end()) {
            cout<<"��վ���ѱ���գ����������룺"<<endl;
            continue;
        }
        cout<<"�������"<<station<<"վ��"<<endl;
        cout<<"�Ƿ�ȷ�Ϸ�ո�վ�㣿(y/n)";
        string confirm;
        while(cin>>confirm) {
            if(confirm=="y") {
                blockedStations.insert(station);
                cout<<"��ճɹ�"<<endl;
                break;
            }
            if(confirm=="n")
                break;
            PrintTextWithColor("����������������룺",4);
        }
        break;
    }
}

void Menu::BlockStationInterval() {
    cout<<"������Ҫ��յ�վ���������ڵ���·��(����0��������һ��)��";
    string input;
    while(cin>>input) {
        int lineNumber;
        try {
            lineNumber = stoi(input);
        }
        catch(...) {
            PrintTextWithColor("����������������룺",4);
            continue;
        }
        if(lineNumber==0)
            break;
        if(lines.find(lineNumber)==lines.end()) {
            PrintTextWithColor("δ�ҵ�����·�����������룺",4);
            continue;
        }
        cout<<"������Ҫ��յ�վ���������ʼվ�����ƣ�";
        string start;
        while(cin>>start) {
            if(!lines[lineNumber].hasStation(start)) {
                cout<<"δ�ҵ���վ�㣬���������룺"<<endl;
                continue;
            }
            cout<<"������Ҫ��յ�վ��������յ�վ�����ƣ�";
            string end;
            while(cin>>end) {
                if(!lines[lineNumber].hasStation(end)) {
                    cout<<"δ�ҵ���վ�㣬���������룺"<<endl;
                    continue;
                }
                if(lines[lineNumber].getStationIndexNum(start)>lines[lineNumber].getStationIndexNum(end)) {
                    PrintTextWithColor("����������������룺",4);
                    end = "0";
                    break;
                }
                cout<<"�������"<<lineNumber<<"���ߵ�"<<start<<"վ�㵽"<<end<<"վ�������"<<endl;
                cout<<"�Ƿ�ȷ�Ϸ�ո����䣿(y/n)";
                string confirm;
                while(cin>>confirm) {
                    if(confirm=="y") {
                        for(auto it = lines[lineNumber].getStationIndex(start);it!=lines[lineNumber].getStationIndex(end);++it) {
                            blockedStations.insert(it->first);
                        }
                        blockedStations.insert(lines[lineNumber].getStationIndex(end)->first);
                        cout<<"��ճɹ�"<<endl;
                        break;
                    }
                    if(confirm=="n")
                        break;
                    PrintTextWithColor("����������������룺",4);
                }
                break;
            }
            if(end == "0")
                continue;
            break;
        }
        break;
    }
}

void Menu::UnblockStation() {
    cout<<"������Ҫ����վ������(����0��������һ��)��";
    string station;
    while(cin>>station) {
        if(station=="0")
            break;
        if(blockedStations.find(station)==blockedStations.end()) {
            cout<<"��վ��δ����գ����������룺"<<endl;
            continue;
        }
        cout<<"�������"<<station<<"վ��"<<endl;
        cout<<"�Ƿ�ȷ�Ͻ���վ�㣿(y/n)";
        string confirm;
        while(cin>>confirm) {
            if(confirm=="y") {
                blockedStations.erase(station);
                cout<<"���ɹ�"<<endl;
                break;
            }
            if(confirm=="n")
                break;
            PrintTextWithColor("����������������룺",4);
        }
        break;
    }
}

void Menu::UnblockStationInterval() {
    cout<<"������Ҫ�ָ���վ���������ڵ���·��(����0��������һ��)��";
    string input;
    while(cin>>input) {
        int lineNumber;
        try {
            lineNumber = stoi(input);
        }
        catch(...) {
            PrintTextWithColor("����������������룺",4);
            continue;
        }
        if(lineNumber==0)
            break;
        if(lines.find(lineNumber)==lines.end()) {
            PrintTextWithColor("δ�ҵ�����·�����������룺",4);
            continue;
        }
        cout<<"������Ҫ�ָ���վ���������ʼվ�����ƣ�";
        string start;
        while(cin>>start) {
            if(!lines[lineNumber].hasStation(start)) {
                cout<<"δ�ҵ���վ�㣬���������룺"<<endl;
                continue;
            }
            cout<<"������Ҫ�ָ���վ��������յ�վ�����ƣ�";
            string end;
            while(cin>>end) {
                if(!lines[lineNumber].hasStation(end)) {
                    cout<<"δ�ҵ���վ�㣬���������룺"<<endl;
                    continue;
                }
                if(lines[lineNumber].getStationIndexNum(start)>lines[lineNumber].getStationIndexNum(end)) {
                    PrintTextWithColor("����������������룺",4);
                    end = "0";
                    break;
                }
                cout<<"�����ָ�"<<lineNumber<<"���ߵ�"<<start<<"վ�㵽"<<end<<"վ�������"<<endl;
                cout<<"�Ƿ�ȷ�ϻָ������䣿(y/n)";
                string confirm;
                while(cin>>confirm) {
                    if(confirm=="y") {
                        for(auto it = lines[lineNumber].getStationIndex(start);it!=lines[lineNumber].getStationIndex(end);++it) {
                            blockedStations.erase(it->first);
                        }
                        blockedStations.erase(lines[lineNumber].getStationIndex(end)->first);
                        cout<<"�ָ��ɹ�"<<endl;
                        break;
                    }
                    if(confirm=="n")
                        break;
                    PrintTextWithColor("����������������룺",4);
                }
                break;
            }
            if(end == "0")
                continue;
            break;
        }
        break;
    }
}

void Menu::TransferMenu() {
    while(true) {
        system("cls");
        PrintTextWithColor("��ǰλ�ڣ���ҳ��->��·�༭�˵�->������Ϣ�˵�",2);
        cout<<"��ͨ������������ѡ���ܣ�"<<endl;
        cout<<"1.��ʾĿǰ���л�����Ϣ"<<endl;
        cout<<"2.��ʾĳվ��Ļ�����Ϣ"<<endl;
        cout<<"3.��ӻ�����Ϣ"<<endl;
        cout<<"4.ɾ��������Ϣ"<<endl;
        cout<<"0.������һ���˵�"<<endl;
        cout<<"����������ѡ��";
        string input;
        while(cin>>input) {
            if(input=="1") {
                ShowAllTransfers();
            }
            else if(input=="2") {
                ShowStationTransfers();
            }
            else if(input=="3") {
                AddTransfer();
            }
            else if(input=="4") {
                RemoveTransfer();
            }
            else if(input=="0") {
                break;
            }
            else {
                PrintTextWithColor("����������������룺",4);
                continue;
            }
            break;
        }
        if(input=="0") {
            break;
        }
        system("pause");
    }
}

void Menu::ShowAllTransfers() {
    if(TS.getTransfers().empty()) {
        cout<<"���޻�����Ϣ"<<endl;
        return;
    }
    const auto & transfers = TS.getTransfers();
    for(const auto & transfer : transfers) {
        cout<<transfer.first.first<<"���ߵ�"<<transfer.first.second<<"վ����Ի���������վ�㣺"<<endl;
        for(const auto & station : transfer.second) {
            PrintTextWithColor("("+to_string(station.first.first)+"����) "+station.first.second+"վ�� ����Ϊ"+to_string(station.second),6);
            cout<<station.first.second<<"վ�� ����Ϊ"<<station.second<<endl;
        }
    }
}

void Menu::ShowStationTransfers() {
    cout<<"������Ҫ��ѯվ�����ڵ���·���(����0��������һ��)��";
    string input;
    while(cin>>input) {
        int lineNumber;
        try {
            lineNumber = stoi(input);
        }
        catch(...) {
            PrintTextWithColor("����������������룺",4);
            continue;
        }
        if(lineNumber==0)
            break;
        if(lines.find(lineNumber)==lines.end()) {
            PrintTextWithColor("δ�ҵ�����·�����������룺",4);
            continue;
        }
        cout<<"������Ҫ��ѯ��վ�����ƣ�";
        string station;
        while(cin>>station) {
            if(!lines[lineNumber].hasStation(station)) {
                cout<<"δ�ҵ���վ�㣬���������룺"<<endl;
                continue;
            }
            cout<<lineNumber<<"���ߵ�"<<station<<"վ����Ի���������վ�㣺"<<endl;
            for(const auto & transfer : TS.getTransfers({lineNumber,station})) {
                PrintTextWithColor("("+to_string(transfer.first.first)+"����) ",6);
                cout<<transfer.first.second<<"վ�� ����Ϊ"<<transfer.second<<endl;
            }
            break;
        }
        break;
    }
}

void Menu::AddTransfer() {
    cout<<"������Ҫ��ӻ�����Ϣ��վ�����ڵ���·���(����0��������һ��)��";
    string input;
    while(cin>>input) {
        int lineNumber;
        try {
            lineNumber = stoi(input);
        }
        catch(...) {
            PrintTextWithColor("����������������룺",4);
            continue;
        }
        if(lineNumber==0)
            break;
        if(lines.find(lineNumber)==lines.end()) {
            PrintTextWithColor("δ�ҵ�����·�����������룺",4);
            continue;
        }
        cout<<"������Ҫ��ӻ�����Ϣ��վ�����ƣ�";
        string station;
        while(cin>>station) {
            if(!lines[lineNumber].hasStation(station)) {
                cout<<"δ�ҵ���վ�㣬���������룺"<<endl;
                continue;
            }
            cout<<"������Ҫ����������·��ţ�";
            string input2;
            while(cin>>input2) {
                int lineNumber2;
                try {
                    lineNumber2 = stoi(input2);
                }
                catch(...) {
                    PrintTextWithColor("����������������룺",4);
                    continue;
                }
                if(lines.find(lineNumber2)==lines.end()) {
                    PrintTextWithColor("δ�ҵ�����·�����������룺",4);
                    continue;
                }
                cout<<"������Ҫ��������վ�����ƣ�";
                string station2;
                while(cin>>station2) {
                    if(!lines[lineNumber2].hasStation(station2)) {
                        cout<<"δ�ҵ���վ�㣬���������룺"<<endl;
                        continue;
                    }
                    cout<<"��������վ��֮��ľ��룺";
                    string input3;
                    while(cin>>input3) {
                        Length len;
                        try {
                            len = stoi(input3);
                        }
                        catch(...) {
                            PrintTextWithColor("����������������룺",4);
                            continue;
                        }
                        if(TS.addTransfer({lineNumber,station},{lineNumber2,station2},len)) {
                            cout<<"��ӳɹ�"<<endl;
                        }
                        else {
                            cout<<"���ʧ��"<<endl;
                            cout<<"����ԭ�򣺻�����Ϣ�Ѵ���/������·��ͬ"<<endl;
                        }
                        break;
                    }
                    break;
                }
                break;
            }
            break;
        }
        break;
    }
}

void Menu::RemoveTransfer() {
    cout<<"������Ҫɾ��������Ϣ��վ�����ڵ���·���(����0��������һ��)��";
    string input;
    while(cin>>input) {
        int lineNumber;
        try {
            lineNumber = stoi(input);
        }
        catch(...) {
            PrintTextWithColor("����������������룺",4);
            continue;
        }
        if(lineNumber==0)
            break;
        if(lines.find(lineNumber)==lines.end()) {
            PrintTextWithColor("δ�ҵ�����·�����������룺",4);
            continue;
        }
        cout<<"������Ҫɾ��������Ϣ��վ�����ƣ�";
        string station;
        while(cin>>station) {
            if(!lines[lineNumber].hasStation(station)) {
                cout<<"δ�ҵ���վ�㣬���������룺"<<endl;
                continue;
            }
            cout<<"������Ҫɾ��������Ϣ�Ļ�����·��ţ�";
            string input2;
            while(cin>>input2) {
                int lineNumber2;
                try {
                    lineNumber2 = stoi(input2);
                }
                catch(...) {
                    PrintTextWithColor("����������������룺",4);
                    continue;
                }
                if(lines.find(lineNumber2)==lines.end()) {
                    PrintTextWithColor("δ�ҵ�����·�����������룺",4);
                    continue;
                }
                cout<<"������Ҫɾ��������Ϣ�Ļ���վ�����ƣ�";
                string station2;
                while(cin>>station2) {
                    if(!lines[lineNumber2].hasStation(station2)) {
                        cout<<"δ�ҵ���վ�㣬���������룺"<<endl;
                        continue;
                    }
                    PrintTextWithColor("����ɾ��"+to_string(lineNumber)+"���ߵ�"+station+"վ�㵽"+to_string(lineNumber2)+"���ߵ�"+station2+"վ��Ļ�����Ϣ",4);
                    cout<<"�Ƿ�ȷ��ɾ����(y/n)";
                    string confirm;
                    while(cin>>confirm) {
                        if(confirm=="y") {
                            if(TS.removeTransfer({lineNumber,station},{lineNumber2,station2})) {
                                cout<<"ɾ���ɹ�"<<endl;
                            }
                            else {
                                cout<<"ɾ��ʧ��"<<endl;
                                cout<<"����ԭ�򣺻�����Ϣ������"<<endl;
                            }
                            break;
                        }
                        if(confirm=="n")
                            break;
                        PrintTextWithColor("����������������룺",4);
                    }
                    break;
                }
                break;
            }
            break;
        }
        break;
    }
}

void Menu::InquiryRouteMenu() {
    while(true) {
        system("cls");
        PrintTextWithColor("��ǰλ�ڣ���ҳ��->·�߲�ѯ�˵�",2);
        cout<<"��ͨ������������ѡ���ܣ�"<<endl;
        cout<<"1.��ѯ��վ��֮���";PrintTextWithColor("ʱ�����",6,false);cout<<"·��"<<endl;
        cout<<"2.��ѯ��վ��֮���";PrintTextWithColor("��������",6,false);cout<<"·��"<<endl;
        cout<<"0.������һ���˵�"<<endl;
        cout<<"����������ѡ��";
        string input;
        while(cin>>input) {
            if(input=="1") {
                InquiryShortestRoute();
            }
            else if(input=="2") {
                InquiryLeastTransferRoute();
            }
            else if(input=="0") {
                break;
            }
            else {
                PrintTextWithColor("����������������룺",4);
                continue;
            }
            break;
        }
        if(input=="0") {
            break;
        }
    }
}

void Menu::InquiryShortestRoute() {
    while(true) {
        system("cls");
        PrintTextWithColor("��ǰλ�ڣ���ҳ��->·�߲�ѯ�˵�->ʱ�����·�߲�ѯ",2);
        cout<<"��������ʼվ�����ڵ���·���(����0��������һ��)��";
        string input;
        while(cin>>input) {
            int lineNumber;
            try {
                lineNumber = stoi(input);
            }
            catch(...) {
                PrintTextWithColor("����������������룺",4);
                continue;
            }
            if(lineNumber==0)
                break;
            if(lines.find(lineNumber)==lines.end()) {
                PrintTextWithColor("δ�ҵ�����·�����������룺",4);
                continue;
            }
            cout<<"��������ʼվ�����ƣ�";
            string start;
            while(cin>>start) {
                if(!lines[lineNumber].hasStation(start)) {
                    PrintTextWithColor("δ�ҵ���վ�㣬���������룺",4);
                    continue;
                }
                cout<<"�������յ�վ�����ڵ���·��ţ�";
                string input2;
                while(cin>>input2) {
                    int lineNumber2;
                    try {
                        lineNumber2 = stoi(input2);
                    }
                    catch(...) {
                        PrintTextWithColor("����������������룺",4);
                        continue;
                    }
                    if(lines.find(lineNumber2)==lines.end()) {
                        PrintTextWithColor("δ�ҵ�����·�����������룺",4);
                        continue;
                    }
                    cout<<"�������յ�վ�����ƣ�";
                    string end;
                    while(cin>>end) {
                        if(!lines[lineNumber2].hasStation(end)) {
                            PrintTextWithColor("δ�ҵ���վ�㣬���������룺",4);
                            continue;
                        }
                        if(lineNumber==lineNumber2&&start==end) {
                            PrintTextWithColor("������յ���ͬ��������·�����Ѿ����յ��ˡ�",4);
                            system("pause");
                            break;
                        }
                        // vector<pair<·�߳���,vector<pair<��·����,<�ϳ�վ��,�³�վ��>>>>>
                        RouteResult result =GetRoute::InquiryShortestRoute({lineNumber,start},{lineNumber2,end},lines,blockedStations,TS);
                        system("cls");
                        if(result.empty()) {
                            PrintTextWithColor("δ�ҵ�����������·��",4);
                        }
                        else {
                            if(result.size()!=1) {
                                cout<<"�ҵ���"<<result.size()<<"������";PrintTextWithColor("ʱ�����",6,false);cout<<"��·��:"<<endl;
                            }
                            int i = 1;
                            for(const auto & route : result) {
                                if(result.size()!=1)
                                    PrintTextWithColor("·��"+to_string(i),9,false);
                                else
                                    PrintTextWithColor("��ѯ��·�ߣ�",9,false);
                                cout<<" ��ʱ��Ϊ";PrintTextWithColor(to_string(route.first),6,false);cout<<"����"<<endl;
                                for(const auto & line : route.second) {
                                    if(line.second.first==line.second.second)
                                        continue;
                                    cout<<"����";PrintTextWithColor(to_string(line.first)+"����",3,false);
                                    cout<<"�� "<<line.second.first<<" վ�ϳ� -> "<<line.second.second<<" վ�³�"<<endl;
                                }
                                i++;
                                if(i==4) {
                                    PrintTextWithColor("�����ʾ3��·��",4);
                                    break;
                                }
                            }
                        }
                        system("pause");
                        break;
                    }
                    break;
                }
                break;
            }
            break;
        }
        if(input=="0") {
            break;
        }
    }
}

void Menu::InquiryLeastTransferRoute() {
    while(true) {
        system("cls");
        PrintTextWithColor("��ǰλ�ڣ���ҳ��->·�߲�ѯ�˵�->��������·�߲�ѯ",2);
        cout<<"��������ʼվ�����ڵ���·���(����0��������һ��)��";
        string input;
        while(cin>>input) {
            int lineNumber;
            try {
                lineNumber = stoi(input);
            }
            catch(...) {
                PrintTextWithColor("����������������룺",4);
                continue;
            }
            if(lineNumber==0)
                break;
            if(lines.find(lineNumber)==lines.end()) {
                PrintTextWithColor("δ�ҵ�����·�����������룺",4);
                continue;
            }
            cout<<"��������ʼվ�����ƣ�";
            string start;
            while(cin>>start) {
                if(!lines[lineNumber].hasStation(start)) {
                    PrintTextWithColor("δ�ҵ���վ�㣬���������룺",4);
                    continue;
                }
                cout<<"�������յ�վ�����ڵ���·��ţ�";
                string input2;
                while(cin>>input2) {
                    int lineNumber2;
                    try {
                        lineNumber2 = stoi(input2);
                    }
                    catch(...) {
                        PrintTextWithColor("����������������룺",4);
                        continue;
                    }
                    if(lines.find(lineNumber2)==lines.end()) {
                        PrintTextWithColor("δ�ҵ�����·�����������룺",4);
                        continue;
                    }
                    cout<<"�������յ�վ�����ƣ�";
                    string end;
                    while(cin>>end) {
                        if(!lines[lineNumber2].hasStation(end)) {
                            PrintTextWithColor("δ�ҵ���վ�㣬���������룺",4);
                            continue;
                        }
                        if(lineNumber==lineNumber2&&start==end) {
                            PrintTextWithColor("������յ���ͬ��������·�����Ѿ����յ��ˡ�",4);
                            system("pause");
                            break;
                        }
                        // vector<pair<���˴���,vector<pair<��·����,<�ϳ�վ��,�³�վ��>>>>>
                        RouteResult result = GetRoute::InquiryLeastTransferRoute({lineNumber,start},{lineNumber2,end},lines,blockedStations,TS);
                        system("cls");
                        if(result.empty()) {
                            PrintTextWithColor("δ�ҵ�����������·��",4);
                        }
                        else {
                            if(result.size()!=1) {
                                cout<<"�ҵ���"<<result.size()<<"������";PrintTextWithColor("��������",6,false);cout<<"��·��:"<<endl;
                            }
                            int i = 1;
                            for(const auto & route : result) {
                                if(result.size()!=1)
                                    PrintTextWithColor("·��"+to_string(i),9,false);
                                else
                                    PrintTextWithColor("��ѯ��·�ߣ�",9,false);
                                cout<<" �ܻ��˴���Ϊ";PrintTextWithColor(to_string(route.first),6,false);cout<<"��"<<endl;
                                for(const auto & line : route.second) {
                                    if(line.second.first==line.second.second)
                                        continue;
                                    cout<<"����";PrintTextWithColor(to_string(line.first)+"����",3,false);
                                    cout<<"�� "<<line.second.first<<" վ�ϳ� -> "<<line.second.second<<" վ�³�"<<endl;
                                }
                                i++;
                                if(i==4) {
                                    PrintTextWithColor("�����ʾ3��·��",4);
                                    break;
                                }
                            }
                        }
                        system("pause");
                        break;
                    }
                    break;
                }
                break;
            }
            break;
        }
        if(input=="0") {
            break;
        }
    }
}

void Menu::FileMenu() {
    while(true) {
        system("cls");
        PrintTextWithColor("��ǰλ�ڣ���ҳ��->�ļ������˵�",2);
        cout<<"��ͨ������������ѡ���ܣ�"<<endl;
        cout<<"����λ�ڳ���Ŀ¼�µ�line.txt��"<<endl;
        cout<<"1.���浱ǰ����"<<endl;
        cout<<"2.��ȡ�浵����"<<endl;
        cout<<"3.��ָ���ļ���ȡ����"<<endl;
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
            else if(input=="3") {
                cout<<"�������ļ�����";
                string filename;
                while(cin>>filename) {
                    //���ǰ�����˫���ţ���ɾ��
                    if(filename.front()=='\"'&&filename.back()=='\"') {
                        filename = filename.substr(1,filename.size()-2);
                    }
                    if(!FileIO::LoadMain(filename,lines,blockedStations,settings,TS)) {
                        PrintTextWithColor("��ȡʧ��",4);
                        cout<<"����ԭ���ļ������ڻ��ļ���ʽ����"<<endl;
                    }
                    else cout<<"����ɶ�ȡ"<<endl;
                    system("pause");
                    break;
                }
            }
            else if(input=="0") {
                break;
            }
            else {
                PrintTextWithColor("����������������룺",4);
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
    if(!FileIO::SaveMain(lines,blockedStations,settings,TS)) {
        PrintTextWithColor("����ʧ��",4);
        cout<<"����ԭ�򣺴���/���ļ�ʧ��"<<endl;
    }
    else cout<<"����ɱ���"<<endl;
    system("pause");
}

void Menu::ReadLines() {
    if(!FileIO::LoadMain("lines.txt",lines,blockedStations,settings,TS)) {
        PrintTextWithColor("��ȡʧ��",4);
        cout<<"����ԭ���ļ������ڻ��ļ���ʽ����"<<endl;
    }
    else cout<<"����ɶ�ȡ"<<endl;
    system("pause");
}


void Menu::SettingMenu() {
    //��һ��boolֵ��ʾ�Ƿ��ڳ�������ʱ�Զ���ȡ��·��Ϣ
    //�ڶ���boolֵ��ʾ�Ƿ��ڳ����˳�ʱ�Զ�������·��Ϣ
    //������boolֵ��ʾ�Ƿ�����ʾ·��ʱ��ʾվ������
    //���ĸ�boolֵ��ʾ�Ƿ�����ʾ·��ʱ��ʾվ���Ƿ񱻽���
    while(true) {
        system("cls");
        PrintTextWithColor("��ǰλ�ڣ���ҳ��->���ò˵�",2);
        cout<<"��ͨ�������������ı书�ܵ��Ƿ����ã�"<<endl;
        cout<<"1.��������ʱ�Զ���ȡ��·��Ϣ\t\t";PrintTextWithColor((settings[0]?"(��)":"(��)"),settings[0]?2:4);
        cout<<"2.�����˳�ʱ�Զ�������·��Ϣ\t\t";PrintTextWithColor((settings[1]?"(��)":"(��)"),settings[1]?2:4);
        cout<<"3.����ʾ·��ʱ��ʾվ������\t\t";PrintTextWithColor((settings[2]?"(��)":"(��)"),settings[2]?2:4);
        cout<<"4.����ʾ·��ʱ��ʾվ���Ƿ񱻽���\t";PrintTextWithColor((settings[3]?"(��)":"(��)"),settings[3]?2:4);
        cout<<"5.����ʾ·��ʱ��ʾվ�㻻����Ϣ\t\t";PrintTextWithColor((settings[4]?"(��)":"(��)"),settings[4]?2:4);
        cout<<"6.������ɫ���\t\t\t\t";PrintTextWithColor((settings[5]?"(��)":"(��)"),settings[5]?2:4);
        cout<<"0.������һ���˵�"<<endl;
        cout<<"����������ѡ��";
        string input;
        while(cin>>input) {
            if(input=="1") {
                settings[0] = !settings[0];
            }
            else if(input=="2") {
                settings[1] = !settings[1];
            }
            else if(input=="3") {
                settings[2] = !settings[2];
            }
            else if(input=="4") {
                settings[3] = !settings[3];
            }
            else if(input=="5") {
                settings[4] = !settings[4];
            }
            else if(input=="6") {
                settings[5] = !settings[5];
            }
            else if(input=="0") {
                break;
            }
            else {
                PrintTextWithColor("����������������룺",4);
                continue;
            }
            break;
        }
        if(input=="0") {
            break;
        }
    }
}

void Menu::TestMenu() {
    while(true) {
        system("cls");
        PrintTextWithColor("��ǰλ�ڣ���ҳ��->�����߲˵�",2);
        cout<<"��ͨ������������ѡ���ܣ�"<<endl;
        cout<<"1.�������뻻����Ϣ"<<endl;
        cout<<"2.�����������"<<endl;
        cout<<"0.������һ���˵�"<<endl;
        cout<<"����������ѡ��";
        string input;
        while(cin>>input) {
            if(input=="0") {
                break;
            }
            if(input=="1") {
                EnterTransferInformationInBatches();
            }
            else if(input=="2") {
                PrintTextWithColor("���������������",4);
                cout<<"�Ƿ�ȷ�������(y/n)";
                string confirm;
                while(cin>>confirm) {
                    if(confirm=="y") {
                        lines.clear();
                        blockedStations.clear();
                        settings = {false,false,true,true,true,true,true,true,true,true};
                        TS.clear();
                        cout<<"������"<<endl;
                        PrintTextWithColor("ע�⣺���Ĵ浵�ļ����ᱻɾ�����������ʱ�ָ����浵״̬",4);
                        system("pause");
                        break;
                    }
                    if(confirm=="n")
                        break;
                    PrintTextWithColor("����������������룺",4);
                }
            }
            else {
                PrintTextWithColor("����������������룺",4);
                continue;
            }
            break;
        }
        if(input=="0") {
            break;
        }
    }
}

void Menu::EnterTransferInformationInBatches() {
    cout<<"�����뻻����Ϣ�������ʽΪ��վ���� ��·������...0�����������룬ֱ������#����ȫ������"<<endl;
    string station;
    while(cin>>station) {
        if(station=="#") {
            break;
        }
        if(blockedStations.find(station)!=blockedStations.end()) {
            cout<<"��վ���ѱ����"<<endl;
            continue;
        }
        vector<int> targetLines;
        string input;
        while(cin>>input) {
            if(input=="0") {
                break;
            }
            try {
                int lineNumber = stoi(input);
                if(lines.find(lineNumber)==lines.end()) {
                    cout<<"δ�ҵ�����·�����������룺"<<endl;
                    continue;
                }
                targetLines.push_back(lineNumber);
            }
            catch(...) {
                cout<<"����������������룺"<<endl;
                continue;
            }
        }
        if(targetLines.empty()) {
            cout<<"����������һ����·��"<<endl;
            continue;
        }
        for(int i = 0;i<targetLines.size()-1;i++) {
            for(int j = i+1;j<targetLines.size();j++) {
                TS.addTransfer(pair<int,string>(targetLines[i],station),pair<int,string>(targetLines[j],station),1);
            }
        }//������·���������
    }
    cout<<"�������"<<endl;
    system("pause");
}
