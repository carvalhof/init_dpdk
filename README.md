# DPDK
- https://www.dpdk.org/

## Supported hardware
- https://core.dpdk.org/supported/

## Performance Reports
- https://core.dpdk.org/perf-reports/
  - https://fast.dpdk.org/doc/perf/DPDK_23_11_NVIDIA_NIC_performance_report.pdf

## Programmer's Guide
- https://doc.dpdk.org/guides/prog_guide/index.html

## API
- https://doc.dpdk.org/api-22.11/index.html

## Quick Start Guide
- https://core.dpdk.org/doc/quick-start/

## Pktgen Application
- https://pktgen-dpdk.readthedocs.io/en/latest/

## Versions
- https://core.dpdk.org/download/
- DPDK 23.11.1 (LTS)
- Ubuntu 22.04 (LTS)
- Kernel 5.15


# Installing DPDK
```bash
./dpdk.sh
```

# Compiling and running `helloworld.c`
```bash
make
make run ARGS="arg0 arg1 arg2"
```


# Examples
```bash
make run ARGS="--help"
make run ARGS="-c 0x3"
```