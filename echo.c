#include <stdio.h>
#include <signal.h>
#include <rte_common.h>
#include <rte_eal.h>
#include <rte_ethdev.h>
#include <rte_mbuf.h>
#include <rte_ether.h>
#include <rte_ip.h>
#include <rte_tcp.h>

#define BURST_SIZE 32
#define NUM_MBUFS 8191
#define RX_RING_SIZE 1024
#define MBUF_CACHE_SIZE 512

static volatile bool force_quit;

static void signal_handler(int signum) {
    if (signum == SIGINT) {
        force_quit = true;
    }
}

int main(int argc, char *argv[]) {
    int ret;
    uint16_t port_in;
    uint16_t port_out;
    struct rte_mempool *mbuf_pool;
    struct rte_eth_dev_info dev_info;
    struct rte_eth_conf port_conf = { 0 };
    struct rte_mbuf *pkts_burst[BURST_SIZE];

    ret = rte_eal_init(argc, argv);
    if (ret < 0) {
        rte_exit(EXIT_FAILURE, "Error initializing DPDK EAL.\n");
    }

    argc -= ret;
    argv += ret;

    signal(SIGINT, signal_handler);

    mbuf_pool = rte_pktmbuf_pool_create("MBUF_POOL", NUM_MBUFS, MBUF_CACHE_SIZE, 0, RTE_MBUF_DEFAULT_BUF_SIZE, rte_socket_id());
    if (mbuf_pool == NULL) {
        rte_exit(EXIT_FAILURE, "Error creating mbuf pool.\n");
    }

    port_in = 0;
    ret = rte_eth_dev_configure(port_in, 1, 1, &port_conf);
    if (ret != 0) {
        rte_exit(EXIT_FAILURE, "Error configuring Ethernet port.\n");
    }

    port_out = 1;
    ret = rte_eth_dev_configure(port_out, 1, 1, &port_conf);
    if (ret != 0) {
        rte_exit(EXIT_FAILURE, "Error configuring Ethernet port.\n");
    }

    rte_eth_dev_info_get(port_in, &dev_info);
    printf("Port %u: %u RX queues, %u TX queues.\n", port_in, dev_info.nb_rx_queues, dev_info.nb_tx_queues);
    rte_eth_dev_info_get(port_out, &dev_info);
    printf("Port %u: %u RX queues, %u TX queues.\n", port_out, dev_info.nb_rx_queues, dev_info.nb_tx_queues);

    ret = rte_eth_rx_queue_setup(port_in, 0, RX_RING_SIZE, rte_eth_dev_socket_id(port_in), NULL, mbuf_pool);
    if (ret < 0) {
        rte_exit(EXIT_FAILURE, "Error setting up RX queue.\n");
    }

    ret = rte_eth_tx_queue_setup(port_out, 0, RX_RING_SIZE, rte_eth_dev_socket_id(port_out), NULL);
    if (ret < 0) {
        rte_exit(EXIT_FAILURE, "Error setting up RX queue.\n");
    }

    ret = rte_eth_dev_start(port_in);
    if (ret < 0) {
        rte_exit(EXIT_FAILURE, "Error starting Ethernet port.\n");
    }

    ret = rte_eth_dev_start(port_out);
    if (ret < 0) {
        rte_exit(EXIT_FAILURE, "Error starting Ethernet port.\n");
    }

    printf("Capturing packets... Press Ctrl+C to quit.\n");

    while (!force_quit) {
        const uint16_t nb_rx = rte_eth_rx_burst(port_in, 0, pkts_burst, BURST_SIZE);
        if (nb_rx == 0) {
            continue;
        }

        // TODO: filter all packets in 'pkts_burst'.
        // Be careful in 'rte_eth_tx_burst' arguments.
        // Handling accordingly the 'pkt_burst' array.
        // Make sure to free unsent packets.

        const uint16_t nb_tx = rte_eth_tx_burst(port_out, 0, pkts_burst, nb_rx);
        printf("Received %d packets and sent %d packets.\n", nb_rx, nb_tx);
    }

    rte_eth_dev_stop(port_in);
    rte_eth_dev_stop(port_out);
    rte_eth_dev_close(port_in);
    rte_eth_dev_close(port_out);

    return 0;
}
