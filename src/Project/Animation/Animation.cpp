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
    if (auto target = a_event->target.get()) {
        if (auto actor = target->As<RE::Actor>()) {
            for (auto idx : AshesOfWar::_effectMap) {
                if (auto dhandle = RE::TESDataHandler::GetSingleton()) {
                    if (auto effect = dhandle->LookupForm<RE::EffectSetting>(idx.first, idx.second); effect) {
                        if (a_event->magicEffect == effect->formID) {
                            actor->NotifyAnimationGraph("AOW_Start");
                            break;
                        }
                    }
                }
            }
        }
        else {
            logger::info("Invalid actor ptr, TESObjectREFR FormID -> {}", target->formID);
        }
    }

    return RE::BSEventNotifyControl::kContinue;
}