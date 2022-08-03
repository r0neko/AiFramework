#ifndef SINGLETON_HPP
#define SINGLETON_HPP

namespace ai_framework {
    /// <summary>
    /// Base Singleton templated class which exposes a static method that gets a global instance of the object.
    /// </summary>
    template <class T>
    struct Singleton {
        static T &instance() {
            static T _itx;
            return _itx;
        }
    };
} // namespace ai_framework::generic

#endif