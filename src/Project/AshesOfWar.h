#pragma once
#include "Project/Animation/Animation.h"
#include "Project/AoWObj/AshOfWarObj.h"
#include "Project/Payload/Payload.h"
#include "Project/Power/Power.h"

#include <toml++/toml.h>

namespace Loki {

	class AshesOfWar : 
        public PlayAOWAnimation,
        public GiveAOWPower,
        public AnimationPayload {
	
	public:
        AshesOfWar() {
            constexpr auto path = L"Data/SKSE/Plugins/AshesOfWar";
            constexpr auto ext = L".toml";
            constexpr auto basecfg = L"Data/SKSE/Plugins/AshesOfWar/loki_AshesOfWar.toml";

            auto dataHandle = RE::TESDataHandler::GetSingleton();

            const auto readToml = [&](std::filesystem::path path) {
                logger::info("Reading {}...", path.string());
                try {
                    const auto tbl = toml::parse_file(path.c_str());
                    auto& arr = *tbl.get_as<toml::array>("AshOfWar");

                    for (auto&& elem : arr) {
                        auto& aowTable = *elem.as_table();

                        auto payload = aowTable["Payload"].value<std::string>();
                          logger::info("Payload annotation -> {}", *payload);

                        auto spells = aowTable["SpellFormIDs"].as_array();
                        std::vector<RE::SpellItem*> spellVector = {};
                        if (spells) {
                            for (auto& spell : *spells) {
                                logger::info("Spell Form ID -> {x}", *spell.value<RE::FormID>());
                                if (auto spellItem = RE::TESForm::LookupByID(*spell.value<RE::FormID>())->As<RE::SpellItem>()) {
                                    spellVector.push_back(spellItem);
                                }
                            }
                        }
                        
                        auto damageType = aowTable["DamageType"].value<uint32_t>();
                          logger::info("Damage Type -> {}", *damageType);
                        auto magickaCost = aowTable["MagickaCost"].value<float>();
                          logger::info("Magicka Cost -> {}", *magickaCost);
                        auto staminaCost = aowTable["StaminaCost"].value<float>();
                          logger::info("Stamina Cost -> {}", *staminaCost);

                        AshOfWar* aow = new AshOfWar(spellVector, *damageType, *magickaCost, *staminaCost);

                        payloadMap.insert_or_assign(*payload, aow);
                    }
                    logger::info("Successfully read {}...", path.string());
                }
                catch (const toml::parse_error& e) {
                    std::ostringstream ss;
                    ss << "Error parsing file \'" << *e.source().path << "\':\n"
                        << '\t' << e.description() << '\n'
                        << "\t\t(" << e.source().begin << ')';
                    logger::error(ss.str());
                }
                catch (const std::exception& e) {
                    logger::error("{}", e.what());
                }
                catch (...) {
                    logger::error("Unknown failure"sv);
                }
            };

            logger::info("Reading _AshesOfWar.toml files...");

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

            logger::info("Finished reading _AshesOfWar.toml files");

            AssignMaps();

        }
        virtual ~AshesOfWar() {
        
        }
        static AshesOfWar* GetSingleton() {
            static AshesOfWar singleton;// = new AshOfWar(); apparently how it is now just runs the ctor because
            return &singleton;        // who even knows anymore. I didn't know this. Did you? 
        }

        void InstallMGEFEventSink();
        void InstallEquipEventSink();
        void InstallAnimEventSink();
        static void AssignMaps();

        static inline std::unordered_map<std::string, AshOfWar*> payloadMap = {};

        static inline std::vector<RE::EffectSetting*> _effectVec;
        static inline std::unordered_map<RE::EnchantmentItem*, RE::SpellItem*> _enchSpellMap;

	private:

	protected:
	
	};

};