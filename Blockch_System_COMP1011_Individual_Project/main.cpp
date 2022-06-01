#include <cstring>
#include <string>
#include <iostream>
#include "SHA1.hpp"
#include "SHA1.cpp"
#define max 1000
using namespace std;

struct block // the structure of block
{
	int index;	   // the index of the block
	string text;   // the text that the user want to store
	string p_hash; // previous hash value
	string hash;   // hash value
	block *next;   // linked list
};

struct blockchain // the structure of blockchain
{
	struct block block_array[max]; // define a maximum of 1000 blocks in the blockchain
	int max_size;
};

string hash_function(string s) // the hash function
{
	string input(s);
	SHA1 checksum;
	checksum.update(input);
	char hash[41];
	strcpy(hash, checksum.final().c_str());
	return hash;
}

void information(blockchain *block, int index) // print block
{
	cout << endl
		 << "\t\t\tHere is the information of Block No." << index + 1 << endl;
	cout << endl;
	cout << "\tIndex: " << block->block_array[index].index << endl;
	cout << "\tText: " << block->block_array[index].text << endl;
	cout << "\tHash value: " << block->block_array[index].hash << endl;
	cout << "\tPrevious hash value: " << block->block_array[index].p_hash << endl;
	cout << endl;
}

void menu() // the menu of blockchain
{
	cout << endl
		 << "---------------------------------------------------------" << endl;
	cout << "|\t\t\tBlockChain Menu\t\t\t|" << endl;
	cout << "|\t\t1.Add the block\t\t\t\t|" << endl
		 << "|\t\t2.Search the block \t\t\t|" << endl
		 << "|\t\t3.Print the hash value \t\t\t|" << endl
		 << "|\t\t4.Print the text \t\t\t|" << endl
		 << "|\t\t5.Check the integrity\t\t\t|" << endl
		 << "|\t\t0.Quit the system  \t\t\t|" << endl;
	cout << "---------------------------------------------------------" << endl;
}

void add_block(blockchain *block) // add block
{
	if (block->max_size == max)
	{
		cout << "Input failure." << endl;
		return;
	}
	else
	{
		cout << "Enter the number of blocks you want to add: ";
		int add_number = 0;
		cin >> add_number; // confirm the index of the added block
		if (add_number > 0)
		{
			int new_size;
			new_size = block->max_size + add_number;
			string text, p_hash, hash;
			if (block->max_size != 0) // recall the hash value of the previous block
			{
				p_hash = block->block_array[block->max_size - 1].hash;
			}
			for (int i = block->max_size; i < new_size; i++)
			{
				cout << endl;
				cout << "\tPlease enter the imformation of block No." << i + 1 << endl;
				cout << "\tPlease enter the text: ";
				cin.clear();
				cin.sync();
				getline(cin, text);
				hash = hash_function(text);

				block->block_array[i].index = i + 1;
				block->block_array[i].text = text;
				block->block_array[i].p_hash = p_hash;
				block->block_array[i].hash = hash;

				p_hash = hash;
				block->max_size++;
			}
			cout << endl
				 << "You have added " << add_number << " block(s) successfully." << endl;

			for (int i = 1; i < block->max_size - 1; i++) // let the block be the structure of linked list
			{
				block->block_array[i].next = &block->block_array[i + 1];
			}

			block->block_array[block->max_size].next = NULL; // linked list of the end will be NULL
		}
		else
		{
			cout << "Input failure." << endl;
		}
	}
}

void search_block(blockchain *block) // search block
{
	if (block->max_size == 0)
	{
		cout << "The blockchain is empty." << endl;
	}
	else
	{
		int select, index;
		string hash, text;
		bool check = false;
		cout << endl
			 << "\t1.Search by block number" << endl;
		cout << "\t2.Search by the text of the block" << endl;
		cout << "\t3.Search by the hash values of the block" << endl;
		cout << endl;
		cout << "Please enter the search method: ";
		cin >> select;
		if (block->max_size == 0)
		{
			cout << "The blockchain is empty." << endl;
			return;
		}
		switch (select)
		{
		case 1:
			cout << "Please enter the block number: ";
			cin >> index; // let user input the block number they want to search
			if (index > block->max_size)
				cout << "The block under this index has not yet been created." << endl;
			else
				information(block, index - 1);
			break;

		case 2:
			cout << "Please enter the text of the block: ";
			cin >> text;
			for (int i = 0; i < block->max_size; i++)
			{
				if (block->block_array[i].text == text)
				{
					information(block, i);
					check = true;
				}
			}
			if (check){}
			else
				cout << "There are no blocks in the blockchain that can match the input information." << endl;
			break;

		case 3:
			cout << "Please enter the hash value of the block: ";
			cin >> hash;
			for (int i = 0; i < block->max_size; i++)
			{
				if (block->block_array[i].hash == hash)
				{
					information(block, i);
					check = true;
				}
			}
			if (check){}
			else
				cout << "There are no blocks in the blockchain that can match the input information." << endl;

			break;

		default:
			cout << "Input failure." << endl;
			break;
		}
	}
}

void print_hash(blockchain *block) // print the hash value of the blockchain
{
	cout << endl
		 << "\t\tHere is the hash value in the blockchain" << endl
		 << endl;
	for (int i = 0; i < block->max_size; i++)
	{
		cout << "\tBlock No." << i + 1 << endl;
		cout << "\tHash value: " << block->block_array[i].hash << endl;
		cout << "\tPrevious hash value: " << block->block_array[i].p_hash << endl;
		cout << endl;
	}
}

void print_text(blockchain *block) // print the text of the blockchain
{
	cout << endl
		 << "\t\tHere is the text in the blockchain" << endl
		 << endl;
	for (int i = 0; i < block->max_size; i++)
	{
		cout << "\tBlock No." << i + 1 << endl;
		cout << "\tText: " << block->block_array[i].text << endl;
		cout << endl;
	}
}

void check_blockchain(blockchain *block) // check the integrity of the blockchain
{
	if (block->max_size == 0)
	{
		cout << "The blockchain is empty." << endl;
	}
	else
	{
		bool check = true;
		for (int i = 0; i < block->max_size - 1; i++) // Check all hash values, compare with their previous hash values
		{
			if (block->block_array[i + 1].p_hash != block->block_array[i].hash)
			{
				cout << "\tThe chain between block " << i + 1 << " and block " << i + 2 << " exists problems" << endl;
				check = false;
			}
		}
		if (check)
		{
			cout << "\tThe chain between all blocks are integral" << endl;
		}
	}
}

int main()
{
	blockchain block;
	block.max_size = 0;
	int select;

	while (true)
	{
		menu();
		cout << "Please enter the number in the Menu: ";
		cin >> select;
		switch (select)
		{
		case 1:
			add_block(&block);
			break;
		case 2:
			search_block(&block);
			break;
		case 3:
			print_hash(&block);
			break;
		case 4:
			print_text(&block);
			break;
		case 5:
			check_blockchain(&block);
			break;
		case 0:
			return 0;
			break;
		default:
			cout << "Please enter a correct number." << endl;
			break;
		}
	}
}