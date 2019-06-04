# COMP1521 17s2 Final Exam
# void colSum(m, N, a)

   .text
   .globl colSum

# params: m=$a0, N=$a1, a=$a2
colSum:
# prologue
   addi $sp, $sp, -4
   sw   $fp, ($sp)
   la   $fp, ($sp)
   addi $sp, $sp, -4
   sw   $ra, ($sp)
   addi $sp, $sp, -4
   sw   $s0, ($sp)
   addi $sp, $sp, -4
   sw   $s1, ($sp)
   addi $sp, $sp, -4
   sw   $s2, ($sp)
   addi $sp, $sp, -4
   sw   $s3, ($sp)
   addi $sp, $sp, -4
   sw   $s4, ($sp)
   addi $sp, $sp, -4
   sw   $s5, ($sp)
   # if you need to save more than six $s? registers
   # add extra code here to save them on the stack

# suggestion for local variables (based on C code):
# m=#s0, N=$s1, a=$s2, row=$s3, col=$s4, sum=$s5

   # add code for your colSum function here
   move  $s0, $a0
   move  $s1, $a1
   move  $s2, $a2
   
   # for (col = 0; col < N; col++) 
   li    $s4, 0
   for:
   bge   $s4, $s1, end_for1
   
   # sum = 0;
   li    $s5, 0
   
   # for (row = 0; row < N; row++)
   li    $s3, 0
   for2:
   bge   $s3, $s1, end_for2
   
   # m[row][col]
   move  $t0, $s3       # row
   mul   $t0, $t0, $s1  # row*N
   add   $t0, $t0, $s4  # row*N + col
   mul   $t0, $t0, 4    # (row*N+col)*4
   add   $t0, $t0, $s0  # (row*N+col)*4 + m
   lw    $t0, ($t0)     # m[][]
   
   # sum += m[row][col];
   add   $s5, $s5, $t0
   
   addi  $s3, $s3, 1
   j   for2
   end_for2:
   
   # a[col] = sum
   move  $t1, $s4       # col
   mul   $t1, $t1, 4         # col*4
   add   $t1, $t1, $s2  # col*4 + a
   sw    $s5, ($t1)
   
   addi  $s4, $s4, 1
   j  for
   end_for1:
   

# epilogue
   # if you saved more than six $s? registers
   # add extra code here to restore them
   lw   $s5, ($sp)
   addi $sp, $sp, 4
   lw   $s4, ($sp)
   addi $sp, $sp, 4
   lw   $s3, ($sp)
   addi $sp, $sp, 4
   lw   $s2, ($sp)
   addi $sp, $sp, 4
   lw   $s1, ($sp)
   addi $sp, $sp, 4
   lw   $s0, ($sp)
   addi $sp, $sp, 4
   lw   $ra, ($sp)
   addi $sp, $sp, 4
   lw   $fp, ($sp)
   addi $sp, $sp, 4
   j    $ra

