#include "SimpleButton.h"

namespace simpleButton {
    Button::Button() {
        enable();
    }

    Button::Button(uint8_t pin) {
        this->button_pin = pin;
        enable();
    }

    Button::Button(uint8_t pin, bool inverted) {
        this->button_pin      = pin;
        this->button_inverted = inverted;
        enable();
    }

    Button::~Button() {}

    void Button::enable() {
        button_enabled = true;

        if ((button_pin < 255) && !button_setup) {
            pinMode(button_pin, INPUT);
            button_setup = true;
        }
    }

    void Button::disable() {
        button_enabled = false;
    }

    void Button::reset() {
        pushedFlag   = false;
        releasedFlag = false;
        holdFlag     = false;
    }

    void Button::push() {
        if (!state) {
            state = true;

            prevPushTime    = pushTime;
            prevReleaseTime = millis();
            pushedFlag      = true;

            pushTime = millis();
            holdTime = millis();
            holdFlag = false;
        }
    }

    void Button::release() {
        if (state) {
            state        = false;
            releasedFlag = true;
        }
    }

    void Button::click() {
        click(defaultMinPushTime);
    }

    void Button::click(uint32_t time) {
        push();
        pushTime        = millis() - time;
        prevReleaseTime = millis() - defaultMinReleaseTime;
        release();
    }

    uint16_t Button::read() {
        bool currentState = false;

        if (button_enabled && button_setup) {
            currentState = digitalRead(button_pin);

            if (button_inverted) currentState = !currentState;
        }

        return (uint16_t)currentState;
    }

    void Button::update() {
        if (button_enabled && button_setup && (millis() - updateTime >= updateInterval)) {
            update(read());
        }
    }

    void Button::update(uint16_t state) {
        updateTime = millis();

        if (state > 0) push();
        else release();
    }

    bool Button::isInverted() {
        return button_inverted;
    }

    bool Button::isEnabled() {
        return button_enabled;
    }

    bool Button::isSetup() {
        return button_setup;
    }

    uint16_t Button::getState() {
        return state;
    }

    int Button::getClicks() {
        return (int)clicks;
    }

    int Button::getPushTime() {
        return (int)(millis() - pushTime);
    }

    bool Button::pushed() {
        if (pushedFlag) {
            pushedFlag = false;
            return true;
        }
        return false;
    }

    bool Button::released() {
        if (releasedFlag) {
            releasedFlag = false;
            return true;
        }
        return false;
    }

    bool Button::clicked() {
        return clicked(defaultMinPushTime);
    }

    bool Button::clicked(uint32_t minPushTime) {
        return clicked(minPushTime, defaultMinReleaseTime);
    }

    bool Button::clicked(uint32_t minPushTime, uint32_t minReleaseTime) {
        bool notHolding     = !holdFlag;
        bool minTime        = millis() - pushTime >= minPushTime;
        bool releaseTimeout = millis() - prevReleaseTime >= minReleaseTime;

        if (notHolding && minTime && releaseTimeout) {
            if (released()) {
                clicks++;
                return true;
            }
        }

        return false;
    }

    bool Button::doubleClicked() {
        return doubleClicked(defaultMinPushTime);
    }

    bool Button::doubleClicked(uint32_t minPushTime) {
        return doubleClicked(minPushTime, defaultTimeSpan);
    }

    bool Button::doubleClicked(uint32_t minPushTime, uint32_t timeSpan) {
        return doubleClicked(minPushTime, defaultMinReleaseTime, timeSpan);
    }

    bool Button::doubleClicked(uint32_t minPushTime, uint32_t minReleaseTime, uint32_t timeSpan) {
        bool wasPrevClicked = prevReleaseTime - prevPushTime >= minPushTime;
        bool inTimeSpan     = millis() - prevPushTime <= timeSpan;
        bool releaseTimeout = millis() - prevReleaseTime >= minReleaseTime;

        if (wasPrevClicked && inTimeSpan && releaseTimeout) {
            if (clicked(minPushTime)) {
                pushTime = 0;
                return true;
            }
        }

        return false;
    }

    bool Button::held() {
        return held(defaultHoldInterval);
    }

    bool Button::held(uint32_t interval) {
        if (getState() && (millis() - holdTime >= interval)) {
            holdTime = millis();
            holdFlag = true;
            return true;
        }
        return false;
    }
}