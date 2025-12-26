

import pico.hw;

// TODO(): is below even needed?
// Provide a dummy _fini so newlib's cleanup hook has a target.
extern "C" void _fini() {}

auto main() -> int {

  pico::hw::InitLedPin();

  while (true) {
    pico::hw::ToggleLed();
    pico::hw::BusyDelay(12000000);
  }
}
