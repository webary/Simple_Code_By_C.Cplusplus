#include <iostream>
#include <fstream>
#include <string>
using namespace std;
/**
��������Ҫʹ����getline()����,�÷�����:
  ��������������Ǳ�׼����������cin,Ҳ������һ���ļ�����������fin;
  (1)����������ĳ�Ա����:
   basic_istream<char>&
   istream::getline(char *str, streamsize n, char delim = '\n');
   ��������ǳ�Ա���������Ա���ͨ���������.streamsizeΪsigned integer type
   @prama:strΪC�ַ�������׵�ַ,�������ն�ȡ�Ľ��.ע�����ַ�����
   @prama:nΪ����ȡ���ַ�����
   @prama:delim��ѡ,��ʾ��ȡ�����ַ�ʱ�Զ�ֹͣ��ȡ,Ĭ��Ϊ���з�
  (2)ȫ�ֺ���
   basic_istream<char>&
   getline(basic_istream<char>& in, string& str);
   @prama:inΪ���������������;
   @prama:strΪ��Ҫ�����ȡ�����ݵ�Ŀ���ַ���,ע����string���������
**/

const char sep[3] = { 0x1F, 0x7C }; //�ָ���
int main()
{
    //����������һ��������Ϣ���ļ�
    ofstream fout("ol_msg.msg", ios::app);
    string fromUser = "userA";
    if (fout.is_open()) {
        fout << fromUser << sep << __TIME__ << sep << "hello!" << endl;
        fout.close();
    }
    ///��һ�ַ�ʽ,ÿ�ζ�ȡһ���ֶ�,ͨ�����ݶ�ȡ������־���Զ��ҵ��ֶεĽ���
    ifstream fin("ol_msg.msg");
    if (fin.is_open()) {
        cout << "From:\tOn:\t\tContent: " << endl;
        while (!fin.eof()) { //δ���ļ�β
            char _from[20];
            if (!fin.getline(_from, 20, sep[0]))
                break;
            fin.ignore(1); //����һ���ַ�

            char _time[20];
            fin.getline(_time, 20, sep[0]);
            fin.ignore(1); //����һ���ַ�

            string content;
            getline(fin, content); //��ȡ����ʣ������ݼ�Ϊ��Ϣ����
            cout << _from << "\t" << _time << "\t" << content << endl;
        }
        fin.close();
    }
    cout << endl;
    ///�ڶ��ַ�ʽ,ÿ�ζ�ȡһ��,Ȼ����ͨ�����ҷָ������ֿ������ֶ�
    ifstream fin2("ol_msg.msg");
    if (fin2.is_open()) {
        string line;
        while (getline(fin2, line)) { //�ɹ���ȡ��һ��
            string _time, content;
            string::size_type pos = line.find(sep); //���ҷָ�����λ��
            fromUser = line.substr(0, pos); //��ȡ��ߵĲ���Ϊ��һ�ֶ�
            line = line.substr(pos + 2); //����һ�ֶ�����ȥ��

            pos = line.find(sep); //���ҵڶ����ָ���
            _time = line.substr(0, pos); //��ȡ�ڶ��ֶ�

            content = line.substr(pos + 2); //ʣ���Ϊ�����ֶ�
            cout << fromUser << "\t" << _time << "\t" << content << endl;
        }
        fin2.close();
    }
    //ofstream f_del("ol_msg.msg"); //����ļ�����
    //f_del.close();
    return 0;
}
