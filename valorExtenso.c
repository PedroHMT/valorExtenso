#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

char *validaNum(int reais, int cent);
char *consultaMilhar(int valor);
char *consultaCentena(int valor, int i);
char *consultaDezena(int valor, int i, int i1);
char *consultaUnidade(int valor, int i);
FILE *dadosCheques;

int main(){
    setlocale(LC_ALL, "Portuguese");
    menu();
}

void menu(){
    float valor;
    int opcao, reais, centavos;
    home:
    printf("\n\n- Automação de Cheque Bancários -\n");
    printf("1 - Escrever um número por extenso.\n");
    printf("2 - Imprimir todos os números do arquivo na tela.");
    printf("\n\nSeleciona uma opção: ");
    scanf("%d",&opcao);
    switch(opcao){
        case 1:
            printf("\nInsira o valor (0 - 9999,99): ");
            scanf("%f", &valor);
            if((valor > 9999.99) || (valor <= 0)){
                printf("\n Valor fora do intervalo determinado.\n\n");
                goto home;
            }else{
                reais = (int)valor;
                centavos = (int)((valor - reais)*100);
                validaNum(reais, centavos);
                goto home;
            }
            break;
        case 2:
            printf("\n-- Imprimindo os valores --\n");
            readFile();
            break;
        default:
            printf("[ERROR]: Opção Inválida.");
            goto home;
            break;
    }
}

char *validaNum(int reais, int cent){
    char *milhar = "", *centena = "", *dezena = "", *unidade = "", *cent_dezena = "", *cent_unidade = "";
    int i;
    // REAIS
    if(reais >= 1000){
        milhar = consultaMilhar(reais);
        reais = reais % 1000;
    }

    if(reais >= 100){
        if(milhar != ""){
            centena = consultaCentena(reais, 1);
        }else if(milhar == ""){
            centena = consultaCentena(reais, 2);
        }
        reais = reais % 100;
    }

    if(reais >= 10 && reais < 20){
        if(milhar != "" || centena != ""){
            dezena = consultaDezena(reais, 1, 1);
        }else if(milhar == "" && centena == ""){
            dezena = consultaDezena(reais, 1, 2);
        }
        reais = 0;
    }else if(reais >= 20){
        if(milhar != "" || centena != ""){
            dezena = consultaDezena(reais, 2, 1);
        }else if(milhar == "" && centena == ""){
            dezena = consultaDezena(reais, 2, 2);
        }
        reais = reais % 10;
    }

    if(reais >= 1){
        if(milhar != "" || centena != "" || dezena != ""){
            unidade = consultaUnidade(reais, 1);
        }else if(milhar == "" && centena == "" && dezena == ""){
            unidade = consultaUnidade(reais, 2);
        }

    }
    // CENTAVOS
    if(cent >= 10 && cent < 20){
        cent_dezena = consultaDezena(cent, 1, 2);
        cent = 0;
    }else if(cent >= 20){
        cent_dezena = consultaDezena(cent, 2, 2);
        cent = cent % 10;
    }

    if(cent >= 1){
        if(cent_dezena != ""){
            cent_unidade = consultaUnidade(cent, 1);
        }else if(cent_dezena == ""){
            cent_unidade = consultaUnidade(cent, 2);
        }

    }else if(cent_dezena == "" && cent == 0){
        cent_unidade = "zero";
    }

    if(dadosCheques=fopen("dadosCheques.txt","a")){
        printf("%s%s%s%s reais e %s%s centavos\n", milhar, centena, dezena, unidade, cent_dezena, cent_unidade);
        fprintf(dadosCheques, "%s%s%s%s reais e %s%s centavos\n", milhar, centena, dezena, unidade, cent_dezena, cent_unidade);
        fclose(dadosCheques);
    }
}

char *consultaMilhar(int valor){
    char *extenso;
    int resto;
    if(valor >= 1000){
        resto = valor%1000;
        valor = valor - resto;
        switch(valor){
            case 1000:
                extenso = "mil";
                break;
            case 2000:
                extenso = "dois mil";
                break;
            case 3000:
                extenso = "três mil";
                break;
            case 4000:
                extenso = "quatro mil";
                break;
            case 5000:
                extenso = "cinco mil";
                break;
            case 6000:
                extenso = "seis mil";
                break;
            case 7000:
                extenso = "sete mil";
                break;
            case 8000:
                extenso = "oito mil";
                break;
            case 9000:
                extenso = "nove mil";
                break;
        }
    }
    return extenso;
}

char *consultaCentena(int valor, int i){
    char *extenso;
    int resto;
    resto = valor%100;
    valor = valor - resto;
    if(resto == 0){
        switch(valor){
        case 100:
            if(i == 1){ extenso = " e cem"; }
            else if(i == 2){ extenso = "cem"; }
            break;
        case 200:
            if(i == 1){ extenso = " e duzentos"; }
            else if(i == 2){ extenso = "duzentos"; }
            break;
        case 300:
            if(i == 1){ extenso = " e trezentos"; }
            else if(i == 2){ extenso = "trezentos"; }
            break;
        case 400:
            if(i == 1){ extenso = " e quatrocentos"; }
            else if(i == 2){ extenso = "quatrocentos"; }
            break;
        case 500:
            if(i == 1){ extenso = " e quinhentos"; }
            else if(i == 2){ extenso = "quinhentos"; }
            break;
        case 600:
            if(i == 1){ extenso = " e seissentos"; }
            else if(i == 2){ extenso = "seissentos"; }
            break;
        case 700:
            if(i == 1){ extenso = " e setecentos"; }
            else if(i == 2){ extenso = "setecentos"; }
            break;
        case 800:
            if(i == 1){ extenso = " e oitocentos"; }
            else if(i == 2){ extenso = "oitocentos"; }
            break;
        case 900:
            if(i == 1){ extenso = "e novecentos"; }
            else if(i == 2){ extenso = "novecentos"; }
            break;
        }
    }else if(resto != 0){
        switch(valor){
        case 100:
            extenso = " cento";
            break;
        case 200:
            extenso = " duzentos";
            break;
        case 300:
            extenso = " trezentos";
            break;
        case 400:
            extenso = " quatrocentos";
            break;
        case 500:
            extenso = " quinhentos";
            break;
        case 600:
            extenso = " seiscentos";
            break;
        case 700:
            extenso = " setecentos";
            break;
        case 800:
            extenso = " oitocentos";
            break;
        case 900:
            extenso = " novecentos";
            break;
        }
    }
    return extenso;
}

char *consultaDezena(int valor, int i, int i1){
    char *extenso;
    int resto;
    if(i == 1){
        switch(valor){
            case 10:
                if(i1 == 1){ extenso = " e dez"; }
                else if(i1 == 2){ extenso = "dez"; }
                break;
            case 11:
                if(i1 == 1){ extenso = " e onze"; }
                else if(i1 == 2){ extenso = "onze"; }
                break;
            case 12:
                if(i1 == 1){ extenso = " e doze"; }
                else if(i1 == 2){ extenso = "doze"; }
                break;
            case 13:
                if(i1 == 1){ extenso = " e treze"; }
                else if(i1 == 2){ extenso = "treze"; }
                break;
            case 14:
                if(i1 == 1){ extenso = " e catorze"; }
                else if(i1 == 2){ extenso = "catorze"; }
                extenso = " catorze";
                break;
            case 15:
                if(i1 == 1){ extenso = " e quinze"; }
                else if(i1 == 2){ extenso = "quinze"; }
                break;
            case 16:
                if(i1 == 1){ extenso = " e dezesseis"; }
                else if(i1 == 2){ extenso = "dezesseis"; }
                break;
            case 17:
                if(i1 == 1){ extenso = " e dezessete"; }
                else if(i1 == 2){ extenso = "dezessete"; }
                break;
            case 18:
                if(i1 == 1){ extenso = " e dezoito"; }
                else if(i1 == 2){ extenso = "dezoito"; }
                break;
            case 19:
                if(i1 == 1){ extenso = " e dezenove"; }
                else if(i1 == 2){ extenso = "dezenove"; }
                break;
        }
    }else if(i == 2){
        resto = valor%10;
        valor = valor - resto;
        switch(valor){
            case 20:
                if(i1 == 1){ extenso = " e vinte"; }
                else if(i1 == 2){ extenso = "vinte"; }
                break;
            case 30:
                if(i1 == 1){ extenso = " e trinta"; }
                else if(i1 == 2){ extenso = "trinta"; }
                break;
            case 40:
                if(i1 == 1){ extenso = " e quarenta"; }
                else if(i1 == 2){ extenso = "quarenta"; }
                break;
            case 50:
                if(i1 == 1){ extenso = " e cinquenta"; }
                else if(i1 == 2){ extenso = "cinquenta"; }
                break;
            case 60:
                if(i1 == 1){ extenso = " e sessenta"; }
                else if(i1 == 2){ extenso = "sessenta"; }
                break;
            case 70:
                if(i1 == 1){ extenso = " e setenta"; }
                else if(i1 == 2){ extenso = "setenta"; }
                break;
            case 80:
                if(i1 == 1){ extenso = " e oitenta"; }
                else if(i1 == 2){ extenso = "oitenta"; }
                break;
            case 90:
                if(i1 == 1){ extenso = " e noventa"; }
                else if(i1 == 2){ extenso = "noventa"; }
                break;
        }
    }
    return extenso;
}

char *consultaUnidade(int valor, int i){
    char *extenso;
    switch(valor){
        case 1:
            if(i == 1){ extenso = " e um"; }
            else if(i == 2){ extenso = "um"; }
            break;
        case 2:
            if(i == 1){ extenso = " e dois"; }
            else if(i == 2){ extenso = "dois"; }
            break;
        case 3:
            if(i == 1){ extenso = " e três"; }
            else if(i == 2){ extenso = "três"; }
            break;
        case 4:
            if(i == 1){ extenso = " e quatro"; }
            else if(i == 2){ extenso = "quatro"; }
            break;
        case 5:
            if(i == 1){ extenso = " e cinco"; }
            else if(i == 2){ extenso = "cinco"; }
            break;
        case 6:
            if(i == 1){ extenso = " e seis"; }
            else if(i == 2){ extenso = "seis"; }
            break;
        case 7:
            if(i == 1){ extenso = " e sete"; }
            else if(i == 2){ extenso = "sete"; }
            break;
        case 8:
            if(i == 1){ extenso = " e oito"; }
            else if(i == 2){ extenso = "oito"; }
            break;
        case 9:
            if(i == 1){ extenso = " e nove"; }
            else if(i == 2){ extenso = "nove"; }
            break;
    }
    return extenso;
}

void readFile(){
    char *linha;
    char temp[100];
    dadosCheques=fopen("dadosCheques.txt","r");
    while(!feof(dadosCheques)){
        if((linha = fgets(temp, 100, dadosCheques)) != NULL){
            printf("%s", linha);
        }
    }
    fclose(dadosCheques);
}
