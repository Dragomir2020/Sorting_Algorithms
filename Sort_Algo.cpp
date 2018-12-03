
//Libraries
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
//#include "Sort.h"


// Sorting classes that allow for insertion, quick and merge sort
namespace DataStructures{
    
    namespace Sort{
        
        // Base interface
        //template <typename T>
        class SortInterface{
        public:
            // Would love to do this but cant have templated pure virtual functions
            //virtual void Sort(std::vector<T> * x) = 0;
            virtual int getComparisonCount() = 0;
        };
        
        // Used to hold all meta data to return to user
        struct MetaData{
            int MegerSortComparisions;
            int InsertionSortComparisions;
            int QuickSortComparisions;
            int Threshold;
            
        };
        
        // Implementation of the Insertion Sort Algorithm
        class InsertionSort : public SortInterface{
        public:
            InsertionSort(){
                compCount = 0;
            }
            
            template <typename T>
            void Sort(std::vector<T> * x){
                return RecursiveSort(0,0,x);
            }
            
            int getComparisonCount(){
                return compCount;
            }
            
        private:
            int compCount;
            
            template <typename T>
            void RecursiveSort(int currentIndex, int swapIndex, std::vector<T> * x){
                compCount += 1;
                if(x->at(currentIndex + 1) < x->at(currentIndex)){
                    std::swap(x->at(currentIndex + 1),x->at(currentIndex));
                }
                compCount += 1;
                if(currentIndex == 0){
                    compCount += 1;
                    if((swapIndex+1) != x->size()){
                        return RecursiveSort(swapIndex, swapIndex + 1, x);
                    } else {
                        return;
                    }
                } else {
                    return RecursiveSort(currentIndex - 1, swapIndex, x);
                }
            }
        };
        
        //Implementation of the Merge Sort Algorithm
        class MergeSort : public SortInterface{
        public:
            MergeSort(){
            }
        
            template <typename T>
            void Sort(std::vector<T> * A){
                compCount = 0;
                std::vector<T> B(*A);
                Split(A,&B,0,A->size());
                B.clear();
            }
            
            int getComparisonCount(){
                return compCount;
            }
            
        private:
            int compCount;
            
            template <typename T>
            void Split(std::vector<T> * A, std::vector<T> * B, int beg, int end){
                compCount += 1;
                if((end - beg) < 2){
                    return;
                }
                int mid = (end + beg) / 2; // Rounds down because of int datatype
                Split(B,A, beg, mid);
                Split(B,A, mid, end);
                Merge(B,A, beg, mid, end);
            }
            
            template <typename T>
            void Merge(std::vector<T> * A, std::vector<T> * B, int beg, int mid, int end){
                int i = beg;
                int j = mid;
                for(int k = beg; k < end; k++){
                    compCount += 1;
                    if(i < mid){
                        compCount += 2;
                        if((j >= end || A->at(i) <= A->at(j))){
                            B->at(k) = A->at(i);
                            i += 1;
                        } else {
                            B->at(k) = A->at(j);
                            j += 1;
                        }
                    } else {
                        B->at(k) = A->at(j);
                        j += 1;
                    }
                }
            }
        };
        
        // Implementation of the Quick Sort Algorithm
        class QuickSort : public SortInterface{
        public:
            
            QuickSort(){
            }
            
            template <typename T>
            void Sort(std::vector<T> * x){
                RecursiveSort(x, 0, x->size()-1);
            }
            
            int getComparisonCount(){
                return compCount;
            }
            
        private:
            int compCount;
            
            template <typename T>
            void RecursiveSort(std::vector<T> * x, int low, int high){
                compCount += 1;
                if(low < high){
                    int p = Partition(x, low, high);
                    RecursiveSort(x, low, p - 1);
                    RecursiveSort(x, p + 1, high);
                }
            }
            
            template <typename T>
            int Partition(std::vector<T> * x, int low, int high){
                int i = low;
                for(int j = low; j < high; j++){
                    compCount += 1;
                    if(x->at(j) < x->at(high)){
                       std::swap(x->at(i),x->at(j));
                        i += 1;
                    }
                }
                std::swap(x->at(i),x->at(high));
                return i;
            }
            
        };
        
        // This class uses the other sorting algorithms based on the threshold
        class DynamicSort{
        public:
            // Takes threshold to decide what algorithm to use
            DynamicSort(int threshold){
                data.Threshold = threshold;
                data.MegerSortComparisions = 0;
                data.InsertionSortComparisions = 0;
                data.QuickSortComparisions = 0;
            }
            
            template <typename T>
            void Sort(std::vector<T> * x){
                if(x->size() > data.Threshold){
                    // Perform quick and merge sort
                    std::vector<T> y(*x);
                    MergeSort * merge = new MergeSort();
                    merge->Sort(x);
                    data.MegerSortComparisions = merge->getComparisonCount();
                    QuickSort * quick = new QuickSort();
                    quick->Sort(x);
                    data.QuickSortComparisions = quick->getComparisonCount();
                } else {
                    InsertionSort * insertion = new InsertionSort();
                    insertion->Sort(x);
                    data.InsertionSortComparisions = insertion->getComparisonCount();
                }
            }
            
            int getMergeCompCount(){
                return data.MegerSortComparisions;
            }
            
            int getInsertionCompCount(){
                return data.InsertionSortComparisions;
            }
            
            int getQuickCompCount(){
                return data.QuickSortComparisions;
            }

        private:
            MetaData data;
            
        };
    
    }
}

// Main program used to update the user can get the direct the control flow
int main(int argc, char* argv[]){
    
    bool cont = 1;
    while(cont){
        
        std::cout << "\nThis is a dynamic sorting program.\n" << std::endl;
        
        std::cout << "Set a threshold. This will be used to choose either insertion sort or merge/quick sort." << std::endl;
        int threshold = 10;
        std::cin >> threshold;
        std::cout << "\n";
        
        std::cout << "What is the size of your list?" << std::endl;
        int iterations = 15; // Number of random values to sort
        std::cin >> iterations;
        std::cout << "\n";
        
        std::vector<int> v;
        bool gen = 0;
        if(iterations <= 15){
            std::cout << "Should the list be random or generated? Choose 0 for random and 1 for inputed." << std::endl;
            std::cin >> gen;
            std::cout << "\n";
        }
        if(gen){
            int val;
            for(int i = 0; i < iterations; i++){
                std::cout << "Input Element " << std::to_string(i+1) << ": " << std::endl;
                std::cin >> val;
                v.push_back(val);
            }
            std::cout << "\n";
        } else {
            // MAYBE CHANGE THESE RANGES
            int min = 1;
            int max = 100;
            srand(time(0));
            for(int i = 0; i < iterations; i++){
                int randVal = rand() % max + min;
                v.push_back(randVal);
            }
        }
        bool disp = 0;
        if(iterations <= 15){
            std::cout << "Should the list be displayed? 0 for no 1 for yes" << std::endl;
            std::cin >> disp;
            std::cout << "\n";
        }
        
        if(disp){
            for(int i = 0; i < v.size(); i++){
                std::cout << "Input(" << std::to_string(i) << "): " << std::to_string(v.at(i)) << std::endl;
            }
            std::cout << "\n";
        }
        
        // Sort lists with given parameters
        DataStructures::Sort::DynamicSort * dynamicSort = new DataStructures::Sort::DynamicSort(threshold);
        dynamicSort->Sort(&v);
        
        if(disp){
            for(int i = 0; i < v.size(); i++){
                std::cout << "Output(" << std::to_string(i) << "): " << std::to_string(v.at(i)) << std::endl;
            }
            std::cout << "\n";
        }
        
        bool showComp = 1;
        std::cout << "Should the comparison count be shown? 0 for no 1 for yes" << std::endl;
        std::cin >> showComp;
        std::cout << "\n";
        
        // If used defined show number of comparisions
        if(showComp){
            std::cout << "Merge Sort Comparison Count: " << std::to_string(dynamicSort->getMergeCompCount()) << std::endl;
            std::cout << "Insertion Sort Comparison Count: " << std::to_string(dynamicSort->getInsertionCompCount()) << std::endl;
            std::cout << "Quick Sort Comparison Count: " << std::to_string(dynamicSort->getQuickCompCount()) << std::endl;
            std::cout << "\n";
        }
 
        // Ask user to continue
        std::cout << "Would you like to sort another list? Enter 1 for yes and 0 for no." << std:: endl;
        std::cin >> cont;
    
    }
    
	
}


