#include "sidepanel.h"

SidePanel::SidePanel(QWidget *parent) : QWidget(parent)
{

}

int SidePanel::desiredWidth()
{
    return m_desiredWidth;
}
