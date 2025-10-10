#include "HotKeyController.hpp"

#include <core/HotKeyEntry.hpp>

#include "HotKeyAdapter.hpp"

struct HotKeyController::Impl
{
    HotKeyAdapter adapter;
};

HotKeyController::HotKeyController()
    : _impl{std::make_unique<Impl>()}
{
    QObject::connect(&_impl->adapter, &HotKeyAdapter::actionTriggered, this, [this](const Where::HotKey::Action action) {
        using namespace Where::HotKey;

        switch (action) {
        case Where::HotKey::Action::NONE:
            return;
        case Where::HotKey::Action::SHOW_SEARCH_BAR:
            emit showSearchBar();
            return;
        }
    });

    _impl->adapter.start();
}

HotKeyController::~HotKeyController()
{

}
