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

    ao_client = new AOClient(this);
    connect(ao_client, &AOClient::playerCount, this, &MainWindow::updatePlayerCount);
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
    struct ServerInfo server_info = server_infos.value(server_name);

    ao_client->startConnection(server_info.ip, server_info.port);

    ui->player_count->setText("Player Count:");
    ui->server_info->setText(server_info.description);
}

void MainWindow::updatePlayerCount(int current, int max)
{
    ui->player_count->setText(QString("Player Count: %1/%2").arg(current).arg(max));
    ao_client->disconnectFromHost();
}

MainWindow::~MainWindow()
{
    delete ui;
}

