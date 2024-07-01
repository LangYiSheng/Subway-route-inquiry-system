//
// Created by LanCher on 24-6-29.
//

#include "Menu.h"

void Menu::MainMenu() {
    if(FileIO::GETSET0()) {
        if(!FileIO::LoadMain(lines,blockedStations,settings,TS)) {
            cout<<"�Զ���ȡ�浵ʧ��"<<endl;
            system("pause");
        }
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
        cout<<"5.����-���ó����һЩ����"<<endl;
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
            else if(input=="5") {
                SettingMenu();
            }
            else if(input=="99") {
                TestMenu();
            }
            else if(input=="0") {
                cout<<"��лʹ��"<<endl;
                if(settings[1]) {
                    if(!FileIO::SaveMain(lines,blockedStations,settings,TS)) {
                        cout<<"�Զ�����浵ʧ��"<<endl;
                        system("pause");
                    }
                    else {
                        cout<<"���Զ�����浵"<<endl;
                    }
                }
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
            for(const auto & station : line.second.getStationsWithLength()) {
                cout<<station.first;
                if(settings[3]&&blockedStations.find(station.first)!=blockedStations.end())
                    cout<<"(�ѷ��)";
                if(settings[4]&&TS.hasTransfer({line.first,station.first})) {
                    cout<<"( �ɻ�������";
                    for(const auto & transfer : TS.getTransfers({line.first,station.first})) {
                        cout<<transfer.first.first<<"����"<<transfer.first.second<<" ";
                    }
                    cout<<")";
                }
                if(station!=line.second.getStationsWithLength().back())
                    if(settings[2])
                        cout<<"->"<<station.second<<"->";
                    else
                        cout<<"->";
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
            for(const auto & station : lines[lineNumber].getStationsWithLength()) {
                cout<<station.first;
                if(settings[3]&&blockedStations.find(station.first)!=blockedStations.end())
                    cout<<"(�ѷ��)";
                if(settings[4]&&TS.hasTransfer({lineNumber,station.first})) {
                    cout<<"( �ɻ�������";
                    for(const auto & transfer : TS.getTransfers({lineNumber,station.first})) {
                        cout<<transfer.first.first<<"����"<<transfer.first.second<<" ";
                    }
                    cout<<")";
                }
                if(station!=lines[lineNumber].getStationsWithLength().back())
                    if(settings[2])
                        cout<<"->"<<station.second<<"->";
                    else
                        cout<<"->";
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
        cout<<"4.����վ��"<<endl;
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

void Menu::BlockStationMenu() {
    while(true) {
        system("cls");
        cout<<"��ǰλ�ڣ���ҳ��->��·�༭�˵�->����վ��"<<endl;
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
                cout<<"����������������룺"<<endl;
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
            cout<<station<<endl;
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
            cout<<"����������������룺"<<endl;
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
            cout<<"����������������룺"<<endl;
            continue;
        }
        if(lineNumber==0)
            break;
        if(lines.find(lineNumber)==lines.end()) {
            cout<<"δ�ҵ�����·�����������룺"<<endl;
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
                    cout<<"����������������룺"<<endl;
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
                    cout<<"����������������룺"<<endl;
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
            cout<<"����������������룺"<<endl;
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
            cout<<"����������������룺"<<endl;
            continue;
        }
        if(lineNumber==0)
            break;
        if(lines.find(lineNumber)==lines.end()) {
            cout<<"δ�ҵ�����·�����������룺"<<endl;
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
                    cout<<"����������������룺"<<endl;
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
                    cout<<"����������������룺"<<endl;
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
        cout<<"��ǰλ�ڣ���ҳ��->��·�༭�˵�->������Ϣ�˵�"<<endl;
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
                cout<<"����������������룺"<<endl;
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
            cout<<"("<<station.first.first<<"����) "<<station.first.second<<"վ�� ����Ϊ"<<station.second<<endl;
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
            cout<<"����������������룺"<<endl;
            continue;
        }
        if(lineNumber==0)
            break;
        if(lines.find(lineNumber)==lines.end()) {
            cout<<"δ�ҵ�����·�����������룺"<<endl;
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
                cout<<"("<<transfer.first.first<<"����) "<<transfer.first.second<<"վ�� ����Ϊ"<<transfer.second<<endl;
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
            cout<<"����������������룺"<<endl;
            continue;
        }
        if(lineNumber==0)
            break;
        if(lines.find(lineNumber)==lines.end()) {
            cout<<"δ�ҵ�����·�����������룺"<<endl;
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
                    cout<<"����������������룺"<<endl;
                    continue;
                }
                if(lines.find(lineNumber2)==lines.end()) {
                    cout<<"δ�ҵ�����·�����������룺"<<endl;
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
                            cout<<"����������������룺"<<endl;
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
            cout<<"����������������룺"<<endl;
            continue;
        }
        if(lineNumber==0)
            break;
        if(lines.find(lineNumber)==lines.end()) {
            cout<<"δ�ҵ�����·�����������룺"<<endl;
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
                    cout<<"����������������룺"<<endl;
                    continue;
                }
                if(lines.find(lineNumber2)==lines.end()) {
                    cout<<"δ�ҵ�����·�����������룺"<<endl;
                    continue;
                }
                cout<<"������Ҫɾ��������Ϣ�Ļ���վ�����ƣ�";
                string station2;
                while(cin>>station2) {
                    if(!lines[lineNumber2].hasStation(station2)) {
                        cout<<"δ�ҵ���վ�㣬���������룺"<<endl;
                        continue;
                    }
                    cout<<"����ɾ��"<<lineNumber<<"���ߵ�"<<station<<"վ�㵽"<<lineNumber2<<"���ߵ�"<<station2<<"վ��Ļ�����Ϣ"<<endl;
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
                        cout<<"����������������룺"<<endl;
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
    if(!FileIO::SaveMain(lines,blockedStations,settings,TS)) {
        cout<<"����ʧ��"<<endl;
        cout<<"����ԭ�򣺴���/���ļ�ʧ��"<<endl;
    }
    else cout<<"����ɱ���"<<endl;
    system("pause");
}

void Menu::ReadLines() {
    if(!FileIO::LoadMain(lines,blockedStations,settings,TS)) {
        cout<<"��ȡʧ��"<<endl;
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
        cout<<"��ǰλ�ڣ���ҳ��->���ò˵�"<<endl;
        cout<<"��ͨ�������������ı书�ܵ��Ƿ����ã�"<<endl;
        cout<<"1.��������ʱ�Զ���ȡ��·��Ϣ\t\t"<<(settings[0]?"(��)":"(��)")<<endl;
        cout<<"2.�����˳�ʱ�Զ�������·��Ϣ\t\t"<<(settings[1]?"(��)":"(��)")<<endl;
        cout<<"3.����ʾ·��ʱ��ʾվ������\t\t"<<(settings[2]?"(��)":"(��)")<<endl;
        cout<<"4.����ʾ·��ʱ��ʾվ���Ƿ񱻽���\t"<<(settings[3]?"(��)":"(��)")<<endl;
        cout<<"5.����ʾ·��ʱ��ʾվ�㻻����Ϣ\t\t"<<(settings[4]?"(��)":"(��)")<<endl;
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

void Menu::TestMenu() {
    while(true) {
        system("cls");
        cout<<"��ǰλ�ڣ���ҳ��->�����߲��Բ˵�"<<endl;
        cout<<"��ͨ������������ѡ���ܣ�"<<endl;
        cout<<"1.�������뻻����Ϣ"<<endl;
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

void Menu::EnterTransferInformationInBatches() {
    cout<<"�����뻻����Ϣ�������ʽΪ����·���1 վ����1 ��·���2 վ����2 ����1 ��·���3 վ����3 ��·���4 վ����4 ����2 ..."<<endl;
    cout<<"վ����֮���ÿո������վ�������ܰ����ո񣬾���Ϊ������"<<endl;
    cout<<"������վ����Ϊ0ʱֹͣ����"<<endl;
    cout<<"�����룺";
    string input;
    while(cin>>input) {
        if(input=="0")
            break;
        int lineNumber1;
        try {
            lineNumber1 = stoi(input);
        }
        catch(...) {
            cout<<"����������������룺"<<endl;
            continue;
        }
        if(lines.find(lineNumber1)==lines.end()) {
            cout<<"δ�ҵ�����·�����������룺"<<endl;
            continue;
        }
        string station1;
        while(cin>>station1) {
            if(!lines[lineNumber1].hasStation(station1)) {
                cout<<"δ�ҵ���վ�㣬���������룺"<<endl;
                continue;
            }
            int lineNumber2;
            try {
                lineNumber2 = stoi(input);
            }
            catch(...) {
                cout<<"����������������룺"<<endl;
                continue;
            }
            if(lines.find(lineNumber2)==lines.end()) {
                cout<<"δ�ҵ�����·�����������룺"<<endl;
                continue;
            }
            string station2;
            while(cin>>station2) {
                if(!lines[lineNumber2].hasStation(station2)) {
                    cout<<"δ�ҵ���վ�㣬���������룺"<<endl;
                    continue;
                }
                Length len=0;
                while(cin>>input) {
                    try {
                        len = stoi(input);
                        break;
                    }
                    catch(...) {
                        cout<<"����������������룺"<<endl;
                        continue;
                    }
                }
                if(!TS.addTransfer({lineNumber1,station1},{lineNumber2,station2},len)) {
                    cout<<"���ʧ��"<<endl;
                }
                break;
            }
            break;
        }
    }
}
