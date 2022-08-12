#include <generic/signal_source.hpp>

using namespace ai_framework;

void SignalSource::listen(std::string_view type, SignalDelegateFunc listener) {
    auto l = SignalDelegate(new SignalDelegateFunc(listener));
    signal_delegates[type.data()].push_back(l);
    printf("Registered listener for '%s'!\n", type.data());
}

void SignalSource::dismiss(std::string_view type, SignalDelegate listener) {
    auto &delegates = signal_delegates[type.data()];
    auto x = std::find(delegates.begin(), delegates.end(), listener);

    if (x != delegates.end())
        delegates.erase(x);
}

void SignalSource::emit(std::string_view type, void *data) {
    //printf("Dispatching signal '%s'...\n", type.data());

    if (!signal_delegates.contains(type.data()))
        return;

    auto listeners = signal_delegates[type.data()];

    //printf("Dispatching to %zi listeners!\n", listeners.size());

    for (auto e : listeners)
        (*e)(data);
}