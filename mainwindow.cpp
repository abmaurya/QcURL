#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <sstream>

using namespace curlpp::options;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), customAgentLineEdit(0), dataLineEdit(0)
{
    ui->setupUi(this);
    curlpp::initialize();
    connect(ui->sendPutPushButton, SIGNAL(clicked()), this, SLOT(OnSendPushButton()));
    connect(ui->dataCheckBox, SIGNAL(stateChanged(int)), this, SLOT(OnDataCheckBoxStateChanged(int)));
    connect(ui->userAgentCheckBox, SIGNAL(stateChanged(int)), this, SLOT(OnUserAgentCheckBoxStateChanged(int)));
    ui->centralwidget->setLayout( ui->mainWindowLayout);
    sendButtonIndex = ui->mainWindowLayout->count()-1;
}

MainWindow::~MainWindow()
{
    curlpp::terminate();
    delete ui;
}

void MainWindow::OnSendPushButton()
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
            if(ui->userAgentCheckBox->isChecked())
            {
                myRequest.setOpt<UserAgent>(customAgentLineEdit->text().toStdString());
            }


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
        if(!dataLineEdit)
        {
            dataLineEdit = new QTextEdit(ui->centralwidget);
            dataLineEdit->setPlaceholderText("Your data here");
            ui->mainWindowLayout->insertWidget(sendButtonIndex - 1, dataLineEdit);
        }
        dataLineEdit->show();
    }
    else
    {
        dataLineEdit->hide();
    }
}

void MainWindow::OnUserAgentCheckBoxStateChanged(int state)
{
    if(state == Qt::CheckState::Checked)
    {
        if(!customAgentLineEdit)
        {
            customAgentLineEdit = new QLineEdit(ui->centralwidget);
            customAgentLineEdit->setPlaceholderText("Your custom agent here");
            //increment sendButtonIndex because we want to keep always add
            // the custom data field below custom agent field
            ui->mainWindowLayout->insertWidget(sendButtonIndex++ - 1, customAgentLineEdit);
        }
        customAgentLineEdit->show();
    }
    else
    {
        // delete le;
        customAgentLineEdit->hide();
    }
}

