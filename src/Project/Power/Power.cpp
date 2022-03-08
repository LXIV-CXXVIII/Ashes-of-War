#include "Power.h"
#include "Project/AshesOfWar.h"

Loki::GiveAOWPower* Loki::GiveAOWPower::GetSingleton() {
    static GiveAOWPower singleton;
    return &singleton;
}

auto Loki::GiveAOWPower::ProcessEvent(const RE::TESEquipEvent* a_event, RE::BSTEventSource<RE::TESEquipEvent>* a_eventSource) -> RE::BSEventNotifyControl {
    if (!a_event) {
        return RE::BSEventNotifyControl::kContinue;
    }
    if (!a_event->actor) {
        return RE::BSEventNotifyControl::kContinue;
    }

    if (auto form = RE::TESForm::LookupByID(a_event->baseObject); form) {
        if (form->IsWeapon()) {
            if (auto objectWEAP = form->As<RE::TESObjectWEAP>(); objectWEAP) {
                if (a_event->equipped) {
                    for (auto idx : AshOfWar::_enchSpellMap) {
                        if (objectWEAP->formEnchanting->data.baseEnchantment->formID == idx.first->formID) {
                            a_event->actor.get()->As<RE::Actor>()->AddSpell(idx.second);
                        }
                    }
                } else {
                    for (auto idx : AshOfWar::_enchSpellMap) {
                        if (objectWEAP->formEnchanting->data.baseEnchantment->formID == idx.first->formID) {
                            a_event->actor.get()->As<RE::Actor>()->RemoveSpell(idx.second);
                        }
                    }
                }
            } else {
                logger::info("Invalid TESObjectWEAP pointer");
            }
        }
    }
    return RE::BSEventNotifyControl::kContinue;
}