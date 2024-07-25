#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <rte_common.h>
#include <rte_eal.h>
#include <rte_ethdev.h>
#include <rte_mbuf.h>
#include <rte_hash.h>
#include <rte_jhash.h>
#include <rte_ip.h>
#include <rte_udp.h>
#include <rte_tcp.h>

#define BURST_SIZE 32
#define HASH_ENTRIES 1024

struct flow_key {
    uint32_t src_ip;
    uint32_t dst_ip;
    uint16_t src_port;
    uint16_t dst_port;
    uint8_t protocol;
} __attribute__((packed));

struct flow_entry {
    struct flow_key key;
    // TODO: fill in the necessary data 
} __attribute__((packed));

static const struct rte_hash_parameters hash_params = {
    .name = "flow_table",
    .entries = HASH_ENTRIES,
    .key_len = sizeof(struct flow_key),
    .hash_func = rte_jhash,
    .hash_func_init_val = 0,
};

static struct rte_hash *flow_table;

static void extract_5tuple(struct rte_mbuf *mbuf, struct flow_key *key) {
    // TODO: fill 'key' using 5-tuple of the packet 'mbuf'
}

static void process_packet(struct rte_mbuf *mbuf) {
    struct flow_key key;
    struct flow_entry *flow;
    int ret;

    extract_5tuple(mbuf, &key);

    ret = rte_hash_lookup_data(flow_table, &key, (void **)&flow);
    if (ret < 0) {
        struct flow_entry new_flow = { .key = key }; // TODO: initialize the 'flow' fields with appropriate data
        rte_hash_add_key_data(flow_table, &key, &new_flow);
    } else {
        // TODO: update the 'flow' fields with appropriate data
    }
}

int main(int argc, char *argv[]) {
    // ...
    // TODO: we omit this initialization part.
    // ...

    flow_table = rte_hash_create(&hash_params);
    if (flow_table == NULL)
        rte_exit(EXIT_FAILURE, "Cannot create flow table\n");

    while (1) {
        const uint16_t nb_rx = rte_eth_rx_burst(port_in, 0, pkts_burst, BURST_SIZE);
        if (nb_rx == 0) {
            continue;
        }

        // TODO: filter the packets.
        // 'filter_packets' contains all filtered packets.
        // 'nb_filter_packets' represents the number of filtered packets.

        for (int i = 0; i < nb_filter_packets; i++) {
            process_packet(filter_packets[i]);
        }
    }

    return 0;
}
