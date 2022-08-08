#ifndef SIGNAL_SOURCE_HPP
#define SIGNAL_SOURCE_HPP

#include <framework_build.hpp>

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace ai_framework {
    /// <summary>
    /// A standard void function that has a void* as the only argument.
    /// </summary>
    using SignalDelegateFunc = std::function<void(void *)>;
    using SignalDelegate = std::shared_ptr<SignalDelegateFunc>;

    /// <summary>
    /// An interface that can be implemented by classes in order to receive events that can be listened.
    /// </summary>
    struct AI_API SignalSource {
        /// <summary>
        /// Listens for a specific event type and calls the specified function when the event is dispatched.
        /// </summary>
        /// <param name="type">A string with the name of the event.</param>
        /// <param name="listener">A delegate listener function which will be called.</param>
        /// <param name="listener">A delegate listener function which will be called.</param>
        void listen(std::string_view type, SignalDelegateFunc listener);

        /// <summary>
        /// Removes the listener for the specific event type.
        /// </summary>
        /// <param name="type">A string with the name of the event.</param>
        /// <param name="listener">A delegate listener function which will be called.</param>
        void dismiss(std::string_view type, SignalDelegate listener);

      protected:
        /// <summary>
        /// Dispatch an event.
        /// </summary>
        /// <param name="type">A string with the name of the event.</param>
        /// <param name="data">A pointer to the properties passed.</param>
        void emit(std::string_view type, void *data);

      private:
        std::unordered_map<std::string, std::vector<SignalDelegate>> signal_delegates;
    };
} // namespace ai_framework

#endif