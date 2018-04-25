/*
 * send-unicast.c
 *
 *  Created on: Apr 18, 2018
 *      Author: Mats
 */

#include "contiki.h"
#include "net/rime/rime.h"
#include "sys/energest.h"
#include <stdio.h>

/*---------------------------------------------------------------------------*/
PROCESS(example_unicast_process, "Example unicast");
AUTOSTART_PROCESSES(&example_unicast_process);
/*---------------------------------------------------------------------------*/
static void
recv_uc(struct unicast_conn *c, const linkaddr_t *from)
{
  printf("unicast message received from %d.%d\n",
	 from->u8[0], from->u8[1]);
}
/*---------------------------------------------------------------------------*/
static void
sent_uc(struct unicast_conn *c, int status, int num_tx)
{
  const linkaddr_t *dest = packetbuf_addr(PACKETBUF_ADDR_RECEIVER);
  if(linkaddr_cmp(dest, &linkaddr_null)) {
    return;
  }
  printf("unicast message sent to %02X:%02X: status %d num_tx %d\n",
    dest->u8[0], dest->u8[1], status, num_tx);


  /* Flush all energest times so we can read latest values */
      //energest_flush();
          printf("Energest CPU: %lu LPM: %lu IRQ: %lu TRANSMIT: %lu LISTEN: %lu SECOND: %lu \r\n",
                 (unsigned long)(energest_type_time(ENERGEST_TYPE_CPU)),
                 (unsigned long)(energest_type_time(ENERGEST_TYPE_LPM)),
  			   (unsigned long)(energest_type_time(ENERGEST_TYPE_IRQ)),
  			   (unsigned long)(energest_type_time(ENERGEST_TYPE_TRANSMIT)),
  			   (unsigned long)(energest_type_time(ENERGEST_TYPE_LISTEN)),
			   (unsigned long)(RTIMER_SECOND));
          energest_flush();
}
/*---------------------------------------------------------------------------*/
static const struct unicast_callbacks unicast_callbacks = {recv_uc, sent_uc};
static struct unicast_conn uc;

static struct etimer et;
linkaddr_t addr;
uint8_t packets_sent;
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(example_unicast_process, ev, data)
{
  PROCESS_EXITHANDLER(unicast_close(&uc);)

  PROCESS_BEGIN();

  unicast_open(&uc, 146, &unicast_callbacks);

  energest_init();


  while(packets_sent<10) {


    etimer_set(&et, CLOCK_SECOND*5);

    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));

    packetbuf_copyfrom("Hello", 5);
    addr.u8[0] = 0x2d;
    addr.u8[1] = 0xf9;
    printf("addr %02X:%02X \r\n", addr.u8[0], addr.u8[1]);
    printf("own addr %02X:%02X \r\n", linkaddr_node_addr.u8[0], linkaddr_node_addr.u8[1]);

    if(!linkaddr_cmp(&addr, &linkaddr_node_addr)) {
          unicast_send(&uc, &addr);
    }

   packets_sent++;


  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
