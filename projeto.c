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
    int trocou = 0;
    for(int i = 0; i < n -1; i++){
        for(int j = 0; j < n - 1; j++){
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

void quickLeituraPorId(int ids[], int unidadeIds[], int meses[],int anos[],float consumos[],int inicio,int fim){
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
    quickLeituraPorId(ids, unidadeIds, meses, anos, consumos, inicio, p - 1);
    quickLeituraPorId(ids, unidadeIds, meses, anos, consumos, p + 1, fim);


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
    carregarUnidades("unidades.csv", unidadeIdsCatalogo, descricoes, MAX);
    for(int i = 0; i < 3; i++ ){
        printf("%d",unidadeIdsCatalogo[i]); 
        printf(" %s\n", descricoes[i]);
        
    }
    int total_leituras = carregarLeituras("leituras.txt", ids, unidadeIds, meses, anos, consumos, MAX);
    mergeSortLeituraPorId(ids, unidadeIds, meses, anos, consumos, 0, MAX - 2);
    for(int i = 0; i < total_leituras; i++){
        printf("%d %d %d %d %.1f \n", ids[i], unidadeIds[i], meses[i], anos[i], consumos[i]);

    }
}