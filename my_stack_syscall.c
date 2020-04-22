#include<linx/syscalls.h>
#include<linux/kernel.h>
#include<linux/linkage.h>

#define MAXSIZE 500

int stack[MAXSIZE];
int top = -1;

int value_inside(int val, int arr[], int stack_top)
{
  int i;
  for(i=0; i < top; i++)
  {
    if(arr[i] == val)
      return 1;
  }
  return 0;
}


SYSCALL_DEFINE1(jamie_push,int,a){

int i;
printk(KERN_INFO "[System call] jamie_push(): ");
printk("Push %d", a);

overlap = value_inside(a, stack, top);

if(overlap)
  printk(KERN_ERR "overlap value");
else
{
  top++;
  stack[top] = a;

  printk("Stack Top-----------------\n");
  for(i=top; i >= 0; i--)
  {
    printk("%d",stack[i]);
  }
  printk("Stack Bottom--------------\n");
}

SYSCALL_DEFINE0(jamie_pop)
{
  int x = -1;
  if(top == -1)
    printk(KERN_ERR "stack underflow");
  else
  {
    x = stack[top--];
    printk(KERN_INFO "[System call] jamie_pop(): ");
    printk("Pop %d", x);
    printk("Stack Top-----------------\n");
    for(i=top; i >= 0; i--)
    {
      printk("%d",stack[i]);
    }
    printk("Stack Bottom--------------\n");
  }
  return x;
}
