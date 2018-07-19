#include "ButtonPCF.h"

namespace simpleButton {
    ButtonPCF::ButtonPCF() {
        enable();
    }

    ButtonPCF::ButtonPCF(Button* button, PCF857x* pcf, uint8_t pin) {
        this->button     = button;
        this->pcf        = pcf;
        this->button_pin = pin;
        enable();
    }

    ButtonPCF::~ButtonPCF() {}

    void ButtonPCF::enable() {
        button_enabled = true;

        if (button && pcf && (button_pin < 8)) {
            button->enable();
            button_setup = true;

            pcf->write(button_pin, button->isInverted());
            update();
            reset();
        }
    }

    void ButtonPCF::disable() {
        button_enabled = false;

        if (button) button->disable();
    }

    void ButtonPCF::reset() {
        if (button) button->reset();
    }

    void ButtonPCF::push() {
        if (button) button->push();
    }

    void ButtonPCF::release() {
        if (button) button->release();
    }

    void ButtonPCF::click() {
        if (button) button->click();
    }

    void ButtonPCF::click(uint32_t time) {
        if (button) button->click(time);
    }

    bool ButtonPCF::read() {
        if (button_enabled && button_setup) {
            bool curState = pcf->read(button_pin) != 0;

            if (button->isInverted()) curState = !curState;
            return curState;
        }

        return false;
    }

    void ButtonPCF::update() {
        if (button_enabled && button_setup) {
            update(read());
        }
    }

    void ButtonPCF::update(bool state) {
        if (button) button->update(state);
    }

    bool ButtonPCF::isEnabled() {
        return button_enabled;
    }

    bool ButtonPCF::isSetup() {
        return button_setup;
    }

    bool ButtonPCF::getState() {
        return button ? button->getState() : false;
    }

    int ButtonPCF::getClicks() {
        return button ? button->getClicks() : 0;
    }

    int ButtonPCF::getPushTime() {
        return button ? button->getPushTime() : 0;
    }

    bool ButtonPCF::pushed() {
        return button ? button->pushed() : false;
    }

    bool ButtonPCF::released() {
        return button ? button->released() : false;
    }

    bool ButtonPCF::clicked() {
        return button ? button->clicked() : false;
    }

    bool ButtonPCF::clicked(uint32_t minPushTime) {
        return button ? button->clicked(minPushTime) : false;
    }

    bool ButtonPCF::doubleClicked() {
        return button ? button->doubleClicked() : false;
    }

    bool ButtonPCF::doubleClicked(uint32_t minPushTime) {
        return button ? button->doubleClicked(minPushTime) : false;
    }

    bool ButtonPCF::doubleClicked(uint32_t minPushTime, uint32_t timeSpan) {
        return button ? button->doubleClicked(minPushTime, timeSpan) : false;
    }

    bool ButtonPCF::holded() {
        return button ? button->holded() : false;
    }

    bool ButtonPCF::holded(uint32_t interval) {
        return button ? button->holded(interval) : false;
    }
}