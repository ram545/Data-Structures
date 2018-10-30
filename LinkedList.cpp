#include<iostream>
#include<cstdlib>
#include<cstring>
using namespace std;

struct node{
    char* name;
    int data;
    node *next;
};

class LinkedLst{
    private:
        node *head;
        int length;
    public:
        LinkedLst();
        ~LinkedLst();
        void Insert(char* name,int data);
        void Remove(int position);
        void Print(int position);
        bool IsEmpty();
};

void LinkedLst::Insert(char* name,int data){
    cout << name << " " << data << endl;
    node *temp = (struct node*)malloc(sizeof(struct node));
    node *prev = NULL,*cur=NULL;
    temp->name = new char[strlen(name)];
    strcpy(temp->name,name);
    temp->data = data;
    temp->next = NULL;
    if(this->head==NULL || this->head->data > data){
        temp->next = this->head;
        this->head = temp;
    }
    else{
        cur = this->head;
        while(cur!=NULL){
            if(cur->data < data){
                prev = cur;
                cur = cur->next;
            }
            else{
                prev->next = temp;
                temp->next = cur;
                break;
            }
        }
        if(cur == NULL)
            prev->next = temp;
    }
    cout << strlen(name) << endl;
}

LinkedLst::LinkedLst(){
    this->head = NULL;
    this->length = 0;
}

LinkedLst::~LinkedLst(){
    struct node* cur = NULL;
    while(this->head!=NULL){
        cur = this->head;
        this->head = this->head->next;
        delete cur;
    }
    this->length=0;
}

void LinkedLst::Remove(int pos){
    if(IsEmpty() && pos > this->length)
        cout << "Invalid Records" << endl;
    else{
        int pos_count=0;
        struct node* temp = NULL,*temp1;
        temp = this->head;
        if(pos=0){
            this->head = this->head->next;
            delete temp;
        }
        else{
            while(temp!=NULL){
                if(pos_count == pos-1){
                    temp1 = temp->next;
                    temp->next = temp1->next;
                    delete temp1;
                    break;
                }
                pos_count++;
            }
        }
    }
}

bool LinkedLst::IsEmpty(){
    return this->length ? false : true;
}

void LinkedLst::Print(int pos){
    if(IsEmpty() && pos > this->length)
        cout << "Invalid Records" << endl;
    else{
        int pos_count=0;
        struct node* cur = this->head;
        while(cur!=NULL && pos_count<=pos){
            cout << cur->name << cur->data << endl;
            cur = cur->next;
            pos_count++;
        }
    }
}

int main(int argc,char** argv){
    LinkedLst *lst = new LinkedLst();
    char *input,*cmd,*par1,*par2;
    int N;
    do{
        input = new char[40];
        par1 = new char[30];
        par2 = new char[10];
        delete[] cmd;
        cmd = new char[7];
        cin.getline(input,40);
        cmd = strtok(input," ");
        if(strcmp(cmd,"insert")==0){
            par1 = strtok(NULL," ");
            par2 = strtok(NULL," ");
            N = atoi(par2);
            lst->Insert(par1,N);
        }
        else if(strcmp(cmd,"remove")==0){
            par1 = strtok(input," ");
            N = atoi(par1);
            lst->Remove(N);
        }
        else if(strcmp(cmd,"print")==0){
            par1 = strtok(input," ");
            N = atoi(par1);
            lst->Print(N);
        }
        delete[] input;
        delete[] par1;
        delete[] par2;
    }while(strcmp(cmd,"stop")!=0);
}
