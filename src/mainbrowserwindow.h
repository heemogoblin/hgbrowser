#ifndef MAINBROWSERWINDOW_H
#define MAINBROWSERWINDOW_H

#include <QMainWindow>
#include <QWebEngineView>
#include <QLineEdit>
#include <QApplication>
#include <QPushButton>
#include <QProgressBar>
#include <QMenu>
#include <regex>

#include "hgwebview.h"

class MainBrowserWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainBrowserWindow(QWidget *parent = nullptr);

private slots:
    void LoadPage();
    void Home();
    void StartLoad();
    void ReloadButtonAction();
    void Search();
    void AfterLoad(QWebEnginePage* newPage);
    void TabSwitched(QWebEngineView* newTab);

signals:
    void StopLoad();
    void Reload();

private:
    HGWebView* view;
    QLineEdit* inputBar;
    QLineEdit* searchBar;
    QPushButton* goButton;
    QPushButton* backButton;
    QPushButton* forwardButton;
    QPushButton* homeButton;
    QPushButton* loadButton;
    QProgressBar* progressBar;
    QPushButton* menuButton;
    QPushButton* searchButton;
    QMenu* menu;

    bool pageLoaded;

    void ResizeView();
    void resizeEvent(QResizeEvent* e) override;

    void UpdateInputDlg();

    const std::regex url_regex;


};
#endif // MAINBROWSERWINDOW_H
