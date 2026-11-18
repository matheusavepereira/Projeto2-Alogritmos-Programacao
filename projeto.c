/*
Bruno Rosa Maia - RA: 10769813
João Vitor Paro Nunes dos Santos - RA: 10769888
Matheus Pereira - RA: 1296734
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 1000
int ids[MAX];
int unidadeIds[MAX];
int meses[MAX];
int anos[MAX];
float consumos[MAX];

int unidadeIdsCatalogo[MAX];
char descricoes[MAX][50];

int carregarUnidades(const char nomeArquivo[], int unidadeIdsCatalogo[], char descricoes[][50], int max) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    
    if (arquivo == NULL) {
        return -1;
    }

    char linha[max];
    int registrosCarregados = 0;

    while (registrosCarregados < max && fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\r\n")] = 0;

        if (strlen(linha) == 0) {
            continue;
        }

        char* token = strtok(linha, ";");
        if (token != NULL) {
            unidadeIdsCatalogo[registrosCarregados] = atoi(token); 
            
            token = strtok(NULL, ";");
            if (token != NULL) {
                strncpy(descricoes[registrosCarregados], token, 49);
                descricoes[registrosCarregados][49] = '\0'; 
            } else {
                descricoes[registrosCarregados][0] = '\0';
            }
            registrosCarregados++;
        }
    }
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

int buscaLinear(int ids[], int n, int idProcurado){
    for(int i = 0; i < n; i++){
        if(ids[i] == idProcurado){
            return i;
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

int encontrarUnidadeMaiorConsumo(int unidadeIds[], float consumos[], int n){
    if(n <= 0){
        return -1;
    }
    
    int melhorId = unidadeIds[0];
    float melhorTotal = calcularConsumoUnidade(unidadeIds, consumos, n, melhorId);
    
    for(int i = 1; i < n; i++){
        int idAtual = unidadeIds[i];
        float totalAtual = calcularConsumoUnidade(unidadeIds, consumos, n, idAtual);
        
        if(totalAtual > melhorTotal || (totalAtual == melhorTotal && idAtual < melhorId)){
            melhorId = idAtual;
            melhorTotal = totalAtual;
        }
    }
    
    return melhorId;
}

void trocar_int(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}
void trocar_float(float *x, float *y){
    float temp = *x;
    *x = *y;
    *y = temp;
}

void bubbleSortLeituraPorId(int ids[], int unidadeIds[], int meses[], int anos[], float consumos[], int n){
    for(int i = 0; i < n -1; i++){
        int trocou = 0;
        for(int j = 0; j < n - 1 - i; j++){
            if(ids[j] > ids[j + 1]){
                trocar_int(&ids[j], &ids[j + 1]);
                trocar_int(&unidadeIds[j], &unidadeIds[j + 1]);
                trocar_int(&meses[j], &meses[j + 1]);
                trocar_int(&anos[j], &anos[j + 1]);
                trocar_float(&consumos[j], &consumos[j + 1]);
                trocou = 1;
            }
        }
        if(trocou == 0){
            return;
        }
    }
}

void insertionSortLeituraPorId(int ids[], int unidadeIds[], int meses[], int anos[], float consumos[], int n){
    for(int i = 1; i < n; i ++){
        int chave = ids[i];
        int chave1 = unidadeIds[i];
        int chave2 = meses[i];
        int chave3 = anos[i];
        float chave4 = consumos[i];
        int j = i -1;
        while(j >= 0 && ids[j] > chave){
            ids[j + 1] = ids[j];
            unidadeIds[j + 1] = unidadeIds[j];
            meses[j + 1] = meses[j];
            anos[j + 1] = anos[j];
            consumos[j + 1] = consumos[j]; 
            j = j -1;
        }
        ids[j + 1] = chave;
        unidadeIds[j + 1] = chave1;
        meses[j + 1] = chave2;
        anos[j + 1] = chave3;
        consumos[j + 1] = chave4;
    }

}
void selectionSortLeituraPorId(int ids[], int unidadeIds[], int meses[], int anos[], float consumos[], int n){
    for(int i = 0; i < n; i++){
        int minimo = i;
        for(int j = i + 1; j < n;j++){
            if(ids[j] < ids[minimo]){
                minimo = j;
            }

        }
        if(minimo != i){
            trocar_int(&ids[minimo], &ids[i]);
            trocar_int(&unidadeIds[minimo], &unidadeIds[i]);
            trocar_int(&meses[minimo], &meses[i]);
            trocar_int(&anos[minimo], &anos[i]);
            trocar_float(&consumos[minimo], &consumos[i]);

        }
    }
}

void quickSortLeituraPorId(int ids[], int unidadeIds[], int meses[],int anos[],float consumos[],int inicio,int fim){
    if (inicio >= fim){
        return;
    }
    int pivo = ids[fim];
    int i = inicio;

    for(int j = inicio; j < fim; j++){
        if(ids[j] < pivo){
            trocar_int(&ids[i], &ids[j]);
            trocar_int(&unidadeIds[i], &unidadeIds[j]);
            trocar_int(&meses[i], &meses[j]);
            trocar_int(&anos[i], &anos[j]);
            trocar_float(&consumos[i], &consumos[j]);
            i++;
        }
    }
    trocar_int(&ids[i], &ids[fim]);
    trocar_int(&unidadeIds[i], &unidadeIds[fim]);
    trocar_int(&meses[i], &meses[fim]);
    trocar_int(&anos[i], &anos[fim]);
    trocar_float(&consumos[i], &consumos[fim]);
    int p = i;
    quickSortLeituraPorId(ids, unidadeIds, meses, anos, consumos, inicio, p - 1);
    quickSortLeituraPorId(ids, unidadeIds, meses, anos, consumos, p + 1, fim);


}


void mergeSortLeituraPorId(int ids[], int unidadeIds[], int meses[], int anos[], float consumos[], int inicio, int fim) {
    if (inicio >= fim) {
        return;
    }

    int meio = inicio + (fim - inicio) / 2;

    mergeSortLeituraPorId(ids, unidadeIds, meses, anos, consumos, inicio, meio);
    mergeSortLeituraPorId(ids, unidadeIds, meses, anos, consumos, meio + 1, fim);


    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    int L_ids[n1], L_unidades[n1], L_meses[n1], L_anos[n1];
    float L_consumos[n1];

    int R_ids[n2], R_unidades[n2], R_meses[n2], R_anos[n2];
    float R_consumos[n2];

    for (int i = 0; i < n1; i++) {
        L_ids[i] = ids[inicio + i];
        L_unidades[i] = unidadeIds[inicio + i];
        L_meses[i] = meses[inicio + i];
        L_anos[i] = anos[inicio + i];
        L_consumos[i] = consumos[inicio + i];
    }

    for (int j = 0; j < n2; j++) {
        R_ids[j] = ids[meio + 1 + j];
        R_unidades[j] = unidadeIds[meio + 1 + j];
        R_meses[j] = meses[meio + 1 + j];
        R_anos[j] = anos[meio + 1 + j];
        R_consumos[j] = consumos[meio + 1 + j];
    }

    int i = 0, j = 0, k = inicio;

    while (i < n1 && j < n2) {
        if (L_ids[i] <= R_ids[j]) {
            ids[k] = L_ids[i];
            unidadeIds[k] = L_unidades[i];
            meses[k] = L_meses[i];
            anos[k] = L_anos[i];
            consumos[k] = L_consumos[i];
            i++;
        } else {
            ids[k] = R_ids[j];
            unidadeIds[k] = R_unidades[j];
            meses[k] = R_meses[j];
            anos[k] = R_anos[j];
            consumos[k] = R_consumos[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        ids[k] = L_ids[i];
        unidadeIds[k] = L_unidades[i];
        meses[k] = L_meses[i];
        anos[k] = L_anos[i];
        consumos[k] = L_consumos[i];
        i++;
        k++;
    }

    while (j < n2) {
        ids[k] = R_ids[j];
        unidadeIds[k] = R_unidades[j];
        meses[k] = R_meses[j];
        anos[k] = R_anos[j];
        consumos[k] = R_consumos[j];
        j++;
        k++;
    }
}

int main(){
    int total_unidades = carregarUnidades("unidades.csv", unidadeIdsCatalogo, descricoes, MAX);
    if(total_unidades == -1){
        printf("Erro ao abrir o arquivo unidades.csv. Encerrando o programa.\n");
        return 1;
    }
    
    int total_leituras = carregarLeituras("leituras.txt", ids, unidadeIds, meses, anos, consumos, MAX);
    if(total_leituras == -1){
        printf("Erro ao abrir o arquivo leituras.txt. Encerrando o programa.\n");
        return 1;
    }

    int opcao;
    bool ordenado = false;

    do{
        printf("\n===== SISTEMA DE ANALISE DE CONSUMO DE ENERGIA =====\n");
        printf("\n1. Mostrar leituras ordenadas por ID");
        printf("\n2. Buscar leitura por ID");
        printf("\n3. Calcular consumo de uma unidade");
        printf("\n4. Calcular consumo em um periodo");
        printf("\n5. Identificar unidade com maior consumo");
        printf("\n6. Sair da aplicacao\n");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:{
                if(!ordenado){
                    int ordenacao;
                    printf("\nEscolha o algoritmo de ordenacao:\n");
                    printf("\n1. Bubble Sort");
                    printf("\n2. Insertion Sort");
                    printf("\n3. Selection Sort");
                    printf("\n4. Quick Sort");
                    printf("\n5. Merge Sort\n");
                    printf("\nOpcao: ");
                    scanf("%d", &ordenacao);

                    switch(ordenacao){
                        case 1:
                            bubbleSortLeituraPorId(ids, unidadeIds, meses, anos, consumos, total_leituras);
                            break;
                        case 2:
                            insertionSortLeituraPorId(ids, unidadeIds, meses, anos, consumos, total_leituras);
                            break;
                        case 3:
                            selectionSortLeituraPorId(ids, unidadeIds, meses, anos, consumos, total_leituras);
                            break;
                        case 4:
                            quickSortLeituraPorId(ids, unidadeIds, meses, anos, consumos, 0, total_leituras - 1);
                            break;
                        case 5:
                            mergeSortLeituraPorId(ids, unidadeIds, meses, anos, consumos, 0, total_leituras - 1);
                            break;
                        default:
                            printf("\nOpcao invalida.\n");
                            continue;
                    }
                    ordenado = true;
                }

                printf("\nLeituras ordenadas por ID:\n");
                printf("ID | Unidade | Descricao | Mes | Ano | Consumo (kWh)\n");
                for(int i = 0; i < total_leituras; i++){
                    int j = buscaLinear(unidadeIdsCatalogo, total_unidades, unidadeIds[i]);
                    printf("%d | %d | %s | %d | %d | %.2f\n", ids[i], unidadeIds[i], descricoes[j], meses[i], anos[i], consumos[i]);
                }
                break;
            }
            case 2:{
                int idBusca, opcaoBusca, pos;

                printf("\nDigite o ID da leitura: ");
                scanf("%d", &idBusca);
                
                printf("\nEscolha o algoritmo de busca:\n");
                printf("\n1. Busca linear");
                printf("\n2. Busca binaria\n");
                printf("\nOpcao: ");
                scanf("%d", &opcaoBusca);

                if(opcaoBusca == 1){
                    pos = buscaLinear(ids, total_leituras, idBusca);
                }
                else if(opcaoBusca == 2){
                    if(!ordenado){
                        insertionSortLeituraPorId(ids, unidadeIds, meses, anos, consumos, total_leituras);
                        ordenado = true;
                    }
                    pos = buscaBinaria(ids, total_leituras, idBusca);
                }
                else{
                    printf("Opcao invalida.\n");
                    break;
                }

                if(pos == -1){
                    printf("\nLeitura nao encontrada.\n");
                }
                else{
                    int j = buscaLinear(unidadeIdsCatalogo, total_unidades, unidadeIds[pos]);
                    printf("\nLeitura encontrada:\n");
                    printf("Unidade: %d\n", unidadeIds[pos]);
                    printf("Descricao: %s\n", descricoes[j]);
                    printf("Mes: %d\n", meses[pos]);
                    printf("Ano: %d\n", anos[pos]);
                    printf("Consumo: %.2f kWh\n", consumos[pos]);
                }
                break;
            }
            case 3:{
                int idUnidade;
                printf("\nDigite o ID da unidade: ");
                scanf("%d", &idUnidade);
                
                int j = buscaLinear(unidadeIdsCatalogo, total_unidades, idUnidade);
                if(j == -1){
                    printf("\nUnidade nao encontrada.\n");
                }
                else{
                    printf("\nConsumo da Unidade:\n");
                    printf("Unidade: %d\n", idUnidade);
                    printf("Descricao: %s\n", descricoes[j]);
                    printf("Consumo total: %.2f kWh\n", calcularConsumoUnidade(unidadeIds, consumos, total_leituras, idUnidade));
                }
                break;
            }
            case 4:{
                int mesIni, anoIni, mesFim, anoFim;
                printf("\nDigite o mes inicial: ");
                scanf("%d", &mesIni);
                printf("\nDigite o ano inicial: ");
                scanf("%d", &anoIni);
                printf("\nDigite o mes final: ");
                scanf("%d", &mesFim);
                printf("\nDigite o ano final: ");
                scanf("%d", &anoFim);

                if(mesIni < 1 || mesIni > 12 || mesFim < 1 || mesFim > 12 || anoIni * 12 + mesIni > anoFim * 12 + mesFim){
                    printf("\nPeriodo invalido.\n");
                }
                else{
                    printf("\nConsumo no periodo:\n");
                    printf("Periodo: %02d/%d ate %02d/%d\n", mesIni, anoIni, mesFim, anoFim);
                    printf("Consumo total: %.2f kWh\n", calcularConsumoPeriodo(meses, anos, consumos, total_leituras, mesIni, anoIni, mesFim, anoFim));
                }
                break;
            }
            case 5:{
                int idMaior = encontrarUnidadeMaiorConsumo(unidadeIds, consumos, total_leituras);
                if(idMaior == -1){
                    printf("\nNao ha leituras carregadas.\n");
                }
                else{
                    int j = buscaLinear(unidadeIdsCatalogo, total_unidades, idMaior);
                    printf("\nUnidade com maior consumo:\n");
                    printf("Unidade: %d\n", idMaior);
                    printf("Descricao: %s\n", descricoes[j]);
                    printf("Consumo total: %.2f kWh\n", calcularConsumoUnidade(unidadeIds, consumos, total_leituras, idMaior));
                }
                break;
            }
            case 6:
                printf("\nEncerrando o programa.\n");
                break;
            
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
        }
    } while(opcao != 6);

    return 0;
}