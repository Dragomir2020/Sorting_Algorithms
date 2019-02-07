# Sorting_Algorithms
Sample c++ sorting algorithms implemented

**Discussion**

Homework #2: Data Structures and Algorithms

**InsertionSort vs. MergeSort and QuickSort t-values sampling results**

| **Size** | **3** | **4** | **5** | **10** | **11** |
| --- | --- | --- | --- | --- | --- |
| **InsertionSort** | 11 | 18 | 27 | 102 | 123 |
| **MergeSort** | 16 | 25 | 39 | 111 | 122 |
| **QuickSort** | 8 | 13 | 19 | 64 | 76 |

\*Note these values are 3 number averages, and results will vary from list to list of the same size.

After experimenting with the various lists using our program, we determined ideal threshold values for the use of Insertion sort vs. Merge sort and Quick sort. Ideal threshold values for Insertion sort vs. Merge sort hover around t=10 and t=11, while Quick sort almost always sorts faster that Insertion sort. Quick sort should be used over Merge sort and Insertion sort in this context.

**MergeSort vs. QuickSort t-values sampling results**

| **Size** | **30** | **35** | **40** | **100** | **20,000** |
| --- | --- | --- | --- | --- | --- |
| **MergeSort** | 462 | 570 | 653 | 2053 | 868,597 |
| **QuickSort** | 420 | 592 | 712 | 3584 | 3,026,445 |

\*Note these values are 3 number averages, and results will vary from list to list of the same size.

Based off of these results, using Quick sort rather than Merge sort for small lists is ideal. When list sizes reach values between 30 and 40, though, switching to Merge sort would yield the quickest sorting results. However, one must take into consideration whether storage is a limiting factor, since Merge sort is a storage-heavy method. While Merge sort uses fewer comparisons after reaching t-values of 30 or 40, the differences in comparison counts are small at first. Even when reaching t-values of 100, the number of comparisons are of the same magnitude and may not make a major difference in computing times. Only when reaching higher t-values such as 20,000 will a difference in computing times between the two methods become noticeable.

### Execution Greater Than Threshold
![Threshold Over](/SampleOutput1.JPG)

### Execution Less Than Threshold
![Threshold Under](/SampleOutput2.JPG)
