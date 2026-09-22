# Processamento-Digital-de-Imagens-PNM-Trabalho2-INF110
Código de processamento digital de imagens, com foco em aplicação de filtros, em formato pnm. Este projeto foi desenvolvido como parte do **Trabalho Prático 2** da disciplina de **Programação I (INF 110)** na **Universidade Federal de Viçosa (UFV)**. O objetivo é manipular imagens nos formatos P2 (tons de cinza) e P3 (coloridas) através de operações matriciais em C++.

## Funcionalidades

O programa permite a leitura de arquivos nos formatos **PGM (P2)** e **PPM (P3)** em modo ASCII e a aplicação dos seguintes filtros:

* **Ajuste de Brilho:** Filtros para clarear e escurecer as imagens com base em porcentagens.
* **Negativo:** Inverte as cores das imagens.
* **Espelhado:** Espelha as imagens em relação ao eixo vertical.
* **Tons de cinza:** Transformação de imagens coloridas(P3) em imagens em tons de cinza(P2).
* **Filtro de Sobel:** Algoritmo de detecção de bordas, destacando regiões em que há brusca mudança de luminosidade.
* **Pixelização:** Reduz a resolução espacial da imagem, criando a sensação de pixels maiores.

## Tecnologias Utilizadas

* **Linguagem:** C++
* **Formatos Suportados:** PNM (P2 e P3 ASCII)
* **Paradigma:** Programação Estruturada
