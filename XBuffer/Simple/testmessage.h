struct student
{
    int id;
    string name;
    int age;
    string sc;
};

struct teacher
{
    string name;
    int age;
};

struct message
{
    int id;
    string name;
    string des;
    teacher[] stues;
    teacher teacher;
};