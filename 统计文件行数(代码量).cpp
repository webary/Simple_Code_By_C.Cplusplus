#include <string>
#include <fstream>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    if(argc < 2) { //没有传入命令行参数,即没有文件名
        cout << "啊哦, 请换个姿势打开我吧！比如把一堆代码文件拖到我身上..." << endl;
        cin.get();
        return 0;
    }
    int sum = 0, sum_space = 0, fileNums = 0;//代码总行数,空行总行数,代码文件数
    for(int i = 1; i < argc; ++i) {
        string fName = argv[i];
        string::size_type pos = fName.rfind('.'); //找到文件后缀前的一个.号
        if(pos == string::npos) //没有文件后缀跳过这个文件
            continue;
        string format = fName.substr(pos); //取得文件格式
        if(format != ".cpp" && format != ".h" && format != ".hpp" && format != ".c")
            continue;
        ifstream fin(argv[i]); //打开该文件
        int cnt = 0, cnt_space = 0;
        string str;
        while(getline(fin, str)) { //每次读一行,统计行数
            if(str.find_first_not_of(" \t") == str.npos) //检查是否为空行
                ++cnt_space;
            ++cnt;
        }
        fin.close();
        if((pos = fName.rfind('\\')) != string::npos) //只取文件名,不要路径
            fName = fName.substr(pos + 1);
        cout << "文件<" << fName << ">有 " << cnt << "行！空行: " << cnt_space
             << ", 非空行: " << cnt - cnt_space << "\n\n";
        sum += cnt;
        sum_space += cnt_space;
        ++fileNums;
    }
    cout << "\n" << fileNums << "个代码文件共有 " << sum << "行！\n其中空行有 "
         << sum_space << "行,去除空行后有 " << sum - sum_space << "行" << endl;
    cin.get();
    return 0;
}
