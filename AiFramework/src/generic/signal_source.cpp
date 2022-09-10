#include <generic/signal_source.hpp>
#include <generic/logger.hpp>

using namespace ai_framework;

CLogger _signal_logger("SignalSource");

void SignalSource::listen(std::string_view type, SignalDelegateFunc listener) {
    auto l = SignalDelegate(new SignalDelegateFunc(listener));
    signal_delegates[type.data()].push_back(l);
    _signal_logger.log(LoggerLevel::DEBUG, "Registered listener for '%s'!", type.data());
}

void SignalSource::dismiss(std::string_view type, SignalDelegate listener) {
    auto &delegates = signal_delegates[type.data()];
    auto x = std::find(delegates.begin(), delegates.end(), listener);

    if (x != delegates.end())
        delegates.erase(x);
}

void SignalSource::emit(std::string_view type, void *data) {
    //_signal_logger.log(LoggerLevel::DEBUG, "Dispatching signal '%s'...", type.data());

    if (!signal_delegates.contains(type.data()))
        return;

    auto listeners = signal_delegates[type.data()];

    //_signal_logger.log(LoggerLevel::DEBUG, "Dispatching to %zi listeners!", listeners.size());

    for (auto e : listeners)
        (*e)(data);
}