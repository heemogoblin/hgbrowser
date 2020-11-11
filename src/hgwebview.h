#ifndef HGWEBVIEW_H
#define HGWEBVIEW_H

#include <QWidget>
#include <QTabWidget>
#include <QWebEngineView>
#include <QPushButton>

class HGWebView : public QWidget
{
    Q_OBJECT
public:
    explicit HGWebView(QWidget *parent = nullptr);
    void loadPage(QUrl url);
    void reloadCurrentPage();
    void stopLoad();
    QWebEnginePage* currentPage();
    void addPage(QUrl url);
    ~HGWebView();
    void resize_window(int width, int height);
signals:
    void pageLoaded(QWebEnginePage* page);
    void tabSwitched(QWebEngineView* currentTab);
    void pageLoadProgress(int percent);
    void loadStarted();

public slots:
    void back();
    void forward();
    void setCurrentTabText(QString text);

private slots:
    void onLoadProgress(int percent);
    void onTabBarChanged();
    void onLoadFinished(bool state);
    void onLoadStarted();
    void onNewTabButtonPressed();
    void onDownloadRequested(QWebEngineDownloadItem* download);
    void onTabCloseRequested(int index);

private:
    QTabWidget* mainView;
    QPushButton* newTabButton;

    QWebEngineView* currentView;
    bool tabsClosable = false;
};

#endif // HGWEBVIEW_H
