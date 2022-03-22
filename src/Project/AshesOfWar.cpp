#include "AshesOfWar.h"

void Loki::AshesOfWar::InstallMGEFEventSink() {
    auto sourceHolder = RE::ScriptEventSourceHolder::GetSingleton();
    if (sourceHolder) { sourceHolder->AddEventSink(PlayAOWAnimation::GetSingleton()); }
}

void Loki::AshesOfWar::InstallEquipEventSink() {
    auto sourceHolder = RE::ScriptEventSourceHolder::GetSingleton();
    if (sourceHolder) { sourceHolder->AddEventSink(GiveAOWPower::GetSingleton()); }
}

void Loki::AshesOfWar::AssignMaps() {

    constexpr auto path = L"Data/SKSE/Plugins/Ashes";
    constexpr auto ext = L".toml";

    auto dataHandle = RE::TESDataHandler::GetSingleton();

    const auto readToml = [&](std::filesystem::path path) {
        logger::info("Reading {}...", path.string());
        try {
            const auto tbl = toml::parse_file(path.c_str());
            auto& arr = *tbl.get_as<toml::array>("Spell");

            for (auto&& elem : arr) {
                auto& spellTable = *elem.as_table();

                auto eff = spellTable["EffectFormID"].value<RE::FormID>();
                  logger::info("Effect Form ID -> {0:#x}", *eff);
                auto ench = spellTable["EnchantmentFormID"].value<RE::FormID>();
                  logger::info("Enchantment Form ID -> {0:#x}", *ench);
                auto pow = spellTable["PowerFormID"].value<RE::FormID>();
                  logger::info("Power Form ID -> {0:#x}", *pow);
                    std::pair<RE::FormID, RE::FormID> pair = { *ench, *pow };
                auto esp = spellTable["EspName"].value<std::string>();
                  logger::info("EspName -> {}", *esp);

                _effectMap.insert_or_assign(*eff, *esp);
                _enchPowMap.insert_or_assign(*esp, pair);
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

    logger::info("Reading all .toml files...");

    if (std::filesystem::is_directory(path)) {
        for (const auto& file : std::filesystem::directory_iterator(path)) {
            if (std::filesystem::is_regular_file(file) && file.path().extension() == ext) {
                readToml(file.path());
            }
        }
    }

    logger::info("Finished reading all .toml files");

}