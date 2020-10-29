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
    pageTabs = new QTabBar(this);
    mainView = new QWebEngineView(this);
    mainView->setZoomFactor(DEFAULT_ZOOM_FACTOR);
    newTabButton = new QPushButton(this);
    newTabButton->setIcon(QIcon("C:\\Users\\artyo\\Documents\\HGBrowser\\1.0\\data\\plus.png"));

    pageTabs->setTabsClosable(true);



    QObject::connect(pageTabs, SIGNAL (currentChanged(int)), this, SLOT (onTabBarChanged()));
    QObject::connect(pageTabs, SIGNAL (tabCloseRequested(int)), this, SLOT (onTabCloseRequested(int)));
    QObject::connect(mainView, SIGNAL (loadFinished(bool)), this, SLOT (onLoadFinished(bool)));
    QObject::connect(mainView, SIGNAL (loadProgress(int)), this, SLOT (onLoadProgress(int)));
    QObject::connect(mainView, SIGNAL (loadStarted()), this, SLOT (onLoadStarted()));
>>>>>>> parent of 7a88008... yy
    QObject::connect(newTabButton, SIGNAL (clicked()), this, SLOT (onNewTabButtonPressed()));
}
// TODO: webpage iconsS

void HGWebView::loadPage(QUrl url)
{
<<<<<<< HEAD
    currentView->load(url);
=======

    mainView->load(url);
>>>>>>> parent of 7a88008... yy
}

QWebEnginePage* HGWebView::currentPage()
{
<<<<<<< HEAD
    return currentView->page();
=======
    return mainView->page();
>>>>>>> parent of 7a88008... yy
}

void HGWebView::addPage(QUrl url)
{
<<<<<<< HEAD
    QWebEngineView* newView = new QWebEngineView(mainView);
    mainView->addTab(newView, url.toEncoded());
=======
    pageTabs->addTab(url.toEncoded());
    // Add to oages list
>>>>>>> parent of 7a88008... yy
}

void HGWebView::onLoadProgress(int percent)
{
    emit pageLoadProgress(percent);
}

void HGWebView::onTabBarChanged()
{
<<<<<<< HEAD
    currentView = dynamic_cast<QWebEngineView*>(mainView->currentWidget());
    emit tabSwitched(currentView->page());
    QObject::connect(currentView, SIGNAL (loadFinished(bool)), this, SLOT (onLoadFinished(bool)));
    QObject::connect(currentView, SIGNAL (loadProgress(int)), this, SLOT (onLoadProgress(int)));
    QObject::connect(currentView, SIGNAL (loadStarted()), this, SLOT (onLoadStarted()));
=======
    // Change page
    emit tabSwitched(mainView->page());
    QObject::connect(mainView, SIGNAL (loadFinished(bool)), this, SLOT (onLoadFinished(bool)));
    QObject::connect(mainView, SIGNAL (loadProgress(int)), this, SLOT (onLoadProgress(int)));
    QObject::connect(mainView, SIGNAL (loadStarted()), this, SLOT (onLoadStarted()));
>>>>>>> parent of 7a88008... yy
}

void HGWebView::back()
{
<<<<<<< HEAD
    currentView->back();
=======
    mainView->back();
>>>>>>> parent of 7a88008... yy
}

void HGWebView::forward()
{
<<<<<<< HEAD
    currentView->forward();
=======
    mainView->forward();
>>>>>>> parent of 7a88008... yy
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
<<<<<<< HEAD
        emit pageLoaded(currentView->page());
=======
        emit pageLoaded(mainView->page());
>>>>>>> parent of 7a88008... yy
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
<<<<<<< HEAD
    mainView->addTab(newView, "");
=======
    pageTabs->addTab("");
    // Add new page to list
>>>>>>> parent of 7a88008... yy
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
<<<<<<< HEAD
    mainView->removeTab(index);
=======
    pageTabs->removeTab(index);
    // Remove page from list
>>>>>>> parent of 7a88008... yy
}
