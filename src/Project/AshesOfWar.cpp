#include "AshesOfWar.h"

void Loki::AshesOfWar::InstallMGEFEventSink() {
    auto sourceHolder = RE::ScriptEventSourceHolder::GetSingleton();
    if (sourceHolder) { sourceHolder->AddEventSink(PlayAOWAnimation::GetSingleton()); }
}

void Loki::AshesOfWar::InstallEquipEventSink() {
    auto sourceHolder = RE::ScriptEventSourceHolder::GetSingleton();
    if (sourceHolder) { sourceHolder->AddEventSink(GiveAOWPower::GetSingleton()); }
}

void Loki::AshesOfWar::InstallAnimEventSink() {
    //auto sourceHolder = RE::ScriptEventSourceHolder::GetSingleton();
    //if (sourceHolder) { sourceHolder->AddEventSink(AnimationPayload::GetSingleton()); }

    auto player = RE::PlayerCharacter::GetSingleton();
    RE::BSTSmartPointer<RE::BSAnimationGraphManager> animationGraphManagerPtr;
    if (player->GetAnimationGraphManager(animationGraphManagerPtr))
    {
        RE::BShkbAnimationGraph* animationGraph = animationGraphManagerPtr->graphs[animationGraphManagerPtr->activeGraph].get();
        animationGraph->AddEventSink(AnimationPayload::GetSingleton());
    }
}

void Loki::AshesOfWar::AssignMaps() {

    constexpr auto path = L"Data/SKSE/Plugins/Spells";
    constexpr auto ext = L".toml";
    constexpr auto basecfg = L"Data/SKSE/Plugins/Spells/loki_Spells.toml";

    auto dataHandle = RE::TESDataHandler::GetSingleton();

    const auto readToml = [&](std::filesystem::path path) {
        logger::info("Reading {}...", path.string());
        try {
            const auto tbl = toml::parse_file(path.c_str());
            auto& arr = *tbl.get_as<toml::array>("Spell");

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

    logger::info("Reading _Spells.toml files...");

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

    logger::info("Finished reading _Spells.toml files");

}