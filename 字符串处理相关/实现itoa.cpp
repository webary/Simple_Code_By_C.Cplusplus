/** ʵ��char* itoa(int value,char* str);��value���浽str�в�����
	��չ:ʵ��char* itoa(int value,char* str,unsigned radix);
		 ��value��radix���Ʊ��浽str�в�����
 **/
#include<stdio.h>

char* itoa(int num,char* str) {
    char temp;
    unsigned unum = (unsigned)num;
    int i=0,j,k=0;
    if(num<0) { //ʮ���Ƹ���
        unum = -unum;
        str[i++] = '-';
        k = 1;
    }
    //�洢���ֵ�ÿһλ
    do {
        str[i++] = unum % 10 + '0';
        unum /= 10;
    } while(unum);
    str[i]='\0';	//���һλ��0���������׳��ֶ����ַ�
    //��������
    for(j=k; j<=(i-1)/2; j++) {
        temp = str[j];
        str[j] = str[i-1+k-j];
        str[i-1+k-j] = temp;
    }
    return str;
}

char* itoa(int num,char* str,unsigned radix) {
    char index[]= "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ",temp;
    unsigned unum = (unsigned)num;
    int i=0,j,k=0;
    if(radix==10 && num<0) { //ʮ���Ƹ���
        unum = -unum;
        str[i++] = '-';
        k = 1;
    }
    //�洢���ֵ�ÿһλ
    do {
        str[i++] = index[(unum%radix) % 36];
        unum /= radix;
    } while(unum);
    str[i]='\0';	//���һλ��0���������׳��ֶ����ַ�
    //��������
    for(j=k; j<=(i-1)/2; j++) {
        temp = str[j];
        str[j] = str[i-1+k-j];
        str[i-1+k-j] = temp;
    }
    return str;
}

int main()
{
	int a, base = 16;
    char str[128];
	while(scanf("%d",&a)==1)
		printf("ʮ����%d��Ӧ��%d������Ϊ %s\n\n",a,base,itoa(a,str,base));
		//puts(itoa(a,str));
	return 0;
}
