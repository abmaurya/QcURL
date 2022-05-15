#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <sstream>

using namespace curlpp::options;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    curlpp::initialize();
    connect(ui->getPutPushButton, SIGNAL(clicked()), this, SLOT(OnGetPutPushButton()));
    connect(ui->dataCheckBox, SIGNAL(stateChanged(int)), this, SLOT(OnDataCheckBoxStateChanged(int)));

}

MainWindow::~MainWindow()
{
    curlpp::terminate();
    delete ui;
}

void MainWindow::OnGetPutPushButton()
{
    try
        {
            // Our request to be sent.
            curlpp::Easy myRequest;

            // Set the URL.
            myRequest.setOpt<Url>(ui->urlLineEdit->text().toStdString());
            //Set the port
            if(!ui->urlLineEdit->text().contains("http"))
            {
                myRequest.setOpt<Port>(std::stol(ui->portLineEdit->text().toStdString()));
            }
            //Set Redirection
            myRequest.setOpt<FollowLocation>(ui->followRedirectCheckBox->isChecked());
            myRequest.setOpt<Verbose>(ui->verbosCheckBox->isChecked());


            std::stringstream ss;
            // Send request and get a result in stringstream.
            ss<<myRequest;
            ui->resultTextBrowser->clear();
            ui->resultTextBrowser->setText(ss.str().c_str());
        }

        catch(curlpp::RuntimeError & e)
        {
             qDebug() << e.what();
        }

        catch(curlpp::LogicError & e)
        {
            qDebug() << e.what();
    }
}

void MainWindow::OnDataCheckBoxStateChanged(int state)
{
    if(state == Qt::CheckState::Checked)
    {
        ui->getPutPushButton->setText(PUT);
    }
    else
    {
        ui->getPutPushButton->setText(GET);
    }
}

