#include <iostream>
#include <windows.h>
#include <mysql.h>
#include <sstream>
using namespace std;

void insert(string name,string depart,int salary,MYSQL* conn){
    string sl = to_string(salary);
    string qti = "INSERT INTO Employee_Info(emp_name,department,salary) VALUES('"+name+"','"+depart+"','"+sl+"')";
    const char* q = qti.c_str();
    mysql_query(conn,q);
}
void display(MYSQL_RES* res){
    MYSQL_ROW row;
    while(row = mysql_fetch_row(res)){
        for(int i=0;i<4;i++){
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
        /*create_table = "CREATE TABLE Employee_Info(emp_id int AUTO_INCREMENT,emp_name varchar(30),department varchar(60),salary int,PRIMARY KEY (emp_id))";
        const char* q = create_table.c_str();
        mysql_query(conn,q);*/
        int cond = 90;
        cout<<"If want to exit this programme press 0\n";;
        cout<<"If want to insert in table press 1\n";
        while(cond!=0){
            cout<<"select the option";
            cin>>cond;
            if(cond==1){
                cout<<"Enter name of the employee: ";
                string name;
                cin>>name;
                cout<<"Enter department of the employee: ";
                string department;
                cin>>department;
                cout<<"Enter salary of the employee: ";
                int salary;
                cin>>salary;
                insert(name,department,salary,conn);
            }
        }
        string third_hi_salary = "SELECT * FROM `employee_info` ORDER BY `salary` DESC LIMIT 1 OFFSET 2";
        const char* q = third_hi_salary.c_str();
        mysql_query(conn,q);
        MYSQL_RES* res=mysql_store_result(conn);
        MYSQL_ROW row = mysql_fetch_row(res);
        cout<<"Third highest salary is: "<<row[3]<<"\n";
        string display_fir_las = "(select *from employee_info order by emp_id ASC LIMIT 1)UNION(select *from employee_info order by emp_id DESC LIMIT 1)";
        const char* q1 = display_fir_las.c_str();
        mysql_query(conn,q1);
        res=mysql_store_result(conn);
        cout<<"1st and last entry of employee_info table : \n";
        display(res);
        /*create_table = "CREATE TABLE Emp_Details(emp_id int AUTO_INCREMENT,emp_name varchar(30),department varchar(60),salary int,PRIMARY KEY (emp_id))";
        const char* q2 = create_table.c_str();
        mysql_query(conn,q2);
        string q_copy_table = "INSERT INTO `Emp_Details` SELECT * FROM `employee_info`";
        const char* q3 = q_copy_table.c_str();
        mysql_query(conn,q3);
        string q_display_copied_table = "SELECT * FROM Emp_Details";
        const char* q4 = q_display_copied_table.c_str();
        mysql_query(conn,q4);
        res=mysql_store_result(conn);
        cout<<"Data of Emp_Details table : \n";
        display(res);*/
    }
    else{
        cout << "Database is not connected" << endl;
    }

    return 0;
}
