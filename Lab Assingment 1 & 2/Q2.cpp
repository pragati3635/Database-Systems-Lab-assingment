#include <iostream>
#include <windows.h>
#include <mysql.h>
#include <sstream>
#include <typeinfo>
using namespace std;

void insert_employee(string name,string street,string city,MYSQL* conn){
    string qti = "INSERT INTO Employee(emp_name,street,city) VALUES('"+name+"','"+street+"','"+city+"')";
    const char* q = qti.c_str();
    mysql_query(conn,q);
    qti = "SELECT LAST_INSERT_ID()";
    const char* q1 = qti.c_str();
    mysql_query(conn,q1);
    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(res);
    cout<<"Your employee id is "<<row[0]<<"\n";
}
void insert_company(string name,string city,MYSQL* conn){
    string qti = "INSERT INTO Company(comp_name,city) VALUES('"+name+"','"+city+"')";
    const char* q = qti.c_str();
    mysql_query(conn,q);
    qti = "SELECT LAST_INSERT_ID()";
    const char* q1 = qti.c_str();
    mysql_query(conn,q1);
    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(res);
    cout<<"Your company id is "<<row[0]<<"\n";
}
void insert_works(int id,string name,int co_id,string comp,int salary,MYSQL* conn){
    string qti = "INSERT INTO Works(emp_id,comp_id,emp_name,comp_name,salary) VALUES('"+to_string(id)+"','"+to_string(co_id)+"','"+name+"','"+comp+"','"+to_string(salary)+"')";
    const char* q = qti.c_str();
    mysql_query(conn,q);
}
void display(MYSQL_RES* res,int n){
    MYSQL_ROW row;
    while(row = mysql_fetch_row(res)){
        for(int i=0;i<n;i++){
            cout<<row[i]<<" ";
        }
        cout<<"\n";
    }
}


int main()
{
    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,"192.168.1.100","pragati3635","_,8xM4KNmfJXd8f","database1",0,NULL,0);
    if(conn){
        cout << "Database is connected" << endl;
        string create_table;
        /*create_table = "CREATE TABLE Employee(emp_id int AUTO_INCREMENT,emp_name varchar(30),street varchar(100),city varchar(30),PRIMARY KEY (emp_id))";
        const char* q = create_table.c_str();
        mysql_query(conn,q);
        create_table = "CREATE TABLE Company(comp_id int AUTO_INCREMENT,comp_name varchar(60),city varchar(30),PRIMARY KEY (comp_id))";
        const char* q1 = create_table.c_str();
        mysql_query(conn,q1);
        create_table = "CREATE TABLE Works(emp_id int,comp_id int,emp_name varchar(30),comp_name varchar(60),salary int,FOREIGN KEY (emp_id) REFERENCES Employee(emp_id),FOREIGN KEY (comp_id) REFERENCES Company(comp_id))";
        const char* q2 = create_table.c_str();
        mysql_query(conn,q2);
        create_table = "CREATE TABLE Managers(emp_id int,emp_name varchar(30),manager_emp_id int,manager_name varchar(30),FOREIGN KEY (emp_id) REFERENCES Employee(emp_id),FOREIGN KEY (manager_emp_id) REFERENCES Employee(emp_id))";
        const char* q3 = create_table.c_str();
        mysql_query(conn,q3);*/
        int cond = 90;
        cout<<"If want to exit this programme press 0\n";;
        cout<<"If want to insert in Employee table press 1\n";
        cout<<"If want to insert in Company table press 2\n";
        cout<<"If want to insert in Work table press 3\n";
        cout<<"If you want to update workplace of employee press 4\n";
        while(cond!=0){
            cout<<"select the option\n";
            cin>>cond;
            if(cond==1){
                cout<<"Enter name of the employee: ";
                string name;
                cin>>name;
                cout<<"Enter street of the employee: ";
                string street;
                cin>>street;
                cout<<"Enter city of the employee: ";
                string city;
                cin>>city;
                insert_employee(name,street,city,conn);

            }
            else if(cond==2){
                cout<<"Enter name of the company: ";
                string name;
                cin>>name;
                cout<<"Enter city of the company: ";
                string city;
                cin>>city;
                insert_company(name,city,conn);
            }
            else if(cond == 3){
                cout<<"Enter id of the employee: ";
                int id;
                cin>>id;
                cout<<"Enter name of the employee: ";
                string name;
                cin>>name;
                cout<<"Enter id of the comp: ";
                int co_id;
                cin>>co_id;
                cout<<"Enter comp of the employee: ";
                string comp;
                cin>>comp;
                cout<<"Enter the salary : ";
                int salary;
                cin>>salary;
                insert_works(id,name,co_id,comp,salary,conn);
            }
            else if(cond==4){
                string id1;
                cout<<"Enter the id of employee whose work place to update: \n";
                cin>>id1;
                string id2;
                cout<<"Company id : \n";
                cin>>id2;
                string q_update_company = "Update Works SET comp_id = '"+id2+"' WHERE emp_id='"+id1+"'";
                const char* q7 = q_update_company.c_str();
                mysql_query(conn,q7);
            }
        }
        string q_SBI_emp = "SELECT emp_id,emp_name from Works WHERE comp_name = 'SBI'";
        const char* q4 = q_SBI_emp.c_str();
        mysql_query(conn,q4);
        MYSQL_RES* res = mysql_store_result(conn);
        cout<<"Names of employees working in SBI : \n";
        display(res,2);
        string q_city = "SELECT emp_name,city from Employee WHERE emp_id IN(SELECT emp_id FROM Works WHERE comp_name='SBI')";
        const char* q5 = q_city.c_str();
        mysql_query(conn,q5);
        res = mysql_store_result(conn);
        cout<<"Names of employees and cities working in SBI : \n";
        display(res,2);
        string q_not_SBI_emp = "SELECT emp_id,emp_name from Works WHERE comp_name != 'SBI'";
        const char* q6 = q_not_SBI_emp.c_str();
        mysql_query(conn,q6);
        res = mysql_store_result(conn);
        cout<<"Names of employees not working in SBI : \n";
        display(res,2);

    }
    else{
        cout << "Database is not connected" << endl;
    }

    return 0;
}
