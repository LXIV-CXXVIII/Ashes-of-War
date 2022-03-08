#include "Animation.h"
#include "Project/AshesOfWar.h"

Loki::PlayAOWAnimation* Loki::PlayAOWAnimation::GetSingleton() {
    static PlayAOWAnimation singleton;
    return &singleton;
}

auto Loki::PlayAOWAnimation::ProcessEvent(const RE::TESMagicEffectApplyEvent* a_event, RE::BSTEventSource<RE::TESMagicEffectApplyEvent>* a_eventSource) -> RE::BSEventNotifyControl {
    if (!a_event) {
        return RE::BSEventNotifyControl::kContinue;
    }

    auto ptr = Loki::AshesOfWar::GetSingleton();
    if (auto actor = a_event->target.get()->As<RE::Actor>(); actor) {
        for (auto idx : AshesOfWar::_effectVec) {
            if (a_event->magicEffect == idx->formID) {
                actor->NotifyAnimationGraph("AOW_Start");
            }
        }
    }

    return RE::BSEventNotifyControl::kContinue;
}