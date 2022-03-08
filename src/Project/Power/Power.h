#pragma once

namespace Loki {

    class GiveAOWPower :
        public RE::BSTEventSink<RE::TESEquipEvent> {

    public:
        static GiveAOWPower* GetSingleton();

        auto ProcessEvent(const RE::TESEquipEvent* a_event, RE::BSTEventSource<RE::TESEquipEvent>* a_eventSource)->RE::BSEventNotifyControl override;

    protected:
        GiveAOWPower() = default;
        GiveAOWPower(const GiveAOWPower&) = delete;
        GiveAOWPower(GiveAOWPower&&) = delete;
        virtual ~GiveAOWPower() = default;

        auto operator=(const GiveAOWPower&)->GiveAOWPower & = delete;
        auto operator=(GiveAOWPower&&)->GiveAOWPower & = delete;
    };

};