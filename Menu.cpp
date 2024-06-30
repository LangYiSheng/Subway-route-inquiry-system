//
// Created by LanCher on 24-6-29.
//

#include "Menu.h"

void Menu::MainMenu() {
    if(FileIO::LoadMain(lines)) {
        cout<<"�Զ���ȡ�浵�ɹ�"<<endl;
        system("pause");
    }
    while(true) {
        system("cls");
        cout<<"��ӭʹ���Ϻ�������·��ѯϵͳ"<<endl;
        cout<<"�����ڴ洢��·����Ϊ��"<<lines.size()<<endl;
        cout<<"��ͨ������������ѡ���ܣ�"<<endl;
        cout<<"1.��·��ѯ-��ȡ������·����Ϣ"<<endl;
        cout<<"2.��·�༭-�༭������·����Ϣ"<<endl;
        cout<<"3.·�߲�ѯ-��ѯվ���ĳ�����·  "<<endl;
        cout<<"4.����/��ȡ-������ȡ������·��Ϣ"<<endl;
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
                InquiryLine();
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
                    cout<<' '<<station;
                else
                    cout<<' '<<station<<' '<<"->";
            }
            cout<<endl;
        }
    system("pause");
}

void Menu::InquiryLine() {
    system("cls");
    cout<<"��ǰλ�ڣ���ҳ��->��·��ѯ�˵�->��ѯĳ����·"<<endl;
    while(true) {
        cout<<"������Ҫ��ѯ����·���(����0��������һ��)��";
        string input;
        while(cin>>input) {
            int lineNumber;
            try {
                lineNumber = stoi(input);
            }
            catch(...) {
                cout<<"����������������룺"<<endl;
                continue;
            }
            if(lineNumber==0)
                break;
            if(lines.find(lineNumber) == lines.end()) {
                cout<<"δ�ҵ�����·�����������룺"<<endl;
                continue;
            }
            cout<<lineNumber<<"����"<<": "<<endl;
            for(const auto & station : lines[lineNumber].getStations()) {
                if(station == lines[lineNumber].getStations().back())
                    cout<<station<<' ';
                else
                    cout<<' '<<station<<' '<<"->";
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
                RemoveLine();
            }
            else if(input=="3") {
                EditLine();
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
            cout<<"����������������룺"<<endl;
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
            cout<<"����������������룺"<<endl;
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
    cout<<"��ǰλ�ڣ���ҳ��->��·�༭�˵�->ɾ����·"<<endl;
    while(true) {
        cout<<"������Ҫɾ������·���(����0��������һ��)��";
        string input;
        while(cin>>input) {
            int lineNumber;
            try {
                lineNumber = stoi(input);
            }
            catch(...) {
                cout<<"����������������룺"<<endl;
                continue;
            }
            if(lineNumber==0)
                break;
            if(lines.find(lineNumber) == lines.end()) {
                cout<<"δ�ҵ�����·�����������룺"<<endl;
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
                cout<<"����������������룺"<<endl;
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
        cout<<"��ǰλ�ڣ���ҳ��->��·�༭�˵�->�༭��·"<<endl;
        cout<<"������Ҫ�༭����·���(����0��������һ��)��";
        string input;
        while(cin>>input) {
            int lineNumber;
            try {
                lineNumber = stoi(input);
            }
            catch(...) {
                cout<<"����������������룺"<<endl;
                continue;
            }
            if(lineNumber==0)
                break;
            if(lines.find(lineNumber) == lines.end()) {
                cout<<"δ�ҵ�����·�����������룺"<<endl;
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
            cout<<"7.�����·����"<<endl;
            cout<<"8.�ָ���·����"<<endl;
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
                else if(input2=="7") {
                    /*CloseLine(lineNumber);*/
                    cout<<"��δ����"<<endl;

                }
                else if(input2=="8") {
                    /*OpenLine(lineNumber);*/
                    cout<<"��δ����"<<endl;
                }
                else if(input2=="0") {
                    break;
                }
                else {
                    cout<<"����������������룺"<<endl;
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
                    cout<<"����������������룺"<<endl;
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
                        cout<<"����������������룺"<<endl;
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
                    cout<<"����������������룺"<<endl;
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
            cout<<"����������������룺"<<endl;
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
                cout<<"����������������룺"<<endl;
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
            cout<<"����������������룺"<<endl;
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
            cout<<"����������������룺"<<endl;
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
            cout<<"����������������룺"<<endl;
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
            cout<<"����������������룺"<<endl;
            continue;
        }
        if(num<=0) {
            cout<<"����������������룺"<<endl;
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
            cout<<"����������������룺"<<endl;
        }
        break;
    }
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
