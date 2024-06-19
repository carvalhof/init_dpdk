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

static void print_eth_hdr(const struct rte_ether_hdr *eth_hdr) {
    char src_mac_str[RTE_ETHER_ADDR_FMT_SIZE];
    char dst_mac_str[RTE_ETHER_ADDR_FMT_SIZE];

    rte_ether_format_addr(src_mac_str, RTE_ETHER_ADDR_FMT_SIZE, &eth_hdr->src_addr);
    rte_ether_format_addr(dst_mac_str, RTE_ETHER_ADDR_FMT_SIZE, &eth_hdr->dst_addr);

    printf("Ethernet Header:\n");
    printf("  Source MAC: %s\n", src_mac_str);
    printf("  Destination MAC: %s\n", dst_mac_str);
    printf("  EtherType: %04X\n", rte_be_to_cpu_16(eth_hdr->ether_type));
}

static void print_ip_hdr(__rte_unused const struct rte_ipv4_hdr *ip_hdr) {
    //TODO
}

int main(int argc, char *argv[]) {
    int ret;
    uint16_t port_id;
    struct rte_ipv4_hdr *ip_hdr;
    struct rte_mempool *mbuf_pool;
    struct rte_ether_hdr *eth_hdr;
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

    port_id = 0;
    ret = rte_eth_dev_configure(port_id, 1, 1, &port_conf);
    if (ret != 0) {
        rte_exit(EXIT_FAILURE, "Error configuring Ethernet port.\n");
    }

    rte_eth_dev_info_get(port_id, &dev_info);
    printf("Port %u: %u RX queues, %u TX queues.\n", port_id, dev_info.nb_rx_queues, dev_info.nb_tx_queues);

    ret = rte_eth_rx_queue_setup(port_id, 0, RX_RING_SIZE, rte_eth_dev_socket_id(port_id), NULL, mbuf_pool);
    if (ret < 0) {
        rte_exit(EXIT_FAILURE, "Error setting up RX queue.\n");
    }

    ret = rte_eth_dev_start(port_id);
    if (ret < 0) {
        rte_exit(EXIT_FAILURE, "Error starting Ethernet port.\n");
    }

    printf("Capturing packets... Press Ctrl+C to quit.\n");

    while (!force_quit) {
        const uint16_t nb_rx = rte_eth_rx_burst(port_id, 0, pkts_burst, BURST_SIZE);
        if (nb_rx == 0) {
            continue;
        }

        for (uint16_t i = 0; i < nb_rx; ++i) {
            eth_hdr = rte_pktmbuf_mtod(pkts_burst[i], struct rte_ether_hdr *);

            print_eth_hdr(eth_hdr);

            if (eth_hdr->ether_type == rte_cpu_to_be_16(RTE_ETHER_TYPE_IPV4)) {
                ip_hdr = rte_pktmbuf_mtod_offset(pkts_burst[i], struct rte_ipv4_hdr *, sizeof(struct rte_ether_hdr));

                print_ip_hdr(ip_hdr);
            }

            rte_pktmbuf_free(pkts_burst[i]);
        }
    }

    rte_eth_dev_stop(port_id);
    rte_eth_dev_close(port_id);

    return 0;
}
