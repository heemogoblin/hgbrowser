#ifndef HGWEBPAGECACHE_H
#define HGWEBPAGECACHE_H

#include <QUrl>
#include <QWebEngineView>
#include <QList>

#define PAGE_CACHE_AMT 5

struct PageCacheItem
{
    bool saved;
    union  {
        QWebEngineView* view;
        QUrl url;
    };
    int index;
};

class HGWebPageCache
{
public:
    HGWebPageCache();
    void addPage(QWebEngineView* page, int index);
    QWebEngineView* getPage(int index);
    void removePage(int index);

private:
    QList<PageCacheItem> cache;
};

#endif // HGWEBPAGECACHE_H
