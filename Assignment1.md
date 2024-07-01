# Assignment 1

Nesse exercício, você deve criar um arquivo DPDK `filter.c`, baseado no arquivo `dump.c`, para receber pacotes por meio da interface **tap0** criada pelo seu programa DPDK e imprimir as seguintes informações:

1. Se for um pacote TCP e o *\<length\>* for maior que 512, imprimir:
```
"IP_origem:Porta_origem -> IP_destino:Porta_destino (<flags>) -- Length: <length>"
```

2. Se for um pacote TCP e Porta_destino=543, imprimir:
```
"IP_origem:Porta_origem -> IP_destino:Porta_destino"
```

3. Se for um pacote IP e o *\<length\>* for maior ou igual que 100 e menor ou igual a 1000, imprimir:
    * Se for TCP, imprimir: 
    ```
    "[TCP] <length> <flags>"
    ```
    * Se for UDP, imprimir: 
    ```
    "[UDP] <checksum>"
    ```
    * Caso contrário, imprimir: 
    ```
    "Non-TCP && Non-UDP"
    ```

4. Se for um pacote TCP, *\<length\>* menor que 400 e estiver a string *"GET "* no payload, imprimir:
```
"[HTTP GET] <length>"
```

5. Além disso, ao final, contabilizar as seguintes informações:
- \# packets:
- \# IP packets: 
- \# non-IP packets:
- \# UDP packets:
- \# TCP packets:
- \# non-TCP && non-UDP:

6. Dos pacotes TCP, contabilizar de acordo com o tamanho do payload:
- \# < 63: 
- \# 64-255: 
- \# 256-511: 
- \# 511-1023: 
- \# \>1024:

7. Para todos os pacotes TCP e UDP, gerar estatística sobre as portas de origem e destino:
- \# Lista das 10 principais portas de origem, com valores absolutos e percentuais
- \# Lista das 10 principais portas de destino, com valores absolutos e percentuais
- \# Lista dos 10 principais pares (porta de origem, porta de destino), com valores absolutos e percentuais
- Importante! Gerar estatísticas separadas para TCP e UDP.

9. Para cada caso positivo dos passos 1, 2, 3 e 4, colete o tempo (em us) do processamento de cada pacote. Ao final, apresente a média e o intervalo de confiança de 95\% de cada um dos casos.

## Importante:
- *\<length\>*: Tamanho informado no cabeçalho IP;
- *\<flags\>*: Flags do TCP, *e.g.,* SYN, SYN+ACK, ACK, RST, etc;
- *\<checksum\>*: Checksum do UDP expresso em Hexadecimal.

## Programa auxiliar:
- Para injetar pacotes de um arquivo `.pcap`, utilize código `inject.py` em Python a seguir:
```Python
import sys
from scapy.all import *

def inject_packets(interface, pcap_file):
    try:
        packets = rdpcap(pcap_file)
        for packet in packets:
            sendp(packet, iface=interface, verbose=0)
    except FileNotFoundError:
        sys.exit(1)
    except PermissionError:
        sys.exit(1)
    except Exception as e:
        sys.exit(1)

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print('USAGE: python3 {} <interface> <file.pcap>'.format(sys.argv[0]))
        sys.exit(1)

    interface = sys.argv[1]
    pcap_file = sys.argv[2]

    inject_packets(interface, pcap_file)
```

- Será necessário instalar o `scapy`:
```bash
pip3 install scapy
```

- Para executar o `inject.py`, injetando os pacotes do arquivo `file.pcap` na interface `tap0`, execute:
```bash
sudo python3 inject.py tap0 file.pcap
```

## Arquivos `.pcap`

- O arquivo .pcap que você deve analisará será oriundo da sua própria navegação cotidiana na Internet. Para isso, enquanto estiver utilizando a Internet em seu computador, deixe o tcpdump aberto e capturando pacotes da sua interface de rede. Ao configurar o tcpdump, não se esqueça de colocar a opção para exportar a saída para uma arquivo. Após ter gerado o arquivo .pcap, utilize-o como entrada para realizar a tarefa descrita acima. Certifique-se de ter um arquivo .pcap com pelo menos 50 MB de tamanho para processamento.
