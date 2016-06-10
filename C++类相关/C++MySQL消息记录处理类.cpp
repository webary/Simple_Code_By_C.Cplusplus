#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <stdexcept>
#include <set>
#include <windows.h> //�����ڰ���mysql.h֮ǰ����windows.h
#include <mysql.h>

using std::string;
using std::vector;
using std::endl;

///���ݿ���������,�����������ݿ�,����װ���������ݿ���ز���
class DB_Connector {
protected:
    MYSQL* mysql; //mysql���ӵľ��
public:
    static string host_, user_, passwd_, db_;
public:
    inline DB_Connector();
    inline virtual ~DB_Connector();
    //ִ��sql���,�ɹ��򷵻�0,ʧ�ܷ��ط�0
    inline int query(const string& sql);
    //������һ�εĴ�����ʾ
    inline string error();
    //��ȡ�����,���䱣�浽��άstring������
    inline vector<vector<string> > getResult();
};

DB_Connector::DB_Connector()
{
    mysql = mysql_init(NULL);
    if (mysql_real_connect(mysql, host_.c_str(), user_.c_str(),
                           passwd_.c_str(), db_.c_str(), 0, 0, 0) == 0) {
        string err = "Failed to connect database server: " + error();
        throw std::logic_error(err);
    }
    query("set names 'GBK'");//�����ַ���,��ֹ���ĳ�������
}

DB_Connector::~DB_Connector()
{
    mysql_close(mysql); //�ر�mysql����
}

//ִ��sql���,�ɹ��򷵻�0,ʧ�ܷ��ط�0
int DB_Connector::query(const string& sql)
{
    return mysql_query(mysql, sql.c_str());
}

//������һ�εĴ�����ʾ
string DB_Connector::error()
{
    return mysql_error(mysql);
}

//��ȡ�����,���䱣�浽��άstring������
vector<vector<string> > DB_Connector::getResult()
{
    vector<vector<string> >result;
    MYSQL_RES* res = mysql_store_result(mysql);
    if (res == NULL)
        return result;
    unsigned num = mysql_num_fields(res); //�����������
    for (MYSQL_ROW row; (row = mysql_fetch_row(res)) != NULL;) {
        result.push_back(vector<string>(num));
        for (size_t cur = result.size() - 1, i = 0; i < num; ++i) {
            result[cur][i] = row[i];
        }
    }
    mysql_free_result(res); //�ͷŽ������Դ
    return result;
}


///��Ϣ������
class DB_Msg {
protected:
    DB_Connector db_conn; //���ݿ�����������
    const string tbName;  //Ҫ�����ı���
    std::ofstream fsLog;  //��־��¼�ļ���
public:
    inline DB_Msg(const string& _tableName, const string& _logFileName);
    inline virtual ~DB_Msg();
    //�����Ϣ
    inline void push(const string& to, const string& from, const string& msg);
    //��ȡִ��ָ��sql����Ľ��
    inline vector<vector<string> > getBySql(const string& sql);
    //����ָ��sql���ɾ����Ӧ��¼
    inline void removeBySql(const string& sql);
    //��ȡ��ǰ���ں�ʱ��,���ڸ�����־
    inline static string getTime();
protected:
    //�����洢�����¼�ı�
    inline void createTable();
};

DB_Msg::DB_Msg(const string& _tableName, const string& _logFileName)
    : tbName(_tableName)
{
    if (_logFileName != "") {
        fsLog.open(_logFileName, std::ios::app);
    }
    createTable();
}

DB_Msg::~DB_Msg()
{
    if (fsLog) {
        fsLog.close();
    }
}
//�����Ϣ
void DB_Msg::push(const string& to, const string& from, const string& msg)
{
    string sql = "insert into " + tbName + "(toUser,fromUser,msg) values('"
                 + to + "','" + from + "','" + msg + "')";
    if (fsLog) {
        fsLog << getTime() << ">>>execute: " + sql << endl;
    }
    if (db_conn.query(sql) != 0 && fsLog) { //ִ��sql���ʧ�ܷ��ط�0
        fsLog << "Failed to insert: " << db_conn.error() << endl;
    }
}
//��ȡִ��ָ��sql����Ľ��
vector<vector<string> > DB_Msg::getBySql(const string& sql)
{
    vector<vector<string> >result;
    if (fsLog) {
        fsLog << getTime() << ">>>execute: " + sql << endl;
    }
    if (db_conn.query(sql) == 0) {   //ִ�гɹ���ѽ�����
        result = db_conn.getResult();
    } else if (fsLog) {
        fsLog << "Failed to search: " << db_conn.error() << endl;
    }
    return result;
}
//����ָ��sql���ɾ����Ӧ��¼
void DB_Msg::removeBySql(const string& sql)
{
    if (fsLog) {
        fsLog << getTime() << ">>>execute: " << sql << endl;
    }
    if (db_conn.query(sql) != 0 && fsLog) {
        fsLog << "Failed to delete: " << db_conn.error() << endl;
    }
}
//��ȡ��ǰ���ں�ʱ��,���ڸ�����־
inline string DB_Msg::getTime()
{
    char time_buf[64];
    time_t now_time = time(NULL);
    strftime(time_buf, 64, "%Y-%m-%d %H:%M:%S ", localtime(&now_time));
    return time_buf;
}
//�����洢�����¼�ı�
void DB_Msg::createTable()
{
    db_conn.query("show tables like '" + tbName + "'");
    auto res = db_conn.getResult();
    if (res.size() > 0 && res[0][0] == tbName) {
        return;
    }
    string sql = "CREATE TABLE `" + tbName + "` ("
                 "`id` tinyint(4) NOT NULL AUTO_INCREMENT,"
                 "`toUser` varchar(20) NOT NULL,"
                 "`fromUser` varchar(20) NOT NULL,"
                 "`time` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,"
                 "`msg` text NOT NULL,"
                 "PRIMARY KEY (`id`)"
                 ") ENGINE=InnoDB DEFAULT CHARSET=utf8;";
    if (fsLog) {
        fsLog << getTime() << ">>>execute: " << sql << endl;
    }
    if (db_conn.query(sql) != 0 && fsLog) {
        fsLog << "Failed to create: " << db_conn.error() << endl;
    }
}


///������Ϣ������ - �����ڷ�������
class DB_OfflineMsg : public DB_Msg {
public:
    DB_OfflineMsg(const string& _tableName, const string& _logFileName = "")
        : DB_Msg(_tableName, _logFileName)
    {}
    //��������Ϣ���еõ����з��͸�user����Ϣ,��ȡ�������ݿ�ɾ��
    inline vector<vector<string> > pop(const string& user);
};

//��������Ϣ���еõ����з��͸�user����Ϣ,��ȡ�������ݿ�ɾ��
vector<vector<string> > DB_OfflineMsg::pop(const string& user)
{
    string sql = "select fromUser,time,msg from " + tbName
                 + " where toUser='" + user + "'";
    vector<vector<string> >result = getBySql(sql);
    //ɾ������user��������Ϣ
    if (result.size() > 0) {
        sql = "delete from " + tbName + " where toUser='" + user + "'";
        removeBySql(sql);
    }
    return result;
}

///�����¼��Ϣ������
class DB_ChatLogMsg : public DB_Msg {
public:
    //�û�����ʶ�û�,��־�ļ���Ϊ��ʱ������,ǰ׺�����������ڿͻ��˻��Ƿ�������
    inline DB_ChatLogMsg(const string& _userName, const string& _logFileName = "",
                         const string& _prefix = "")
        : DB_Msg(_prefix + "chat_log_" + _userName, _logFileName), userName(_userName)
    {}
    //��������¼��Ϣ
    inline void push(const string& userOthers, const string& msg, bool isReceived = 1);
    //����յ��Ĵ�ʱ���¼��������Ϣ
    inline void pushOffline(const string& from, const string& msg, const string& _time);
    //��ȡ��Ϣuser�����Ļ򷢸�user��������Ϣ
    inline vector<vector<string> > get(const string& user);
    //�ڸ��û��������¼�в�����withUser�İ���str����Ϣ��¼
    inline vector<vector<string> > find(const string& str, const string& withUser = "*");
    //���ݴ��ݵ��û���ɾ�����Ӧ�û��������¼,����"*"��ɾ�����м�¼
    inline void remove(const string& user);
    //��ȡ�뵱ǰ�û��������¼���û��б�
    inline vector<string> getUserWithChatLog();
    //��ȡ��ǰ�û����û���
    inline const string& getUserName();
protected:
    string userName; //���û����û���
};

//��������¼��Ϣ
void DB_ChatLogMsg::push(const string& userOthers, const string& msg, bool isReceived)
{
    if (isReceived) { //�յ�����Ϣ
        DB_Msg::push(userName, userOthers, msg);
    } else { //��������Ϣ
        DB_Msg::push(userOthers, userName, msg);
    }
}
//����յ��Ĵ�ʱ���¼��������Ϣ
void DB_ChatLogMsg::pushOffline(const string& from, const string& msg,
                                const string& _time)
{
    string sql = "insert into " + tbName + "(toUser,fromUser,time,msg) values('"
                 + userName + "','" + from + "','" + _time + "','" + msg + "')";
    if (fsLog) {
        fsLog << getTime() << ">>>execute: " + sql << endl;
    }
    if (db_conn.query(sql) != 0 && fsLog) { //ִ��sql���ʧ�ܷ��ط�0
        fsLog << "Failed to insert: " << db_conn.error() << endl;
    }
}
//��ȡ��Ϣuser�����Ļ򷢸�user��������Ϣ
vector<vector<string> > DB_ChatLogMsg::get(const string& user)
{
    string sql = "select fromUser,time,msg from " + tbName;
    if (user != "*") {
        sql += " where toUser='" + user + "' or fromUser='" + user + "'";
    }
    return getBySql(sql);
}
//�ڸ��û��������¼�в�����withUser�İ���str����Ϣ��¼
vector<vector<string> > DB_ChatLogMsg::find(const string& str, const string& withUser)
{
    string sql = "select fromUser,toUser,time,msg from " + tbName + " where ";
    if (withUser != "*") {
        sql += "(toUser='" + withUser + "' or fromUser='" + withUser + "') and";
    }
    sql += " msg like '%" + str + "%'";
    return getBySql(sql);
}
//���ݴ��ݵ��û���ɾ�����û�user�������¼,����"*"��ɾ�����м�¼
void DB_ChatLogMsg::remove(const string& user)
{
    string sql = "delete from " + tbName;
    if (user != "*") {
        sql += " where toUser='" + user + "' or fromUser='" + user + "'";
    }
    removeBySql(sql);
}
//��ȡ�뵱ǰ�û��������¼���û��б�
vector<string> DB_ChatLogMsg::getUserWithChatLog()
{
    string sql = "select distinct toUser from " + tbName;
    auto users = getBySql(sql);
    std::set<string> userList;
    for (auto &line : users) {
        userList.insert(line[0]);
    }
    sql = "select distinct fromUser from " + tbName;
    users = getBySql(sql);
    for (auto &line : users) {
        userList.insert(line[0]);
    }
    userList.erase(userList.find(userName)); //ɾ���û��б��е��Լ�
    //��������浽vector<string>�з���
    vector<string> res;
    res.reserve(userList.size());
    for (auto &elem : userList) {
        res.push_back(elem);
    }
    return res;
}

//��ȡ��ǰ�û����û���
inline const string& DB_ChatLogMsg::getUserName()
{
    return userName;
}

using std::cout;
//��ֱ�������ѯ���
inline std::ostream& operator<<(std::ostream& out, const vector<vector<string> >& res)
{
    if (res.size() == 0) {
        cout << "�������ݿ���ʾ!" << endl;
        return out;
    }
    for (auto &it : res) { //��ʾ��ȡ����������Ϣ����
        for (auto &elem : it) {
            cout << elem << " ";
        }
        cout << endl;
    }
    return out;
}


string DB_Connector::host_ = "localhost";
string DB_Connector::user_ = "root";
string DB_Connector::passwd_ = "123456";
string DB_Connector::db_ = "mfc_qq";

using namespace std;
int main()
{
    DB_OfflineMsg off_msg("offline_msg", "offileMsg.log");
    off_msg.push("to", "from", "hey");   //����һ��������Ϣ
    auto res = off_msg.pop("to"); //��ȡ�������û���ȫ��������Ϣ
    cout << res << endl;

    DB_ChatLogMsg clMsg("Bob", "chat_log_Bob.log");
    clMsg.push("Miranda-lym", "hello", 0);
    clMsg.push("Miranda-lym", "hi!", 1);
    clMsg.push("Miranda-lym", "this a test case!", 0);
    clMsg.push("Miranda-lym", "soga,I get it!", 1);
    clMsg.push("John", "what are you doing!", 1);
    cout << clMsg.get("Miranda-lym") << endl;

    cout << "find 'hi':\n" << clMsg.find("hi") << endl;

    auto userList = clMsg.getUserWithChatLog();
    cout << "users that have chated with " <<clMsg.getUserName()<<endl;
         for (auto &elem : userList)
             cout << elem << endl;
    cin.get();
    return 0;
}
