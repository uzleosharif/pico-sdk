
module;

#include "hardware/structs/io_bank0.h"
#include "hardware/structs/padsbank0.h"
#include "hardware/structs/sio.h"
#include "pico/platform.h"

export module pico.hw;

import std;

namespace pico::hw {

export auto InitializeLedPin() -> void;
export auto BusyDelay(std::uint32_t cycles) -> void;
export auto ToggleLed() -> void;

}  // namespace pico::hw

namespace {

std::uint8_t constexpr kLedPin{25};

template <typename T = std::bitset<32>>
  requires(std::unsigned_integral<T> or std::same_as<T, std::bitset<32>>)
consteval auto GetLedMask() -> T {
  std::bitset<32> led_mask{};
  led_mask.set(kLedPin);

  if constexpr (std::is_same_v<T, std::bitset<32>>) {
    return led_mask;
  }

  return static_cast<T>(led_mask.to_ulong());
}

}  // namespace

namespace pico::hw {

auto InitializeLedPin() -> void {
  // Configure the pad for push-pull output: 4 mA drive, Schmitt enabled, no
  // pulls.
  padsbank0_hw->io[kLedPin] =
      (PADS_BANK0_GPIO25_DRIVE_VALUE_4MA << PADS_BANK0_GPIO25_DRIVE_LSB) |
      PADS_BANK0_GPIO25_SCHMITT_BITS;

  // Route the pin to the SIO peripheral so we can drive it directly.
  io_bank0_hw->io[kLedPin].ctrl = GPIO_FUNC_SIO;

  // Enable output on the pin via SIO.
  sio_hw->gpio_oe_set = GetLedMask<std::uint32_t>();
}

auto BusyDelay(std::uint32_t cycles) -> void {
  busy_wait_at_least_cycles(cycles);
}

auto ToggleLed() -> void {
  sio_hw->gpio_togl = GetLedMask<std::uint32_t>();
}

}  // namespace pico::hw
