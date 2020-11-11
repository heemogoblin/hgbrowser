#include "hgwebview.h"

#include <QDebug>
#define PUTLINE qDebug() << __FILE__ << " " << __LINE__ << "\n"

HGWebView::HGWebView(QWidget *parent) : QWidget(parent)
{
    mainView = new QTabWidget(this);
    mainView->resize(parent->size().width(), parent->size().height() - 22);
    currentView = new QWebEngineView;
    currentView->resize(mainView->size());
    mainView->addTab(currentView, "");
    currentView->load(QUrl("about:blank"));
    QObject::connect(mainView, SIGNAL (currentChanged(int)), this, SLOT (onTabBarChanged()));
    QObject::connect(mainView, SIGNAL (tabCloseRequested(int)), this, SLOT (onTabCloseRequested(int)));
    QObject::connect(currentView, SIGNAL (loadFinished(bool)), this, SLOT (onLoadFinished(bool)));
    QObject::connect(currentView, SIGNAL (loadProgress(int)), this, SLOT (onLoadProgress(int)));
    QObject::connect(currentView, SIGNAL (loadStarted()), this, SLOT (onLoadStarted()));
    newTabButton = new QPushButton;
    mainView->setCornerWidget(newTabButton);
    newTabButton->setIcon(QIcon("C:\\Users\\artyo\\Documents\\HGBrowser\\1.0\\data\\plus.png"));

    QObject::connect(newTabButton, SIGNAL (clicked()), this, SLOT (onNewTabButtonPressed()));
}
// TODO: webpage icons

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
    newView->load(url);
    mainView->addTab(newView, url.toEncoded());
}

void HGWebView::onLoadProgress(int percent)
{
    emit pageLoadProgress(percent);
}

void HGWebView::onTabBarChanged()
{
    currentView = dynamic_cast<QWebEngineView*>(mainView->currentWidget());
    if (currentView){
        emit tabSwitched(currentView);
        QObject::connect(currentView, SIGNAL (loadFinished(bool)), this, SLOT (onLoadFinished(bool)));
        QObject::connect(currentView, SIGNAL (loadProgress(int)), this, SLOT (onLoadProgress(int)));
        QObject::connect(currentView, SIGNAL (loadStarted()), this, SLOT (onLoadStarted()));
    }
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
    if (state)
        emit pageLoaded(currentView->page());
    mainView->setTabText(mainView->currentIndex(), currentView->page()->url().toEncoded());
}

void HGWebView::onLoadStarted()
{
    emit loadStarted();
}

HGWebView::~HGWebView()
{
    delete currentView;
}

void HGWebView::resize_window(int width, int height)
{
    mainView->resize(width, height - 20);
}

void HGWebView::onNewTabButtonPressed()
{
    QWebEngineView* newView = new QWebEngineView;
    mainView->addTab(newView, "");
    mainView->setCurrentWidget(newView);
    if (mainView->count() > 1)
        mainView->setTabsClosable(true);

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
    if (mainView->count() == 1)
        mainView->setTabsClosable(false);
}
