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
            if(cur->data <= data){
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
    this->length++;
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
    if(IsEmpty() || pos > this->length || pos==0)
        cout << "Error while removing records" << endl;
    else{
        int pos_count=2;
        struct node* temp = NULL,*temp1;
        temp = this->head;
        if(pos==1){
            this->head = temp->next;
            delete temp;
        }
        else{
            while(temp!=NULL){
                if(pos_count == pos){
                    temp1 = temp->next;
                    temp->next = temp1->next;
                    temp1->next = NULL;
                    delete temp1;
                    break;
                }
                temp = temp->next;
                pos_count++;
            }
        }
    this->length--;
    }
}

bool LinkedLst::IsEmpty(){
    return (this->length==0) ? true : false;
}

void LinkedLst::Print(int pos){
    if(IsEmpty() || pos > this->length || pos==0)
        cout << "Error while printing records" << endl;
    else{
        int pos_count=0;
        struct node* cur = this->head;
        while(cur!=NULL && pos_count<pos){
            cout << cur->name << '\t' << cur->data << endl;
            cur = cur->next;
            pos_count++;
        }
    }
}

int main(int argc,char** argv){
    LinkedLst *lst = new LinkedLst();
    char *cmd,*par1;
    int N;
    do{
        delete[] cmd;
        cmd = new char[7];
        cin >> cmd;
        if(strcmp(cmd,"insert")==0){
            par1 = new char[30];
            cin >> par1 >> N;
            lst->Insert(par1,N);
            delete[] par1;
        }
        else if(strcmp(cmd,"remove")==0){
            cin >> N;
            lst->Remove(N);
        }
        else if(strcmp(cmd,"print")==0){
            cin >> N;
            lst->Print(N);
        }
        cin.ignore(250,'\n');
    }while(strcmp(cmd,"stop")!=0);
}
