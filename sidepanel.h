#ifndef SIDEPANEL_H
#define SIDEPANEL_H

#include <QWidget>

class SidePanel : public QWidget
{
    Q_OBJECT
public:
    explicit SidePanel(QWidget *parent = nullptr);
    int desiredWidth();

signals:

private:
    const int m_desiredWidth = 200;
};

#endif // SIDEPANEL_H
