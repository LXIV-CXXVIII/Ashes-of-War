#include "Power.h"
#include "Project/AshesOfWar.h"

RE::EnchantmentItem* Loki::InventoryManager::GetExtraDataImpl(RE::InventoryEntryData* a_1) {

    using func_t = decltype (Loki::InventoryManager::GetExtraDataImpl);
    REL::Relocation<func_t> func { REL::ID(15788) };
    return func(a_1);

}

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
    /**
    auto inv = a_event->actor->GetInventory();


    for (auto idx : *(inv.begin()->second.second->extraLists)) {
        auto type = idx->GetByType(RE::ExtraDataType::kEnchantment);
        auto huh = type->GetType();

        RE::EnchantmentItem* item;
        if (auto dataHandle = RE::TESDataHandler::GetSingleton()) {
            item = dataHandle->LookupForm<RE::EnchantmentItem>(0xD62, "loki_POISE.esp");
        }
        

        for (auto a = idx->begin(); a != idx->end(); ++a); {
            
        }
    }
    */
    

    if (auto form = RE::TESForm::LookupByID(a_event->baseObject)) {
        if (form->IsWeapon()) {
            if (auto objectWEAP = form->As<RE::TESObjectWEAP>()) {
                if (auto dhandle = RE::TESDataHandler::GetSingleton()) {

                    for (auto idx : AshesOfWar::_enchPowMap) {

                        auto GetEnchant = [objectWEAP]() -> RE::EnchantmentItem* {
                            auto formEnchant = objectWEAP->formEnchanting;
                            return formEnchant ? formEnchant : nullptr;
                        };

                        objectWEAP->formEnchanting->effects.begin();
                        
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
                            if (auto incomingEnchant = GetEnchant()) {
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