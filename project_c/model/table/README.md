<p align="center">
  <img src="https://img.shields.io/static/v1?label=API&message=JP&color=ff2a00&style=for-the-badge&logo=ghost"/>
</p>

<center>

# :orange_book: Standart Table :orange_book:

</center>

<img  src="../../../pictures/bannerJose(final).png">

<center>
    
#### An *API* to simulate a database in your program

</center>

<center>

####	🚀 In progress 🚀 

</center>

## :scroll: Summary

<!--ts-->
* [About project](#about-project)
* [Dependencies](#dependencies)
* [User guide](#user-guide)
     * :checkered_flag: [Implementation](#implementation)
     * :icecream: [Functions](#functions)
* [Programmer guide](#programmer-guide)
     * [The System](#the-system)
* [Author](#author)

<!--te-->


##  About project

The **Standart Table** is a *database* **API** that provides *structures* and *functions* in order to simulate a database like **MySQL** or **MongoDB**. 

## Dependencies

To use the **Standart Table** you need *GLib library* - version **2.68.1**. For more information: https://developer.gnome.org/glib/  

After install **GLib**, to compile your project use the following flag:

	`pkg-config --cflags --libs glib-2.0`

Futhermore, the *Standart Table* use **<ncurses.h>** library, so you need a special flag to compile:

    -lncurses

## User guide 

### :checkered_flag: Implementation

### :icecream: Functions 

#### table_new()

```c
TABLE * table_new (int fields, int index, const char *fmt, ...);
```
Creates a new **TABLE**. The number os columns in the table is the **fields** paramater. The type of each column is indicated in the **fmt** parameter. The rest of the paramaters are the **header name** of which column.

**Parameters**

* ***fields*** :arrow_right: number of columns of the TABLE
* ***index*** :arrow_right: the number of the column to be the **id**
* ***fmt*** :arrow_right: string with the type format of each column
* ***...*** :arrow_right: header names of each column

**Returns**

A new allocated TABLE

**Example**

```c
TABLE * t;
t = table_new (3,0, "s d f", "name", "age", "height");
```
In this example, ```s``` indicates that the ```name``` column has *string type information*, ```d``` indicates that the ```age```column has the *integer type information* and ```f``` indicates that the ```height``` column has the *float type information*.

:information_source: **Since: 1.0**

#### table_destroy()

```c
void table_destroy (TABLE * t);
```
Remove all ROWS from the TABLE.

**Parameters**

* ***t*** :arrow_right: a TABLE

:information_source: **Since: 1.0**

#### table_append()

```c
int table_append (TABLE * t, ...);
```

Inserts a ROW in the TABLE.

**Parameters**

* ***t*** :arrow_right: a TABLE
* ***...*** :arrow_right: **pointes** to the values to fill the ROW 

**Example**

```c
TABLE * t;
t = table_new (3,0, "s d f", "name", "age", "height");

char * name = "Bekele";
int age = 38;
float height = 56.0;

table_append (t, &name, &age, &height);
```
This example shows a **important** point to use this function: it receives *

:information_source: **Since: 1.0**

#### table_to_file()

```c
int table_to_file (FILE *fp, TABLE *t, const char delim);
```

### TODO: correct function prototype

## Programmer Guide

