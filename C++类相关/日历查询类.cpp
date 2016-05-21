//������
#include<iostream>
#include<conio.h>
#include<cstdlib>
#include<ctime>
#include<string>
#include<iomanip>
using namespace std;

int ren[13] = {0, 31, 60, 91, 131, 162, 192, 223, 254, 284, 315, 335, 366} ; //������
int pin[13] = {0, 31, 59, 90, 130, 161, 191, 222, 253, 283, 314, 334, 365} ;

int ren_month[13] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int pin_month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

inline bool isprim(int year)
{
    return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
}
void print(int month, int weekly, int tol_day)
{
    int k = 1;
    cout.width(3);
    cout << month << "  SUN MON TUE WED THU FRI SAT" << endl;
    cout << "     ";
    int kongge = weekly % 7;
    while (kongge) {
        cout << "    ";
        kongge--;
    }
    for (k = 1; k <= tol_day ; k++) {
        cout << setw(3) << setiosflags(ios::right) << k << " ";
        if (weekly % 7 == 6)
            cout << endl << "     ";
        weekly++;
    }
    cout << endl;
}

class Calender {
public :
    Calender() {};
    Calender(int y): year(y) {};
    Calender(int y, int m): year(y), month(m) {};
    Calender(int y, int m, int d): year(y), month(m), day(d) {};
    ~Calender() {};
    void show1();
    void show2();
    void show3();
private:
    int year;
    int month;
    int day;
};
void Calender::show1()
{
    time_t current;
    struct tm *t;
    time(&current); //�õ�Ŀǰ��ʱ��
    t = localtime(&current);
    t->tm_year += 1900;
    t->tm_mon += 1;
    cout << "�����ʱ��Ϊ��" << t->tm_year << " �� ";
    cout << t->tm_mon << " �� " << t->tm_mday << " ��" << endl;
    cout << "��Ҫ��ѯ��ʱ��Ϊ: " << year << " �� " << month << " �� " << day << "��" << endl;
    //�ж��Ƿ�����
    int en, start;
    if (isprim(t->tm_year)) //��һ��Ϊ����
        start = ren[t->tm_mon - 1] + t->tm_mday ;
    else
        start = pin[t->tm_mon - 1] + t->tm_mday ;
    if (isprim(year))
        en = ren[month - 1] + day;
    else
        en = pin[month - 1] + day;
    int  year_cha = year - t->tm_year;
    int ans = (year_cha / 4) * 366 + (year_cha - year_cha / 4) * 365 + en - start;
    cout << "�����" << ans << " ��" << endl;
    cout << "��һ���ǣ�" << t->tm_wday + ans % 7 << endl;
}
void Calender::show2()
{
    time_t current;
    struct tm *t;
    time(&current); //�õ�Ŀǰ��ʱ��
    t = localtime(&current);
    int en, start, sday = 1;
    t->tm_year += 1900;
    t->tm_mon++;
    if (isprim(t->tm_year)) //��һ��Ϊ����
        start = ren[t->tm_mon - 1] + t->tm_mday ;
    else
        start = pin[t->tm_mon - 1] + t->tm_mday ;
    if (isprim(year))
        en = ren[month - 1] + sday;
    else
        en = pin[month - 1] + sday;
    int  year_cha = year - t->tm_year;
    int ans = (year_cha / 4) * 366 + (year_cha - year_cha / 4) * 365 + en - start;
    //�õ����³�һ�����ڼ�
    int weekly = t->tm_wday + ans % 7;
    if (weekly < 0)weekly += 7;
    if (isprim(year))
        print(month, weekly, ren_month[month]);
    else
        print(month, weekly, pin_month[month]);
}
void Calender::show3()
{
    int start, ans;
    time_t k = time(NULL);
    struct tm *t = localtime(&k);
    //�Ƴ���Ϊ���ڼ�����
    int sday = 1, mon = 1;
    t->tm_year += 1900;
    t->tm_mon++;
    if (isprim(t->tm_year))
        start = ren[t->tm_mon - 1] + t->tm_mday;
    else
        start = pin[t->tm_mon - 1] + t->tm_mday;
    int year_cha = (year - t->tm_year);
    ans = (year_cha / 4) * 366 + (year_cha - year_cha / 4) * 365 + 1 - start;
    int weekly = t->tm_wday + ans % 7;
    if (weekly < 0)weekly += 7;
    if (isprim(year)) {
        for (int i = 1; i <= 12 ; i++ )
            print(i, (weekly + ren[i - 1]) % 7, ren_month[i]);
    } else
        for (int i = 1; i <= 12 ; i++ )
            print(i, (weekly + pin[i - 1]) % 7, pin_month[i]);

}

int main()
{
    int aa, bb, cc;
    while (1) {
        cout << "����Ҫ�鿴ʲô��\n";
        cout << "1.ĳ��ĳ��ĳ�վ����ڵ������Լ������ڼ�" << endl;
        cout << "2.ĳ��ĳ�µ�һ���µ�����" << endl;
        cout << "3.ĳ�������" << endl;
        switch (getche()) {
            case '1': {
                    cout << "������ �� ��" << endl;
                    cin >> aa >> bb >> cc;
                    Calender stu(aa, bb, cc);
                    stu.show1();
                    break;
                }
            case '2': {
                    cout << "������ ��" << endl;
                    cin >> aa >> bb;
                    Calender tt(aa, bb);
                    cout << "this  is " << aa << " Calender !" << endl;
                    tt.show2();
                    break;
                }
            case '3': {
                    cout << "���� ��" << endl;
                    cin >> aa;
                    Calender stu(aa);
                    stu.show3();
                    break;
                }
            case 'q':
            case 'Q':
                return 0;
        }
        system("pause");
        system("cls");
    }
    return 0;
}
