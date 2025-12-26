
module;

#include "hardware/structs/io_bank0.h"
#include "hardware/structs/padsbank0.h"
#include "hardware/structs/sio.h"
#include "pico/platform.h"

#include <cstdint>

export module pico.hw;

namespace pico::hw {

export auto InitLedPin() -> void;
export auto BusyDelay(std::uint32_t cycles) -> void;
export auto ToggleLed() -> void;

} // namespace pico::hw

namespace {
constexpr uint LED_PIN = 25;
constexpr uint32_t LED_MASK = 1u << LED_PIN;
} // namespace

namespace pico::hw {

auto InitLedPin() -> void {
  // Configure the pad for push-pull output: 4 mA drive, Schmitt enabled, no
  // pulls.
  padsbank0_hw->io[LED_PIN] =
      (PADS_BANK0_GPIO25_DRIVE_VALUE_4MA << PADS_BANK0_GPIO25_DRIVE_LSB) |
      PADS_BANK0_GPIO25_SCHMITT_BITS;

  // Route the pin to the SIO peripheral so we can drive it directly.
  io_bank0_hw->io[LED_PIN].ctrl = GPIO_FUNC_SIO;

  // Enable output on the pin via SIO.
  sio_hw->gpio_oe_set = LED_MASK;
}

auto BusyDelay(std::uint32_t cycles) -> void {
  busy_wait_at_least_cycles(cycles);
}

auto ToggleLed() -> void { sio_hw->gpio_togl = LED_MASK; }

} // namespace pico::hw
