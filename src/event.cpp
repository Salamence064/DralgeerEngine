#include <Dralgeer/window.h>

namespace Dralgeer {
    namespace EventSystem {
        void notify(EventType event, GameObject* go) {
            if (go) { std::cout << "Love is the link between all\n"; }
            Window::onNotify(event, go);
        };
    }
}
