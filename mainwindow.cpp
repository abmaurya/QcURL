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
    curlHandler = QSharedPointer<CurlHandler>::create();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OnSendPushButton()
{
    auto redirection = ui->followRedirectCheckBox->isChecked();
    auto verbose = ui->verbosCheckBox->isChecked();
    std::string customAgent = "";
    if(ui->userAgentCheckBox->isChecked())
    {
        if(customAgentLineEdit->text().size() <= 0)
        {
            return;
        }
        customAgent = customAgentLineEdit->text().toStdString();
    }
    if(ui->urlLineEdit->text().size() <= 0)
    {
        return;
    }
    auto url = ui->urlLineEdit->text().toStdString();
    unsigned long long portNumber = 443;
    if(ui->urlLineEdit->text().size() > 0)
    {
        portNumber = std::stol(ui->portLineEdit->text().toStdString());
    }

    std::string result = curlHandler->SendData(redirection, verbose, url, portNumber, customAgent);
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

