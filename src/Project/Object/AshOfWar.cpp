#include "AshOfWar.h"
#include "Project/AshesOfWar.h"

void Loki::AshOfWar::DoAshOfWar(const RE::Actor* a_actor) {
    RE::Actor* actor = (RE::Actor*)a_actor;

    if (actor->GetActorValue(RE::ActorValue::kStamina) < _properties.staminaCost ||
        actor->GetActorValue(RE::ActorValue::kMagicka) < _properties.magickaCost) {
        logger::info("Failed requirement check");
        //TODO: TrueHUD Bars flash
        return;
    }

    actor->RestoreActorValue(RE::ACTOR_VALUE_MODIFIER::kDamage, RE::ActorValue::kMagicka, _properties.magickaCost * -1.00f);
    actor->RestoreActorValue(RE::ACTOR_VALUE_MODIFIER::kDamage, RE::ActorValue::kStamina, _properties.staminaCost * -1.00f);

    float effectiveness = 0;
    switch (_properties.type) {

        case Properties::DamageType::kElemental: {
            for (auto idx : actor->selectedPower->As<RE::SpellItem>()->effects) {
                for (auto ind : AshesOfWar::_effectVec) {
                    if (idx->baseEffect->formID == ind->formID) {
                        effectiveness = idx->effectItem.magnitude;
                    }
                }
            }
            break;
        }

        case Properties::DamageType::kPhysical: {
            if (auto object = actor->GetAttackingWeapon()->object; object) {
                if (auto weapon = object->As<RE::TESObjectWEAP>(); weapon) {
                    effectiveness = weapon->GetAttackDamage() * actor->GetActorValue(RE::ActorValue::kAttackDamageMult);
                }
            }
            break;
        }

    }
    for (auto spell : _properties.spells) {
        actor->GetMagicCaster(RE::MagicSystem::CastingSource::kInstant)->
            Cast(spell, false, actor, effectiveness, false, 0.0f, 0);
    }
    //

}