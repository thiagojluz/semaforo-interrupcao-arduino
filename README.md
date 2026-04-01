# Prática 1: Sistemas Operacionais Embarcados - UFPR 🚦
### Este repositório contém o projeto de um **Semáforo Inteligente com Interrupção de Hardware**, desenvolvido como material didático para a disciplina de **Sistemas Operacionais Embarcados** no Departamento de Engenharia Elétrica (DELT) da **UFPR**. 

## 🎯 Objetivo Didático
A proposta desta prática é demonstrar a implementação de **multitarefa cooperativa manual** e o conceito de **Troca de Contexto** em sistemas sem a presença de um Kernel RTOS (como o FreeRTOS). 

O foco é evidenciar:
1. **Tratamento de Eventos Assíncronos:** Uso de interrupções externas para garantir a segurança do pedestre, ignorando delays bloqueantes do ciclo principal. 
2. **Gerenciamento de Estado:** A necessidade de salvar o estado atual dos registros (LEDs) antes de desviar o fluxo para a ISR (Interrupt Service Routine) e restaurá-los ao retornar ao loop principal. 

## 🧠 Competências Demonstradas
* Programação de sistemas embarcados em nível bare-metal (sem sistema operacional)
* Projeto de sistemas reativos baseados em eventos
* Uso de interrupções de hardware (ISR) para tratamento de eventos assíncronos
* Gerenciamento manual de estados e fluxo de execução
* Conceitos fundamentais de sistemas de tempo real
* Análise de riscos relacionados a delays bloqueantes
* Escrita de código didático e documentado

## 🛠️ Especificações Técnicas
* **Hardware:** Arduino (ATMega328P) via simulador **Wokwi**. 
* **Lógica de Controle:**
    * **Ciclo Veicular:** Alternância entre Via A e Via B (15s verde, 5s amarelo). 
    * **Prioridade Pedestre:** Interrupção por hardware no pino 2 (botão). 
    * **Segurança:** Transição forçada para amarelo/vermelho antes da liberação da travessia e sinalização de encerramento por LED piscante. 

## 💡 Relevância Técnica
Este exercício simula problemas reais encontrados em sistemas embarcados críticos, como a necessidade de responder a eventos assíncronos (interruptores, sensores, falhas) sem comprometer a segurança ou a lógica principal do sistema. 
A prática evidencia limitações de abordagens baseadas em delays e a importância de arquiteturas orientadas a eventos, comuns em aplicações industriais e automotivas.

## 🚀 Como Executar
1. O código principal está localizado no arquivo sketch.ino.
2. As conexões de hardware estão descritas no arquivo diagram.json. 
3. **Simulação Online:** Você pode testar o comportamento do sistema diretamente no navegador:
    * ▶️ [Link para a Simulação no Wokwi](https://wokwi.com/projects/425977618350130177) 

## 🧪 Validação e Testes

* Testes funcionais realizados via simulação no Wokwi
* Verificação do comportamento da ISR durante diferentes estados do ciclo do semáforo
* Avaliação da integridade do estado dos LEDs após retorno da interrupção

## 📚 Evolução do Projeto
Esta é a primeira de uma série de práticas. Na sequência deste portfólio, outros exemplos serão apresentados utilizando o FreeRTOS no ESP32, demonstrando como o escalonamento de tarefas (Tasks) e semáforos binários simplificam a gestão de sistemas críticos e de tempo real. 

---
### Prof. Thiago José da Luz, PhD 
