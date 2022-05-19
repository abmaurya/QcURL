#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void OnUserAgentCheckBoxStateChanged(int state);
    void OnGetPutPushButton();
    void OnDataCheckBoxStateChanged(int state);

private:
    Ui::MainWindow *ui;
    const QString GET{"Get"};
    const QString PUT{"POST"};
};
#endif // MAINWINDOW_H
