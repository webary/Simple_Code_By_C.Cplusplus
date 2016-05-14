#include <iostream>
#include <ctime>
using namespace std;

//m*n �� n*p �ľ�����˵õ� m*p �ľ���
template<int m, int n, int p>
void matMultiply(int (&a)[m][n], int (&b)[n][p], int (&c)[m][p])
{
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < p; ++j) {
            c[i][j] = 0;
            for (int k = 0; k < n; ++k)
                c[i][j] += a[i][k] * b[k][j];
        }
}
//���þֲ���ԭ���Ż����ʵ�ִ���
template<int m, int n, int p>
void matMultiply2(int (&a)[m][n], int (&b)[n][p], int (&c)[m][p])
{
    std::fill(&c[0][0], &c[m - 1][p], 0);
    for (int i = 0; i < m; ++i)
        for (int k = 0; k < n; ++k)
            for (int j = 0; j < p; ++j)
                c[i][j] += a[i][k] * b[k][j];
}

//��������м�ʱͳ��
#define tip() _tip(__LINE__)
inline void _tip(int line)
{
    static clock_t t1 = clock();
    static int lastLine = 0;
    cout << "--L:" << lastLine << "->" << line << '\t' << clock() - t1 << "ms" << endl;
    lastLine = line;
    t1 = clock();
}

//�Ժ������м�ʱͳ��
#define tipFunc(func) \
{ \
    cout << "--L:" << __LINE__; \
    clock_t t1 = clock(); \
    func; \
    cout << '\t' << clock() - t1 << "ms\t" << #func << endl; \
}

//����ϴ�,��Ҫ����Ϊȫ�ֵ�
const int m = 500, n = 700, p = 900;
int a[m][n] = {
    {1, 0, 0, 2},
    {0, 2, 0, 3},
    {0, 1, 4, 0}
};
int b[n][p] = {
    {1, 2, 3},
    {2, 3, 4},
    {3, 4, 5},
    {4, 5, 6}
};
int c[m][p] = {0};

int main()
{
    tipFunc(matMultiply(a, b, c));
    tipFunc(matMultiply2(a, b, c));
//  for (auto& it : c) {
//      for (auto& elem : it)
//          cout << elem << ' ';
//      cout << endl;
//  }
    tip();
    matMultiply2(a, b, c);
    tip();
    return 0;
}
