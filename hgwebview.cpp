#include "hgwebview.h"

#include <QDebug>
#define PUTLINE qDebug() << __FILE__ << " " << __LINE__ << "\n"

HGWebView::HGWebView(QWidget *parent) : QWidget(parent)
{
    mainView = new QTabWidget(this);
    mainView->resize(parent->size().width(), parent->size().height() - 22);
    currentView = new QWebEngineView;
    currentView->resize(mainView->size());
    qDebug() << mainView->size().width() << mainView->size().height();
    mainView->addTab(currentView, "test");
    currentView->load(QUrl("about:blank"));
    QObject::connect(mainView, SIGNAL (currentChanged(int)), this, SLOT (onTabBarChanged()));
    QObject::connect(currentView, SIGNAL (loadFinished(bool)), this, SLOT (onLoadFinished(bool)));
    QObject::connect(currentView, SIGNAL (loadProgress(int)), this, SLOT (onLoadProgress(int)));
    QObject::connect(currentView, SIGNAL (loadStarted()), this, SLOT (onLoadStarted()));
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
    mainView->addTab(newView, url.toEncoded());
}

void HGWebView::onLoadProgress(int percent)
{
    emit pageLoadProgress(percent);
}

void HGWebView::onTabBarChanged()
{
    currentView = dynamic_cast<QWebEngineView*>(mainView->currentWidget());
    emit tabSwitched(currentView);
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
