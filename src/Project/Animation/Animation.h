#pragma once

namespace Loki {

    class PlayAOWAnimation :
        public RE::BSTEventSink<RE::TESMagicEffectApplyEvent> {

    public:
        static PlayAOWAnimation* GetSingleton();

        auto ProcessEvent(const RE::TESMagicEffectApplyEvent* a_event, RE::BSTEventSource<RE::TESMagicEffectApplyEvent>* a_eventSource) -> RE::BSEventNotifyControl override;

    protected:
        PlayAOWAnimation() = default;
        PlayAOWAnimation(const PlayAOWAnimation&) = delete;
        PlayAOWAnimation(PlayAOWAnimation&&) = delete;
        virtual ~PlayAOWAnimation() = default;

        auto operator=(const PlayAOWAnimation&)->PlayAOWAnimation & = delete;
        auto operator=(PlayAOWAnimation&&)->PlayAOWAnimation & = delete;

    };

};