//
//  main.cpp
//  project2
//
//  Created by 曹旭宏 on 2017/11/2.
//  Copyright © 2017年 xuhong. All rights reserved.
//

#include <mysql.h>
#include <iostream>
#include <unistd.h>
#include <ctime>
#include <sstream>
#include <string>
#include <stdio.h>
#include <iomanip>
#include <cstdio>
#include <cstring>

void input();
void Transcript();
void Personal_Details();
void Enroll();
void Withdraw();
void Logout();
void Change_pass();
void Change_addr();
void DropCourse();
void DeleteCourse();
void getSystemTime();
void coursedetail();
void Chooseclass();
void free();
int year;
int month;
std::string address;
std::string years;
std::stringstream ss;
std::string username;
std::string passcode;
std::string dropnum;
std::string dropquarter;
std::string dropyear;


using namespace std;
MYSQL *connection, mysql;
int main () {
    mysql_init(&mysql);
    connection = mysql_real_connect(&mysql, "localhost", "root", "19950216",
                                    "project3-nudb", 0, 0, 0);
    if (connection == NULL) {
        //unable to connect
        printf("Oh Noes!\n"); }
    else
    {
        printf("You are now connected. Welcome!\n");
    }
    
    /*MYSQL_RES *res_set;
    MYSQL_ROW row;
    mysql_query(connection,"SELECT * FROM student;");
    res_set = mysql_store_result(connection);
    int numrows = (int)mysql_num_rows(res_set);
    // Display results
    for (int i = 0; i < numrows; i++) {
        row = mysql_fetch_row( res_set );
        if( row != NULL)
        {
            cout << "ID : " << row[0] << endl;
            cout << "Name: " << row[1] << endl;
            cout << "Password: " << row[2] << endl;
        }
    }
    // free resources
    mysql_free_result( res_set );*/
    cout << "*****************************************" << endl;
    cout << "*****************************************" << endl;
    cout << "******      WELCOME TO CEASAR     *******" << endl;
    cout << "*****************************************" << endl;
    cout << "*****************************************" << endl;
    getSystemTime();
 
    // student login
    cout << "Username : ";
    cin >> username;
    cout << "Password : ";
    cin >> passcode;
    input();

};

void input(){
    mysql_init(&mysql);
    connection = mysql_real_connect(&mysql, "localhost", "root", "19950216",
                                   "project3-nudb", 0, 0, 0);
    
    int t=0;
   
    MYSQL_RES *res_set;
    MYSQL_ROW row;
    mysql_query(connection,"SELECT * FROM student;");
    res_set = mysql_store_result(connection);
    int numrows = (int)mysql_num_rows(res_set);
    // Display results
    for (int i = 0; i < numrows; i++) {
        row = mysql_fetch_row( res_set );
        if( row != NULL && row[0]==username && row[2]==passcode )
        {
            cout << "Name: " << row[1] << endl;
            t=1;
        }
    }
    if(!t){
        cout << "Login Failed. Please try again.The username and/or password you entered was invalid." << endl;
        main();
    }
    while(true) {
        mysql_query(connection,"SELECT * FROM transcript");
        res_set = mysql_store_result(connection);
        numrows = (int)mysql_num_rows(res_set);
        ss << year;
        string years = ss.str();
        // Display results
        
        cout << "CourseNum" << "    " << "Semester" << "    " << "Year" << endl;
        
        for (int i = 0; i < numrows; i++) {
            row = mysql_fetch_row( res_set );
            if( row != NULL && row[3] == years && row[0] == username )
            {
                if (month > 8 && month < 12 && !strncmp(row[2],"Q1",2)) {
                    cout << row[1] << "       " << row[2] << "        " << row[3] << endl;
                }
                else if ((month > 11 || month < 3)  && !strncmp(row[2],"Q2",2)){
                    cout << row[1] << "       " << row[2] << "        " << row[3] << endl;
                }
                else if (month > 2 && month < 6 && !strncmp(row[2],"Q3",2)){
                    cout << row[1] << "       " << row[2] << "        " << row[3] << endl;
                }
                else if (month > 5 && month < 9 && !strncmp(row[2],"Q4",2)){
                    cout << row[1] << "       " << row[2] << "        " << row[3] << endl;
                }
            }
        }
        // free resources
        mysql_free_result( res_set );
        ss.str(" ");
        int choice;
        cout << "1.Transcript;" << endl ;
        cout << "2.Personal_Details;" << endl ;
        cout << "3.Enroll;" << endl ;
        cout << "4.Withdraw;" << endl;
        cout << "5.Log out;" << endl;
        cin >> choice ;
        switch (choice){
            case 1:
                Transcript();
                break;
            case 2:
                Personal_Details();
            case 3:
                Enroll();
                break;
            case 4:
                Withdraw();
                break;
            case 5:
                Logout();
                break;
            default:
                input();
        }
    }
    
    
}

void Transcript(){
    MYSQL_RES *res_set;
    MYSQL_ROW row;
    mysql_query(connection,"SELECT * FROM transcript;");
    res_set = mysql_store_result(connection);
    int numrows = (int)mysql_num_rows(res_set);
    
    // Display results
    cout << "CourseNum" << "    " << "Semester" << "    " << "Year" << "       " << "grade" << endl;
    for (int i = 0; i < numrows; i++) {
        row = mysql_fetch_row( res_set );
        if (row[4] == NULL && row[0]==username) {
            cout << row[1] << "       " << row[2] << "        " << row[3] << "        " << "null" << endl;
        }
        if( row[4] != NULL && row != NULL && row[0]==username )
        {
                cout << row[1] << "       " << row[2] << "        " << row[3] << "        " << row[4] << endl;
        }
    }
    // free resources
    mysql_free_result( res_set );
    int choice;
    cout << "1.Back to Student menu;" << endl ;
    cout << "2.Coursedetail;" << endl ;
    cin >> choice;
    switch (choice) {
        case 1:
            input();
            break;
        case 2:
            coursedetail();
            break;
    }
    
};
void coursedetail(){
    cout << "Please enter the course number: " ;
    string courseNum ;
    cin >> courseNum ;
    MYSQL_RES *res_set;
    MYSQL_ROW row;
    mysql_query(connection,"SELECT * FROM coursedetail;");
    res_set = mysql_store_result(connection);
    int numrows = (int)mysql_num_rows(res_set);
    // Display results
    cout << setw(10) << "CourseNum" << "|" << setw(42) <<  "Coursename" << "|" << setw(10) << "Year" << "|" << setw(10) << "Quater" << "|" << setw(10) << "Classtime" << "|" ;
    cout << setw(10) << "Enrollment" << "|"  << setw(20) << "Maximum enrollment" << "|" << setw(30) << "Lecturer" << "|" << setw(10) << "Credits" << "|" << endl;
    for (int i = 0; i < numrows; i++) {
        row = mysql_fetch_row( res_set );
        if (row[0] == courseNum) {
            cout << setw(10) << row[0] << "|" << setw(42) << row[10] << "|" << setw(10) << row[2] << "|" << setw(10) << row[1] << "|" << setw(10) << row[3] << "|" ;
            cout << setw(10) << row[6] <<  "|" << setw(20) << row[7] <<  "|" << setw(30) << row[5] <<  "|" << setw(10) << row[11] << "|" << endl ;
        }
    }
    mysql_free_result( res_set );
    int choice;
    cout << "1. Back to Transcript;" << endl;
    cin >> choice;
    switch (choice) {
        case 1:
            Transcript();
            break;
    }
}


void Enroll(){
    MYSQL_RES *res_set;
    MYSQL_ROW row;
    string query = "CALL enrollment(" + username + ")";
    string nexty = "2018";
    mysql_query(connection, query.c_str());
    res_set = mysql_store_result(connection);
    int numrows = (int)mysql_num_rows(res_set);
    ss << year;
    string years = ss.str();
    // Display results
    for (int i = 0; i < numrows; i++) {
        row = mysql_fetch_row( res_set );
        if( (row[2] == years && !strncmp(row[1],"Q1",2)) || (!strncmp(row[1],"Q2",2) && row[2] == nexty))
        {
                cout << row[0] << "       " << row[2] << "        " << row[1] << endl;
     }
     }
    ss.str(" ");
    free();
    int choice;
    cout << "1.Enroll some class;" << endl;
    cout << "2.Back to Student menu;" << endl;
    cin >> choice;
    switch (choice) {
        case 1:
            Chooseclass();
            break;
        case 2:
            input();
            break;
        default:
            break;
    }
    
};

void Chooseclass(){
    mysql_init(&mysql);
    connection = mysql_real_connect(&mysql, "localhost", "root", "19950216",
                                    "project3-nudb", 0, 0, 0);
    string CourseNum;
    string Userid = username;
    string eSemester;
    string notif;
    string precourse;
    string output;
    string eyear;
    string err;
    string i = "1";
    string n = "2";
    string unen = "0";
    //char query;
    cout << "Enter the CourseNum:" ;
    cin >> CourseNum;
    cout << "Choose Semester:" ;
    cin >> eSemester;
    cout << "Choose Year:" ;
    cin >> eyear;
    MYSQL_RES *res_set;
    MYSQL_ROW row;
    string query = "CALL coursecheck_correctinput('"+ username +"','"+ CourseNum +"','"+ eSemester +"','"+ eyear +"', @notif , @output);";
    //string query = "CALL coursecheck_correctinput('3213','COMP3308','Q1','2017', @notif , @output);";
    cout << query << endl;
    mysql_query(connection, query.c_str());
    mysql_query(connection, "select @notif, @output;");
    res_set = mysql_store_result(connection);
    row = mysql_fetch_row( res_set );
   // cout << row[0] << row[1] << endl;
        if(row[1] == i){
        cout << "-----------------" <<"Enroll successfully!!!" << "-----------------" <<endl;
    }
        if(row[1] == unen){
            cout << "-----------------" << "Enroll failed, you may need to take prereqcourse:" << row[0] <<  "-----------------" << endl;
            cout <<  "-----------------" << "Or the course enrollment is beyond max!!" <<  "-----------------" << endl ;
        }
    if(row[1] == n ){
        cout << "-----------------    Invalid combination   -----------------" << endl;
    }
    if(row == NULL){
        cout << row[0] << endl;
    }
    free();
    return;

};
void Personal_Details(){
    
    MYSQL_RES *res_set;
    MYSQL_ROW row;
    
    
    std::string show_stu="SELECT * FROM student where Id="+username+";";
    mysql_query(connection, show_stu.c_str());
    res_set = mysql_store_result(connection);
    row = mysql_fetch_row( res_set );
    
    
    
    cout << "ID" << "           " << "Name" << "              " << "Password"<< "           " << "Address" << endl;
    cout << row[0] << "       " << row[1] << "         " << row[2]<< "            " << row[3] << endl;
    
    // free resources
    mysql_free_result(res_set);
    
    // change address or password
    int choice;
    cout << "1.Change password;" << endl ;
    cout << "2.Change address;" << endl ;
    cout << "3.Back to Student menu;" << endl ;
    cout << "4.Log out;" << endl;
    cin >> choice ;
    switch (choice){
        case 1:
            Change_pass();
            break;
        case 2:
            Change_addr();
            break;
        case 3:
            input();
            break;
        case 4:
            Withdraw();
            break;
        case 5:
            Logout();
            break;
        default:{
            cout << "Wrong Choice!\n" <<endl;
            cout << "Please make another selection!\n" <<endl;
            Personal_Details();
            break;
        }
            
    }
};

void Change_pass(){
    
    MYSQL_RES *res_set;
    MYSQL_ROW row;
    
    int choice;
    
    //check if the original password is correct
    std::string table_id= "SELECT * FROM student where Id="+username+";";
    mysql_query(connection,table_id.c_str());
    res_set = mysql_store_result(connection);
    row = mysql_fetch_row( res_set );
    
    cout << "Please enter your original code here: " << endl;
    cin >> passcode;
    
    
    if(passcode == row[2]){
        cout << "Please type your new code here: " << endl;
        cin >> passcode;
        
        std::string change_pass = "UPDATE student SET student.Password = '"+passcode+"' WHERE student.Id = "+username+";";
        mysql_query(connection, change_pass.c_str());
        cout << "The password has been updated!" << endl;
        
        mysql_free_result(res_set);
        Personal_Details();
        
    }
    else{
        cout << "Please type the right original code! \n" <<endl;
        cout << "1. Continue to change passcode\n" <<endl;
        cout << "2. Back to Personal details\n" <<endl;
        cin >> choice;
        switch(choice){
            case 1:
                Change_pass();
            case 2:
                Personal_Details();
            default:{
                cout << "Wrong Choice!\n" <<endl;
                cout << "Please make another selection!\n" <<endl;
                Change_pass();
            }
                
        }
    }
};

void Change_addr(){
    MYSQL_RES *res_set;
    
    cout << "Please type your new address here: " << endl;
    cin >> address;
    
    std::string change_pass = "UPDATE student SET student.Address = '"+address+"' WHERE student.Id = "+username+";";
    mysql_query(connection, change_pass.c_str());
    res_set = mysql_store_result(connection);
    cout << "The address has been updated!" << endl;
    
    mysql_free_result( res_set );
    Personal_Details();
};


void Withdraw(){
    MYSQL_RES *res_set;
    MYSQL_ROW row;
    
    string query = "CALL dropcourses(" + username + ");";
    mysql_query(connection, query.c_str());
    res_set = mysql_store_result(connection);
    int numrows = (int)mysql_num_rows(res_set);
    
    if(numrows != 0){
        for (int i = 0; i < numrows; i++){
            row = mysql_fetch_row( res_set );
            if ( row != NULL){
                cout << row[0] << "       " << row[1] << "        " << row[2] << endl;
            }
        }
    }
    else{
        
        cout << "\nNo courses can be dropped\n" << endl;
        int choice;
        cout << "1. Back to Student menu\n" << endl;
        cin >> choice;
        if (choice == 1){
            input();
        }
        else{
            cout << "Wrong Choice! \n" << endl;
            input();
        }
        free();
    }
    cout << "1.Continue your drop" <<endl;
    cout << "2.Back to Student menu" <<endl;
    int choice2;
    cin >> choice2;
    if(choice2 == 1 ){
        DropCourse();
    }
    else if (choice2 == 2){
        input();
    }
    else{
        cout << "Wrong choice! Please choose again\n" << endl;
        Withdraw();
    }
};
void DropCourse(){
    cout <<"\nYou could drop one of courses listed above\n" << endl;
    cout << "Please enter the courseNum you chose to drop: " << endl;
    cin >> dropnum;
    cout << "Please enter the year of the course: "<< endl;
    cin >> dropyear;
    cout << "Please enter the quarter of the course: "<< endl;
    cin >> dropquarter;
    
    mysql_init(&mysql);
    connection = mysql_real_connect(&mysql, "localhost", "root", "19950216",
                                    "project3-nudb", 0, 0, 0);
    
    
    MYSQL_RES *res_set;
    MYSQL_ROW row;
    
    string query = "CALL rightwithdraw('" + username + "', '" + dropnum +"', '" + dropyear + "', '" + dropquarter + "' );";
    
    mysql_query(connection, query.c_str());
    res_set = mysql_store_result(connection);
    row = mysql_fetch_row( res_set );
    
    free();
    if( row != NULL){
        
        free();
        DeleteCourse();
        
    }
    
    else {
        cout <<"Invalid Combination of Course Information\n" << endl;
        Withdraw();
    }
    
    free();
};

void DeleteCourse(){
    
    MYSQL_RES *res_set;
    MYSQL_ROW row;
    
    string withdraw="CALL deletecourses (" +username+ ", '" +dropnum+"', '" +dropyear+ "', '" +dropquarter+"', @err);";
    mysql_query(connection, withdraw.c_str());
    res_set = mysql_store_result(connection);
    free();
    
    cout << "Successfully withdraw!\n" << endl;
    
    //warning trigger
    mysql_query(connection, "Select @status;");
    res_set=mysql_store_result(connection);
    row=mysql_fetch_row(res_set);
    if (!strncmp(row[0],"below",2)){
        cout<<"*** WARNING: The enrollment of this course is below 50% ***\n"<<endl;}
    free();
    
    
    cout << "1.Withdraw another class\n" <<endl;
    cout << "2.Back to Student menu\n" << endl;
    int choice;
    cin >> choice;
    if(choice == 1 ){
        Withdraw();
    }
    else if (choice == 2){
        input();
    }
    else{
        cout << "Wrong Choice !" << endl;
        input();
    }
    
};

void Logout(){
    main();
};
void free(){
    int status;
    MYSQL_RES *res_set;
    do{
        res_set = mysql_store_result(connection);
        if (res_set){
            mysql_free_result(res_set);
        }
        status = mysql_next_result(connection);
    }while (status == 0);
}

void getSystemTime()
{
    time_t timer;
    time(&timer);
    tm* t_tm = localtime(&timer);
    year = t_tm->tm_year+1900;
    month = t_tm->tm_mon+1;
    int day = t_tm->tm_mday;
    cout<< "Today is "<< year <<" "<< month <<" "<< day <<endl;
} ;
