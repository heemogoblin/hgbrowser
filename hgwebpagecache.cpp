#include "hgwebpagecache.h"

HGWebPageCache::HGWebPageCache() {}

void HGWebPageCache::addPage(QWebEngineView *page, int index)
{
    if (cache.size() <= PAGE_CACHE_AMT){
        PageCacheItem item;
        item.saved = false;
        item.index = index;
        item.view = page;
    }
}
