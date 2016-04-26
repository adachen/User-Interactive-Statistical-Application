/***************************************************************************************************************************************
Title: User Interactive Statistical Application
Author: Ada Chen
Date Created: November 5th, 2014
Description: Uses command line to read a given text. Gives the user an interactive menu that counts the total number of integers in a
file, retrieves the Maximum and Minimum of integers, computes the sum, mean, variance, and standard deviation of the numbers.
It also sorts the numbers from largest to smallest and outputs the list onto a separate text file.
Purpose: Practice navigating around arrays, using command line, reading and writing text files, and functions.
Usage: Input an option to do one of the 8 choices given.
******************************************************************************************************************************************/
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

//function prototypes
int size_of_sample();
void max_sample(int array[], int size);
void min_sample(int array[], int size);
int sum_sample(int array[], int size);
float variance(int array[], int size);
float standarddev(int array[], int size);
int sortarray (int array[], int maxsize, int size);

//command-line arguments
int main(int argc, char *argv[])
{
    cout << argv[0] << ":";
    for (int i=1; i<argc; i++){ //loop to read and output the text file
        cout << argv[i] << " ";
    }
    cout << endl;
//variable declarations
    int x=0;
    int maxsize=1000;
    char option;
    int size;
    int array[1000]; //setting array with its max elements
    //set size equal to the function that calculates the size of the sample
    size=size_of_sample();

    //opens and reads a given file
    ifstream infile;
    infile.open("Random_Input.txt");

    //if file fails to be read, output error message
    if (infile.fail()){
        cout << "File cannot be read\n";
        return 0;
    }
    //if file has elements greater than 1000, program will not run
    if(size > 1000){
        cout << "Program does not support this file";
        return 0;
    }

    //fills array with the elements from the text file
   	while((!infile.eof()) && (x < size)){
        int y;
        infile>>y;
        array[x]= y;
        x++;
    }
    for(int z=0; z<size; z++){
        cout << array[z]<<" ";
    }
    cout << endl << endl;

    //use do while loop to repeat the program instead of exiting after each input
    do {
        //user interactive menu
        cout << "\n\nWelcome, please select an option from the following menu:\n(Use letters a through h)\n\na. Count the total number of integers in the file \nb. Retrieve the Maximum and Minimum of integers present in the list \nc. Compute the total sum of the numbers \nd. Compute the mean \ne. Compute Variance \nf. Compute Standard Deviation \ng. Sort integers from largest to smallest \nh. Exit Program \n\n";
        cout << "Option: ";
        cin >> option;
        cout << "\n\n";

        //if user picks option a, runs and outputs the function that calculates total elements in the text file
        if ((option == 'a') || (option == 'A')){
            cout << "The total number of integers in this file is: " << size;
        }

        //if user picks option b, runs and outputs the function that calculates max and min of the sample
        else if ((option == 'b') || (option == 'B')){
            max_sample(array, size);
            min_sample(array, size);
        }

        //if user picks option c, runs and outputs the function that adds up the integers in the file
        else if ((option == 'c') || (option == 'C')){
            cout << "The sum of the integers is: " << sum_sample(array, size);
        }

        //if user picks option d, calculates the sum of the sample and divides it by the size of the sample to get the mean
        else if ((option == 'd') || (option == 'D')){
            float sum, sizesample;
            float mean;
            sum = sum_sample(array, size);
            sizesample = size_of_sample();
            mean = sum/sizesample;
            cout << "The mean of the integers is: " << mean;
        }

        //if user picks option e, runs and outputs the function that calculates the variance of the integers
        else if ((option == 'e') || (option == 'E')){
            cout << "The variance of the integers is: " << variance(array, size);
        }

        //if user picks option f, runs and outputs the standard deviation of the integers
        else if ((option == 'f') || (option == 'F')){
            cout << "The standard deviation is: " <<standarddev(array, size);
        }

        //if user picks option g, sorts the integers from largest to smallest and outputs the result onto a separate text file
        else if ((option == 'g') || (option == 'G')){
            sortarray(array, maxsize, size);
            cout << "Sorted values of integers printed to file called Sorted_output.txt" <<endl;
        }

        //if user picks option h, program will exit.
        else if ((option== 'h') || (option== 'H')){
            cout << "Program will now exit" << endl;
            return 0;
        }

        //if user picks anything else besides a through h, outputs an error message
        else {
            cout << "Invalid option!" <<endl;
        }
    //program will run as long as they don't press h
    }while ((option != 'h')||(option != 'H'));

return 0;
}

//function definitions

//function calculates size of the file
int size_of_sample(){
    int x=0;
    int size=0;
    ifstream infile;
    infile.open("Random_Input.txt");
        while (infile>>x){
            size++;
        }
    infile.close();
    return size;
}

//function calculates max of the array using loops
void max_sample(int array[], const int size){
    int maximum;
    maximum=array[0];
    for(int x=1; x<size; x++){
        if(array[x]>=maximum){    //if a number is larger than the first element in the array, it is set to be the maximum and repeats until it has went through the entire array
            maximum=array[x];
        }
    }
    cout<<"The maximum of the integers is: "<< maximum << endl;
}


//function calculates the min of the array using loops
void min_sample(int array[], int size){
    int minimum;
    minimum=array[0];
    for(int x=1; x<size; x++){
        if(array[x]<=minimum){ //if a number is smaller than the first element in the array, it is set to be the minimum and repeats until it has went through the entire array
            minimum=array[x];
        }
    }
     cout<<"The minimum of the integers: "<< minimum <<endl;
}


//function calculates the sum of all integers in the file
int sum_sample(int array[], int size){
    int sum=0;
    for (int x=0; x<size; x++){
        sum=sum+array[x];
    }

    return sum;
}

//function calculates the variance of the integers
float variance(int array[], int size){
    float sum, sizesample, variance, difference, mean;
    variance = 0;
    sum = sum_sample(array, size);
    sizesample = size_of_sample();    //first you find the mean
    mean = sum/sizesample;

    for(int x=0; x<size; x++){
        difference=0;
        difference=(array[x]-mean);         //subtract the mean for each number and square the result
        difference=(difference*difference);
        variance=(variance + difference);
    }

       sizesample=(size-1);
       variance=(variance/sizesample);      //average the squared differences
       return variance;
}


//function calculates the standard deviation of the integers
float standarddev(int array[], int size){
    float sum, sizesample, variance, difference, mean, standarddev;
    variance = 0;
    sum = sum_sample(array, size);
    sizesample = size_of_sample();
    mean = sum/sizesample;

    for(int x=0; x<size; x++){                   //computes variance
        difference=0;
        difference=(array[x]-mean);
        difference=(difference*difference);
        variance=(variance+difference);
    }

       sizesample=(size-1);
       variance=(variance/sizesample);      //square root of the variance
       standarddev=sqrt(variance);
       return standarddev;
}


//extra credit : sorts the array from largest to smallest and outputs onto a text file
int sortarray (int array[], int maxsize, int size){
    ofstream file;
    file.open("Sorted_output.txt");  //creates a text file for output
    int temp=0;
    for(int x=0; x<size; x++){
        for(int y=x; y<size; y++){
            if(array[x]<= array[y]){     //sorting the array from largest to smallest
                temp=array[x];
                array[x]=array[y];
                array[y]=temp;
            }

        }
            file<<array[x]<<endl;;  //outputs results onto a text file
     }
            file.close();
}
