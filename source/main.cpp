#include "MKE18F16.h"
#include "clock_config.h"
#include "pin_mux.h"

using namespace BSP;

int main() {

    // initialize board hardware
    BOARD_InitBootClocks();
    BOARD_InitBootPins();

    while(true);


}
