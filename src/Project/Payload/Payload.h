#pragma once

namespace Loki {

    class AnimationPayload :
        public RE::BSTEventSink<RE::BSAnimationGraphEvent> {

    public:
        static AnimationPayload* GetSingleton();

        auto ProcessEvent(const RE::BSAnimationGraphEvent* a_event, RE::BSTEventSource<RE::BSAnimationGraphEvent>* a_eventSource) -> RE::BSEventNotifyControl override;

    protected:
        AnimationPayload() = default;
        AnimationPayload(const AnimationPayload&) = delete;
        AnimationPayload(AnimationPayload&&) = delete;
        virtual ~AnimationPayload() = default;

        auto operator=(const AnimationPayload&)->AnimationPayload & = delete;
        auto operator=(AnimationPayload&&)->AnimationPayload & = delete;

    };

};