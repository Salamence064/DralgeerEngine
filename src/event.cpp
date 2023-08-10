#include <Dralgeer/window.h>

namespace Dralgeer {
    namespace EventSystem {
        void notify(EventType event, GameObject* go) {
            Window::onNotify(event, go);
        };
    }
}
