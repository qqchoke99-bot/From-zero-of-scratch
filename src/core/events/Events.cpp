#include <cameraoverhaul/events/EventBus.hpp>

namespace cameraoverhaul::events {

EventBus& bus() {
    static EventBus instance;
    return instance;
}

}
