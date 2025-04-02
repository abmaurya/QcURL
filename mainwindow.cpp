#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QSharedPointer>
#include <curlhandler.h>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), customAgentLineEdit(0), dataLineEdit(0)
{
    ui->setupUi(this);
    connect(ui->sendPutPushButton, SIGNAL(clicked()), this, SLOT(OnSendPushButton()));
    connect(ui->dataCheckBox, SIGNAL(stateChanged(int)), this, SLOT(OnDataCheckBoxStateChanged(int)));
    connect(ui->userAgentCheckBox, SIGNAL(stateChanged(int)), this, SLOT(OnUserAgentCheckBoxStateChanged(int)));
    ui->centralwidget->setLayout( ui->mainWindowLayout);
    sendButtonIndex = ui->mainWindowLayout->count()-1;
    ui->methodName->addItems(METHOD_NAME);
    curlHandler = QSharedPointer<CurlHandler>::create();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OnSendPushButton()
{
    CurlOptions curlOp;
    curlOp.Redirection = ui->followRedirectCheckBox->isChecked();
    curlOp.Verbose = ui->verbosCheckBox->isChecked();
    if(ui->userAgentCheckBox->isChecked())
    {
        if(customAgentLineEdit->text().size() <= 0)
        {
            return;
        }
        curlOp.CustomAgent = customAgentLineEdit->text().toStdString();
    }
    if(ui->urlLineEdit->text().size() <= 0)
    {
        return;
    }
    curlOp.Url = ui->urlLineEdit->text().toStdString();

    if(ui->urlLineEdit->text().size() > 0)
    {
        curlOp.PortNumber = std::stol(ui->portLineEdit->text().toStdString());
    }
    curlOp.Post = ui->methodName->currentText() == METHOD_NAME[1]?true:false;
    if(curlOp.Post)
    {
        curlOp.PostData = dataLineEdit->toMarkdown().toStdString();
    }
    std::string result = curlHandler->SendData(curlOp);
    ui->resultTextBrowser->clear();
    ui->resultTextBrowser->setText(result.c_str());
}

void MainWindow::OnDataCheckBoxStateChanged(int state)
{
    if(state == Qt::CheckState::Checked)
    {
        if(!dataLineEdit)
        {
            dataLineEdit = new QTextEdit(ui->centralwidget);
            dataLineEdit->setPlaceholderText("Your data here");
            ui->mainWindowLayout->insertWidget(sendButtonIndex - 1u, dataLineEdit);
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
            //increment sendButtonIndex because we want to always keep
            // the custom data field below custom agent field
            ui->mainWindowLayout->insertWidget(sendButtonIndex++ - 1u, customAgentLineEdit);
        }
        customAgentLineEdit->show();
    }
    else
    {
        // delete le;
        customAgentLineEdit->hide();
    }
}

