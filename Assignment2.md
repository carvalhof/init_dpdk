# Assignment 2

Nesse exercício, você deve modificar o arquivo `echo.c` para (1) receber pacotes por meio da interface **tap0**, (2) filtrar determinados pacotes recebidos e (3) enviar os pacotes filtrados por meio da interface **tap1**. Ambas as interfaces são criadas pelo seu programa DPDK.

Você deve injetar os pacotes na interface **tap0** por meio do arquivo `.pcap` (vamos chamá-lo de `entrada.pcap`) do exercício anterior ([Assignment1](./Assignment1.md)) e salvar os pacotes que foram repassados para a interface **tap1**, por meio do programa **tcpdump**, por exemplo:

```bash
sudo tcpdump -i tap1 -w saida.pcap
```

Durante o desenvolvimento desse exercício, você deve:

1. Ler de um arquivo `filtro.txt` o filtro que deve ser implementado no programa `echo.c`
    *  A estrutura desse arquivo segue o seguinte formato:
        ```
        [TCP | UDP] [IP_origem | *]:[Porta_origem | *] [IP_destino | *]:[Porta_destino | *]
        ```
        * `|` significa **OU**
        * `*` significa que pode ter qualquer valor (_wildcard_). 
        * `[` e `]` não fazem parte da sintaxe.
    *  O arquivo [exemplo.txt](./exemplo.txt) apresenta o exemplo de cinco filtros.

2. Obter os dois arquivos pcap ao término da execução, a saber: `entrada.pcap` e `saida.pcap`

3. Mostrar quantos pacotes foram filtrados

4. Escrever em um arquivo `filtrados.txt` cada pacote que foi filtrado, na seguinte sintaxe:
```
IP_origem:Porta_origem -> IP_destino:Porta_destino -- Protocol: <protocol> -- Length: <length>
```

5. Observar atentamente os comentários dentro do arquivo `echo.c`

6. Criar uma interface simples que configura as regras a serem filtradas e gerar o arquivo diretamente para executar seu programa DPDK.
