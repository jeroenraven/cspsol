/* File: order_width.cpp 
 * Description: Member functions of class OrderWidth are defined.
 * A OrderWidth object stores all information about an order placed
 * by customer to paper mill.
 */

#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<cassert>

#include "order_width.h"
#include "extern.h"

using namespace std;

int OrderWidth::count = 0;

/*------------------------------------------------------------------------
 * Constructor
------------------------------------------------------------------------*/
OrderWidth::OrderWidth(double width, int demand)
{
	if(demand <= 0) {
		cout<<"incorrect input: demand = "<<demand<<endl;
		exit(-1);
	}
	if(width <= 0 || width > max_pattern_width) {
		cout << "incorrect input: width = " << width;
		cout << " max pattern width = " << max_pattern_width << endl;
		exit(-1);
	}

	this->width = width;
	this->demand = demand;	
	this->id = OrderWidth::count + 1;
	OrderWidth::count++;

	/* Initialize indices. */
	this->master_row_num = -1;
	this->subprob_col_num = -1;
}

/*------------------------------------------------------------------------
Description: Read order data from file and populate container object. 
Assumed Format:
First line of the input file must specify maximum length of roll. 
order_width demand_quantity
------------------------------------------------------------------------*/
void OrderWidth::read_order_data(OrderWidthContainer& ow_set, std::string filename)
{
	ifstream fin;
	double width;
        int demand;

	fin.open(filename.c_str());
	assert(fin != NULL);
	cout << "Reading order data from file " << filename << endl;

	fin >> max_pattern_width;
	fin >> width >> demand;		
	while(fin.eof() == 0)
	{
		OrderWidth * order = new OrderWidth(width, demand);
		ow_set.push_back(order);
		
		fin >> width >> demand;	 /* read next line */
	}	

	cout<<"Total orders read from file = "<<(ow_set.size())<<endl;
	fin.close();
}

/*------------------------------------------------------------------------
 * Print each order object in the container.
------------------------------------------------------------------------*/
void OrderWidth::print_order_list(OrderWidthContainer& ow_set)
{
	OrderWidthIterator ow_iter = ow_set.begin();	
	for(; ow_iter != ow_set.end(); ow_iter++) {
		cout << (*ow_iter)->width <<" "<< (*ow_iter)->demand << endl;
	}
}

/*------------------------------------------------------------------------
Clean up objects in ow_set.
------------------------------------------------------------------------*/
void OrderWidth::clean_up(OrderWidthContainer& ow_set)
{
	OrderWidthIterator ow_iter = ow_set.begin();	
	for(; ow_iter != ow_set.end(); ow_iter++) {
		delete(*ow_iter);
		(*ow_iter) = NULL;
	}
	ow_set.clear();
}

/*------------------------------------------------------------------------
Given master row index find OrderWidth object. 
------------------------------------------------------------------------*/
OrderWidth* OrderWidth::find_orderwidth(OrderWidthContainer& ow_set, int row_index)
{
	OrderWidthIterator ow_iter = ow_set.begin();	
	for(; ow_iter != ow_set.end(); ow_iter++) {
		if((*ow_iter)->get_master_row_num() == row_index)
			return (*ow_iter);
	}
	assert(0);
	return NULL;
}

/*------------------------------------------------------------------------
 * Cleanup orderwidth
------------------------------------------------------------------------*/
OrderWidth::~OrderWidth(void)
{
}

