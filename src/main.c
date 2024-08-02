#include <stdio.h>
#include <xcore/port.h>
#include <xcore/hwtimer.h>
#include <xcore/select.h>

int main() {
    port_t port = XS1_PORT_4C;
    hwtimer_t timer1 = hwtimer_alloc();
    hwtimer_t timer2 = hwtimer_alloc();
    port_enable(port);
    port_out(port, 0b0000);

    uint32_t time1 = hwtimer_get_time(timer1);
    uint32_t time2 = hwtimer_get_time(timer2);

    static const uint32_t INTERVAL1 = 100000000 / 2; // 500ms
    static const uint32_t INTERVAL2 = 100000000 / 3; // 333ms

    hwtimer_set_trigger_time(timer1, time1 + INTERVAL1);
    hwtimer_set_trigger_time(timer2, time2 + INTERVAL2);

    uint32_t port_value = 0;

    while (1) {
        SELECT_RES(
            CASE_THEN(timer1, ontimer1),
            CASE_THEN(timer2, ontimer2)
        ) {
        ontimer1:
            port_value ^= 0b11;
            port_out(port, port_value);
            time1 += INTERVAL1;
            hwtimer_set_trigger_time(timer1, time1 + INTERVAL1);
            break;
        ontimer2:
            port_value ^= 0b1100;
            port_out(port, port_value);
            time2 += INTERVAL2;
            hwtimer_set_trigger_time(timer2, time2 + INTERVAL2);
            break;
        }
    }
}