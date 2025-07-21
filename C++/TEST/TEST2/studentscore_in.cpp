#include<iostream>
#include<fstream>
using namespace std;

struct Student {
    string id;
    string name;
    int one_score;
    int two_score;
    int three_score;
    int total_score;
    double average_score; // 平均分
};

//输入成绩
void input_score(Student& stu) {
    cout << "请输入学生学号: ";
    cin >> stu.id;
    cout << "请输入学生姓名: ";
    cin >> stu.name;
    cout << "请输入学生第一次测试成绩: ";
    cin >> stu.one_score;
    cout << "请输入学生第二次测试成绩: ";
    cin >> stu.two_score;
    cout << "请输入学生第三次测试成绩: ";
    cin >> stu.three_score;
    stu.total_score = stu.one_score + stu.two_score + stu.three_score;
    stu.average_score = stu.total_score / 3.0;
    cout<<"\n";
}

//输出成绩
void output_score(const Student& stu) {
    cout << "学生学号: " << stu.id << endl;
    cout << "学生姓名: " << stu.name << endl;
    cout << "学生第一次测试成绩: " << stu.one_score << endl;
    cout << "学生第二次测试成绩: " << stu.two_score << endl;
    cout << "学生第三次测试成绩: " << stu.three_score << endl;
    cout << "学生总分: " << stu.total_score << endl;
    cout << "学生平均分: " << stu.average_score << endl;
    // 写入文件
    ofstream outf;
    outf.open("C:\\Users\\LIXIN\\Desktop\\123.txt");
    outf<<"成绩如下"<<endl;
    outf << "学生学号: " << stu.id << endl;
    outf << "学生姓名: " << stu.name << endl;
    outf << "学生第一次测试成绩: " << stu.one_score << endl;
    outf << "学生第二次测试成绩: " << stu.two_score << endl;
    outf << "学生第三次测试成绩: " << stu.three_score << endl;
    outf << "学生总分: " << stu.total_score << endl;
    outf << "学生平均分: " << stu.average_score << endl;
    outf.close();
}

int main() {
    Student stu1;
    input_score(stu1);
    output_score(stu1);
    system("pause");
    return 0;
}