#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>

using namespace std;

struct Label{
	char name[30];
	int value;
};

void strcpy(char* str1, char* str2)
{
	int i;
	for (i = 0; str2[i] != 0; i++)
	{
		str1[i] = str2[i];
	}
	str1[i] = 0;
}

void trimSpaces(char line[]){
	// Find the length of the str parameter to the first null terminator
	int length = 0;
	for (int i = 0; line[i] != 0; i++)
		length++;
	
	char result[length + 1];
	
	int count = 0;
	
	// Checks to see if it's the whitespace after the opcode
	bool first = true;
	
	int counter = 0;
	// Trims any initial whitespaces or tabs
	while (line[0] == ' ' || line[0] == '\t')
	{
		for (int j = 0; line[j] != 0; j++)
		{
			line[j] = line[j + 1];
		}
	}
	
	
	// Copies the str parameter with only the first whitespace
	// into another str array
	for (int i = 0; line[i] != 0; i++)
	{
		if ((line[i] == ' ' || line[i] == '\t') && first)
		{
			result[count] = ' ';
			count++;
			first = false;
		}
		
		if (line[i] != ' ' && line[i] != '\t')
		{
			result[count] = line[i];
			count++;
		}
	}
	
	
	// Copies the str from result to line
	int index = 0;
	while (result[index] != 0 && index < count)
	{
		line[index] = result[index];
		index++;
	}
	line[index] = 0;
}

int strCmp(char str1[], char str2[]){
	
	// Finding the length of the two strs
	int str1Length = 0;
	int str2Length = 0;
	
	for (int i = 0; str1[i] != 0; i++)
		str1Length++;
	
	for (int i = 0; str2[i] != 0; i++)
		str2Length++;
	
	// Comparing strs that are of different lengths but are otherwise same
	// If the first str is less than the second str
	if ((str1Length < str2Length) || (str1Length > str2Length))
	{
		return -1;
	}
	
	// If both strs have the same length
	for (int j = 0; j < str2Length; j++){
		
		// If a character in the first str is ahead of the corresponding
		// character in the second str		
		if (str1[j] < str2[j])
			return 1;
		
		// If a character in the first str is behind the corresponding
		// character in the second str
		else if (str1[j] > str2[j])
			return -1;
	}
	
	// If strs are exactly equal
	return 0;
}

int strOperandCheck(char operandStr[], char opcode[], int line) 
{
		if(!strCmp(opcode, (char*)"LD"))//
		{
			bool AlreadyChecked=false;
			if (operandStr[0]=='0' || operandStr[0]=='1'||operandStr[0]=='2'||operandStr[0]=='3'||operandStr[0]=='4'||operandStr[0]=='5'||operandStr[0]=='6'||operandStr[0]=='7'||operandStr[0]=='8'||operandStr[0]=='9')
			{
				int i=1;
				for (i=1 ; operandStr[i]!=',' && operandStr[i]!=0; i++)
				{
					if (operandStr[i]!='0' && operandStr[i]!='1'&&operandStr[i]!='2'&&operandStr[i]!='3'&&operandStr[i]!='4'&&operandStr[i]!='5'&&operandStr[i]!='6'&&operandStr[i]!='7'&&operandStr[i]!='8'&&operandStr[i]!='9')
					{
						cerr << "Error on line " << line << ": invalid missing value for number" << endl;
						return -1;
					}
				}
				if (operandStr[i]!= ',')
				{
					cerr << "Error on line " << line << ": invalid missing comma after Register" << endl;
					return -1;
				}
				if ((operandStr[i]==',' && operandStr[i+1]==',') ||(operandStr[i]==',' && operandStr[i+1]==0) )
				{
					cerr << "Error on line "<<line<<" missing operand" << endl;
					return -1;
				}
				if (operandStr[i+1]!= 'R')
				{
				cerr << "Error on line " << line << ": invalid missing Register after comma; saw "<< operandStr[i+1] << endl;
					/*
					cerr << "Error on line " << line << " : invalid Register after comma; saw \"";
					for (int j = i+1; operandStr[j] != 0; j++)
						cerr << operandStr[j];
					cerr << "\"" << endl;
					
					return -1;
					*/
					return -1;
				}
				int p=i+2;
				if (operandStr[i+2]==0)
				{
					cerr << "Error on line " << line << ": invalid missing integer or extra value" << endl;
					return -1;
				}
					
				for (p = i+2 ; operandStr[p]!=0; p++)
				{
					if (operandStr[p]!='0' && operandStr[p]!='1'&&operandStr[p]!='2'&&operandStr[p]!='3'&&operandStr[p]!='4'&&operandStr[p]!='5'&&operandStr[p]!='6'&&operandStr[p]!='7'&&operandStr[p]!='8'&&operandStr[p]!='9')
					{
						cerr << "Error on line " << line << ": invalid missing value for register or extra value" << endl;
						return -1;
					}
				}
				AlreadyChecked = true;
			}
			if (operandStr[0] == 'R')  //might have to add an error for this case
			{
				int i=1;
				if (operandStr[i]==',')
				{
					cerr << "Error on line " << line << ": invalid missing integer or extra value" << endl;
					return -1;
				}
					
				for (i = 1 ; operandStr[i]!=',' && operandStr[i]!=0; i++)
				{
					if (operandStr[i]!='0' && operandStr[i]!='1'&&operandStr[i]!='2'&&operandStr[i]!='3'&&operandStr[i]!='4'&&operandStr[i]!='5'&&operandStr[i]!='6'&&operandStr[i]!='7'&&operandStr[i]!='8'&&operandStr[i]!='9')
					{
						cerr << "Error on line " << line << ": invalid missing value for register or extra value" << endl;
						return -1;
					}
				}
				
				if (operandStr[i]!=',')
				{
					cerr << "Error on line " << line << ": invalid missing comma after Register" << endl;
					return -1;
				}
				if ((operandStr[i]==',' && operandStr[i+1]==',') ||(operandStr[i]==',' && operandStr[i+1]==0) )
				{
					cerr << "Error on line "<<line<<" missing operand" << endl;
					return -1;
				}
				if (operandStr[i+1]!='R')
				{
				cerr << "Error on line " << line << ": invalid missing Register after comma; saw " << operandStr[i+1] << "" << endl;
				return -1;
				}
				int p=i+2;
				if (operandStr[i+2]==0)
				{
					cerr << "Error on line " << line << ": invalid missing integer or extra value" << endl;
					return -1;
				}
					
				for (p = i+2 ; operandStr[p]!=0; p++)
				{
					if (operandStr[p]!='0' && operandStr[p]!='1'&&operandStr[p]!='2'&&operandStr[p]!='3'&&operandStr[p]!='4'&&operandStr[p]!='5'&&operandStr[p]!='6'&&operandStr[p]!='7'&&operandStr[p]!='8'&&operandStr[p]!='9')
					{
						cerr << "Error on line " << line << ": invalid missing value for register or extra value" << endl;
						return -1;
					}
				}
				AlreadyChecked= true;
			}
			else if(AlreadyChecked==false){
				cerr << "Error on line " << line << ":invalid missing Register; " << "saw " << operandStr[0] << endl; //MIGHT BE invalid , missing, SAME WITH OTHERS WHICH ARE AFTER THE WHOLE CODE.
				return -1;
			}
			return 0;
			
		}
		
		if(!strCmp(opcode, (char*)"LDi")) //working fine
		{
			
			if (operandStr[0]=='0' || operandStr[0]=='1'||operandStr[0]=='2'||operandStr[0]=='3'||operandStr[0]=='4'||operandStr[0]=='5'||operandStr[0]=='6'||operandStr[0]=='7'||operandStr[0]=='8'||operandStr[0]=='9')
			{
				int i=1;
				for (i=1 ; operandStr[i]!=',' && operandStr[i]!=0; i++)
				{
					if (operandStr[i]!='0' && operandStr[i]!='1'&&operandStr[i]!='2'&&operandStr[i]!='3'&&operandStr[i]!='4'&&operandStr[i]!='5'&&operandStr[i]!='6'&&operandStr[i]!='7'&&operandStr[i]!='8'&&operandStr[i]!='9')
					{
						cerr << "Error on line " << line << ": invalid missing value for number or extra value" << endl;
						return -1;
					}
				}
				if (operandStr[i]!= ',')
				{
					cerr << "Error on line " << line << ": invalid missing comma after Register" << endl;
					return -1;
				}
				if ((operandStr[i]==',' && operandStr[i+1]==',') ||(operandStr[i]==',' && operandStr[i+1]==0) )
				{
					cerr << "Error on line "<<line<<" missing operand" << endl;
					return -1;
				}
				if (operandStr[i+1]!='R')
				{
					cerr << "Error on line " << line << ": invalid missing Register after comma; saw " << operandStr[i+1] << "" << endl;
					return -1;
				}
				
				int p=i+2;
				if (operandStr[i+2]==0)
				{
					cerr << "Error on line " << line << ": invalid missing integer or extra value" << endl;
					return -1;
				}
					
				for (p = i+2 ; operandStr[p]!=0; p++)
				{
					if (operandStr[p]!='0' && operandStr[p]!='1'&&operandStr[p]!='2'&&operandStr[p]!='3'&&operandStr[p]!='4'&&operandStr[p]!='5'&&operandStr[p]!='6'&&operandStr[p]!='7'&&operandStr[p]!='8'&&operandStr[p]!='9')
					{
						cerr << "Error on line " << line << ": invalid missing value for register or extra value" << endl;
						return -1;
					}
				}
			}
			else{
				cerr << "Error on line " << line << ": invalid missing Register; " << "saw " << operandStr[0] << endl; 
				return -1;
			}
			return 0;
		}
		
		if(!strCmp(opcode, (char*)"SD")) //working fine so far
		{			
			if (operandStr[0] == 'R') 
			{
				int p=1;
				
				int i=1;
				if (operandStr[i]==',')
				{
					cerr << "Error on line " << line << ": invalid missing integer or extra value" << endl;
					return -1;
				}
					
				for (i=1 ; operandStr[i]!=',' && operandStr[i]!=0; i++)
				{
					if (operandStr[i]!='0' && operandStr[i]!='1'&&operandStr[i]!='2'&&operandStr[i]!='3'&&operandStr[i]!='4'&&operandStr[i]!='5'&&operandStr[i]!='6'&&operandStr[i]!='7'&&operandStr[i]!='8'&&operandStr[i]!='9')
					{
						cerr << "Error on line " << line << ": invalid missing value for register or extra value" << endl;
						return -1;
					}
				}
				
				
				if (operandStr[i]!=',')
				{
					cerr << "Error on line " << line << ": invalid missing comma after Register" << endl;
					return -1;
				}
				if ((operandStr[i]==',' && operandStr[i+1]==',') ||(operandStr[i]==',' && operandStr[i+1]==0) )
				{
					cerr << "Error on line "<<line<<" missing operand" << endl;
					return -1;
				}
				if (operandStr[i+1]!='R' && operandStr[i+1]!='0' && operandStr[i+1]!='1'&&operandStr[i+1]!='2'&&operandStr[i+1]!='3'&&operandStr[i+1]!='4'&&operandStr[i+1]!='5'&&operandStr[i+1]!='6'&&operandStr[i+1]!='7'&&operandStr[i+1]!='8'&&operandStr[i+1]!='9') // need to re-check this condition
				{
					cerr << "Error on line " << line << ": invalid missing Register after comma; saw " << operandStr[p] << "" << endl;
					return -1;
				}
				if (operandStr[i+2]==0)
				{
					cerr << "Error on line " << line << ": invalid missing integer or extra value" << endl;
					return -1;
				}
					
				for (p=i+2; operandStr[p]!=0; p++)
				{
					if (operandStr[p]!='0' && operandStr[p]!='1'&&operandStr[p]!='2'&&operandStr[p]!='3'&&operandStr[p]!='4'&&operandStr[p]!='5'&&operandStr[p]!='6'&&operandStr[p]!='7'&&operandStr[p]!='8'&&operandStr[p]!='9')
					{
						cerr << "Error on line " << line << ": invalid missing value for number or extra value" << endl;
						return -1;
					}
				}
				
			}
			else{
				cerr << "Error on line " << line << ": invalid missing Register; " << "saw " << operandStr[0] << endl;
				return -1;
			}
			return 0;
		}
		if(!strCmp(opcode, (char*)"SDi")) //might be working
		{			
			bool check = true;
			int p=1;
			if (operandStr[0]=='0' || operandStr[0]=='1'||operandStr[0]=='2'||operandStr[0]=='3'||operandStr[0]=='4'||operandStr[0]=='5'||operandStr[0]=='6'||operandStr[0]=='7'||operandStr[0]=='8'||operandStr[0]=='9')
			{
				int i=1;
				for (i=1 ; operandStr[i]!=',' && operandStr[i]!=0; i++)
				{
					if (operandStr[i]!='0' && operandStr[i]!='1'&&operandStr[i]!='2'&&operandStr[i]!='3'&&operandStr[i]!='4'&&operandStr[i]!='5'&&operandStr[i]!='6'&&operandStr[i]!='7'&&operandStr[i]!='8'&&operandStr[i]!='9')
					{
						cerr << "Error on line " << line << ": invalid missing value for number or extra value" << endl;
						return -1;
					}
				}
				if (operandStr[i]!= ',')
				{
					cerr << "Error on line " << line << ": invalid missing comma after number" << endl;
					return -1;
				}
				if ((operandStr[i]==',' && operandStr[i+1]==',') ||(operandStr[i]==',' && operandStr[i+1]==0) )
				{
					cerr << "Error on line "<<line<<" missing operand" << endl;
					return -1;
				}
				if (operandStr[i+1]!='R' && operandStr[i+1]!='0' && operandStr[i+1]!='1'&&operandStr[i+1]!='2'&&operandStr[i+1]!='3'&&operandStr[i+1]!='4'&&operandStr[i+1]!='5'&&operandStr[i+1]!='6'&&operandStr[i+1]!='7'&&operandStr[i+1]!='8'&&operandStr[i+1]!='9') // need to re-check this condition
				{
					cerr << "Error on line " << line << ": invalid missing Register after comma; saw " << operandStr[p] << "" << endl;
					return -1;
				}
				if (operandStr[i+2]==0)
				{
					cerr << "Error on line " << line << ": invalid missing integer or extra value" << endl;
					return -1;
				}
					
				for (p=i+2; operandStr[p]!=0; p++)
				{
					if (operandStr[p]!='0' && operandStr[p]!='1'&&operandStr[p]!='2'&&operandStr[p]!='3'&&operandStr[p]!='4'&&operandStr[p]!='5'&&operandStr[p]!='6'&&operandStr[p]!='7'&&operandStr[p]!='8'&&operandStr[p]!='9')
					{
						cerr << "Error on line " << line << ": invalid missing value for number or extra value" << endl;
						return -1;
					}
				}
			
			}
			else{
				cerr << "Error on line " << line << ": invalid missing number; " << "saw " << operandStr[0] << endl;
				return -1;
			}
			return 0;
		}
		
		if(!strCmp(opcode, (char*)"ADD") || !strCmp(opcode, (char*)"SUB") || !strCmp(opcode, (char*)"MUL") || !strCmp(opcode, (char*)"DIV")) //working fine
		{	
			if (operandStr[0] == 'R')
			{
				int i=1;
				if (operandStr[i]==',')
				{
					cerr << "Error on line " << line << ": invalid missing integer or extra value" << endl;
					return -1;
				}
					
				for (i=1 ; operandStr[i]!=',' && operandStr[i]!=0; i++)
				{
					if (operandStr[i]!='0' && operandStr[i]!='1'&&operandStr[i]!='2'&&operandStr[i]!='3'&&operandStr[i]!='4'&&operandStr[i]!='5'&&operandStr[i]!='6'&&operandStr[i]!='7'&&operandStr[i]!='8'&&operandStr[i]!='9')
					{
						cerr << "Error on line " << line << " : invalid missing value for register or extra value" << endl;
						return -1;
					}
				}
				if (operandStr[i]!=',')
				{
					cerr << "Error on line " << line << " : invalid missing comma after Register" << endl;
					return -1;
				}
				if ((operandStr[i]==',' && operandStr[i+1]==',') ||(operandStr[i]==',' && operandStr[i+1]==0))
				{
					cerr << "Error on line "<<line<<" missing operand" << endl;
					return -1;
				}
				if (operandStr[i+1]!='R')
				{
					cerr << "Error on line " << line << " : invalid missing Register after comma; saw " << operandStr[i+1] << "" << endl;
					return -1;
				}
				if (operandStr[i+2]==',')
				{
					cerr << "Error on line " << line << ": invalid missing integer or extra value" << endl;
					return -1;
				}
					
				for (i=i+2 ; operandStr[i]!=',' && operandStr[i]!=0; i++)
				{
					if (operandStr[i]!='0' && operandStr[i]!='1'&&operandStr[i]!='2'&&operandStr[i]!='3'&&operandStr[i]!='4'&&operandStr[i]!='5'&&operandStr[i]!='6'&&operandStr[i]!='7'&&operandStr[i]!='8'&&operandStr[i]!='9')
					{
						cerr << "Error on line " << line << " : invalid missing value for register or extra value" << endl;
						return -1;
					}
				}
				
				if (operandStr[i]!=',')
				{
					cerr << "Error on line " << line << " : invalid missing comma after Register" << endl;
					return -1;
				}
				if ((operandStr[i]==',' && operandStr[i+1]==',') ||(operandStr[i]==',' && operandStr[i+1]==0))
				{
					cerr << "Error on line "<<line<<" missing operand" << endl;
					return -1;
				}
				if (operandStr[i+1]!='R')
				{
					cerr << "Error on line " << line << " : invalid missing Register after comma; saw " << operandStr[i+1] << "" << endl;
					return -1;
				}
				if (operandStr[i+2]==0)
				{
					cerr << "Error on line " << line << ": invalid missing integer or extra value" << endl;
					return -1;
				}
					
				for (i=i+2 ;operandStr[i]!=0; i++)
				{
					if (operandStr[i]!='0' && operandStr[i]!='1'&&operandStr[i]!='2'&&operandStr[i]!='3'&&operandStr[i]!='4'&&operandStr[i]!='5'&&operandStr[i]!='6'&&operandStr[i]!='7'&&operandStr[i]!='8'&&operandStr[i]!='9')
					{
						cerr << "Error on line " << line << " : invalid missing value for register or extra value" << endl;
						return -1;
					}
				}
				
			}
			else{
				cerr << "Error on line " << line << "invalid missing Register; " << "saw " << operandStr[0] << endl;
				return -1;
			}
			return 0;
		}
		if( !strCmp(opcode, (char*)"SUBi") ||!strCmp(opcode, (char*)"ADDi") || !strCmp(opcode, (char*)"MULi") || !strCmp(opcode, (char*)"DIVi")) //working fine
		{
			if (operandStr[0] == 'R')
			{
				int i=1;
				int p=0;
				if (operandStr[i]==',')
				{
					cerr << "Error on line " << line << ": invalid misssing integer or extra value" << endl;
					return -1;
				}
					
				for (i=1 ; operandStr[i]!=',' && operandStr[i]!=0; i++)
				{
					if (operandStr[i]!='0' && operandStr[i]!='1'&&operandStr[i]!='2'&&operandStr[i]!='3'&&operandStr[i]!='4'&&operandStr[i]!='5'&&operandStr[i]!='6'&&operandStr[i]!='7'&&operandStr[i]!='8'&&operandStr[i]!='9')
					{
						cerr << "Error on line " << line << " : invalid missing value for register or extra value" << endl;
						return -1;
					}
				}
				if (operandStr[i]!=',')
				{
					cerr << "Error on line " << line << " : invalid missing comma after Register" << endl;
					return -1;
				}
				if ((operandStr[i]==',' && operandStr[i+1]==',') ||(operandStr[i]==',' && operandStr[i+1]==0))
				{
					cerr << "Error on line "<<line<<" missing operand" << endl;
					return -1;
				}
				for ( p=i+1; operandStr[p]!=',' && operandStr[i]!=0; p++)
				{
					if (operandStr[p]!='0' && operandStr[p]!='1'&&operandStr[p]!='2'&&operandStr[p]!='3'&&operandStr[p]!='4'&&operandStr[p]!='5'&&operandStr[p]!='6'&&operandStr[p]!='7'&&operandStr[p]!='8'&&operandStr[p]!='9')
					{
						cerr << "Error on line " << line << " : invalid missing number to be added to register or extra value added" << endl;
						return -1;
					}
				}
				if (operandStr[p] != ',')
				{
					cerr << "Error on line " << line << " : invalid missing comma after Register" << endl;
					return -1;
				}
				if ((operandStr[p]==',' && operandStr[p+1]==',') ||(operandStr[p]==',' && operandStr[p+1]==0))
				{
					cerr << "Error on line "<<line<<" missing operand" << endl;
					return -1;
				}
				if (operandStr[p+1] != 'R')
				{
					cerr << "Error on line " << line << " : invalid missing Register after comma; saw " << operandStr[i+1] << "" << endl;
					return -1;
				}
				if (operandStr[p+2]==0)
				{
					cerr << "Error on line " << line << ": invalid missing integer or extra value" << endl;
					return -1;
				}
					
				for (p=p+2 ; operandStr[p]!=0; p++)
				{
					if (operandStr[p]!='0' && operandStr[p]!='1'&&operandStr[p]!='2'&&operandStr[p]!='3'&&operandStr[p]!='4'&&operandStr[p]!='5'&&operandStr[p]!='6'&&operandStr[p]!='7'&&operandStr[p]!='8'&&operandStr[p]!='9')
					{
						cerr << "Error on line " << line << " : invalid missing value for register or extra value" << endl;
						return -1;
					}
				}
				
			}
			else {
				cerr << "Error on line " << line << "invalid missing Register; " << "saw " << operandStr[0] << endl;
				return -1;
			}
			return 0;
		}
		
		if(!strCmp(opcode, (char*)"JZ") || !strCmp(opcode, (char*)"JNZ") || !strCmp(opcode, (char*)"JGZ") || !strCmp(opcode, (char*)"JGEZ") || !strCmp(opcode, (char*)"JLZ") || !strCmp(opcode, (char*)"JLEZ")) //working fine
		{
			
			if (operandStr[0] == 'R')
			{
				int l=0;
				int i=1;
				int p=0;
				if (operandStr[i]==',')
				{
					cerr << "Error on line " << line << ": invalid missing integer or extra value" << endl;
					return -1;
				}
									
				for (i=1 ; operandStr[i]!=',' && operandStr[i]!=0; i++)
				{
					
					if (operandStr[i]!='0'&& operandStr[i]!='1'&&operandStr[i]!='2' && operandStr[i]!='3'&&operandStr[i]!='4'&&operandStr[i]!='5'&&operandStr[i]!='6'&&operandStr[i]!='7'&&operandStr[i]!='8'&&operandStr[i]!='9')
					{
						
						cerr << "Error on line " << line << ": invalid missing number for register, need integer" << endl;
						return -1;
					}
				}
			
				if (operandStr[i]!=',')
				{
					cerr << "Error on line " << line << " : invalid missing comma after Register" << endl;
					return -1;
				}
				if ((operandStr[i]==',' && operandStr[i+1]==',') ||(operandStr[i]==',' && operandStr[i+1]==0))
				{
					cerr << "Error on line "<<line<<" missing operand" << endl;
					return -1;
				}
				
				for (i=i+1; operandStr[i]!=0 ; i++)
				{
					if (operandStr[i]!='0' && operandStr[i]!='1'&&operandStr[i]!='2'&&operandStr[i]!='3'&&operandStr[i]!='4'&&operandStr[i]!='5'&&operandStr[i]!='6'&&operandStr[i]!='7'&&operandStr[i]!='8'&&operandStr[i]!='9')
					{
						cerr << "Error on line " << line << ": invalid missing integer or extra value" << endl;
						return -1;
					}
				}
			}
			else {
				cerr << "Error on line " << line << "invalid missing Register; " << "saw " << operandStr[0] << endl;
				return -1;
			}
			return 0;
		}
		if (!strCmp(opcode, (char*)"JMP")) //working fine
		{ 
			if (operandStr[0]==0)
			{
				cerr << "Error on line "<<line<<" missing operand" << endl;
				return -1;
				
			}
			else 
			{
				for (int h=0 ; operandStr[h]!=0 ; h++)
				{
					if (operandStr[h]!='0' && operandStr[h]!='1'&& operandStr[h]!='2' && operandStr[h]!='3'&&operandStr[h]!='4'&&operandStr[h]!='5'&&operandStr[h]!='6'&&operandStr[h]!='7'&&operandStr[h]!='8'&&operandStr[h]!='9')
					{
						cerr << "Error on line " << line << ": invalid missing integer or extra value" << endl;
						return -1;
					}
				}
			}	
			return 0;
		}
		
}


int main(int argc, char* argv[])
{
	
	// Checks if the file exists
	ifstream infile;
	infile.open(argv[1]);
	
	if (argc != 2)
	{
		cerr << "Error: INVALID ARGUMENTS." << endl; 
		cerr << "Error: File can't be opened." << endl;
		return -1;
	}
	
	if (infile.is_open())
	{
		// cout << "File exists." << endl;
	}
	
	else
	{
		cerr << "Error: File can't be opened." << endl;
		return -1;
	}
	
	const int maxLineLength = 100;
	char line[maxLineLength];
	
	// char nextChar;
	int assemblyInst = 0;
	int numCode = 0;
	int numData = 0;
	int numLines = 1;
	int numALU = 0;
	int numLDSD = 0;
	int numJMP = 0;
	int numErrors = 0;
	int numLabels = 0;
	int codeOccur=0;
	bool AlreadyPrintedOut;
	
	enum LineType {COMMENT, LABEL, ASSEMBLY};
	LineType type;
	
	
	Label labelArray[10];
	
	// Set maximum line length, so we don't overflow the buffer
	infile >> setw(maxLineLength);
  
   // Read from file
	while(infile.getline(line, maxLineLength)) 
	{
		trimSpaces(line);
		type = ASSEMBLY;
		
		if (line[0] == '#')
			type = COMMENT;
		
		if (type != COMMENT)
		{
			for (int i = 0; line[i] != 0 && i < 100; i++)
			{
				if (line[i] == ':'){
					type = LABEL;
					break;
				}
			}
		}
		
		switch(type){
			
			case COMMENT:{
				
				//cout << "COMMENT";
				break;
			}
			
			case LABEL:{
				
				//cout << "LABEL";
				
				char label[30];
				
				int j=0;
				
				if (line[j] == ':')
				{
					cerr << "Error on line " << numLines << ": Invalid label detected" << endl;
					numErrors++;
					break;
				}
				
				while(line[j]!=':')
				{
					label[j] = line[j];
					
					j++;
				}
				label[j] = ':';
				label[j+1] = 0;
				// cout << label << endl;
				
				// When it's a code directive
				
				if (!strCmp(label, (char*)"Code:") && assemblyInst == 0)
				{
					int numElemData = 1;
					codeOccur=1;										
					int val;
					for (val=6; line[val]!=0 && line[val]!='#' && line[val]!='\n'  && line[val] != ' '; val++)
					{
						numElemData++;
					}
					
					char numCodeArray[numElemData];
					int c=0;
					
					for (int y=6; line[y]!=0 && line[y]!='#' && line[y]!='\n'  && line[y] != ' '; y++) 
					{
						numCodeArray[c] = line[y];
						c++;
					}
					
					numCodeArray[c] = 0;
					numCode = atoi(numCodeArray);
					
					break;
				}
				//cout << "Codeoccur " << codeOccur << endl;
				if (!strCmp(label, (char*)"Code:") && assemblyInst != 0 && codeOccur!=1)
				{
					cerr << "Error on Line: 1" << " missing directive (code) before the first assembly instruction" << endl;
					numErrors++;
					AlreadyPrintedOut = true;
					break;
				}
				// When the Code directive is repeated again in the assembly file
				if (!strCmp(label, (char*)"Code:") && codeOccur==1)
				{
					cerr << "Error on line " << numLines << ": duplicate directive found" << endl;
					numErrors++;
					break;
				}
				
				// When it's a data directive
				if (!strCmp(label, (char*)"Data:"))
				{	
					int numElemData = 1;
															
					int val;
					for (val=6; line[val]!=0 && line[val]!='#' && line[val]!='\n'  && line[val] != ' '; val++)
					{
						numElemData++;
					}
					
					char numDataArray[numElemData];
					int c=0;
					
					for (int y=6; line[y]!=0 && line[y]!='#' && line[y]!='\n'  && line[y] != ' '; y++) 
					{
						numDataArray[c] = line[y];
						c++;
					}
					
					numDataArray[c] = 0;
					numData = atoi(numDataArray);
					// cout << numData << endl;
					break;
				}
				
				// When it is not a Code or Data directive
				// Aka when it's a label
				
				int ind = j + 1;
				while (line[ind] != 0 && line[ind] != '#')
				{
					if (line[ind] != ' ' && line[ind] != '\t')
					{
						cerr << "Error on line " << numLines << ": Invalid input detected" << endl;
						numErrors++;
						break;
					}
					ind++;
				}
					
				// Removing colon from the label to insert into data array
				label[j] = 0;
				
				strcpy(labelArray[numLabels].name, label);
				labelArray[numLabels].value = numCode + assemblyInst;
					
				// Checks if there is a duplicate label
				for(int l = 0; l < numLabels - 1; l++)
				{
					if (!strCmp(label, labelArray[l].name)) // shouldnt this be l instead of numlabels
					{
						cerr << "Error on line " << numLines << ": duplicate label detected" << endl;
						numErrors++;
						break;
					}
				}	
					
				// cout << labelArray[numLabels].name << endl;
				numLabels++;
			
				break;
			}
			
			case ASSEMBLY:
			{
				//cout << "Hitting assembly" << endl;
				enum opcodeTypes {LDSD, ALU, JMP};
				opcodeTypes OPCODE = LDSD;
				char opcodeStr[5] = "";
				char operandStr[100] = "";
				int ind = 0;
				int indl;
				
				/*
				if (line[0]=='\n'){
					numLines++;
					break;
				}*/
				
				// Failing for new line character
				/*if (line[0]!='A'&&line[0]!='S'&&line[0]!='L'&&line[0]!='J'&&line[0]!='D'&&line[0]!='M' && line[0] != 0)
				{
					cerr << "Error on Line " << numLines<< " opcode not found" << endl;
					numErrors++;
				}*/
				
				
				//cout<< "After trim spaces: "<<line<< endl;
				for (ind=0; line[ind]!= ' ' && line[ind]!=0; ind++) 
				{
					opcodeStr[ind] = line[ind];
				}
				if ((!(!strCmp(opcodeStr, (char*)"LD") || !strCmp(opcodeStr, (char*)"SD") || !strCmp(opcodeStr, (char*)"LDi") || !strCmp(opcodeStr, (char*)"SDi") || !strCmp(opcodeStr, (char*)"ADD") || !strCmp(opcodeStr, (char*)"SUB") ||!strCmp(opcodeStr, (char*)"MUL") || !strCmp(opcodeStr, (char*)"DIV")|| !strCmp(opcodeStr, (char*)"ADDi") || !strCmp(opcodeStr, (char*)"SUBi") ||!strCmp(opcodeStr, (char*)"MULi") || !strCmp(opcodeStr, (char*)"DIVi") || !strCmp(opcodeStr, (char*)"JLZ")||!strCmp(opcodeStr, (char*)"JZ")||!strCmp(opcodeStr, (char*)"JNZ")||!strCmp(opcodeStr, (char*)"JGZ")||!strCmp(opcodeStr, (char*)"JGEZ")||!strCmp(opcodeStr, (char*)"JLEZ")|| !strCmp(opcodeStr, (char*)"JMP")))&&line[0]!=0)
				{
					cerr << "Error on Line " << numLines<< " invalid or opcode not found" << endl;
					numErrors;
				}
				
				//cout <<strCmp(opcodeStr, "LD")<<"$$$"<<endl;
				if (!strCmp(opcodeStr, (char*)"LD") || !strCmp(opcodeStr, (char*)"SD"))
				{
					
					//cout << "Hitting LD/SD" << endl;
					
					int dummy =0; 
					
					for (indl=ind+1; (line[indl]!= 0) && (line[indl]!= '\n') && (line[indl]!= '#'); indl++)
					{				
						operandStr[dummy] = line[indl];
						dummy++;
					}
					
					//cout << strOperandCheck(operandStr, opcodeStr, numLines) << endl << endl << endl;
					if (strOperandCheck(operandStr, opcodeStr, numLines) < 0)
						numErrors++;
					
					numLDSD++;
					assemblyInst++;
				}
				
				if (!strCmp(opcodeStr, (char*)"LDi") || !strCmp(opcodeStr, (char*)"SDi"))
				{
					//cout << "Hitting LDi/SDi" << endl;
					
					int dummy =0; 
					for (indl=ind+1; line[indl]!= 0 && line[indl]!= ' ' && line[indl]!= '\n' && line[indl]!= '#'; indl++)
					{
						operandStr[dummy] = line[indl];
						dummy++;
					}
					
					if (strOperandCheck(operandStr, opcodeStr, numLines) < 0)
						numErrors++;
					
					numLDSD++;
					assemblyInst++;
				}
				
				if (!strCmp(opcodeStr, (char*)"ADD") || !strCmp(opcodeStr, (char*)"MUL") || !strCmp(opcodeStr, (char*)"SUB") || !strCmp(opcodeStr, (char*)"DIV"))
				{	
					//cout << "Hitting ADD/SUB/MUL/SUB/DIV" << endl;
					
					int dummy =0; 
					for (indl=ind+1; line[indl]!= 0 && line[indl]!= ' ' && line[indl]!= '\n' && line[indl]!= '#'; indl++)
					{
						operandStr[dummy] = line[indl];
						dummy++;
					}
					
					if (strOperandCheck(operandStr, opcodeStr, numLines) < 0)
						numErrors++;
					
					numALU++;
					assemblyInst++;
				}
								
				if (!strCmp(opcodeStr, (char*)"ADDi") || !strCmp(opcodeStr, (char*)"MULi") || !strCmp(opcodeStr, (char*)"SUBi") || !strCmp(opcodeStr, (char*)"DIVi"))
				{				
					//cout << "Hitting ADDi/SUBi/MULi/SUBi/DIVi" << endl;
					
					int dummy =0; 
					for (indl=ind+1; line[indl]!= 0 && line[indl]!= ' ' && line[indl]!= '\n' && line[indl]!= '#'; indl++)
					{
						operandStr[dummy] = line[indl];
						dummy++;
					}
					//cout << "~~~~~" << opcodeStr << "&&" << operandStr << endl <<endl;
					//cout << strOperandCheck(operandStr, opcodeStr, numLines) << endl << endl << endl;
					if (strOperandCheck(operandStr, opcodeStr, numLines) < 0)
						numErrors++;
					
					numALU++;
					assemblyInst++;
				}
				
				if (!strCmp(opcodeStr, (char*)"JZ") || !strCmp(opcodeStr, (char*)"JNZ") || !strCmp(opcodeStr, (char*)"JGZ") || !strCmp(opcodeStr, (char*)"JGEZ")|| !strCmp(opcodeStr, (char*)"JLZ")|| !strCmp(opcodeStr, (char*)"JLEZ"))
				{
					//cout << "Hitting JZ/JNZ/JGZ/JGEZ/JLZ/JLEZ" << endl;
					
					int dummy =0; 
					for (indl=ind+1; line[indl]!= 0 && line[indl]!= ' ' && line[indl]!= '\n' && line[indl]!= '#'; indl++)
					{
						operandStr[dummy] = line[indl];
						dummy++;
					}
					//cout << "~~~~~" << opcodeStr << "&&" << operandStr << endl <<endl;
					//cout << strOperandCheck(operandStr, opcodeStr, numLines) << endl << endl << endl;
					if (strOperandCheck(operandStr, opcodeStr, numLines) < 0)
						numErrors++;
					
					numJMP++;
					assemblyInst++;
				}
				
				if (!strCmp(opcodeStr, (char*)"JMP"))
				{
					//cout << "Hitting JMP" << endl;
					
					int dummy =0; 
					for (indl=ind+1; line[indl]!= 0 && line[indl]!= ' ' && line[indl]!= '\n' && line[indl]!= '#'; indl++)
					{
						operandStr[dummy] = line[indl];
						dummy++;
					}
					
					if (strOperandCheck(operandStr, opcodeStr, numLines) < 0)
						numErrors++;
					
					numJMP++;
					assemblyInst++;
				}
				
				
			} // case: Assembly
			
		} // switch
		
		numLines++;
		
	} // while
	if (codeOccur == 0 && !AlreadyPrintedOut)
	{
		cerr << "Error on Line 1, no code directive found" << endl;
		numErrors++;
	}
	//if (numErrors == 0)
	//{
		// cout << numCode << endl;
		// cout << assemblyInst << endl;	
		cout << "Total number of assembly instructions: " << assemblyInst << endl;
		cout << "Number of Load/Store: " << numLDSD << endl;
		cout << "Number of ALU: " << numALU << endl;
		cout << "Number of Compare/Jump: " << numJMP << endl;
		for (int p = 0; p < numLabels; p++)
		{
			cout << labelArray[p].name << ": " << labelArray[p].value << endl;
		}	
	//}

	return 0;

}