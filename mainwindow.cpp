#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ms_client = new MSClient(this);
    connect(ms_client, &MSClient::serverData, this, &MainWindow::serverData);
    connect(ms_client, &MSClient::msUpdated, this, &MainWindow::clearServerList);
    ms_client->msConnect();
}

void MainWindow::serverData(QString server)
{
    QStringList server_info_list = server.split("&");
    //qDebug() << server_info_list;

    struct ServerInfo server_info = {
        server_info_list[1],
        server_info_list[2],
        server_info_list[3].toInt()
    };

    server_infos.insert(server_info_list[0], server_info);

    ui->server_list->addItem(server_info_list[0]);
}

void MainWindow::clearServerList()
{
    ui->server_list->clear();
}

void MainWindow::populateServerInfo(QListWidgetItem* item)
{
    QString server_name = item->text();
    ui->server_info->setText(server_infos.value(server_name).description);
}

MainWindow::~MainWindow()
{
    delete ui;
}

