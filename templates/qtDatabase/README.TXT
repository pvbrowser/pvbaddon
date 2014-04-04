This pvserver shows howto use the Qt SQL module together with pvbrowser

Search the files for "DATABASE" to find the necessary code for DB access

The files qtdatabase.h and qtdatabase.cpp define a class for handling the database.
In this example we use a MySQL database with the default tables you can find in MySQL.
Please customize / extend this class.

In pvs.pro we add qt to our project and use the qt SQL module.

In pvapp.h we include the according headers.

In main.cpp we define an instance of qtDatabase and open the database.

In mask1_slots.h we make a SQL query and populate a Table in pvbrowser with the result of the query.


