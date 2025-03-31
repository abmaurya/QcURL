#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QLineEdit;
class QTextEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void OnUserAgentCheckBoxStateChanged(int state);
    void OnSendPushButton();
    void OnDataCheckBoxStateChanged(int state);

private:
    Ui::MainWindow *ui;
    QLineEdit* customAgentLineEdit;
    QTextEdit* dataLineEdit;
    const QString GET{"GET"};
    const QString PUT{"POST"};
    size_t sendButtonIndex;
};
#endif // MAINWINDOW_H
