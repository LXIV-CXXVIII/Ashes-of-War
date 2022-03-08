#include "AshOfWarObj.h"

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
                if (idx->baseEffect->formID == 0x0) {
                    effectiveness = idx->effectItem.magnitude;
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

}

void Loki::AshOfWar::AssignMaps() {
    constexpr auto path = L"Data/SKSE/Plugins/Spells";
    constexpr auto ext = L".toml";
    constexpr auto basecfg = L"Data/SKSE/Plugins/Spells/loki_Spells.toml";

    auto dataHandle = RE::TESDataHandler::GetSingleton();

    const auto readToml = [&](std::filesystem::path path) {
        logger::info("Reading {}...", path.string());
        try {
            const auto tbl = toml::parse_file(path.c_str());
            auto& arr = *tbl.get_as<toml::array>("spells");

            for (auto&& elem : arr) {
                auto& spellTable = *elem.as_table();

                auto eff = spellTable["EffectFormID"].value<RE::FormID>();
                logger::info("Effect Form ID -> {}", *eff);
                if (auto effect = RE::TESForm::LookupByID(*eff)->As<RE::EffectSetting>()) {
                    _effectVec.push_back(effect);
                }
                auto ench = spellTable["EnchantmentFormID"].value<RE::FormID>();
                logger::info("Enchantment Form ID -> {}", *ench);
                auto pow = spellTable["PowerFormID"].value<RE::FormID>();
                logger::info("Power Form ID -> {}", *pow);
                if (auto enchantment = RE::TESForm::LookupByID(*eff)->As<RE::EnchantmentItem>(); enchantment) {
                    if (auto power = RE::TESForm::LookupByID(*pow)->As<RE::SpellItem>(); power) {
                        _enchSpellMap.insert_or_assign(enchantment, power);
                    }
                }
            }
            logger::info("Successfully read {}...", path.string());

        } catch (const toml::parse_error& e) {
            std::ostringstream ss;
            ss << "Error parsing file \'" << *e.source().path << "\':\n"
                << '\t' << e.description() << '\n'
                << "\t\t(" << e.source().begin << ')';
            logger::error(ss.str());
        } catch (const std::exception& e) {
            logger::error("{}", e.what());
        } catch (...) {
            logger::error("Unknown failure"sv);
        }
    };

    logger::info("Reading .toml files...");

    auto baseToml = std::filesystem::path(basecfg);
    readToml(baseToml);
    if (std::filesystem::is_directory(path)) {
        for (const auto& file : std::filesystem::directory_iterator(path)) {
            if (std::filesystem::is_regular_file(file) && file.path().extension() == ext) {
                auto filePath = file.path();
                if (filePath != basecfg) {
                    readToml(filePath);
                }
            }
        }
    }

    logger::info("Finished reading .toml files");
}