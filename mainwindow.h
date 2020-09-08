#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "msclient.h"

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

public slots:
    void serverData(QString server);
    void clearServerList();

private:
    Ui::MainWindow *ui;

    MSClient* ms_client;
    struct ServerInfo {
        QString description;
        QString ip;
        int port;
    };

    QMap<QString, ServerInfo> server_infos;
};
#endif // MAINWINDOW_H
