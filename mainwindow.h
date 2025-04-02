#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSharedPointer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QLineEdit;
class QTextEdit;
class CurlHandler;

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
    const QStringList METHOD_NAME{"GET","POST"};
    uint sendButtonIndex;
    QSharedPointer<CurlHandler> curlHandler;
};
#endif // MAINWINDOW_H
