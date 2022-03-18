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
                if (auto dhandle = RE::TESDataHandler::GetSingleton(); dhandle) {
                    if (a_event->equipped) {
                        for (auto idx : AshesOfWar::_enchPowMap) {
                            if (auto enchantment = dhandle->LookupForm<RE::EnchantmentItem>(idx.second.first, idx.first.c_str()); enchantment) {
                                if (auto spell = dhandle->LookupForm<RE::SpellItem>(idx.second.second, idx.first.c_str()); spell) {

                                    auto baseEnchantment = [objectWEAP]() -> RE::EnchantmentItem* {
                                        auto formEnchant = objectWEAP->formEnchanting;
                                        if (!formEnchant) { return nullptr; }
                                        auto baseEnchant = formEnchant->data.baseEnchantment;
                                        return baseEnchant ? baseEnchant : nullptr;
                                    }();
                                    if (baseEnchantment) {
                                        if (baseEnchantment->formID == enchantment->formID) {
                                            a_event->actor.get()->As<RE::Actor>()->AddSpell(spell);
                                            break;
                                        }
                                    }

                                }
                            }
                        }
                    } 
                    else {
                        for (auto idx : AshesOfWar::_enchPowMap) {
                            if (auto enchantment = dhandle->LookupForm<RE::EnchantmentItem>(idx.second.first, idx.first.c_str()); enchantment) {
                                if (auto spell = dhandle->LookupForm<RE::SpellItem>(idx.second.second, idx.first.c_str()); spell) {

                                    auto baseEnchantment = [objectWEAP]() -> RE::EnchantmentItem* {
                                        auto formEnchant = objectWEAP->formEnchanting;
                                        if (!formEnchant) { return nullptr; }
                                        auto baseEnchant = formEnchant->data.baseEnchantment;
                                        return baseEnchant ? baseEnchant : nullptr;
                                    }();
                                    if (baseEnchantment) {
                                        if (baseEnchantment->formID == enchantment->formID) {
                                            a_event->actor.get()->As<RE::Actor>()->RemoveSpell(spell);
                                            break;
                                        }
                                    }

                                }
                            }
                        }
                    }
                }
            } 
            else {
                logger::info("Invalid TESObjectWEAP pointer");
            }
        }
    }
    return RE::BSEventNotifyControl::kContinue;
}