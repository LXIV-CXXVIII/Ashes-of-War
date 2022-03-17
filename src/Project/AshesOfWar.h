#pragma once
#include "Project/Animation/Animation.h"
//#include "Project/Object/AshOfWar.h"
//#include "Project/Payload/Payload.h"
#include "Project/Power/Power.h"

#include <toml++/toml.h>

namespace Loki {

	class AshesOfWar : 
        public PlayAOWAnimation,
        public GiveAOWPower {
	
	public:
        AshesOfWar() {

            AssignMaps();

        }
        virtual ~AshesOfWar() {
        
        }
        static AshesOfWar* GetSingleton() {
            static AshesOfWar singleton;// = new AshOfWar(); apparently how it is now just runs the ctor because
            return &singleton;        // who even knows anymore. I didn't know this. Did you? 
        }
        void AssignMaps();

        void InstallMGEFEventSink();
        void InstallEquipEventSink();

        static inline std::vector<RE::EffectSetting*> _effectVec;
        static inline std::unordered_map<RE::EnchantmentItem*, RE::SpellItem*> _enchSpellMap;

	private:

	protected:
	
	};

};