#include <QApplication>
#include <QWidget>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    window.resize(640, 480); // 设置窗口大小
    window.setWindowTitle("Hello Qt!"); // 设置窗口标题

    QLabel label("我的第一个qt程序", &window);
    QFont font("宋体", 32);
    label.setFont(font);
    label.setStyleSheet("color: red;");
    label.setAlignment(Qt::AlignCenter);
    label.setGeometry(0, 0, 640, 480);

    window.show();

    return app.exec();
}