#ifndef TABBEDWEBPAGEVIEW_H
#define TABBEDWEBPAGEVIEW_H

#include <QTabWidget>
#include <QWebEngineView>

enum class VIEW_TYPE
{
    WEB_VIEW,
    SERVER_CONNECTION
};

class TabbedWebPageView : public QTabWidget
{
    Q_OBJECT
public:
    TabbedWebPageView(QWidget* parent = nullptr);

    void LoadUrl(QUrl url);
    QWebEnginePage* CurrentPage();

private:
    VIEW_TYPE currentViewType;
};

#endif // TABBEDWEBPAGEVIEW_H
