#ifndef HGUSERSETTINGS_H
#define HGUSERSETTINGS_H

#define SETTINGS_FILE "settingsfile.dat"

class HGUserSettings
{
public:
    HGUserSettings();
    ~HGUserSettings();

    unsigned int nPagesToCache();

private:
    // Defaults in case the file is not found
    static unsigned int m_nPagesToCache;
    void loadSettings();
    void writeSettings();

};

/* Settings file format:
 * ___________
 * |key value|
 * |key value|
 * |_________|
 *
 * Current keys:
 * - nPagesToCache - pages to cache
 */

#endif // HGUSERSETTINGS_H
