# Simpol Interpreter written in C for a fictional SIMPOL language

## Authors:

* Edwin D. Vinas

## Forked Original Codes from:
* https://github.com/BernhardPosselt/interpreter

## Dependencies

* getopt
* bison
* make

## Downloading
Clone a copy to your local machine

	git clone https://github.com/edwindvinas/simpol-interpreter.git
	cd simpol-interpreter/
	
## Compiling
Run:

    make

## Running a sample .sim file
To execute a file pass the path as its first argument like:

    ./simpol-interpreter programs/myprogram.sim

## Run in Debug Mode

Run:

    ./simpol-interpreter programs/myprogram.sim -d
	
## Sample Simpol file (.sim)

	variable {
	STG str
	STG name
	INT num1
	INT num2
	INT num3
	BLN bol1
	BLN bol2
	}
	 
	code {
	PUT $The result is: $ IN str
	ASK name
	PUT true IN bol1
	PUT false IN bol2
	PUT ADD 1 2 IN num1
	PUT 100 IN num2
	 
	PRT $Your name is $
	PRT name
	PRT OHR true AND bol1 bol2
	PUT MUL 10 ADD num1 num2 IN num3
	PRT num3
	PRT DIV MUL 10 ADD num1 num2 MUL 10 ADD num1 num2
	PRT $Goodbye!$
	}
	
## Updating Github Repo (Initial commit)

	vi README.md
	git init
	git add README.md
	git commit -m "first commit"
	git remote add origin https://github.com/edwindvinas/simpol-interpreter.git
	git push -u origin master
	
	
## Push updates to Github Repo
	
	git add --all
	git commit -m "your commit comments"
	git remote add origin https://github.com/edwindvinas/simpol-interpreter.git
	git push -u origin master
	
## Running in Google Cloud Shell

	git clone https://github.com/edwindvinas/simpol-interpreter.git
	cd simpol-interpreter/	
	make
	./simpol-interpreter programs/myprogram.sim -d
