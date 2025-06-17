/*
=========================================
| NOME: Stiven Richardy Silva Rodrigues |
| PRONTU?RIO: CB3030202                 |
| TURMA: ADS 371                        |
=========================================
*/

#include <iostream>
#include <locale.h>
#include <string>
#include <conio.h>

using namespace std;

struct No {
    float dado;
    No* prox;
};

// FILAS
struct FilaPonteiro {
    No* ini;
    No* fim;
};

FilaPonteiro* initPonteiro() {
    FilaPonteiro* f = new FilaPonteiro;
    f->ini = NULL;
    f->fim = NULL;
    return f;
}

int isEmpty(FilaPonteiro* f) {
    return (f->ini == NULL);
}

int count(FilaPonteiro* f) {
    int qtde = 0;
    No* no = f->ini;
    while (no != NULL) {
        qtde++;
        no = no->prox;
    }
    return qtde;
}

void enqueue(FilaPonteiro* f, float v) {
    No* no = new No;
    no->dado = v;
    no->prox = NULL;
    if (isEmpty(f)) {
        f->ini = no;
    } else {
        f->fim->prox = no;
    }
    f->fim = no;
}

float dequeue(FilaPonteiro* f) {
    float ret;
    if (isEmpty(f)) {
        ret = -1;
    } else {
        No* no = f->ini;
        ret = no->dado;
        f->ini = no->prox;
        if (f->ini == NULL) {
            f->fim = NULL;
        }
        free(no);
    }
    return ret;
}

void relatorioDeAtendimentos(FilaPonteiro* s) {
	No* aux = s->ini; 
	cout << "| Senhas atendidas durante a execu��o: " << endl;
	
	while (aux != NULL) {
		cout << "| Senha N� " << aux->dado << endl;
		aux = aux->prox;
	}
	cout << "| Total de atendimentos: " << count(s) << endl;
}

void freeFila(FilaPonteiro* f) {
    No* no = f->ini;
    while (no != NULL) {
        No* aux = no->prox;
        free(no);
        no = aux;
    }
    free(f);
}

// LISTA
struct Guiche {
	int id;
	FilaPonteiro* senhasAtendidas;
};

struct ListaGuiche {
	Guiche* guiche;
	ListaGuiche* ant;
};

ListaGuiche* init() {
	return NULL;
}

bool isEmpty(ListaGuiche* lista) {
	return (lista == NULL);
}

ListaGuiche* abreGuiche(Guiche* guiche, ListaGuiche* lista) {
	ListaGuiche* novoGuiche = new ListaGuiche;
	
	novoGuiche->guiche = guiche;
	novoGuiche->ant = lista;
	
	return novoGuiche;
}

ListaGuiche* pesquisaGuiche(int id, ListaGuiche* lista) {
    ListaGuiche* aux;
	aux = lista;
	
	while (aux != NULL && aux->guiche->id != id) {
		aux = aux->ant;
	}
	
	return aux;
}

// FUN??ES DE EXIBI??O
void exibeTitulo() {
    cout << string(50, '=') << endl
         << string(15, ' ') << "FILA DE ATENDIMENTO" << endl
         << string(50, '=') << endl;
}

void limpaTela() {
    cout << string(50, '=') << endl
         << "Pressione qualquer tecla..." << endl;
    _getch();
    system("cls");
}

int main(int argc, char** argv) {
    setlocale(LC_ALL, "");

    int opcao;
    int ii = 1;
    int id = 1;

    FilaPonteiro* senhasGeradas = initPonteiro();
    FilaPonteiro* senhasAtendidas = initPonteiro();
    ListaGuiche* guiches = init();

    exibeTitulo();
    cout << "| Bem vindo a fila de atendimento." << endl;
    limpaTela();

    do {
        exibeTitulo();
        cout << "| Senhas aguardando atendimento: " << count(senhasGeradas) << endl
             << string(50, '=') << endl
             << "| Lista de op��es: \n| 0. Sair\n| 1. Gerar senha\n| 2. Abrir guich�\n| 3. Realizar atendimento\n| 4. Listar senhas atendidas" << endl
             << "| Digite a op��o: ";
        cin >> opcao;
        system("cls");

        switch (opcao) {
            case 0:{
                if(isEmpty(senhasGeradas)) {
					exibeTitulo();
					cout << "| Voc� saiu do programa!\n| Senhas atendidas: " << count(senhasAtendidas) << endl
						 << string(50, '=') << endl;
                    freeFila(senhasGeradas);
                    freeFila(senhasAtendidas);
				} else {
					opcao = -1;
					exibeTitulo();
					cout << "| Op��o inv�lida, senhas aguardando atendimento." << endl;
					limpaTela();
				}
                break;
			}
            case 1: {
                exibeTitulo();
				enqueue(senhasGeradas, ii);
    			cout << "| Senha gerada com sucesso!" << endl
					 << "| Senha N� " << ii++ << endl;
				limpaTela();
                break;
			}
            case 2: {
            	exibeTitulo();
            	Guiche* abrir = new Guiche;
            	abrir->id = id;
            	abrir->senhasAtendidas = initPonteiro();
            	guiches = abreGuiche(abrir, guiches);
            	cout << "| Guich� aberto" << endl
            		 << "| Guich� N� " << id++ << endl;
  	  	  	    limpaTela();
            	break;
			}
			case 3:{
               	exibeTitulo();
               	if(isEmpty(guiches)) {
               		cout << "| Nenhum guich� abrido." << endl;	
				} else {
					if(!isEmpty(senhasGeradas)) {
						int num = 0;
                    	while(!pesquisaGuiche(num, guiches)) {
							cout << "| Digite o Guich�: ";
							cin >> num;
							if (pesquisaGuiche(num, guiches)) {
								Guiche* guicheSelecionado = pesquisaGuiche(num, guiches)->guiche;
								float senhaAtendida = senhasGeradas->ini->dado;
								enqueue(guicheSelecionado->senhasAtendidas, senhaAtendida);
						   	    cout << "| Senha atendida com sucesso." << endl 
								 	 << "| Senha N� " << senhaAtendida << endl;
						    	dequeue(senhasGeradas);
							} else {
								cout << "| Digite um Guich� v�lido." << endl;
							}
						}
					} else {
						cout << "| Nenhuma senhas aguardando atendimento." << endl;
					}
				}
			    limpaTela();
 	   	   	    break;
			}
            case 4: {
            	exibeTitulo();
            	if(isEmpty(guiches)) {
               		cout << "| Nenhum guich� aberto." << endl;	
				} else {
					int num = 0;
                	while(!pesquisaGuiche(num, guiches)) {
						cout << "| Digite o Guich�: ";
						cin >> num;
						if (pesquisaGuiche(num, guiches)) {
							Guiche* guicheAtual = pesquisaGuiche(num, guiches)->guiche;
							relatorioDeAtendimentos(guicheAtual->senhasAtendidas);
						} else {
							cout << "| Digite um Guich� v�lido." << endl;
						}
					}
				}
				limpaTela();
            	break;
			}
            default: {
            	exibeTitulo();
                cout << "| Op��o inv�lida. Tente novamente..." << endl;
                limpaTela();
			}
        }
    } while (opcao != 0);

    return 0;
}