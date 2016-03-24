#include <ctime> //clock()
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <windows.h> //system(),DeleteFile()
using namespace std;

vector<string> getDirFileList(const string& dir)
{
    cout << "reading file list from dir...";
    string cmd = "dir /S /B /O:N /A:-D \"" + dir + "\" >filelist";
    system(cmd.c_str()); //list all files of the dir to 'filelist'
    vector<string> res;
    string fileName;
    ifstream fin("filelist");
    while(getline(fin, fileName)) {
        string::size_type pos = fileName.rfind('.'); //find the last char '.'
        if(pos != string::npos) {
            string fmt = fileName.substr(pos); //get file format
            if(fmt == ".cpp" || fmt == ".h" || fmt == ".hpp" || fmt == ".c")
                res.push_back(fileName);
        }
    }
    fin.close();
    DeleteFile("filelist");
    cout << "\r\t\t\t\t\t\t\r";
    return res;
}

int getFileLine(string fName, pair<int, int>& lines)
{
    string::size_type pos = fName.rfind('.'); //find the last char '.'
    if(pos == string::npos) //ignore files with no file format
        return 0;
    string fmt = fName.substr(pos); //get file format
    if(fmt != ".cpp" && fmt != ".h" && fmt != ".hpp" && fmt != ".c")
        return 0;
    ifstream fin(fName.c_str()); //open the file to read the content
    int cnt = 0, cnt_space = 0; //file lines, space lines
    string str;
    while(getline(fin, str)) { //read a line every time, stastic the lines
        if(str.find_first_not_of(" \t") == str.npos) //check if is a space line
            ++cnt_space;
        ++cnt;
    }
    fin.close();
    cout << "file<" << fName << ">:\n" << cnt << " lines, " << cnt_space
         << " space lines, left " << cnt - cnt_space << "\n\n";
    lines = make_pair(cnt, cnt_space);
    return 1;
}

int main(int argc, char *argv[])
{
    if(argc < 2) { //have no command parameters with file names or paths
        cout << "Oops, please open me in another way! such as drag files or"
             " paths to my '.exe' file..." << endl;
        cin.get();
        return 0;
    }
    int sum = 0, sum_space = 0; //total lines, total space lines
    int fileNums = 0; //the number of file
    for(int i = 1; i < argc; ++i) {
        string fName = argv[i];
        pair<int, int> lines;
        vector<string> fileList;
        if(fName.rfind('.') == string::npos) { //recursively read a directoy
            fileList = getDirFileList(fName);
        } else {
            fileList.push_back(fName);
        }
        for(auto &elem : fileList) { //deal each file from the file list
            if(getFileLine(elem, lines)) {
                ++fileNums;
                sum += lines.first;
                sum_space += lines.second;
            }
        }
    }
    cout << "\n" << fileNums << " files total: " << sum << " lines!\n"
         << sum_space << " space lines, left " << sum - sum_space << " lines\n";
    cout << "\ntime cost: " << clock() / 1000.0 << " s" << endl;
    cin.get();
    return 0;
}
