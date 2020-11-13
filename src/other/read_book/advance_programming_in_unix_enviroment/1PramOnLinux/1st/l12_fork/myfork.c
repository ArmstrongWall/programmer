/*#include <unistd.h>
void main()
{
  pid_t pid;
  int count =0;
   
  //pid=fork();
  pid = vfork();
  count+=1;

  printf("count is %d \r\n",count);

  exit(0);
}
*/
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void main()
{
  pid_t pid;
  
  pid=fork();//vfork
  if ( pid > 0 )
  {
      wait(NULL);//prame can be NULL
      printf("this is father progress\r\n");
      exit(0);
  }
  else
  {
      printf("this id child 1 progress\r\n");
      execl("/bin/ls","ls","/home",NULL);
      printf("this id child 2 progress\r\n");
      exit(0);
  }
}
