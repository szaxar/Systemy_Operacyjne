

struct data{
int year;
int month;
int day;
};


struct person{
string firstName;
string lastName;
data dateOfBirth;
string email;
int number;
};

struct node{
person key;
node *lewy;
node *prawy;
node *rodzic;
}*korzen=NULL;

bool equality(person p1 , person p2);
bool check(person p1 , person p2 , string z);
void push(node *&korzen,node *rod,person x,string z);
void show(node *korzen);
void deleteall(node *root);
node *get(node *root, person val,string z);
void kasowanie( node *start);
void _do(node *korzen,node *tmp , string z );
node *remake(node *korzen,string z);

