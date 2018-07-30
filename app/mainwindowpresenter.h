#ifndef MAINWINDOW_PRESENTER_H
#define MAINWINDOW_PRESENTER_H

#include <QObject>

class MainWindow;

class MainWindowPresenter : public QObject {
public:
    MainWindowPresenter(MainWindow *mainWindow, QObject *parent = nullptr);

private:
    void connectActionsToSlots();

private slots:
    void onOpenFile();

private:
    MainWindow *m_mainWindow;
};

#endif
