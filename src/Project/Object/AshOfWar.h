#pragma once
#include <toml++/toml.h>

namespace Loki {

    class AshOfWar {

    public:
        struct Properties {
            enum DamageType : uint32_t {
                kPhysical = 0,
                kElemental,
            };

            std::vector<RE::SpellItem*> spells;
            DamageType                  type;
            float                       magickaCost;
            float                       staminaCost;
        };

        AshOfWar(std::vector<RE::SpellItem*> a_spells, uint32_t a_type, float a_magCost, float a_stamCost) {
            _properties.spells = a_spells;
            _properties.type = (Properties::DamageType)a_type;
            _properties.magickaCost = a_magCost;
            _properties.staminaCost = a_stamCost;
        }

        void DoAshOfWar(const RE::Actor* a_actor);

    private:
        Properties _properties;

    protected:

    };

};