#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <ctime>     //clock()
#include <windows.h> //system(),DeleteFile()
using namespace std;

vector<string> getDirFileList(const string& dir)
{
    cout << "reading file list from dir...";
    string cmd = "dir /S /B /O:N /A:-D \"" + dir + "\" >filelist";
    system(cmd.c_str()); //list all files of the folder to 'filelist'
    vector<string> res;
    string fileName;

    ifstream fin("filelist");
    while (getline(fin, fileName)) { //get one line (a file name with path)
        string::size_type pos = fileName.rfind('.'); //find the last char '.'
        if (pos != string::npos) {
            string fmt = fileName.substr(pos); //get the format of the file
            if (fmt == ".cpp" || fmt == ".h" || fmt == ".hpp" || fmt == ".c")
                res.push_back(fileName);
        }
    }
    fin.close();

    DeleteFile("filelist");
    cout << "\r\t\t\t\t\t\t\r";
    return res;
}

bool getFileLine(string fName, pair<int, int>& lines)
{
    string::size_type pos = fName.rfind('.'); //find the last char '.'
    if (pos == string::npos) //ignore files with no file format
        return false;
    string fmt = fName.substr(pos); //get file format
    if (fmt != ".cpp" && fmt != ".h" && fmt != ".hpp" && fmt != ".c")
        return false;

    ifstream fin(fName.c_str()); //open the file to read the content
    int cnt = 0, cnt_space = 0;  //file lines, space lines
    string str;
    while (getline(fin, str)) {  //read a line every time, stastic the lines
        if (str.find_first_not_of(" \t") == str.npos) //check if is a space line
            ++cnt_space;

        ++cnt;
    }
    fin.close();

    cout << "file<" << fName << ">:\n" << cnt << " lines, " << cnt_space
         << " space lines, left " << cnt - cnt_space << "\n\n";
    clog << "file<" << fName << ">:\n" << cnt << " lines, " << cnt_space
         << " space lines, left " << cnt - cnt_space << "\n\n";
    lines = make_pair(cnt, cnt_space);
    return true;
}

int cmpFirst(const pair<string, int>& x, const pair<string, int>& y)
{
    return x.first < y.first;
}

int cmpSecond(const pair<string, int>& x, const pair<string, int>& y)
{
    return x.second > y.second;
}

int main(int argc, char *argv[])
{
    if (argc < 2) { //have no command parameters with file names or paths
        cout << "Oops, please open me in another way! such as drag files or"
             " paths to my '.exe' file..." << endl;
        cin.get();
        return 0;
    }

    ofstream logFile("log.log");
    streambuf *sb_log = clog.rdbuf(logFile.rdbuf()); //redirect log output to file

    int sum = 0;       //total lines
    int sum_space = 0; //total space lines
    int fileNums = 0;  //the number of file
    unordered_map<string, int> folderLines;

    for (int i = 1; i < argc; ++i) {
        string fName = argv[i];
        pair<int, int> lines;
        vector<string> fileList;
        string::size_type pos = fName.rfind('.'); //find the last char '.'

        if (pos != string::npos) { //if there is a '.' in the path name
            string fmt = fName.substr(pos); //get file format or ...
            if (fmt == ".cpp" || fmt == ".h" || fmt == ".hpp" || fmt == ".c")
                fileList.push_back(fName);
            else
                fileList = getDirFileList(fName);
        } else
            fileList = getDirFileList(fName);

        for (auto &elem : fileList) { //deal with each file from the file list
            if (getFileLine(elem, lines)) {
                ++fileNums;
                sum += lines.first;
                sum_space += lines.second;
                folderLines[elem.substr(0, elem.rfind('\\'))] += lines.first;
            }
        }
    }

    cout << "\n" << fileNums << " files total: " << sum << " lines!\n"
         << sum_space << " space lines, left " << sum - sum_space << " lines\n";
    clog << "\n" << fileNums << " files total: " << sum << " lines!\n"
         << sum_space << " space lines, left " << sum - sum_space << " lines\n";

    vector<pair<string, int> > sortVec;
    sortVec.reserve(folderLines.size());
    for (auto &folder : folderLines)
        sortVec.push_back(folder);

    sort(sortVec.begin(), sortVec.end(), cmpFirst); //sort by path name asc

    cout << "sort by path name asc:" << endl;
    clog << "sort by path name asc:" << endl;
    for (auto &folder : sortVec) { //output code lines of each folder
        cout << setw(6) << folder.second << ": [" << folder.first << "]" << endl;
        clog << setw(6) << folder.second << ": [" << folder.first << "]" << endl;
    }

    sort(sortVec.begin(), sortVec.end(), cmpSecond); //sort by code lines desc

    cout << "\nsort by code lines desc:" << endl;
    clog << "\nsort by code lines desc:" << endl;
    for (auto &folder : sortVec) { //output code lines of each folder
        cout << setw(6) << folder.second << ": [" << folder.first << "]" << endl;
        clog << setw(6) << folder.second << ": [" << folder.first << "]" << endl;
    }

    cout << "\ntime cost: " << clock() / 1000.0 << " s" << endl;

    clog.rdbuf(sb_log); //restore log output
    cin.get();
    return 0;
}
