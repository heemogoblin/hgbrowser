#include "hgwebview.h"

#include <QDebug>
#define PUTLINE qDebug() << __FILE__ << " " << __LINE__ << "\n"

#define DEFAULT_ZOOM_FACTOR 0.8

HGWebView::HGWebView(QWidget *parent) : QWidget(parent)
{
    mainView = new QTabWidget(this);
    mainView->resize(parent->size().width(), parent->size().height() - 22);
    currentView = new QWebEngineView;
    currentView->setZoomFactor(DEFAULT_ZOOM_FACTOR);
    currentView->resize(mainView->size());
    mainView->addTab(currentView, "");
    currentView->load(QUrl("about:blank"));
    newTabButton = new QPushButton;
    newTabButton->resize(20, 20);
    newTabButton->setIcon(QIcon("C:\\Users\\artyo\\Documents\\HGBrowser\\1.0\\plus.png"));
    mainView->setCornerWidget(newTabButton, Qt::TopRightCorner);
    mainView->setTabsClosable(true);
    QObject::connect(mainView, SIGNAL (currentChanged(int)), this, SLOT (onTabBarChanged()));
    QObject::connect(mainView, SIGNAL (tabCloseRequested(int)), this, SLOT (onTabCloseRequested(int)));
    QObject::connect(currentView, SIGNAL (loadFinished(bool)), this, SLOT (onLoadFinished(bool)));
    QObject::connect(currentView, SIGNAL (loadProgress(int)), this, SLOT (onLoadProgress(int)));
    QObject::connect(currentView, SIGNAL (loadStarted()), this, SLOT (onLoadStarted()));
    QObject::connect(newTabButton, SIGNAL (clicked()), this, SLOT (onNewTabButtonPressed()));
}
// TODO: webpage iconsS

void HGWebView::loadPage(QUrl url)
{
    currentView->load(url);
}

QWebEnginePage* HGWebView::currentPage()
{
    return currentView->page();
}

void HGWebView::addPage(QUrl url)
{
    QWebEngineView* newView = new QWebEngineView(mainView);
    mainView->addTab(newView, url.toEncoded());
}

void HGWebView::onLoadProgress(int percent)
{
    emit pageLoadProgress(percent);
}

void HGWebView::onTabBarChanged()
{
    currentView = dynamic_cast<QWebEngineView*>(mainView->currentWidget());
    emit tabSwitched(currentView->page());
    QObject::connect(currentView, SIGNAL (loadFinished(bool)), this, SLOT (onLoadFinished(bool)));
    QObject::connect(currentView, SIGNAL (loadProgress(int)), this, SLOT (onLoadProgress(int)));
    QObject::connect(currentView, SIGNAL (loadStarted()), this, SLOT (onLoadStarted()));
}

void HGWebView::back()
{
    currentView->back();
}

void HGWebView::forward()
{
    currentView->forward();
}

void HGWebView::stopLoad()
{
    currentView->stop();
}

void HGWebView::reloadCurrentPage()
{
    currentView->reload();
}

void HGWebView::onLoadFinished(bool state)
{
    mainView->setTabText(mainView->currentIndex(), currentView->page()->url().toEncoded());
    //mainView->setTabIcon(mainView->currentIndex(), currentView->page()->icon());
    if (state)
        emit pageLoaded(currentView->page());
}

void HGWebView::onLoadStarted()
{
    emit loadStarted();
}

HGWebView::~HGWebView()
{
}

void HGWebView::resize_window(int width, int height)
{
    mainView->resize(width, height - 20);
}

void HGWebView::onNewTabButtonPressed()
{
    QWebEngineView* newView = new QWebEngineView;
    newView->setZoomFactor(DEFAULT_ZOOM_FACTOR);
    mainView->addTab(newView, "");
}

void HGWebView::setCurrentTabText(QString text)
{
    mainView->setTabText(mainView->currentIndex(), text);
}

void HGWebView::onDownloadRequested(QWebEngineDownloadItem* download)
{

}

void HGWebView::onTabCloseRequested(int index)
{
    mainView->removeTab(index);
}
