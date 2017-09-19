#ifndef SIMULADOR_MIPS_CONTROL_H
#define SIMULADOR_MIPS_CONTROL_H

#include <string>

typedef enum {
    TS_except_alignment_word,
    TS_except_alignment_halfword,
    TS_except_syscall_exit,
    TS_except_syscall_undefined
} TS_except;

/**
* Imprime o conteúdo da memória a partir do endereço start
* até o endereço end.
* @param start
* Primeiro endereco de memória a ser impresso
* @param end
* Endereco no qual a memória pára de ser impressa
* @param format
* Se format == 'h', é usado o formato hexadecimal.
* Se format == 'd', é usado o formato decimal.
*/
void dump_mem(int start, int end, char format);

/**
 * Lê o conteúdo do arquivo binário para a memória emulada
 * iniciando em start_addr.
 * @param start_addr
 * endereço (em words) a partir do qual o conteúdo do arquivo será escrito
 * @param filename
 * nome do arquivo binário a ser lido para a memória emulada
 */
void load_file(int start_addr, const char *filename);

/**
 * Imprime o conteúdo dos registradores do MIPS.
 * @param format
 * Se format == 'h', é usado o formato hexadecimal.
 * Se format == 'd', é usado o formato decimal.
 */
void dump_reg(char format);

/**
 * Carrega a próxima instrução da memória emulada, a coloca em 'ri'
 * e atualiza o valor de PC para apontar para a próxima instrução
 */
void fetch();

/**
 * Extrai todos os campos da instrução:
 * - opcode: código da operação
 * - rs: índice do primeiro registrador fonte
 * - rt: índice do segundo registrador fonte
 * - rd: índice do registrador destino, que recebe o resultado da operação
 * - shamnt: quantidade de deslocamento em instruções shift e rotate
 * - funct: código auxiliar para determinar a instrução a ser executada
 * - k16: constante de 16 bits, valor imediato em instruções tipo I
 * - k26: constante de 26 bits, para instruções tipo J
 */
void decode();

/**
 * Executa a última função lida por 'fetch' e decodificada por 'decode'
 */
void execute();

/**
 * Realiza um ciclo fetch -> decode -> execute
 */
void step();

/**
 * Executa o programa até encontrar uma chamada de sistema
 * para encerramento ou até o PC ultrapassar o limite do
 * segmento de código
 */
void run();

#endif //SIMULADOR_MIPS_CONTROL_H