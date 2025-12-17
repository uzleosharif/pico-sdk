

#include "hardware/structs/io_bank0.h"
#include "hardware/structs/padsbank0.h"
#include "hardware/structs/sio.h"
#include "pico/platform.h"

namespace {

constexpr uint LED_PIN = 25;
constexpr uint32_t LED_MASK = 1u << LED_PIN;

void init_led_pin() {
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

void busy_delay(uint32_t cycles) {
  for (volatile uint32_t i = 0; i < cycles; ++i) {
    tight_loop_contents();
  }
}

} // namespace

// Provide a dummy _fini so newlib's cleanup hook has a target.
extern "C" void _fini() {}

auto main() -> int {
  init_led_pin();

  while (true) {
    sio_hw->gpio_togl = LED_MASK;
    busy_delay(12000000);
  }
}
