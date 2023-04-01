#ifndef CANFUNCTION_H
#define CANFUNCTION_H
// #pragma once

#include <stdint.h>

#include "CAN_common.h"
#include "CANObject.h"

class CANObject;

/******************************************************************************************************************************
 *
 * CANFunction base class: base class for all CAN functions
 *
 ******************************************************************************************************************************/
class CANFunctionBase
{
public:
    CANFunctionBase(CAN_function_id_t id,
                    CANObject *parent,
                    CAN_function_handler_t external_handler = nullptr,
                    CANFunctionBase *next_ok_function = nullptr,
                    CANFunctionBase *next_err_function = nullptr);
    virtual ~CANFunctionBase(){};

    bool operator==(const CANFunctionBase &other);
    bool operator!=(const CANFunctionBase &other);

    void set_id(CAN_function_id_t id);
    CAN_function_id_t get_id();

    void set_parent(CANObject *parent);
    CANObject *get_parent();

    // external handler
    // return value:
    //      true - the next_ok_function will be called after handler
    //      false - the next_err_function will be called after handler
    void set_external_handler(CAN_function_handler_t external_handler);
    CAN_function_handler_t get_external_handler();
    bool has_external_handler();

    void set_next_ok_function(CANFunctionBase *next_ok_function);
    CANFunctionBase *get_next_ok_function();
    bool has_next_ok_function();

    void set_next_err_function(CANFunctionBase *next_err_function);
    CANFunctionBase *get_next_err_function();
    bool has_next_err_function();

    // function state:
    // stopped - function is OFF, it doesn't work, doesn't send any error replay etc.
    //           for example: timer is stopped; event is suppressed
    // active  - function is working in normal mode
    void disable();
    void enable();
    bool is_active();
    CAN_function_state_t get_state();

    // function main handler
    bool process(CANFrame *can_frame = nullptr);

    // function type { responding, automatic, blended, indirect }
    // Responding type - activated if incoming CAN frame received
    // Automatic type - activated by CANObject.update() method
    // Blended type - hybrid of responding and automatic types; will be activated both by incoming CANFrame and by CANObject.update()
    // Indirect type - this function will never activated by CANFrames or CANObject.update(). It will be called by other functions only.
    bool is_responding_function();
    bool is_automatic_function();
    bool is_indirect_function();
    void set_type(CAN_function_type_t func_type);
    CAN_function_type_t get_type();

    static bool is_responding_by_func_id(CAN_function_id_t id);

protected:
    void _set_state(CAN_function_state_t state);

    // virtual method for correct and systematic comparison of derived classes
    // should be complement by derived class
    virtual bool _equals(CANFunctionBase const &other) const;

    // the default CANFunction handler, will be called if there is no external callback function was setted.
    // should be overrided by derived class
    // return value: see CAN_common.h
    virtual CAN_function_result_t _default_handler(CANFrame *can_frame = nullptr) { return CAN_RES_NONE; };

    // derived classes may override this method in case they need do something before or
    // after external handler call
    // if _before_external_handler() returns false then external handler will not be called
    virtual bool _before_external_handler() { return true; };
    // the return value of _after_external_handler() does not affect anything yet
    virtual bool _after_external_handler() { return true; };

    // fills frame with correct error data
    void _fill_error_can_frame(CANFrame &can_frame, pixel_error_codes_t error_code, uint8_t additional_error_code = 0);

private:
    // common properties
    CAN_function_id_t _id = CAN_FUNC_NONE;
    CAN_function_state_t _state = CAN_FS_STOPPED;
    CANObject *_parent = nullptr;
    CAN_function_type_t _type = CAN_FT_INDIRECT;

    // external function handler
    CAN_function_handler_t _external_handler = nullptr;

    // the next function is for the case when function handler returned true
    CANFunctionBase *_next_ok_function = nullptr;
    // the next function is for the case when function handler returned false
    CANFunctionBase *_next_err_function = nullptr;
};

/******************************************************************************************************************************
 *
 * CANFunctionTimerBase: class for timed messages
 *
 ******************************************************************************************************************************/
class CANFunctionTimerBase : public CANFunctionBase
{
public:
    CANFunctionTimerBase(CAN_function_id_t id, CANObject *parent, uint32_t period_ms,
                         CAN_function_handler_t external_handler = nullptr,
                         CANFunctionBase *next_ok_function = nullptr,
                         CANFunctionBase *next_err_function = nullptr);

    virtual ~CANFunctionTimerBase(){};

    void set_period(uint32_t period_ms);
    uint32_t get_period();

protected:
    // virtual method for correct and systematic comparison of derived classes
    // may be complement by derived class
    virtual bool _equals(CANFunctionBase const &other) const;

    virtual CAN_function_result_t _default_handler(CANFrame *can_frame = nullptr) override final;

    // virtual function for correct and systematic comparison of derived classes
    // should be complement by derived class
    virtual CAN_function_result_t _timer_handler() { return CAN_RES_NONE; };

    virtual bool _before_external_handler() override;
    // virtual bool _after_external_handler() override;

private:
    uint32_t _period_ms = UINT32_MAX;
    uint32_t _last_action_tick = 0;
};

/******************************************************************************************************************************
 *
 * CANFunctionTimerNormal: class for normal timed messages
 *
 ******************************************************************************************************************************/
class CANFunctionTimerNormal : public CANFunctionTimerBase
{
public:
    CANFunctionTimerNormal(CANObject *parent, uint32_t period_ms, CAN_function_handler_t external_handler = nullptr,
                           CANFunctionBase *next_ok_function = nullptr, CANFunctionBase *next_err_function = nullptr);

    virtual ~CANFunctionTimerNormal(){};

protected:
    virtual CAN_function_result_t _timer_handler() override;
};

/******************************************************************************************************************************
 *
 * CANFunctionRequest: class for incoming request
 *
 ******************************************************************************************************************************/
class CANFunctionRequest : public CANFunctionBase
{
public:
    CANFunctionRequest(CANObject *parent,
                       CAN_function_handler_t external_handler = nullptr,
                       CANFunctionBase *next_ok_function = nullptr,
                       CANFunctionBase *next_err_function = nullptr);

    virtual ~CANFunctionRequest(){};

protected:
    virtual CAN_function_result_t _default_handler(CANFrame *can_frame = nullptr) override;
};

/******************************************************************************************************************************
 *
 * CANFunctionSimpleSender: just sends the CAN frame specified in the _default_handler() parameters,
 * overrides specified in the CAN frame function ID with value, returned by get_id() 
 * May be useful as the base class for all functions with outcoming messages. But it is very useful itself.
 *
 ******************************************************************************************************************************/
class CANFunctionSimpleSender : public CANFunctionBase
{
public:
    CANFunctionSimpleSender(CANObject *parent,
                          CAN_function_handler_t external_handler = nullptr,
                          CANFunctionBase *next_ok_function = nullptr,
                          CANFunctionBase *next_err_function = nullptr);

    virtual ~CANFunctionSimpleSender(){};

protected:
    virtual CAN_function_result_t _default_handler(CANFrame *can_frame = nullptr) override;

private:
};

/******************************************************************************************************************************
 *
 * CANFunctionSimpleEvent: class for events
 *
 ******************************************************************************************************************************/
class CANFunctionSimpleEvent : public CANFunctionBase
{
public:
    CANFunctionSimpleEvent(CANObject *parent, uint32_t period_ms,
                         CAN_function_handler_t external_handler = nullptr,
                         CANFunctionBase *next_ok_function = nullptr,
                         CANFunctionBase *next_err_function = nullptr);

    virtual ~CANFunctionSimpleEvent(){};

    void set_period(uint32_t period_ms);
    uint32_t get_period();

protected:
    // virtual method for correct and systematic comparison of derived classes
    // may be complement by derived class
    virtual bool _equals(CANFunctionBase const &other) const;

    virtual CAN_function_result_t _default_handler(CANFrame *can_frame = nullptr) override final;

    // virtual function for correct and systematic comparison of derived classes
    // should be complement by derived class
    virtual CAN_function_result_t _event_handler();

    //virtual bool _before_external_handler() override;
    // virtual bool _after_external_handler() override;

private:
    uint32_t _period_ms = UINT32_MAX;
    uint32_t _last_action_tick = 0;
};

#endif // CANFUNCTION_H