# Criptografia em Duas Camadas (Cifra de César + Sequências Numéricas)

**Disciplina:** Algoritmo e Pensamento Computacional
**Professor:** Francisco de Assis Cavallaro
**Grupo:**
- Guilherme Miranda
- Guilherme Vilela
- Cauê Dogani
- João Vitor

## Objetivo
Unir criptografia simples, matemática aplicada (progressões e séries) e conceitos de programação em C (arquivos, ponteiros, menus).

## Como funciona
Cada letra `i` da palavra recebe um deslocamento total:

```
deslocamento[i] = SHIFT + sequencia[i]      (módulo 26)
```

- **Camada 1:** Cifra de César, com SHIFT fixo.
- **Camada 2:** deslocamento dinâmico dado pela sequência numérica escolhida.

| Tipo | Sequência | Fórmula |
|---|---|---|
| 1 | Progressão Aritmética | aₙ = a₁ + (n−1)·r |
| 2 | Progressão Geométrica | aₙ = a₁·qⁿ⁻¹ |
| 3 | Fibonacci | Fₙ = Fₙ₋₁ + Fₙ₋₂ (F₁ = F₂ = 1) |
| 4 | Números primos | 2, 3, 5, 7, 11... |

## Compilar e executar
```bash
gcc -Wall -o cripto criptografia_simples.c
./cripto
```

## Menu
1. Criptografar palavra
2. Descriptografar palavra (mesmos SHIFT e sequência usados na criptografia)
0. Sair

## Arquivos gerados
- `resultado_criptografia.txt`: `Palavra codificada: gswgkle | SHIFT: 3 | Tipo: 3 | Letras: 7`
- `log_execucao.txt`: registro com data/hora de cada operação (criptografar e descriptografar).

## Exemplo
Palavra `coracao`, SHIFT 3, Fibonacci (1, 1, 2, 3, 5, 8, 13):

| Letra | c | o | r | a | c | a | o |
|---|---|---|---|---|---|---|---|
| Deslocamento | 4 | 4 | 5 | 6 | 8 | 11 | 16 |
| Cifrada | g | s | w | g | k | l | e |

Resultado: **gswgkle**.

> **Observação:** o enunciado mostra `fqvdjqb` como saída, mas aplicando a regra `SHIFT + sequência[i]` o resultado é `gswgkle` (ex.: c + 3 + 1 = g, não f). Esta divergência deve ser confirmada com o professor.

## Taxonomia de Bloom no projeto
| Nível | Onde aparece |
|---|---|
| Lembrar | Alfabeto (`'a'` = 97 em ASCII) e fórmulas das progressões |
| Compreender | Efeito do SHIFT e do módulo 26 |
| Aplicar | Funções `gerar_sequencia` e `cifrar` |
| Analisar | Executar a mesma palavra e SHIFT com PA, PG, Fibonacci e primos e comparar (tabela abaixo) |
| Avaliar | Análise abaixo |
| Criar | Sistema completo com menu, arquivo e log |

## Análise de segurança (preencher com o grupo)
Resultado ao rodar `coracao` com SHIFT 3 em cada sequência (PA a₁=1, r=2; PG a₁=1, q=2):

| Sequência | Cifrada |
|---|---|
| PA | guzkooe |
| PG | gtylvjd |
| Fibonacci | gswgkle |
| Primos | huzkqqi |

- Fibonacci repete valores (1, 1) e, no módulo 26, a sequência é periódica, então é mais previsível.
- PA tem padrão linear fácil de detectar.
- PG tende a se repetir em módulo 26 (ciclos curtos).
- Primos não têm fórmula simples, o que dificulta deduzir o padrão.
- Todas as cifras são fracas na prática: com poucas letras, um ataque de força bruta testa todas as combinações facilmente.

## Estrutura do repositório
```
.
├── criptografia_simples.c
├── README.md
├── resultado_criptografia.txt   (gerado)
└── log_execucao.txt             (gerado)
```
