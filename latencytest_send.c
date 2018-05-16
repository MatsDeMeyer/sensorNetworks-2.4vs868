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

static struct etimer et;
linkaddr_t addr;
uint16_t packets_sent = 1;
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
  //printf("unicast message sent to %02X:%02X: status %d num_tx %d\n",
  // dest->u8[0], dest->u8[1], status, num_tx);

}
/*---------------------------------------------------------------------------*/
static const struct unicast_callbacks unicast_callbacks = {recv_uc, sent_uc};
static struct unicast_conn uc;


/*---------------------------------------------------------------------------*/
PROCESS_THREAD(example_unicast_process, ev, data)
{
  PROCESS_EXITHANDLER(unicast_close(&uc);)

  PROCESS_BEGIN();

  unicast_open(&uc, 146, &unicast_callbacks);

  addr.u8[0] = 0x2d;
  addr.u8[1] = 0xf9;
  //printf("addr %02X:%02X \r\n", addr.u8[0], addr.u8[1]);
  //printf("own addr %02X:%02X \r\n", linkaddr_node_addr.u8[0], linkaddr_node_addr.u8[1]);

  //wait 10s
  etimer_set(&et, CLOCK_SECOND*10);
  PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));

  while(packets_sent<301) {


    etimer_set(&et, CLOCK_SECOND);

    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));

    packetbuf_copyfrom(&packets_sent, 16);


    if(!linkaddr_cmp(&addr, &linkaddr_node_addr)) {
          unicast_send(&uc, &addr);
          printf("sent packet '%d'\r\n", packets_sent);
          packets_sent++;


    }



  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
