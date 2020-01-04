/********************************************************************************************************************
*  File: ListTest.c
*  Name: Andrew Craig
*  CruzID: acraig1
*  Assignment: pa4
*********************************************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include"List.h"

int main(int argc, char* argv[])
{
   List A = newList();
   List B = newList();
   long i;
  
   //Store 0 to 100 in A
   //Store -100 to 0 in B
   for(i = 0; i < 100; i++)
   {
      append(A, i);
      
   }

   for(i = -100; i < 0; i++)
   {
      prepend(B, i);
      
   }

   //Print the number of elements in A & B
   printf("List A has %d elements\n", length(A));
   printf("\n");
   printf("List B has %d elements\n", length(B));
   printf("\n");

   //Delete the front and back elements of A until only 10 elements remain
   moveFront(A);
   while(length(A) > 10)
   {
      deleteFront(A);
      if(length(A) != 0)
         deleteBack(A);
   }

   //Print the remaining contents of A
   printf("List A has %d elements\n", length(A));
   printf("\nA: ");
   printList(stdout, A);
   printf("\n");

   //Print the remaining contents of A in reverse
   moveBack(A);
   printf("\nA: ");
   while(index(A) != -1)
   {
      printf("%d ", get(A));
      movePrev(A);
   }
   printf("\n");

   //Move the cursor of A to the 8th element and then delete it
   moveFront(A);
   while(index(A) != 7)
   {
      moveNext(A);
   }
   delete(A);

   //Print the remaining contents of A
   printf("\nA: ");
   printList(stdout, A);
   printf("\n");

   //Insert 1 & 2 before and after the first element in A
   moveFront(A);
   insertBefore(A, 1);
   insertAfter(A, 2);

   //Insert 9 & 10 before and after the last element in A
   moveBack(A);
   insertBefore(A, 9);
   insertAfter(A, 10);

   //Print the new contents of A
   printf("\nA: ");
   printList(stdout, A);
   printf("\n\n\n");

   //Print the first element in A, delete the first element, and then print the new first element of A
   printf("Front(A): %d\n", front(A));
   deleteFront(A);
   printf("Front(A): %d\n", front(A));

   //Print the last element in A, delete the last element, and then print the new last element of A
   printf("Back(A): %d\n", back(A));
   deleteBack(A);
   printf("Back(A): %d\n", back(A));

   //Make a copy of A and see if the two lists are equal
   List C = copyList(A);
   printf("A equals C is %s\n", (equals(A, C)?"true":"false") );

   //Delete back element of C and check if still equal to A
   deleteBack(C);
   printf("A equals C is %s\n", (equals(A, C)?"true":"false") );

   //concat A and C then print the new list
   List D = concatList(A, C);
   printf("\nD: ");
   printList(stdout, D);
   printf("\n\n");

   //Clear B and then check to see if there are any remaining elements
   clear(B);
   if(length(B) != 0)
   {
      moveFront(B);
      printf("B: ");
      while(index(B) != -1)
      {
         printf("%d ", get(B));
         moveNext(B);
      }
      printf("\n");
   }
   else
   {
      printf("List is empty\n");
   }

   freeList(&A);
   freeList(&B);
   freeList(&C);
   freeList(&D);

   return(0);
}

