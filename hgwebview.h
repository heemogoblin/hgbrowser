#ifndef HGWEBVIEW_H
#define HGWEBVIEW_H

#define MAX_PAGES 5
// To do:
// - Constants, settings

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
    void setCurrentTabText(QString text);

signals:
    void pageLoaded(QWebEnginePage* page);
    void tabSwitched(QWebEnginePage* currentTab);
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
    void onNewTabButtonPressed();
    void onDownloadRequested(QWebEngineDownloadItem* download);
    void onTabCloseRequested(int index);

private:
    QTabWidget* mainView;
    QPushButton* newTabButton;

    /* How the caching works:
     * - Max 5 pages in the currentViews
     * - When a page is added it is added to the top of the view
     * - When a page is selected it is moved to the top
     * - When there are more than 5 pages, the page at the end of the list gets its
     *   url added to savedPages;
     */
    QWebEngineView* currentView;
};


#endif // HGWEBVIEW_H
