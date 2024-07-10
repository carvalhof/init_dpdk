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
- https://doc.dpdk.org/api-23.11/index.html

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
make SOURCE="helloworld.c" TARGET="helloworld"
make run TARGET="helloworld" ARGS="arg0 arg1 arg2"
# Examples
make run TARGET="helloworld" ARGS="--help"
make run TARGET="helloworld" ARGS="-c 0x3"
```

# Compiling and running `dump.c`
```bash
make SOURCE="dump.c" TARGET="dump"
make run TARGET="dump" ARGS="--vdev=net_tap0,iface=tap0"
```

# Compiling and running `echo.c`
```bash
make SOURCE="echo.c" TARGET="echo"
make run TARGET="echo" ARGS="--vdev=net_tap0,iface=tap0 --vdev=net_tap1,iface=tap1"
```