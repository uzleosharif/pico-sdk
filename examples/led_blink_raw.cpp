

import pico.hw;

auto main() -> int {
  pico::hw::InitializeLedPin();

  while (true) {
    pico::hw::ToggleLed();
    pico::hw::BusyDelay(12000000);
  }
}
