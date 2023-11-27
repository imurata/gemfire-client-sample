#include <iostream>
#include <thread>
#include <geode/CacheFactory.hpp>
#include <geode/CqAttributesFactory.hpp>
#include <geode/PoolManager.hpp>
#include <geode/RegionFactory.hpp>
#include <geode/RegionShortcut.hpp>
#include <geode/CacheListener.hpp>
#include <geode/EntryEvent.hpp>
using namespace apache::geode::client;
class MyCacheListener : public CacheListener{
public:
    void afterCreate(const EntryEvent &event) override {
        std::cout << "Create " << std::dynamic_pointer_cast<CacheableString>(event.getNewValue())->value() << std::endl;
    }
    void afterUpdate(const EntryEvent &event) override {
        std::cout << "Update " << std::dynamic_pointer_cast<CacheableString>(event.getNewValue())->value() << std::endl;
    }
    void afterDestroy(const EntryEvent &event) override {
        std::cout << "Destroy " << std::dynamic_pointer_cast<CacheableString> (event.getOldValue())->value() << std::endl;
    }
};
int main() {
    auto cache = CacheFactory()
            .set("log-level", "none")
            .create();
    auto pool = cache.getPoolManager()
            .createFactory()
            .addLocator("localhost", 10334)
            .setSubscriptionEnabled(true)
            .create("pool");
    auto regionFactory = cache.createRegionFactory(RegionShortcut::PROXY);
    auto region = regionFactory
            .setPoolName("pool")
            .setCacheListener(std::shared_ptr<CacheListener>(new MyCacheListener()))
            .create("exampleRegion");
    region->registerAllKeys();
    region->put("1", "one");
    region->put("2", "two");
}
