/*
 * Question 2
 * By Zain Afzal 11/08/2018
 * cs2521 2018 semester 2
 * 
 * isPalindrome is a function that takes in a 
 * doubily linked list where each node stores a single 
 * character, i.e 
 *           
 *                 __head___[L]___tail__	
 *                /                     \
 *               v                       v
 *         X <- 'a' <-> 'b' <-> 'c' <-> 'd' -> X
 *
 * And returns true of the word formed by the characters 
 * is a palindrome and false otherwise. i. 
 * 
 * "aaa" -> TRUE   (aaa == aaa)
 * "aba" -> TRUE   (aba == aba)
 * "abb" -> FALSE  (abb != bba)
 * "a"   -> TRUE   (a == a)
 * ""    -> TRUE   ("" == "") (an empty string is said to be a palindrome)
 * 
 * you can assume each character is only a-z lower case.
 * 
 * The original linked list should _NOT_ be altered in any way. 
 */

#include "q2.h"

int isPalindrome(List l) {
    Link a = l->head;
    Link b = l->tail;
    if(a==NULL || b==NULL)return 1;
    while(a!=NULL){
    
        if (a->value != b->value) return FALSE;
        a = a -> next;
        b = b -> prev;
    }
    return TRUE;
    
}

