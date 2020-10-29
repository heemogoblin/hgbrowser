
#include "mainbrowserwindow.h"
#include <regex>

#define EDGE_SIZE 20
#define HOME_PAGE "https://www.google.com/"
#define SIDEBAR_REQUEST 0.15

/*What to do next:
 *
 * Menu at the right
 *
 */

#include <QDebug>
#define PUTLINE qDebug() << __FILE__ << " " << __LINE__ << "\n"

MainBrowserWindow::MainBrowserWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowState(Qt::WindowMaximized);
    view = new HGWebView(this);
    inputBar = new QLineEdit(this);
    goButton = new QPushButton(this);
    backButton = new QPushButton(this);
    forwardButton = new QPushButton(this);
    homeButton = new QPushButton(this);
    loadButton = new QPushButton(this);
    progressBar = new QProgressBar(this);
    menuButton = new QPushButton(this);
    menu = new QMenu(this);
    searchBar = new QLineEdit(this);
    searchButton = new QPushButton(this);
    sidePanel = new HGSidePanel(this);

    inputBar->move(60, 0);
    inputBar->setText(HOME_PAGE);
    goButton->resize(EDGE_SIZE, EDGE_SIZE);
    goButton->setIcon(QIcon("C:\\Users\\artyo\\Documents\\HGBrowser\\1.0\\arrowright.png"));
    backButton->resize(EDGE_SIZE, EDGE_SIZE);
    backButton->setIcon(QIcon("C:\\Users\\artyo\\Documents\\HGBrowser\\1.0\\arrowleft.png"));
    forwardButton->resize(EDGE_SIZE, EDGE_SIZE);
    forwardButton->setIcon(QIcon("C:\\Users\\artyo\\Documents\\HGBrowser\\1.0\\arrowright.png"));
    homeButton->resize(EDGE_SIZE, EDGE_SIZE);
    homeButton->setIcon(QIcon("C:\\Users\\artyo\\Documents\\HGBrowser\\1.0\\home.jpg"));
    loadButton->resize(EDGE_SIZE, EDGE_SIZE);
    loadButton->setIcon(QIcon("C:\\Users\\artyo\\Documents\\HGBrowser\\1.0\\reload.png"));
    //Set up menu before the menu button
    menu->addAction("Poo");
    menuButton->resize(EDGE_SIZE, EDGE_SIZE);
    menuButton->setIcon(QIcon("C:\\Users\\artyo\\Documents\\HGBrowser\\1.0\\menu.png"));
    menuButton->setMenu(menu);
    progressBar->setRange(0, 100);
    progressBar->move(0, EDGE_SIZE);
    progressBar->setTextVisible(false);
    searchBar->setText("Google search");
    searchBar->resize(100, EDGE_SIZE);
    searchButton->resize(EDGE_SIZE, EDGE_SIZE);
    searchButton->setIcon(QIcon("C:\\Users\\artyo\\Documents\\HGBrowser\\1.0\\search.png"));
    view->loadPage(QUrl(HOME_PAGE));
    view->move(0, 22);
    ResizeView();

    QObject::connect(inputBar, SIGNAL (returnPressed()), this, SLOT (LoadPage()));
    QObject::connect(goButton, SIGNAL (clicked()), this, SLOT (LoadPage()));
    QObject::connect(homeButton, SIGNAL(clicked()), this, SLOT(Home()));
    QObject::connect(backButton, SIGNAL(clicked()), view, SLOT(back()));
    QObject::connect(forwardButton, SIGNAL(clicked()), view, SLOT(forward()));
    QObject::connect(view, SIGNAL (pageLoaded(QWebEnginePage*)), this, SLOT (AfterLoad(QWebEnginePage*)));
    QObject::connect(view, SIGNAL (pageLoadProgress(int)), progressBar, SLOT (setValue(int)));
    QObject::connect(view, SIGNAL (loadStarted()), this, SLOT (StartLoad()));
    QObject::connect(view, SIGNAL (tabSwitched(QWebEnginePage*)), SLOT (onTabSwitched(QWebEnginePage*)));
    QObject::connect(loadButton, SIGNAL (clicked()), this, SLOT (ReloadButtonAction()));
    //QObject::connect(searchBar, SIGNAL (returnPressed()), this, SLOT (SearchGoogle()));
    //QObject::connect(searchButton, SIGNAL (clicked()), this, SLOT (SearchGoogle()));
}

void MainBrowserWindow::ResizeView(){
    QSize currentSize = size();
    view->resize_window(currentSize.width() * (1 - SIDEBAR_REQUEST), currentSize.height());
    resize(currentSize.width(), currentSize.height());
    view->resize(currentSize.width() * (1 - SIDEBAR_REQUEST), currentSize.height() - EDGE_SIZE - 2);
    progressBar->resize(currentSize.width(), 2);
    inputBar->resize(currentSize.width() - 240, EDGE_SIZE);
    backButton->move(0, 0);
    forwardButton->move(20, 0);
    loadButton->move(40, 0);
    menuButton->move(currentSize.width() - 20, 0);
    homeButton->move(currentSize.width() - 40, 0);
    searchButton->move(currentSize.width() - 60, 0);
    searchBar->move(currentSize.width() - 160, 0);
    goButton->move(currentSize.width() - 180, 0);
    sidePanel->move(size().width() - size().width() * SIDEBAR_REQUEST, 22);
    sidePanel->resize(size().width() * SIDEBAR_REQUEST, size().height() - 22);
}

void MainBrowserWindow::LoadPage()
{
    QString text = inputBar->text();
    view->loadPage(QUrl(text));
}

void MainBrowserWindow::Home()
{
    view->loadPage(QUrl(HOME_PAGE));
}

void MainBrowserWindow::ReloadButtonAction()
{
    if (pageLoaded)
        view->reloadCurrentPage();
    else
        view->stopLoad();
}

void MainBrowserWindow::StartLoad()
{
    pageLoaded = false;
}

void MainBrowserWindow::AfterLoad(QWebEnginePage* newPage)
{
    pageLoaded = true;
    view->setCurrentTabText(GetUrlText(newPage->url()));
    onTabSwitched(view->currentPage());
}

void MainBrowserWindow::resizeEvent(QResizeEvent* e)
{
    ResizeView();
}

void MainBrowserWindow::Search()
{

}

void MainBrowserWindow::onTabSwitched(QWebEnginePage* newPage)
{
    inputBar->setText(newPage->url().toEncoded());
}

QString MainBrowserWindow::GetUrlText(QUrl url)
{
    if (url.toEncoded().size() > 27)
    {
        QString ns = url.toEncoded();
        ns.truncate(27);
        return ns + "...";
    }
    return url.toEncoded();
}
