#include <iostream>
#include <climits>
using namespace std; 

// creo struttura per albero di ricerca 
struct Node{
    int val; 
    Node* left_child; 
    Node* right_child;    
    Node(int v){
        val=v; 
        left_child=nullptr; 
        right_child=nullptr;  
    }
   
};
struct Bst{
   Node* Root; 
   Bst(){
      Root=nullptr;  
   }
}; 

bool Bst_inserimento(Bst* R, int x){
    
    if(!R){
        return false; 
    }
    if(!R->Root){
        R->Root=new Node(x);
        return true; 
    }
    Node* current=R->Root; 
    while(true){
        if(x>current->val){
            if(current->right_child==nullptr){
                current->right_child=new Node(x); 
                return true; 
            }
            current=current->right_child; 
        }
        else if(x<current->val){
             if(current->left_child==nullptr){
                current->left_child=new Node(x); 
                return true; 
            }
            current=current->left_child; 
        }
        else{
            return false; 
        }
    }
}
Node* inserimento_ricorsivo(Node* R, int x){
    if(R==nullptr){
        R=new Node(x); 
        return R; 
    }
    if(R->val==x){
        return R; 
    }
    if(x>R->val){
        R->right_child=inserimento_ricorsivo(R->right_child,x); 
    }
    if(x<R->val){
         R->left_child=inserimento_ricorsivo(R->left_child,x); 
    }
    return R; 
}
Node* research(Node* R, int x){
    if(!R){
        return nullptr;
    }
    if(R->val==x){
        return R; 
    }
    if(x>R->val){
      return research(R->right_child, x); 
    }
    if(x<R->val){
      return research(R->left_child, x); 
    }
}

bool ricerca_e_cancellazione(Node* R, int x){

    Node* ricerca= research(R,x); 
    if(ricerca==nullptr){
        cout<<"valore non trovato"; 
        return false; 
    }
	
    Node* prev=nullptr; 
	Node* current=R; 
	
	while(current->val!=x || !current ){
		if(x<current->val){
			prev=current; 
			current=current->left_child; 
		}
		else if(x>current->val){
			prev=current; 
			current=current->right_child; 
		}
	}
	if (!current) {
    cout << "non trovato" << endl;
    return false;
	}
        if(current->right_child==nullptr && current->left_child==nullptr){
			cout<<"bea"; 
			if(prev->right_child==current){prev->right_child=nullptr; } 
			if(prev->left_child==current){prev->left_child=nullptr; }
			delete current;
			return true; 
           
		}
        if(( !current->left_child && current->right_child) || ( current->left_child && !current->right_child )){
			if(!current->left_child && current->right_child){ 
				current->val=current->right_child->val;
				current->right_child=nullptr; 
				delete current->right_child;
				return true;
				}
			if(current->left_child && !current->right_child){ 
				current->val=current->left_child->val;
				current->left_child=nullptr; 
				delete current->left_child;
				return true;
				} 
			//ALGORITMO CHE HA SOLO UN FIGLIO 
        }
        if(current->left_child && current->right_child){
            	prev=current; 
				Node* sucessore=current->right_child; 
			    while(sucessore->left_child!=nullptr){
					prev=sucessore; 
					sucessore=sucessore->left_child;  
				} 
				current->val=sucessore->val; 
              if(prev->left_child == sucessore){
              prev->left_child=sucessore->right_child;
			  }
              else{prev->right_child=sucessore->right_child;}
				delete sucessore; 
				return true; 
        }
}
void stampa(Node* R){
	if(!R){
		return; 
	}
	cout<<R->val; 
	stampa(R->left_child);
	stampa(R->right_child); 
}
int main(){ 
    
    Bst* R=new Bst(); 
    int x=9;
    cout<<" inserimento x su albero non ricorsivo "<<endl; 
    Bst_inserimento(R,x); 
    cout<<" verifica inserimento x su albero non ricorsivo= "; 
    cout<<Bst_inserimento(R,x)<<endl;
    cout<<" inserimento x su albero ricorsivo "<<endl; 
    inserimento_ricorsivo(R->Root,20)->val; 
     cout<<" ricerca valore su albero ( non trovandolo )  "; 
    cout<<research(R->Root, 8)<<endl; 
	int uscita=0; 
   //inserimento albero bst 
	while(true){
		cout<<" inserire 1 per smettere di inserire nell' albero "<<endl; 
		cin>>uscita;
		if(uscita==1){
			break; 
		}
		cout<<"inserire x dell bst "<<endl; 
		cin>>x; 
        inserimento_ricorsivo(R->Root,x)->val;  
	}
	//cancellazione
	cout<<"stampa pre= ";  
	stampa(R->Root);
	cout<<endl;
	cout<<"inserire il valore da cancellare "; 
	int canc=0; 
	cin>>canc; 
	cout<<" true o false= ";  
	cout<<ricerca_e_cancellazione(R->Root,canc);
	cout<<endl; 
	cout<<"stampa post= ";
    stampa(R->Root); 
	
     
    
    
    
    
    
    
    
    return 0; 
}