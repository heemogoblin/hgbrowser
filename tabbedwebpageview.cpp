#include "tabbedwebpageview.h"
#include <QDebug>

TabbedWebPageView::TabbedWebPageView(QWidget* parent) :
    QTabWidget(parent)
{

}

void LoadUrl(QUrl url)
{
    qDebug() << "Loading URL\n";
}

QWebEnginePage* CurrentPage()
{
    return nullptr;
}
