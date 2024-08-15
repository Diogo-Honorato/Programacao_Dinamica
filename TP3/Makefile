COMPILADORC = gcc

CFLAGS = -Wall -Wextra -march=native -O2 -g -lm

# Nome do executável
EXECUTABLE = tp3

# Diretórios
HEADER_DIR = Headers
SRC_DIR = Sources
OBJ_DIR = Objetos

# Obter automaticamente todos os arquivos .c no diretório source
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Gerar nomes de arquivos .o a partir dos arquivos .c
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Regra para compilar todos os arquivos .o a partir dos arquivos .c
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	@$(COMPILADORC) $(CFLAGS) $^ -o $@

# Regra para criar diretórios e compilar cada arquivo .c em um arquivo .o correspondente
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | obj_dirs
	@$(COMPILADORC) $(CFLAGS) -I $(HEADER_DIR) -c $< -o $@

# Criação dos diretórios necessários para armazenar os arquivos .o
obj_dirs:
	@mkdir -p $(OBJ_DIR)

# Variáveis para argumentos
ARG1 = D
ARG2 = entrada.txt

# Para rodar com valgrind e verificar vazamentos de memória
leak: $(EXECUTABLE)
	@valgrind --leak-check=full ./$(EXECUTABLE) $(ARG1) $(ARG2)

# Para rodar o gdb com o programa compilado
debug: $(EXECUTABLE)
	gdb --args ./$(EXECUTABLE) $(ARG1) $(ARG2)

# Para rodar o ddd com o programa compilado
DDD: $(EXECUTABLE)
	ddd $(EXECUTABLE) $(ARG1) $(ARG2)

# Limpar arquivos objeto e o executável
clean:
	@rm -rf $(OBJ_DIR) $(EXECUTABLE)

.PHONY: all leak debug DDD clean
