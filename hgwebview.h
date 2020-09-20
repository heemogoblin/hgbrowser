#ifndef HGWEBVIEW_H
#define HGWEBVIEW_H

#include <QWidget>
#include <QTabWidget>
#include <QWebEngineView>

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

private slots:
    void onLoadProgress(int percent);
    void onTabBarChanged();
    void onLoadFinished(bool state);
    void onLoadStarted();

private:
    QTabWidget* mainView;
    QWebEngineView* currentView;
};

#endif // HGWEBVIEW_H
