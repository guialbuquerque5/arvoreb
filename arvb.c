#include "arvb.h"
/* ============================================================================================ */
/* --- Alocação --- */

/*Função para criar e inicializar uma árvore B:*/
Arvore *criar()
{
   Arvore *a = (Arvore *)malloc(sizeof(Arvore));
   a->n = 0;
   a->folha = TRUE;
   //array para inicializar chaves INIT
   /*
   for(int i =0; i < 2*T; i++){
      a->chaves[i] = CHAVES_NULL;
   }*/
   return a;
}

/* ============================================================================================ */
/* --- Impressão --- */

void imprimir(Arvore *a, int nivel)
{

   int i;

   /*Imprime recuo para definir o nível do nó: */
   for (i = 0; i < nivel; i++)
   {
      printf("  ");
   }

   /*Imprime as chaves armazenadas no nó: */
   printf("|");
   for (i = 0; i < a->n; i++)
   {
      //printf("%c|", a->chaves[i]);
      printf("%02d|", a->chaves[i]);
   }
   printf("\n");

   /*Recursivamente imprime as chaves dos filhos: */
   for (i = 0; i <= a->n; i++)
   {
      if (a->folha == FALSE)
      {
         imprimir(a->filhos[i], nivel + 1);
      }
   }
}

/* ============================================================================================ */
/* --- Busca --- */

/*Função para buscar uma chave em uma árvore B:*/
int buscar(Arvore *a, TIPO chave)
{

   int i = 0;

   /*Procurando a chave no vetor de chaves: */
   while ((i < a->n) && (chave > a->chaves[i]))
   {
      i = i + 1;
   }

   if (chave == a->chaves[i])
   {
      /*Achou a chave!*/
      return i;
   }
   else if (a->folha)
   {
      /*Não achou a chave!*/
      return NOT_FOUND;
   }
   else
   {
      /*Buscando a chave no filho: */
      if (a->folha == FALSE)
      {
         return buscar(a->filhos[i], chave);
      }
   }
}

/* ============================================================================================ */
/* --- Inserção --- */

Arvore *dividir_no(Arvore *x, int nodeIndex)
{

   Arvore* new_node = criar();//NO para as maiores chaves
   Arvore* full_node = x->filhos[nodeIndex];//NO para permancer as menores chaves
   new_node->folha = full_node->folha;
   new_node->n = T-1;
   for(int i = 0; i < T-1; i++){
      new_node->chaves[i] = full_node->chaves[i+T];
   }
   if(!isFolha(full_node)){
      for(int i = 0; i< T; i++)
         new_node->filhos[i] = full_node->filhos[i+T];
   }
   full_node->n = T-1;

   for(int i = x->n; i >= nodeIndex; i--){
      x->filhos[i+1] = x->filhos[i];
   }
   x->filhos[nodeIndex+1] = new_node;

   for(int i = x->n-1; i >= nodeIndex; i--){
      x->chaves[i+1] = x->chaves[i]; 
   }
   x->chaves[nodeIndex] = full_node->chaves[T-1];//retira a chave da posição mediana
   ++x->n;
   return x;
}

Arvore *inserir_arvore_nao_cheia(Arvore *x, TIPO k) // mudar nome para nó nao cheio
{
   int i = x->n-1;
   if(isFolha(x)){
      while(i >=0  && k<x->chaves[i]){
            x->chaves[i+1] = x->chaves[i]; //joga a chave uma posição pra frente >>
            --i;
      }
      x->chaves[++i] = k;
      ++x->n;
      return x;
   }else{
      while(i>=0 && k <x->chaves[i]) --i;
      ++i; // paramos uma posição atrás do node a inserir
      if(isFull(x->filhos[i])){
         x = dividir_no(x,i);
         if(k>x->chaves[i])
            i++;
      }
      inserir_arvore_nao_cheia(x->filhos[i],k);
   }
   return x;
   
}


Arvore *inserir(Arvore *raiz, TIPO chave)
{
   Arvore *r = raiz;
   if(isFull(r)){
      Arvore *temp = criar();
      raiz = temp;
      temp->folha = FALSE;
      temp->n = 0;
      temp->filhos[0] = r;
      dividir_no(temp,0);
      return inserir_arvore_nao_cheia(temp,chave);
   }
   else{
      Arvore* e = inserir_arvore_nao_cheia(r,chave);
      //imprimir(e,0);
      return e;
   }
}


/* ============================================================================================ */
/* --- Tools --- */

int isFull(Arvore* a){
   if(a->n == 2 * T - 1)
      return TRUE;
   else
      return FALSE;
}

int isFolha(Arvore* a){
   return a->folha;
}

