#include "hgusersettings.h"
#include <fstream>
#include <string>

unsigned int HGUserSettings::m_nPagesToCache = 5;

HGUserSettings::HGUserSettings()
{
    loadSettings();
}

void HGUserSettings::loadSettings()
{
    std::ifstream file(SETTINGS_FILE);
    while (!file.eof()) {
        std::string key;
        file >> key;

        if (key == "nPagesToCache")
            file >> m_nPagesToCache;
        // And other data points
    }
}

HGUserSettings::~HGUserSettings()
{
    writeSettings();
}

void HGUserSettings::writeSettings()
{
    std::ofstream file(SETTINGS_FILE);
    file << "nPagesToCache" << m_nPagesToCache;
}

unsigned int HGUserSettings::nPagesToCache()
{
    return m_nPagesToCache;
}
