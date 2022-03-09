#include "Payload.h"
#include "Project/AshesOfWar.h"

Loki::AnimationPayload* Loki::AnimationPayload::GetSingleton() {
    static AnimationPayload singleton;
    return &singleton;
}

auto Loki::AnimationPayload::ProcessEvent(const RE::BSAnimationGraphEvent* a_event, RE::BSTEventSource<RE::BSAnimationGraphEvent>* a_eventSource) -> RE::BSEventNotifyControl {
    if (a_event->tag == NULL || a_event->payload == NULL) {
        return RE::BSEventNotifyControl::kContinue;
    }
    if (a_event->tag == "AOW_Start") {
        auto aow = AshesOfWar::payloadMap.find((std::string)a_event->payload);
        if (aow != AshesOfWar::payloadMap.end()) {
            aow->second->DoAshOfWar(a_event->holder->As<RE::Actor>());
        }
    }
    return RE::BSEventNotifyControl::kContinue;
}