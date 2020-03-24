/* Função responsável por calcular o coeficiente de aglomeração de um vértice */
float CoefDeAglomeracao(TipoGrafo *Grafo, int Golfinho){
    int adjacente;
    float cont = 0, n = 0, Resultado;
    Apontador aux1, aux2, aux3;

    // Calcula quantos vértices são adjacentes ao golfinho
    aux1 = Grafo->Adj[Golfinho].Primeiro->Prox;
    while(aux1 != NULL){
        n++;
        aux1 = aux1->Prox;
    }


    aux1 = Grafo->Adj[Golfinho].Primeiro->Prox;
    while(aux1 != NULL){
        adjacente = aux1->Vertice;
        aux2 = aux1->Prox;

        // Calcula quantos vértices adjacentes de um golfinho são também adjacentes a um determinado vértice adjacente
        while(aux2 != NULL){
            aux3 = Grafo->Adj[aux2->Vertice].Primeiro->Prox;

            while(aux3 != NULL){
                if(aux3->Vertice == adjacente){
                    cont++;
                }
                aux3 = aux3->Prox;
            }

            aux2 = aux2->Prox;
        }

        aux1 = aux1->Prox;
    }

    Resultado = cont / (n * ((n-1) / 2));
    printf("Golfinho %d: %.2f\n", Golfinho, Resultado);

    return Resultado;
}

/* Função responsável por calcular o coeficiente médio de aglomeração do grafo */
void MediaDeAglomeracao(TipoGrafo *Grafo){
    float Media = 0;
    int i;

    for(i=1; i<=62; i++){
        Media = Media + CoefDeAglomeracao(Grafo, i);
    }

    Media = Media / 62;

    printf("\nCOEFICIENTE MEDIO DE AGLOMERACAO DO GRAFO: %.2f\n", Media);
}

printf("\n\n---------- COEFICIENTE DE AGLOMERACAO ----------\n");
    MediaDeAglomeracao(&Grafo);