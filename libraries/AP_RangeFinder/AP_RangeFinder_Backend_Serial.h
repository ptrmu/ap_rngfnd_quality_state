#pragma once

#include "AP_RangeFinder_Backend.h"

class AP_RangeFinder_Backend_Serial : public AP_RangeFinder_Backend
{
public:
    // constructor
    AP_RangeFinder_Backend_Serial(RangeFinder::RangeFinder_State &_state,
                                  AP_RangeFinder_Params &_params);

    void init_serial(uint8_t serial_instance) override;

protected:

    // baudrate used during object construction:
    virtual uint32_t initial_baudrate(uint8_t serial_instance) const;

    // the value 0 is special to the UARTDriver - it's "use default"
    virtual uint16_t rx_bufsize() const { return 0; }
    virtual uint16_t tx_bufsize() const { return 0; }

    AP_HAL::UARTDriver *uart = nullptr;

    // update state; not all backends call this!
    virtual void update(void) override;

    // it is essential that anyone relying on the base-class update to
    // implement this:
    virtual bool get_reading(float &reading_m) = 0;

    // maximum time between readings before we change state to NoData:
    virtual uint16_t read_timeout_ms() const { return 200; }

    // 0 is no return value, 100 is perfect.  false means signal_quality
    // is not available and quality_pct set to SIGNAL_QUALITY_NODATA.
    virtual bool get_signal_quality_pct(int8_t &quality_pct) const WARN_IF_UNUSED
    { quality_pct = RangeFinder::SIGNAL_QUALITY_NODATA; return false; }
};
