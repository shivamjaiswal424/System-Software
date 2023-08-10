#!/bin/bash

#Function to display the menu
function display_menu(){
	echo "1.Add an employee record"
	echo "2.Delete an employee record"
	echo "3.Search for an employee record"
	echo "4.Display Employee Details"
	echo "5.Sort employee records"
	echo "6.Exit  the program"
}

#Function to add an employee

function add_employee(){
	echo "Enter Name:"
	read name
	echo "Enter Phone Number:"
	read phone_number
	echo "Enter Employee_ID:"
	read ID
	echo "Name is  ${name}, Phone Number is ${phone_number},Employee ID is ${ID}" >> employees.txt
	echo "Employee is added to system"
}


#Function to delete an employ

function delete_employee(){
	echo "Employee ID to be deleted:"
	read ID
	if grep -q "$ID" employees.txt; then
		grep -v "$ID" employees.txt > temp.txt
		mv temp.txt employees.txt
		echo "Employee record is deleted"
	else
		echo "Employee not found"
	fi
}
#delete_employee



function search_employee(){
	echo "Enter Employee ID:"
	read ID

	if grep -q "$ID"  employees.txt; then
		echo "Employee Details: "
		grep "$ID" employees.txt
	else
		echo "Record not found!"
	fi
}

function display_employee(){
	echo "Employee Records: "
	cat employees.txt
}

function sort_employees(){
	sort -t',' -k2 -n employees.txt > sorted.txt
	echo "Sorted Employee Records: "
	mv sorted.txt employees.txt
	cat employees.txt
}
while true; do
	display_menu
	read choice

	case $choice in
		1) add_employee;;
		2) delete_employee;;
		3) search_employee;;
		4) display_employee;;
		5) sort_employees;;
		6) echo "Ending the program..."; break;;
		*) echo "Invalid choice. Please try again." ;;
	esac
done



