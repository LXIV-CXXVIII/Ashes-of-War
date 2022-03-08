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
        for (auto idx : AshOfWar::_effectVec) {
            if (a_event->magicEffect == idx->formID) {
                actor->NotifyAnimationGraph("dw_AOW_Start");
            } else if (a_event->magicEffect == idx->formID) {
                actor->NotifyAnimationGraph("h2h_AOW_Start");
            } else if (a_event->magicEffect == idx->formID) {
                actor->NotifyAnimationGraph("1hm_AOW_Start");
            } else if (a_event->magicEffect == idx->formID) {
                actor->NotifyAnimationGraph("1hw_AOW_Start");
            } else if (a_event->magicEffect == idx->formID) {
                actor->NotifyAnimationGraph("2hm_AOW_Start");
            } else if (a_event->magicEffect == idx->formID) {
                actor->NotifyAnimationGraph("2hw_AOW_Start");
            }
        }
        /*
        dw_AOW_Start
        h2h_AOW_Start
        1hm_AOW_Start
        1hw_AOW_Start
        2hm_AOW_Start
        2hw_AOW_Start
        */
    }

    return RE::BSEventNotifyControl::kContinue;
}