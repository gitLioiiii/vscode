#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>
#include <QMessageBox>
#include <QTextEdit>

class SimpleWindow : public QMainWindow
{
public:
    SimpleWindow(QWidget *parent = nullptr) : QMainWindow(parent)
    {
        // 设置窗口标题和大小
        setWindowTitle("简单的Qt应用程序");
        setGeometry(100, 100, 400, 300);
        
        // 创建中央部件
        QWidget *centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);
        
        // 创建主布局
        QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
        
        // 创建标题标签
        QLabel *titleLabel = new QLabel("欢迎使用Qt应用程序", this);
        titleLabel->setAlignment(Qt::AlignCenter);
        titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #2c3e50; margin: 10px;");
        mainLayout->addWidget(titleLabel);
        
        // 创建输入区域
        QHBoxLayout *inputLayout = new QHBoxLayout();
        QLabel *nameLabel = new QLabel("姓名:", this);
        nameEdit = new QLineEdit(this);
        nameEdit->setPlaceholderText("请输入您的姓名");
        inputLayout->addWidget(nameLabel);
        inputLayout->addWidget(nameEdit);
        mainLayout->addLayout(inputLayout);
        
        // 创建文本显示区域
        QLabel *displayLabel = new QLabel("显示区域:", this);
        mainLayout->addWidget(displayLabel);
        
        textDisplay = new QTextEdit(this);
        textDisplay->setMaximumHeight(100);
        textDisplay->setPlaceholderText("这里将显示输入的内容...");
        mainLayout->addWidget(textDisplay);
        
        // 创建按钮区域
        QHBoxLayout *buttonLayout = new QHBoxLayout();
        
        QPushButton *submitButton = new QPushButton("提交", this);
        submitButton->setStyleSheet(
            "QPushButton {"
            "    background-color: #3498db;"
            "    color: white;"
            "    border: none;"
            "    padding: 8px 16px;"
            "    border-radius: 4px;"
            "    font-weight: bold;"
            "}"
            "QPushButton:hover {"
            "    background-color: #2980b9;"
            "}"
            "QPushButton:pressed {"
            "    background-color: #21618c;"
            "}"
        );
        
        QPushButton *clearButton = new QPushButton("清空", this);
        clearButton->setStyleSheet(
            "QPushButton {"
            "    background-color: #e74c3c;"
            "    color: white;"
            "    border: none;"
            "    padding: 8px 16px;"
            "    border-radius: 4px;"
            "    font-weight: bold;"
            "}"
            "QPushButton:hover {"
            "    background-color: #c0392b;"
            "}"
            "QPushButton:pressed {"
            "    background-color: #a93226;"
            "}"
        );
        
        QPushButton *aboutButton = new QPushButton("关于", this);
        aboutButton->setStyleSheet(
            "QPushButton {"
            "    background-color: #27ae60;"
            "    color: white;"
            "    border: none;"
            "    padding: 8px 16px;"
            "    border-radius: 4px;"
            "    font-weight: bold;"
            "}"
            "QPushButton:hover {"
            "    background-color: #229954;"
            "}"
            "QPushButton:pressed {"
            "    background-color: #1e8449;"
            "}"
        );
        
        buttonLayout->addWidget(submitButton);
        buttonLayout->addWidget(clearButton);
        buttonLayout->addWidget(aboutButton);
        mainLayout->addLayout(buttonLayout);
        
        // 连接信号和槽
        connect(submitButton, &QPushButton::clicked, this, &SimpleWindow::onSubmitClicked);
        connect(clearButton, &QPushButton::clicked, this, &SimpleWindow::onClearClicked);
        connect(aboutButton, &QPushButton::clicked, this, &SimpleWindow::onAboutClicked);
        
        // 添加一些间距
        mainLayout->addStretch();
    }

private slots:
    void onSubmitClicked()
    {
        QString name = nameEdit->text().trimmed();
        if (name.isEmpty()) {
            QMessageBox::warning(this, "警告", "请输入姓名！");
            return;
        }
        
        QString message = QString("您好，%1！\n欢迎使用这个Qt应用程序。")
                         .arg(name);
        
        textDisplay->append(message);
        nameEdit->clear();
    }
    
    void onClearClicked()
    {
        textDisplay->clear();
        nameEdit->clear();
    }
    
    void onAboutClicked()
    {
        QMessageBox::information(this, "关于", 
            "简单的Qt应用程序\n\n"
            "这是一个使用C++和Qt框架创建的简单界面程序。\n"
            "功能包括：\n"
            "• 输入姓名\n"
            "• 显示欢迎信息\n"
            "• 清空内容\n"
            "• 关于对话框\n\n"
            "版本: 1.0\n"
            "作者: Qt开发者");
    }

private:
    QLineEdit *nameEdit;
    QTextEdit *textDisplay;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // 设置应用程序信息
    app.setApplicationName("简单Qt应用");
    app.setApplicationVersion("1.0");
    app.setOrganizationName("Qt开发者");
    
    // 创建并显示主窗口
    SimpleWindow window;
    window.show();
    
    // 运行应用程序
    return app.exec();
}
