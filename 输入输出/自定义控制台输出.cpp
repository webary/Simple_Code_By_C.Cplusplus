#include<windows.h>
#include<stdio.h>
//����ǰ��
#define FG_R    FOREGROUND_RED
#define FG_G    FOREGROUND_GREEN
#define FG_B    FOREGROUND_BLUE
#define FG_HL   FOREGROUND_INTENSITY    //������ʾ
//���ñ���
#define BG_R    BACKGROUND_RED
#define BG_G    BACKGROUND_GREEN
#define BG_B    BACKGROUND_BLUE
#define BG_HL   BACKGROUND_INTENSITY    //������ʾ

#define SetText(attr) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),attr)

#define setBlue() SetText(FG_HL | FG_B)
#define setGreen() SetText(FG_HL | FG_G)
#define setWhite() SetText(FG_HL | FG_R | FG_G | FG_B)
#define setDefault() SetText(FG_R | FG_G | FG_B)

void test()
{
    puts("����һ���ı����̨��ɫ�����ӣ�\n������������������������������������\n");
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, FG_HL | FG_R);//����Ϊ��ɫ
    puts("*�Ұѽ�ǰ��ɫ����Ϊ��ɫ��,�������Ǻ�ɫ*\n������������������������������������\n");
    SetConsoleTextAttribute(handle, FG_HL | FG_R | BG_B);
    puts("*�Ұѽ�ǰ��ɫ����Ϊ��ɫ��,��������ɫ��*\n������������������������������������\n");
    SetConsoleTextAttribute(handle, FG_HL | BG_HL | FG_G | BG_R | BG_G | BG_B);
    puts("*�Ұѽ�ǰ��ɫ����Ϊ��ɫ��,�������ɫ��*\n������������������������������������\n");

    SetConsoleTextAttribute(handle, FG_HL | FG_R | FG_G | FG_B);
}

int main()
{
    setBlue();
    printf("hadoop-2.4.1  ");
    setGreen();
    puts("hadoop-2.4.1.tar.gz");
    setWhite();
    puts("szu@u2:/usr/hadoop$ cd hadoop-2.4.1/\n"
         "szu@u2:/usr/hadoop/hadoop-2.4.1$ is");
    setBlue();
    printf("bin\tinclude\tlibexec\t\tlogs\netc\tlib\t");
    setWhite();
    printf("LICENSE.txt\tNOTICE.txt\t");
    setBlue();
    puts("sbin\ttmp");

    setWhite();
    puts("szu@u2:/usr/hadoop/hadoop-2.4.1$ cd sbin/");
    setGreen();
    puts("distribute-exclude.sh\tstart-all.cmd\n"
         "hadoop-daemon.sh\tstart-all.sh\n"
         "hadoop-daemons.sh\tstart-balancer.sh\n"
        );
    setWhite();
    puts("szu@u2:/usr/hadoop/hadoop-2.4.1/sbins$ ./start-dfs.sh\n"
         "starting namenodes in[u1]");
    getchar();
    setDefault();
    test();
    return 0;
}
