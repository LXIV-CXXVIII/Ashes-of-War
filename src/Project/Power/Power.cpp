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

    if (auto form = RE::TESForm::LookupByID(a_event->baseObject)) {
        if (form->IsWeapon()) {
            if (auto objectWEAP = form->As<RE::TESObjectWEAP>()) {
                if (auto dhandle = RE::TESDataHandler::GetSingleton()) {

                    for (auto idx : AshesOfWar::_enchPowMap) {

                        auto GetEnchant = [objectWEAP]() -> RE::EnchantmentItem* {
                            auto formEnchant = objectWEAP->formEnchanting;
                            return formEnchant ? formEnchant : nullptr;
                        };

                        auto enchantment = dhandle->LookupForm<RE::EnchantmentItem>(idx.second.first, idx.first.c_str());
                        auto spell = dhandle->LookupForm<RE::SpellItem>(idx.second.second, idx.first.c_str());

                        if (a_event->equipped) {
                            if (auto IncomingEnchant = GetEnchant()) {
                                if (enchantment && IncomingEnchant->formID == enchantment->formID) {
                                    a_event->actor.get()->As<RE::Actor>()->AddSpell(spell);
                                    break;
                                }
                            }
                        }
                        else {
                            if (auto incomingEnchant = GetEnchant(); enchantment) {
                                if (enchantment && incomingEnchant->formID == enchantment->formID) {
                                    a_event->actor.get()->As<RE::Actor>()->RemoveSpell(spell);
                                    break;
                                }
                            }
                        }

                    }

                } else { logger::info("ERROR: Invalid TESDataHandler ptr"); }
            } else { logger::info("ERROR: Invalid TESObjectWEAP ptr"); }
        }
    }
    return RE::BSEventNotifyControl::kContinue;
}