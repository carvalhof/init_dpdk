# Assignment 3

Nesse exercício, você deve modificar o arquivo `flow.c` para (1) receber pacotes por meio da interface **tap0**, (2) filtrar determinados pacotes recebidos e (3) armazenar informações referente às sessões TCP/UDP* dos pacotes recebidos e **filtrados**.

Você deve injetar os pacotes na interface **tap0** por meio do arquivo `.pcap` semelhante aos exercícios anteriores ([Assignment1](./Assignment1.md) e [Assignment2](./Assignment2.md)).

Durante o desenvolvimento deste exercício, você deve:

1. Criar e inicializar as estruturas de dados adequadas (algumas já estão definidas no `flow.c`);

2. Filtrar os pacotes (semelhante ao [Assignment2](./Assignment2.md));

3. Extrair o 5-tuple de cada pacote já filtrado e criar uma **KEY**;

4. Inserir uma nova entrada na tabela com a **KEY** ou atualizar as informações na entrada já existente, buscando por **KEY**;

5. Ao final da execução, imprimir em um arquivo chamado `estatisticas.txt`, as seguintes informações:
    * O **Top5** fluxos (imprimir 5-tuple) que teve maior quantidade de pacotes (o top5 deve estar ordenado em relação à quantidade de pacotes). Por exemplo:
        ```
        1. IP_origem:Porta_origem -> IP_destino:Porta_destino [protocol] -- #packets: <total_packets>
        2. IP_origem:Porta_origem -> IP_destino:Porta_destino [protocol] -- #packets: <total_packets>
        3. IP_origem:Porta_origem -> IP_destino:Porta_destino [protocol] -- #packets: <total_packets>
        4. IP_origem:Porta_origem -> IP_destino:Porta_destino [protocol] -- #packets: <total_packets>
        5. IP_origem:Porta_origem -> IP_destino:Porta_destino [protocol] -- #packets: <total_packets>
        ```
    * O **Top5** fluxos (imprimir 5-tuple) que teve maior quantidade de dados (payload) (o top5 deve estar ordenado em relação à quantidade de bytes). Por exemplo:
        ```
        1. IP_origem:Porta_origem -> IP_destino:Porta_destino [protocol] -- #bytes: <total_bytes>
        2. IP_origem:Porta_origem -> IP_destino:Porta_destino [protocol] -- #bytes: <total_bytes>
        3. IP_origem:Porta_origem -> IP_destino:Porta_destino [protocol] -- #bytes: <total_bytes>
        4. IP_origem:Porta_origem -> IP_destino:Porta_destino [protocol] -- #bytes: <total_bytes>
        5. IP_origem:Porta_origem -> IP_destino:Porta_destino [protocol] -- #bytes: <total_bytes>
        ```

6. Observar atentamente os comentários dentro do arquivo `echo.c`.

*: Apesar do protocolo UDP não ser orientado a conexão, para fins didáticos, vamos assumir que a mesma 5-tuple de protocolos UDP pertencem a mesma **sessão**.