# Prática 1: Sistemas Operacionais Embarcados – Semáforo Inteligente 🚦

Este repositório apresenta o desenvolvimento da **Prática 1** da disciplina de **Sistemas Operacionais Embarcados**, ministrada no **Departamento de Engenharia Elétrica (DELT) da Universidade Federal do Paraná (UFPR)**.  
O projeto consiste na implementação de um **Semáforo Inteligente com Interrupção por Hardware**, desenvolvido como material didático para introduzir conceitos fundamentais de sistemas embarcados reativos.

---

## 🎯 Objetivo Didático

A proposta desta prática é demonstrar a implementação de **multitarefa cooperativa manual** e o conceito de **Troca de Contexto** em sistemas embarcados **sem a utilização de um Kernel RTOS** (como o FreeRTOS).

O foco principal é evidenciar:

- **Tratamento de Eventos Assíncronos:**  
  Uso de interrupções externas para garantir a segurança do pedestre, evitando bloqueios causados por delays no fluxo principal do programa.

- **Gerenciamento de Estado:**  
  Necessidade de salvar o estado atual do sistema (LEDs e fases do semáforo) antes do atendimento da interrupção (ISR) e restaurá‑lo corretamente após o retorno ao loop principal.

---

## 🧠 Competências Demonstradas

- Programação de sistemas embarcados em regime **bare‑metal**
- Uso de **interrupções de hardware (ISR)** para tratamento de eventos externos
- Implementação de sistemas **reativos baseados em eventos**
- Gerenciamento manual de estados e fluxo de execução
- Análise de limitações de código baseado em **delays bloqueantes**
- Introdução a conceitos fundamentais de **sistemas de tempo real**
- Escrita de código didático, organizado e documentado

---

## 🛠️ Especificações Técnicas

### Hardware
- **Microcontrolador:** ATMega328P (Arduino)
- **Ambiente:** Simulação no Wokwi

### Lógica de Controle
- **Ciclo Veicular:**  
  Alternância entre **Via A** e **Via B**, com:
  - 15 segundos de sinal verde
  - 5 segundos de sinal amarelo

- **Prioridade ao Pedestre:**  
  Interrupção por hardware acionada via botão no **pino digital 2**.

- **Segurança Operacional:**  
  Transição forçada para amarelo/vermelho antes da liberação da travessia e sinalização do encerramento da travessia por **LED piscante**.

---

## 💡 Relevância Técnica

Este exercício simula situações comuns em **sistemas embarcados reais**, onde eventos externos imprevisíveis (botões, sensores, falhas) precisam ser tratados com **prioridade**, sem comprometer a segurança ou a lógica principal do sistema.  
A prática evidencia as limitações do uso excessivo de `delay()` e reforça a importância de arquiteturas **orientadas a eventos**, amplamente utilizadas em aplicações **industriais, automotivas e de controle**.

---

## 🚀 Como Executar

1. O código principal está localizado no arquivo `sketch.ino`.
2. As conexões de hardware estão descritas no arquivo `diagram.json`.
3. **Simulação Online:**  
   O comportamento do sistema pode ser testado diretamente no navegador por meio do link abaixo:  
   ▶️ *Link para a Simulação no Wokwi*

---

## 🧪 Validação e Testes

- Verificação do comportamento correto do ciclo veicular em operação normal.
- Testes de acionamento do botão de pedestre em diferentes fases do semáforo.
- Avaliação da resposta imediata da interrupção, independentemente do estágio do ciclo.
- Confirmação da restauração correta do estado do sistema após o retorno da ISR.

---

## 📚 Evolução do Projeto

Esta prática é a **primeira etapa de um portfólio progressivo em Sistemas Operacionais Embarcados**.  
Nas próximas práticas, o mesmo problema será implementado utilizando **FreeRTOS no ESP32**, demonstrando como:

- O escalonamento de tarefas (Tasks) simplifica a lógica de controle;
- Semáforos binários garantem sincronização segura;
- Arquiteturas orientadas a RTOS facilitam o desenvolvimento de sistemas críticos e escaláveis.

---

**Prof. Thiago José da Luz, PhD**  
Departamento de Engenharia Elétrica – UFPR
