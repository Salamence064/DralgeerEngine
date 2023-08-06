#include <Dralgeer/window.h>

namespace Dralgeer {
    namespace EventSystem {
        void notify(EventType event) {
            Window::onNotify(event);
        };
    }
}
