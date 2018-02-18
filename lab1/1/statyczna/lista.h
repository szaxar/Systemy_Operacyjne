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
node *next;
node *prev;
person p;
};

bool equality(person p1 , person p2);
bool check(person p1 , person p2 , string z);
node *make(person p1);
node *add(node *first,person p1);
void show(node *first);
node * get(node *first , person val );
node* _delete(node *first,person p1);

