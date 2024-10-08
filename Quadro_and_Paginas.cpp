#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <vector>

using namespace std;

bool estaPresente(const deque<int>& pag, int proc) {
    for (int q : pag) {
        if (q == proc) {
            return true;
        }
    }
    return false;
}

int posicaoPagina(const deque<int>& pag, int proc) {
    for (int i = 0; i < pag.size(); ++i) {
        if (pag[i] == proc) {
            return i;
        }
    }
    return -1;
}

int fifo(int quadro, const vector<int>& processos){
    deque<int> pag;
    int faltas=0;

    for(int proc : processos){
        if(!estaPresente(pag, proc)){
            if(pag.size()==quadro)
                pag.pop_front();
            pag.push_back(proc);
            faltas++;
        }
    }
    return faltas;
}

int longe(int quadro, const vector<int>& processos){
    deque<int> pag;
    int faltas=0;

    for(int proc : processos){
        int distancia=posicaoPagina(pag, proc);
        if(distancia==-1){
            if(pag.size()==quadro)
                pag.pop_front();
            faltas++;
        }
        else{
            pag.erase(pag.begin()+distancia);
        }
        pag.push_back(proc);
    }

    return faltas;
}

int otm(int quadro, const vector<int>& processos){
    deque<int> pag;
    int faltas=0;

    for(int i=0; i < processos.size(); ++i){
        int proc = processos[i];
        
        if(!estaPresente(pag, proc)){
            if(pag.size()==quadro){
        
                int proxRemove=-1;
                int mais_dist=i;
                
                for(int j=0; j<pag.size();++j){
                    int k;
                    
                    for(k=i+1;k<processos.size();++k){
                        if(pag[j]==processos[k])
                            break;
                    }

                    if(k>mais_dist){
                        mais_dist=k;
                        proxRemove=j;
                    }

                }
                pag.erase(pag.begin()+proxRemove);
            }
            pag.push_back(proc);
            faltas++;
        }
    }
    return faltas;
}

int main(){
    string arquivo = "entrada.txt";
    string linha;

    int quadro;
    vector<int> processos;
    int proc;

    ifstream arq(arquivo);

    arq>>quadro;
    while(arq>>proc){
        processos.push_back(proc);
    }
    arq.close();

    cout<<"FIFO "<<fifo(quadro, processos)<<endl;
    cout<<"OTM "<<otm(quadro, processos)<<endl;
    cout<<"LRU "<<longe(quadro, processos)<<endl;

}
