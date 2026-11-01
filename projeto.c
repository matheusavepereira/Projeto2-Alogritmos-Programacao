#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000
int ids[MAX];
int unidadeIds[MAX];
int meses[MAX];
int anos[MAX];
float consumos[MAX];

int unidadeIdsCatalogo[MAX];
char descricoes[MAX][50];

int carregarUnidades(const char nomeArquivo[], int unidadeIds[], char descricoes[][50], int max) {
    // Abre o arquivo em modo de leitura
    FILE* arquivo = fopen(nomeArquivo, "r");
    
    // Retorna -1 se houver erro ao abrir o arquivo
    if (arquivo == NULL) {
        return -1;
    }

    char linha[max];
    int registrosCarregados = 0;

    // Lê o arquivo linha por linha até o fim ou até atingir o limite 'max'
    while (registrosCarregados < max && fgets(linha, sizeof(linha), arquivo)) {
        // Remove a quebra de linha (\n) do final, se existir
        linha[strcspn(linha, "\r\n")] = 0;

        // Ignora linhas vazias que possam estar no arquivo
        if (strlen(linha) == 0) {
            continue;
        }

        // Separa o primeiro elemento: ID da Unidade
        char* token = strtok(linha, ";");
        if (token != NULL) {
            unidadeIds[registrosCarregados] = atoi(token); // Converte para int
            
            // 5. Separa o segundo elemento: Descrição
            token = strtok(NULL, ";");
            if (token != NULL) {
                // Copia com segurança limitando a 49 caracteres (+1 do \0)
                strncpy(descricoes[registrosCarregados], token, 49);
                descricoes[registrosCarregados][49] = '\0'; // Garante o fim da string
            } else {
                // Caso o arquivo tenha o ID mas falte a descrição
                descricoes[registrosCarregados][0] = '\0';
            }

            // Incrementa o contador de registros bem-sucedidos
            registrosCarregados++;
        }
    }

    // 6. Fecha o arquivo e retorna a quantidade de registros carregados
    fclose(arquivo);
    return registrosCarregados;
}

int carregarLeituras(const char nomeArquivo[], 
                    int ids[],
                    int unidadeIds[],
                    int meses[],
                    int anos[],
                    float consumos[],
                    int max){
    
    FILE *leitura = fopen(nomeArquivo, "r");
    
    if(leitura == NULL){
        return -1;
    }
    
    int i = 0;
    while(i < max && fscanf(leitura, "%d %d %d %d %f", 
                            &ids[i],
                            &unidadeIds[i],
                            &meses[i],
                            &anos[i],
                            &consumos[i]) == 5){
        i++;
    }
    
    fclose(leitura);
    return i;
}

int buscaBinaria(int ids[], int n, int idProcurado){
    int inicio = 0;
    int fim = n - 1;
    
    while(inicio <= fim){
        int meio = inicio + (fim - inicio)/2;
        
        if(ids[meio] == idProcurado){
            return meio;
        }
        if(ids[meio] < idProcurado){
            inicio = meio + 1;
        }
        else{
            fim = meio - 1;
        }
    }
    
    return -1;
}

float calcularConsumoUnidade(int unidadeIds[],
                            float consumos[],
                            int n,
                            int unidadeId){
    float consumoTotal = 0;

    for(int i = 0; i < n; i++){
        if(unidadeIds[i] == unidadeId){
            consumoTotal += consumos[i];
        }
    }

    return consumoTotal;
}

float calcularConsumoPeriodo(int meses[],
                            int anos[],
                            float consumos[],
                            int n,
                            int mesInicial,
                            int anoInicial,
                            int mesFinal,
                            int anoFinal){
    float consumoTotal = 0;
    int inicio = anoInicial * 12 + mesInicial;
    int fim = anoFinal * 12 + mesFinal;

    for(int i = 0; i < n; i++){
        int atual = anos[i] * 12 + meses[i];
        if(atual >= inicio && atual <= fim){
            consumoTotal += consumos[i];
        }
    }

    return consumoTotal;
}

int main(){
    carregarUnidades("unidades.csv", unidadeIdsCatalogo, descricoes, MAX);
    for(int i = 0; i < 3; i++ ){
        printf("%d",unidadeIds[i]); 
        printf(" %s\n", descricoes[i]);
        
    }
}